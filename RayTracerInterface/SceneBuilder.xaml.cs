using System;
using System.Collections.Generic;
using System.Linq;
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
		/// <summary>
		/// Aspect ratio to keep while the box is checked
		/// </summary>
		double ratio = 16.0 / 9.0;
		LibraryHandler.SceneBasedRenderer renderer;
		Action<IRenderPage> RenderAction;
		//List<Renderable> RenderObjects=new List<Renderable>();
		public SceneBuilder(LibraryHandler.SceneBasedRenderer renderer, Action<IRenderPage> moveToRenderer) {
			this.renderer = renderer;
			RenderAction = moveToRenderer;
			InitializeComponent();
			lbshapes.SelectionChanged += Lbshapes_SelectionChanged;
			//lbshapes.ItemsSource = RenderObjects;
		}
		/// <summary>
		/// Informs the window that properties of shapes have been modified
		/// <para>
		///		Should trigger a re-render
		/// </para>
		/// </summary>
		void alertChanges() {

		}
		static TextBlock MakeDefaultTextBlock(string name) =>
			SetCP(0, new TextBlock() {
				Text = name,
				TextWrapping = TextWrapping.NoWrap,
				Foreground = white
			});

		static Grid MakeDefaultGrid() {
			var g = new Grid();
			g.ColumnDefinitions.Add(new ColumnDefinition());
			g.ColumnDefinitions.Add(new ColumnDefinition());
			return g;
		}
		static T SetCP<T>(int CP, T e) where T : UIElement {
			e.SetValue(Grid.ColumnProperty, CP);
			return e;
		}
		byte scale(double d) => (byte)(d * 255);
		System.Windows.Media.Color ConvertColorM(Color c) => System.Windows.Media.Color.FromRgb(scale(c.r), scale(c.g), scale(c.b));
		System.Drawing.Color ConvertColor(Color c) => System.Drawing.Color.FromArgb(255, scale(c.r), scale(c.g), scale(c.b));
		Color ConvertColor(System.Drawing.Color c) => new Color(c.R, c.G, c.B);
		UIElement MakeColorElement(string name, Color value) {
			var g = MakeDefaultGrid();
			g.Children.Add(MakeDefaultTextBlock(name));
			var g2 = SetCP(1, MakeDefaultGrid());
			var box = SetCP(0, new Grid() { Background = new SolidColorBrush(ConvertColorM(value)) });
			var bt = SetCP(1, new Button() {
				Style = FindResource("BTStyle") as Style,
				Content = "Cange",
				HorizontalAlignment = HorizontalAlignment.Center
			});
			bt.Click += (_, __) => {
				var diag = new System.Windows.Forms.ColorDialog() {
					AnyColor = true,
					AllowFullOpen = true,
					SolidColorOnly = true,
					Color = System.Drawing.Color.FromArgb(0, scale(value.r), scale(value.g), scale(value.b))
				};
				if (diag.ShowDialog() == System.Windows.Forms.DialogResult.OK) {
					value = ConvertColor(diag.Color);
					box.Background = new SolidColorBrush(ConvertColorM(value));
					updateCurrentObject(name, value);
					alertChanges();
				}
			};
			g2.Children.Add(box);
			g2.Children.Add(bt);
			g.Children.Add(g2);
			return g;
		}

		static readonly SolidColorBrush white = new SolidColorBrush(Colors.White);
		UIElement MakeVectorElement(string name, Vec value) {
			var g = MakeDefaultGrid();
			var sp = SetCP(1, new WrapPanel() { Orientation = Orientation.Horizontal });
			g.Children.Add(sp);
			//Murdering Code Duplication since 2019
			void mktb(string text, double v, Action<double> apply) {
				var gr = new StackPanel() { Orientation = Orientation.Horizontal };
				var block = new TextBlock() {
					Text = text,
					Foreground = white,
					Margin = new Thickness(3, 2, 3, 2)
				};
				gr.Children.Add(block);
				var box = new TextBox() {
					Text = v.ToString(),
					Style = FindResource("TBStyle") as Style
				};
				box.TextChanged += (obj, _) => {
					var tb = obj as TextBox;
					if (double.TryParse(tb.Text, out var res)) {
						apply(res);
						updateCurrentObject(name, value);
						alertChanges();
					}
					else if (tb.Text.Trim().Length == 0) {
						if (tb.Text.Length != 0)
							tb.Text = "";
					}
					else
						tb.Text = "0";
				};
				gr.Children.Add(box);
				sp.Children.Add(gr);
			}
			g.Children.Add(MakeDefaultTextBlock(name));
			mktb("X", value.x, (res) => value.x = res);
			mktb("Y", value.y, (res) => value.y = res);
			mktb("Z", value.z, (res) => value.z = res);
			return g;
		}
		UIElement MakeDoubleElement(string name, double value) {
			var g = MakeDefaultGrid();
			g.Children.Add(MakeDefaultTextBlock(name));
			var tbValue = new TextBox() {
				Text = value.ToString(),
				Style = FindResource("TBStyle") as Style
			};
			tbValue.SetValue(Grid.ColumnProperty, 1);
			tbValue.TextChanged += (_, __) => {
				if (double.TryParse(tbValue.Text, out var res)) {
					updateCurrentObject(name, res);
					alertChanges();
				}
				else if (tbValue.Text.Trim().Length == 0) {
					if (tbValue.Text.Length != 0)
						tbValue.Text = "";
				}
				else
					tbValue.Text = "0";
			};
			g.Children.Add(tbValue);

			return g;
		}
		object CurrentObject;
		Type CurrentType;
		void updateCurrentObject<T>(string fieldName, T value) {
			var fi = CurrentType.GetField(fieldName);
			if (fi != null && fi.FieldType == typeof(T))
				fi.SetValue(CurrentObject, value);
		}
		private void Lbshapes_SelectionChanged(object __, SelectionChangedEventArgs _) {
			CurrentObject = _.AddedItems[0];
			CurrentType = CurrentObject.GetType();
			var elements = new List<UIElement>();
			foreach (var f in CurrentType.GetFields()) {
				var field = f.GetValue(CurrentObject);
				var name = f.Name;
				if (field is Color c)
					elements.Add(MakeColorElement(name, c));
				else if (field is Vec v)
					elements.Add(MakeVectorElement(name, v));
				else if (field is double d)
					elements.Add(MakeDoubleElement(name, d));
			}
			spProperties.Children.Clear();
			foreach (var e in elements) {
				spProperties.Children.Add(e);
				spProperties.Children.Add(new Separator() { Background = new SolidColorBrush(Colors.Black),Margin=new Thickness(0,5,0,5) });
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
		private void TbW_KeyUp(object sender, System.Windows.Input.KeyEventArgs e) {
			if (cbLink.IsChecked == true && int.TryParse(tbW.Text, out var i))
				tbH.Text = ((int)(1 / ratio * i)).ToString();
		}
		/// <summary>
		/// Handler for applying the set aspect ratio while entering numbers
		/// </summary>
		private void TbH_KeyUp(object sender, System.Windows.Input.KeyEventArgs e) {
			if (cbLink.IsChecked == true && int.TryParse(tbH.Text, out var i))
				tbW.Text = ((int)(ratio * i)).ToString();
		}
		public Action OnBack { get; set; }
		private void Button_Click(object sender, RoutedEventArgs e) {
			var Selector = new ShapeSelector(this.renderer);
			if (Selector.ShowDialog() == true)
				lbshapes.Items.Add(Selector.result);
			//lbshapes.Items.Add(Selector.result);
		}
	}
}
