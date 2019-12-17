using System;
using System.Collections.ObjectModel;
using System.Globalization;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
namespace RayTracerInterface {
	/// <summary>
	/// Interaktionslogik für SceneBuilder.xaml
	/// </summary>
	public partial class SceneBuilder : Page, IRenderPage {
		public Action OnBack { get; set; }
		/// <summary>
		/// Aspect ratio to keep while the box is checked
		/// </summary>
		double ratio = 16.0 / 9.0;
		readonly Action<IRenderPage> RenderAction;
		readonly LibraryHandler.SceneBasedRenderer sbr;
		Camera cam;
		static readonly SolidColorBrush white = new SolidColorBrush(Colors.White);
		readonly ObservableCollection<Renderable> Shapes;
		//Label lbshapesContainer => lbshapesContainerContainer.Content as Label;
		//ListBox Lbshapes => lbshapesContainer.Content as ListBox;
		//List<Renderable> RenderObjects=new List<Renderable>();		
		
		public SceneBuilder(LibraryHandler.SceneBasedRenderer renderer, Action<IRenderPage> moveToRenderer) {
			InitializeComponent();
			Shapes = new ObservableCollection<Renderable>();
			sbr = renderer;
			RenderAction = moveToRenderer;
			Lbshapes.SelectionChanged += Lbshapes_SelectionChanged;
			Lbshapes.ItemsSource = Shapes;
			Lbshapes.ItemTemplateSelector = new ShapeTemplateSelector(FindResource("ShapeTemplateDefault") as DataTemplate, FindResource("ShapeTemplateGroup") as DataTemplate);
			RenderLoop();
		}
		private void Lbshapes_SelectionChanged(object _, SelectionChangedEventArgs scea) {
			spProperties.Children.Clear();
			if (scea.AddedItems.Count == 0) {
				spProperties.Children.Add(new TextBlock() {
					Foreground = white,
					TextWrapping = TextWrapping.Wrap,
					Text = "Kein Element ausgewählt"
				});
				return;
			}
			AddToSP(spProperties, VisualizeObject(scea.AddedItems[0]));
		}
		/// <summary>
		/// Stores aspect ratio or unchecks itself if one of the given values is invalid
		/// </summary>
		private void CheckBox_Click(object sender, RoutedEventArgs _) {
			if (sender is CheckBox cb && cb.IsChecked == true) {
				try {
					ratio = double.Parse(tbW.Text,CultureInfo.InvariantCulture) / double.Parse(tbH.Text, CultureInfo.InvariantCulture);
				}
				catch {
					cb.IsChecked = false;
				}
			}
		}
		/// <summary>
		/// Handler for applying the set aspect ratio while entering numbers
		/// </summary>
		private void TbW_KeyUp(object _, KeyEventArgs __) {
			if (cbLink.IsChecked == true && int.TryParse(tbW.Text, out var i))
				tbH.Text = ((int)(1 / ratio * i)).ToString();
		}
		/// <summary>
		/// Handler for applying the set aspect ratio while entering numbers
		/// </summary>
		private void TbH_KeyUp(object _, KeyEventArgs __) {
			if (cbLink.IsChecked == true && int.TryParse(tbH.Text, out var i))
				tbW.Text = ((int)(ratio * i)).ToString();
		}
		static T FindParentT<T>(FrameworkElement o) where T : FrameworkElement => o == null ? null : (o is T t ? t : FindParentT<T>((o.Parent ?? VisualTreeHelper.GetParent(o)) as FrameworkElement));
		ListBox FindParentListBox(FrameworkElement source) =>
			source == null ?
				null :
				source.GetType() == typeof(ListBox) ?
				source as ListBox :
					FindParentListBox((source.Parent ?? VisualTreeHelper.GetParent(source)) as FrameworkElement
					);
		private void Button_Click(object source, RoutedEventArgs _) {
			var Selector = new ShapeSelector(sbr);
			Selector.Init();
			if (Selector.ShowDialog() == true) {
				//(FindParentListBox(source as FrameworkElement).ItemsSource as ObservableCollection<Renderable>).Add(Selector.result);
				Shapes.Add(Selector.result);
				AlertChanges();
			}
		}
		private void DeleteShape(object sender, RoutedEventArgs _) {
			var snd = sender as Button;
			(FindParentListBox(snd).ItemsSource as ObservableCollection<Renderable>).Remove(((snd.Parent as Grid).Children[0] as VisualStorage).Storage as Renderable);
			AlertChanges();
		}
		
		private void SelectCameraClick(object _, RoutedEventArgs __) {
			var Selector = new CameraSelector(sbr);
			Selector.Init();
			if (Selector.ShowDialog() == true) {
				cam = Selector.result;
				VisualizeCamera();
				AlertChanges();
			}
		}
		private void BtExport_Click(object _, RoutedEventArgs __) {
			var dlg = new Microsoft.Win32.SaveFileDialog {
				DefaultExt = "*.xml;",
				CheckPathExists = true,
				RestoreDirectory = true,
				DereferenceLinks = true,
				Title = "Please select the Scene file",
				Filter = "Scene XML *.xml|*.xml"
			};
			if (dlg.ShowDialog() == true)
				Save(dlg.FileName);
		}
		private void BtImport_Click(object _, RoutedEventArgs __) {
			var dlg = new Microsoft.Win32.OpenFileDialog {
				DefaultExt = "*.xml;",
				CheckFileExists = true,
				CheckPathExists = true,
				Multiselect = false,
				RestoreDirectory = true,
				DereferenceLinks = true,
				Title = "Please select the Scene file",
				Filter = "Scene XML *.xml|*.xml"
			};
			if (dlg.ShowDialog() == true)
				Load(dlg.FileName);
		}
		private void BtFullRender_Click(object _, RoutedEventArgs __) {
			if (int.TryParse(tbH.Text, out var h) && int.TryParse(tbW.Text, out var w) && int.TryParse(tbSX.Text, out int FSAA)) {
				var dlg = new Microsoft.Win32.SaveFileDialog {
					DefaultExt = "*.png;",
					CheckPathExists = true,
					RestoreDirectory = true,
					DereferenceLinks = true,
					Title = "Please choose a output filename",
					Filter = "HQ Rendered Image *.png|*.png"
				};
				if (dlg.ShowDialog() == true) {
					if (rendering) {
						if (sbr is LibraryHandler.MaterialRenderer mathand && mathand.CanAbort) {
							mathand.AbortRender();
							aborted = true;
						}
						else
							while (rendering) Task.Delay(100).Wait();
					}
					sbr.StartSuperRender(w, h, FSAA, dlg.FileName);
					RenderAction(new RenderPage(sbr, -1, w) { Ofile = dlg.FileName });
				}
			}
			else {
				MessageBox.Show("A image dimension field is invalid!", "Invalid Field", MessageBoxButton.OK, MessageBoxImage.Error);
			}
		}
		private void CS_Click(object _, RoutedEventArgs __) => Clipboard.SetText(GetSceneString().Replace(',', '.'));
		private void CC_Click(object _, RoutedEventArgs __) => Clipboard.SetText(Camera.SerializeThis(cam).Replace(',', '.'));
	}
}
