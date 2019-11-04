using System;
using System.Collections.Generic;
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
		Action<IRenderPage> RenderAction;
		LibraryHandler.SceneBasedRenderer sbr;
		Camera cam;
		static readonly SolidColorBrush white = new SolidColorBrush(Colors.White);
		//List<Renderable> RenderObjects=new List<Renderable>();
		public SceneBuilder(LibraryHandler.SceneBasedRenderer renderer, Action<IRenderPage> moveToRenderer) {
			this.sbr = renderer;
			RenderAction = moveToRenderer;
			InitializeComponent();
			lbshapes.SelectionChanged += Lbshapes_SelectionChanged;
			//lbshapes.ItemsSource = RenderObjects;
			RenderLoop();
		}
		DateTime lastChange = DateTime.Now;
		async Task DoRender(double scale) {
			if (!int.TryParse(tbW.Text, out int i_w) || !int.TryParse(tbH.Text, out int i_h)) return;
			lbScale.Content = $"{scale}x";
			int w = (int)(i_w * scale);
			int h = (int)(i_h * scale);
			pbrendering.Maximum = w;
			pbrendering.Value = 0;
			var scene = new Scene();
			foreach (var elem in lbshapes.Items)
				scene.objects.Add(elem as Renderable);
			sbr.SetScene(scene.Serialize());
			sbr.SetCamera(Camera.SerializeThis(cam));
			sbr.StartPreviewRender(w, h);
			while (pbrendering.Value != w) {
				pbrendering.Value = sbr.Status;
				await Task.Delay(100);
			}
			while (sbr.ReturnCode == -1) await Task.Delay(100);
			iResults.Source = (BitmapSource)new ImageSourceConverter().ConvertFrom(File.ReadAllBytes(System.IO.Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location) + "\\" + sbr.SceneFile));

		}
		static readonly double[] scales = { 0.01, 0.02, 0.04, 0.08, 0.25, 0.40, 0.5, 1 };
		//static readonly int[] WaitTime = {   100,  100,  200,  500, 1000, 3000, 20000, 0 };
		async Task<DateTime> RenderRepeater() {
			var start = lastChange;
			if (lbshapes.Items.Count == 0) return start;
			for (int n = 0; n < scales.Length && lastChange == start; n++) {
				var s = System.Diagnostics.Stopwatch.StartNew();
				await DoRender(scales[n]);
				s.Stop();
				var t = DateTime.Now+s.Elapsed;
				while (t > DateTime.Now && lastChange == start) await Task.Delay(100);
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
			foreach (var e in VisualizeObject(scea.AddedItems[0])) {
				spProperties.Children.Add(e);
				spProperties.Children.Add(new Separator() { Height = 1.5, Background = new SolidColorBrush(Colors.Black), Margin = new Thickness(0, 5, 0, 5) });
			}
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
		private void Button_Click(object _, RoutedEventArgs __) {
			var Selector = new ShapeSelector(this.sbr);
			Selector.Init();
			if (Selector.ShowDialog() == true) {
				lbshapes.Items.Add(Selector.result);
				alertChanges();
			}
		}
		private void DeleteShape(object sender, RoutedEventArgs _) {
			lbshapes.Items.Remove((((sender as Button).Parent as Grid).Children[0] as Label).Content);
			alertChanges();
		}
		private void SelectCameraClick(object _, RoutedEventArgs __) {
			var Selector = new CameraSelector(sbr);
			Selector.Init();
			if (Selector.ShowDialog() == true) {
				spCam.Children.Clear();
				spCam.Children.Add(new Label() {
					Content = Selector.result.GetType().Name,
					HorizontalAlignment = HorizontalAlignment.Center,
					Foreground = white
				});
				foreach (var e in VisualizeObject(cam = Selector.result)) {
					spCam.Children.Add(e);
					spCam.Children.Add(new Separator() { Height = 1.5, Background = new SolidColorBrush(Colors.Black), Margin = new Thickness(0, 5, 0, 5) });
				}
				var bt = new Button() {
					Content = "Ändern",
					Style = FindResource("BTStyle") as Style
				};
				bt.Click += SelectCameraClick;
				spCam.Children.Add(bt);
				alertChanges();
			}
		}
	}
}
