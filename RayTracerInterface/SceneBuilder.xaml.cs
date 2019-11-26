using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Xml;
using System.Xml.Serialization;

namespace RayTracerInterface {
	public class Constants {
		public static string MyString;
	}
	public class ShapeTemplateSelctor : DataTemplateSelector {
		public DataTemplate GroupTemplate { get; set; }

		public ShapeTemplateSelctor(DataTemplate defaul, DataTemplate GroupTemplate) {
			this.GroupTemplate = GroupTemplate;
			DefaultTemplate = defaul;

		}

		public DataTemplate DefaultTemplate { get; set; }

		public override DataTemplate SelectTemplate(object item, DependencyObject container) => item is Group ? GroupTemplate : DefaultTemplate;
	}
	/// <summary>
	/// Interaktionslogik für SceneBuilder.xaml
	/// </summary>
	public partial class SceneBuilder : Page, IRenderPage {
		public class SaveContainer {
			[XmlArray("shapes")]
			[XmlArrayItem("Sphere", typeof(Sphere))]
			[XmlArrayItem("Plain", typeof(Plane))]
			[XmlArrayItem("Group", typeof(Group))]
			public Renderable[] shapes;
			public Camera camera;

		}
		public Action OnBack { get; set; }
		/// <summary>
		/// Aspect ratio to keep while the box is checked
		/// </summary>
		double ratio = 16.0 / 9.0;
		Action<IRenderPage> RenderAction;
		LibraryHandler.SceneBasedRenderer sbr;
		Camera cam;
		static readonly SolidColorBrush white = new SolidColorBrush(Colors.White);
		ObservableCollection<Renderable> Shapes;
		//Label lbshapesContainer => lbshapesContainerContainer.Content as Label;
		//ListBox Lbshapes => lbshapesContainer.Content as ListBox;
		//List<Renderable> RenderObjects=new List<Renderable>();		
		public void Save(string filename) {
			//try {
			using (var fs = new FileStream(filename, FileMode.Create))
				Save(fs);
			//}
			//catch (Exception ex) {
			//	MessageBox.Show($"ERROR WRITING CONFIG FILE: {ex.ToString()}", ex.GetType().Name);
			//}
		}
		public void Save(Stream target) {
			using (var writer = new StreamWriter(target, new UTF8Encoding())) {
				var tmp = new Renderable[Shapes.Count];
				Shapes.CopyTo(tmp, 0);
				new XmlSerializer(typeof(SaveContainer)).Serialize(writer, new SaveContainer() { camera = cam, shapes = tmp });
				writer.Close();
			}
		}
		public void Load(string path) {
			using (var fs = new FileStream(path, FileMode.Open))
				Load(fs);
		}
		public void Load(Stream from) {
			using (var reader = XmlReader.Create(from))
				Load(reader);
		}
		public void Load(XmlReader reader) {
			var dat = new XmlSerializer(typeof(SaveContainer)).Deserialize(reader) as SaveContainer;
			this.cam = dat.camera;
			VisualizeCamera();
			Shapes.Clear();
			foreach (var e in dat.shapes) 
				Shapes.Add(e);
			Lbshapes.SelectedIndex = 0;
			alertChanges();
		}
		public static DataTrigger genDT(string forWhat) => new DataTrigger() {
			Binding = new Binding() {
				RelativeSource = new RelativeSource() {
					Mode = RelativeSourceMode.FindAncestor,
					AncestorType = typeof(ListBoxItem)
				},
				Path = new PropertyPath(forWhat)
			},
			Value = true
		};
		public static DataTrigger addSetters(DataTrigger dt, Setter[] arr) {
			foreach (var s in arr) dt.Setters.Add(s);
			return dt;
		}
		public static Style addSetters(Style s, Setter[] arr) {
			foreach (var se in arr) s.Setters.Add(se);
			return s;
		}
		public SceneBuilder(LibraryHandler.SceneBasedRenderer renderer, Action<IRenderPage> moveToRenderer) {
			InitializeComponent();
			Shapes = new ObservableCollection<Renderable>();
			this.sbr = renderer;
			RenderAction = moveToRenderer;
			Lbshapes.SelectionChanged += Lbshapes_SelectionChanged;
			Lbshapes.ItemsSource = Shapes;
			Lbshapes.ItemTemplateSelector = new ShapeTemplateSelctor(FindResource("ShapeTemplateDefault") as DataTemplate, FindResource("ShapeTemplateGroup") as DataTemplate);
			RenderLoop();
		}
		DateTime lastChange = DateTime.Now;
		string GetSceneString() {
			var scene = new Scene();
			foreach (var elem in Shapes)
				scene.objects.Add(elem as Renderable);
			return scene.Serialize();
		}
		async Task DoRender(double scale) {
			if (!int.TryParse(tbW.Text, out int i_w) || !int.TryParse(tbH.Text, out int i_h)) return;
			lbScale.Content = $"{scale}x";
			int w = (int)(i_w * scale);
			int h = (int)(i_h * scale);
			pbrendering.Maximum = w;
			pbrendering.Value = 0;
			sbr.SetScene(GetSceneString());
			sbr.SetCamera(Camera.SerializeThis(cam));
			//return;
			sbr.StartPreviewRender(w, h);
			while (pbrendering.Value != w) {
				pbrendering.Value = sbr.Status;
				await Task.Delay(1000 / 60);
			}
			while (sbr.ReturnCode == -1) await Task.Delay(1000 / 60);
			string file = System.IO.Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location) + "\\" + sbr.SceneFile;
			while (!File.Exists(file)) await (Task.Delay(10));
			iResults.Source = (BitmapSource)new ImageSourceConverter().ConvertFrom(File.ReadAllBytes(file));
		}
		static readonly double[] scales = { 0.01, 0.02, 0.04, 0.08, 0.25, 0.40, 0.5, 1 };
		//static readonly int[] WaitTime = {   100,  100,  200,  500, 1000, 3000, 20000, 0 };
		async Task<DateTime> RenderRepeater() {
			var start = lastChange;
			if (Shapes.Count == 0) return start;
			for (int n = 0; n < scales.Length && lastChange == start; n++) {
				//var s = System.Diagnostics.Stopwatch.StartNew();
				await DoRender(scales[n]);
				//s.Stop();
				//var t = DateTime.Now + s.Elapsed;
				//while (t > DateTime.Now && lastChange == start) await Task.Delay(100);
			}
			return start;
		}
		async void RenderLoop() {
			while (this.Visibility != Visibility.Visible) await Task.Delay(500);
			sbr.Initialize3d();
			DateTime last = DateTime.MinValue;
			while (this.Visibility == Visibility.Visible) {
				if (cam == null) {
					await Task.Delay(1000);
					continue;
				}
				if (lastChange > last)
					last = await RenderRepeater();
				await Task.Delay(100);
			}
		}
		/// <summary>
		/// Informs the window that properties of shapes have been modified
		/// <para>
		///		Should trigger a re-render
		/// </para>
		/// </summary>
		void alertChanges() {
			lastChange = DateTime.Now;

		}

		private void Lbshapes_SelectionChanged(object __, SelectionChangedEventArgs scea) {
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
					ratio = double.Parse(tbW.Text) / double.Parse(tbH.Text);
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
		T FindParentT<T>(FrameworkElement o) where T : FrameworkElement => o == null ? null : (o is T t ? t : FindParentT<T>((o.Parent == null ? VisualTreeHelper.GetParent(o) : o.Parent) as FrameworkElement));
		ListBox FindParentListBox(FrameworkElement source) =>
			source == null ?
				null :
				source.GetType() == typeof(ListBox) ?
				source as ListBox :
					FindParentListBox(
						source.Parent == null ?
							VisualTreeHelper.GetParent(source) as FrameworkElement :
							source.Parent as FrameworkElement
					);
		private void Button_Click(object source, RoutedEventArgs _) {
			var Selector = new ShapeSelector(sbr);
			Selector.Init();
			if (Selector.ShowDialog() == true) {
				//(FindParentListBox(source as FrameworkElement).ItemsSource as ObservableCollection<Renderable>).Add(Selector.result);
				Shapes.Add(Selector.result);
				alertChanges();
			}
		}
		private void DeleteShape(object sender, RoutedEventArgs _) {
			var snd = sender as Button;
			(FindParentListBox(snd).ItemsSource as ObservableCollection<Renderable>).Remove(((snd.Parent as Grid).Children[0] as VisualStorage).Storage as Renderable);
			alertChanges();
		}
		void VisualizeCamera() {
			spCam.Children.Clear();
			spCam.Children.Add(new Label() {
				Content = cam.GetType().Name,
				HorizontalAlignment = HorizontalAlignment.Center,
				Foreground = white
			});
			foreach (var e in VisualizeObject(cam)) {
				spCam.Children.Add(e);
				spCam.Children.Add(new Separator() { Height = 1.5, Background = new SolidColorBrush(Colors.Black), Margin = new Thickness(0, 5, 0, 5) });
			}
			var bt = new Button() {
				Content = "Ändern",
				Style = FindResource("BTStyle") as Style
			};
			bt.Click += SelectCameraClick;
			spCam.Children.Add(bt);
		}
		private void SelectCameraClick(object _, RoutedEventArgs __) {
			var Selector = new CameraSelector(sbr);
			Selector.Init();
			if (Selector.ShowDialog() == true) {
				cam = Selector.result;
				VisualizeCamera();
				alertChanges();
			}
		}

		private void btExport_Click(object _, RoutedEventArgs __) {
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

		private void btImport_Click(object _, RoutedEventArgs __) {
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

		private void btFullRender_Click(object _, RoutedEventArgs __) {
			if (int.TryParse(tbH.Text, out int h) && int.TryParse(tbW.Text, out int w) && int.TryParse(tbSX.Text, out int FSAA)) {
				var dlg = new Microsoft.Win32.SaveFileDialog {
					DefaultExt = "*.png;",
					CheckPathExists = true,
					RestoreDirectory = true,
					DereferenceLinks = true,
					Title = "Please choose a output filename",
					Filter = "HQ Rendered Image *.png|*.png"
				};
				if (dlg.ShowDialog() == true) {
					sbr.StartSuperRender(w, h, FSAA, dlg.FileName);
					RenderAction(new RenderPage(sbr, -1, w) { ofile = dlg.FileName });
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
