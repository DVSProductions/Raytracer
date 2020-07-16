using System;
using System.Collections.Generic;
using System.Globalization;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;

namespace RayTracerInterface.UIHelpers {
	class VisualizationHelper {
		int[] customColors = new int[16];
		private readonly Style BTStyle, TBStyle;
		readonly SolidColorBrush BGBrush, LRBrush;
		public event Action OnChanges=()=> { };
		static readonly SolidColorBrush white = new SolidColorBrush(Colors.White);
		readonly Renderer.BasicRenderer sbr;
		public VisualizationHelper(FrameworkElement ResourceSource, Renderer.BasicRenderer relatedRenderer) {
			BTStyle = ResourceSource.FindResource("BTStyle") as Style;
			TBStyle = ResourceSource.FindResource("TBStyle") as Style;
			BGBrush = ResourceSource.FindResource("BGColor") as SolidColorBrush;
			LRBrush = ResourceSource.FindResource("LightRed") as SolidColorBrush;
			sbr = relatedRenderer;
		}
		public static void UpdateCurrentObject<T>(string fieldName, T value, object CurrentObject) {
			var fi = CurrentObject.GetType().GetField(fieldName);
			if (fi != null && (fi.FieldType == typeof(T) || (fi.FieldType.IsEnum && value.GetType() == fi.FieldType)))
				fi.SetValue(CurrentObject, value);
		}
		public static StackPanel AddToSP(StackPanel target, List<UIElement> elems) {
			foreach (var e in elems) {
				target.Children.Add(e);
				target.Children.Add(new Separator() { Height = 1.5, Background = new SolidColorBrush(Colors.Black), Margin = new Thickness(0, 5, 0, 5) });
			}
			return target;
		}
		public static Style MakeStyle(Type targetType, List<Setter> setters) {
			var s = new Style(targetType);
			foreach (var set in setters)
				s.Setters.Add(set);
			return s;
		}
		public static byte Scale(double d) => (byte)(d * 255);
		public static T SetCP<T>(int CP, T e) where T : UIElement {
			e.SetValue(Grid.ColumnProperty, CP);
			return e;
		}
		public static TextBlock MakeDefaultTextBlock(string name) =>
			SetCP(0, new TextBlock() {
				Text = name,
				TextWrapping = TextWrapping.NoWrap,
				Foreground = white,
				VerticalAlignment = VerticalAlignment.Center
			});
		public static Grid MakeDefaultGrid(int? fixNameWidth = null) {
			var g = new Grid();
			g.ColumnDefinitions.Add(fixNameWidth.HasValue ?
				new ColumnDefinition() { Width = new GridLength(fixNameWidth.Value) } :
				new ColumnDefinition() { Width = new GridLength(1, GridUnitType.Star) }
				);
			g.ColumnDefinitions.Add(new ColumnDefinition() { Width = new GridLength(5) });
			g.ColumnDefinitions.Add(new ColumnDefinition() { Width = new GridLength(2, GridUnitType.Star) });
			return g;
		}
		public static System.Windows.Media.Color ConvertColorM(Color c) => System.Windows.Media.Color.FromRgb(Scale(c.r), Scale(c.g), Scale(c.b));
		public static System.Drawing.Color ConvertColor(Color c) => System.Drawing.Color.FromArgb(255, Scale(c.r), Scale(c.g), Scale(c.b));
		public static Color ConvertColor(System.Drawing.Color c) => new Color(c.R, c.G, c.B);
		public UIElement MakeMaterialElement(string name, AMaterial value, object CurrentObject, int? fixNameWidth) {
			var g = MakeDefaultGrid(fixNameWidth);
			g.Children.Add(MakeDefaultTextBlock(name));
			g.Children.Add(SetCP(2, AddToSP(new StackPanel(), VisualizeObject(value, null, true))));
			if (sbr is Renderer.MaterialRenderer) {
				g.RowDefinitions.Add(new RowDefinition());
				g.RowDefinitions.Add(new RowDefinition());
				var bt = SetCP(2, new Button() {
					Style = BTStyle,
					Content = "Change Mat",
					HorizontalAlignment = HorizontalAlignment.Center
				});
				bt.Click += (_, __) => {
					var diag = new MaterialSelector(sbr as Renderer.MaterialRenderer);
					diag.Init();
					if (diag.ShowDialog() == true) {
						if (value.TYPEID() != (diag.result).TYPEID()) {
							if (value is AAlbedoMat am) {
								if (diag.result is AAlbedoMat am2) {
									am2.Albedo = am.Albedo;
									am2.Emission = am.Emission;
								}
								else
									(diag.result as AMaterial).Emission = am.Albedo;
							}
							else {
								if (diag.result is AAlbedoMat am2)
									am2.Albedo = value.Emission;
								else
									(diag.result as AMaterial).Emission = value.Emission;
							}
						}
						value = diag.result;
						UpdateCurrentObject(name, value, CurrentObject);
						(g.Children[1] as StackPanel).Children.Clear();
						SetCP(2, AddToSP(g.Children[1] as StackPanel, VisualizeObject(value, null, true)));
						OnChanges();
					}
				};
				bt.SetValue(Grid.RowProperty, 1);
				//bt.SetValue(Grid.ColumnSpanProperty, 2);
				g.Children.Add(bt);
			}
			return g;
		}
		public UIElement MakeTransformElement(string name, ATransformation value, object CurrentObject, bool canBeChanged, int? fixNameWidth) {
			var g = MakeDefaultGrid(fixNameWidth);
			g.Children.Add(MakeDefaultTextBlock(name));
			g.Children.Add(SetCP(2, AddToSP(new StackPanel(), VisualizeObject(value, null, true))));
			if (canBeChanged) {
				g.RowDefinitions.Add(new RowDefinition());
				g.RowDefinitions.Add(new RowDefinition());
				var bt = SetCP(2, new Button() {
					Style = BTStyle,
					Content = "Change",
					HorizontalAlignment = HorizontalAlignment.Center
				});
				bt.Click += (_, __) => {
					var diag = new TransformSelector(sbr as Renderer.TransformableRenderer);
					diag.Init();
					if (diag.ShowDialog() == true) {
						value = diag.result;
						UpdateCurrentObject(name, value, CurrentObject);
						(g.Children[1] as StackPanel).Children.Clear();
						SetCP(2, AddToSP(g.Children[1] as StackPanel, VisualizeObject(value, null, true)));
						OnChanges();
					}
				};
				bt.SetValue(Grid.RowProperty, 1);
				//bt.SetValue(Grid.ColumnSpanProperty, 2);
				g.Children.Add(bt);
			}
			return g;
		}
		public UIElement MakeColorElement(string name, Color value, object CurrentObject, int? fixNameWidth) {
			var g = MakeDefaultGrid(fixNameWidth);
			g.Children.Add(MakeDefaultTextBlock(name));
			var g2 = SetCP(2, MakeDefaultGrid());
			var box = SetCP(0, new Grid() { Background = new SolidColorBrush(ConvertColorM(value)) });
			var bt = SetCP(2, new Button() {
				Style = BTStyle,
				Content = "Change",
				HorizontalAlignment = HorizontalAlignment.Center
			});
			bt.Click += (_, __) => {
				var diag = new System.Windows.Forms.ColorDialog() {
					AnyColor = true,
					AllowFullOpen = true,
					SolidColorOnly = true,
					FullOpen = true,
					ShowHelp = false,
					Color = System.Drawing.Color.FromArgb(0, Scale(value.r), Scale(value.g), Scale(value.b)),
					CustomColors = customColors
				};
				if (diag.ShowDialog() == System.Windows.Forms.DialogResult.OK) {
					value = ConvertColor(diag.Color);
					box.Background = new SolidColorBrush(ConvertColorM(value));
					UpdateCurrentObject(name, value, CurrentObject);
					OnChanges();
					customColors = diag.CustomColors;
				}
			};
			g2.Children.Add(box);
			g2.Children.Add(bt);
			g.Children.Add(g2);
			return g;
		}
		public UIElement MakeVectorElement(string name, Vec value, object CurrentObject, int? fixNameWidth) {
			var g = MakeDefaultGrid(fixNameWidth);
			var sp = SetCP(2, new WrapPanel() { Orientation = Orientation.Horizontal });
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
					Style = TBStyle
				};
				box.TextChanged += (obj, _) => {
					var tb = obj as TextBox;
					if (double.TryParse(tb.Text, NumberStyles.Any, CultureInfo.InvariantCulture, out var res)) {
						apply(res);
						UpdateCurrentObject(name, value, CurrentObject);
						OnChanges();
					}
					else if (tb.Text.Trim().Length == 0) {
						if (tb.Text.Length != 0)
							tb.Text = "";
					}
					else if (tb.Text == "-")
						return;
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
		public UIElement MakeTBBasedElement(string name, object value, Action<TextBox> validation, int? fixNameWidth) {
			var g = MakeDefaultGrid(fixNameWidth);
			g.Children.Add(MakeDefaultTextBlock(name));
			var tbValue = SetCP(2, new TextBox() {
				Text = value.ToString(),
				Style = TBStyle
			});
			tbValue.TextChanged += (_, __) => validation(tbValue);
			g.Children.Add(tbValue);
			return g;
		}
		public UIElement MakeDoubleElement(string name, double value, object CurrentObject, int? fixNameWidth) =>
			MakeTBBasedElement(name, value, (tbValue) => {
				var cidx = tbValue.CaretIndex;
				tbValue.Text = tbValue.Text.Replace(',', '.');
				tbValue.CaretIndex = cidx;
				if (tbValue.Text == "-")
					return;
				else if (tbValue.Text.Trim().Length == 0) {
					if (tbValue.Text.Length != 0)
						tbValue.Text = "";
				}
				else if (double.TryParse(tbValue.Text, NumberStyles.Any, CultureInfo.InvariantCulture, out var res)) {
					UpdateCurrentObject(name, res, CurrentObject);
					OnChanges();
				}
				else
					tbValue.Text = "0";
			}, fixNameWidth);
		public UIElement MakeUShortElement(string name, ushort value, object CurrentObject, int? fixNameWidth) {
			var previous = "0";
			return MakeTBBasedElement(name, value, (tbValue) => {
				if (ushort.TryParse(tbValue.Text, NumberStyles.Integer, CultureInfo.InvariantCulture, out var res)) {
					UpdateCurrentObject(name, res, CurrentObject);
					OnChanges();
				}
				else if (tbValue.Text.Trim().Length == 0) {
					if (tbValue.Text.Length != 0)
						tbValue.Text = "";
				}
				else if (tbValue.Text == "-")
					return;
				else
					tbValue.Text = previous;
				previous = tbValue.Text;
			}, fixNameWidth);
		}
		public UIElement MakeStringElement(string name, string value, object CurrentObject, int? fixNameWidth) =>
			MakeTBBasedElement(name, value, (tbValue) => {
				if (tbValue.Text.Length != 0) {
					UpdateCurrentObject(name, tbValue.Text, CurrentObject);
					OnChanges();
					if (CurrentObject is Renderable r)
						r.Trigger(name);
				}
			}, fixNameWidth);
		public UIElement MakeTransformListElement(string name, List<ATransformation> value, object CurrentObject, int? fixNameWidth) {
			var root = new FieldSet() {
				Header = name,
				Background = BGBrush,
				Foreground = white,
				BorderBrush = LRBrush
			};
			var g = new Grid() {
				Margin = new Thickness(5)
			};
			var content = new StackPanel() {
				VerticalAlignment = VerticalAlignment.Stretch,
				HorizontalAlignment = HorizontalAlignment.Stretch,
				Margin = new Thickness(0, 0, 0, 30),
				MinHeight = 50,
			};
			var btAddTransform = new Button() {
				Style = BTStyle,
				Content = "Add Transform",
				VerticalAlignment = VerticalAlignment.Bottom,
				Height = 30
			};
			void showTransform(ATransformation t) {
				var ng = new Grid();
				ng.ColumnDefinitions.Add(new ColumnDefinition());
				ng.ColumnDefinitions.Add(new ColumnDefinition() { Width = new GridLength(20) });
				var b = SetCP(2, new Button() {
					Content = "x",
					Style = BTStyle,
					VerticalAlignment = VerticalAlignment.Center,
					Height = 20,
				});
				b.Resources.Add("Rounder", MakeStyle(typeof(Border), new List<Setter>() { new Setter(Border.CornerRadiusProperty, 10) }));
				b.Click += (_, __) => {
					content.Children.Remove(ng);
					value.Remove(t);
					OnChanges();
				};
				string[] names = { "T", "R", "S", "C" };
				ng.Children.Add(MakeRecursiveObject(names[t.TYPEID()] + value.Count, t, fixNameWidth ?? 30));
				ng.Children.Add(b);
				content.Children.Add(ng);
			}
			void addTransform(ATransformation t) {
				showTransform(t);
				value.Add(t);
			}
			foreach (var t in value)
				showTransform(t);
			btAddTransform.Click += (_, __) => {
				var selecta = new TransformSelector(sbr as Renderer.TransformableRenderer);
				selecta.Init();
				if (selecta.ShowDialog() == true)
					addTransform(selecta.result);
			};
			g.Children.Add(content);
			g.Children.Add(btAddTransform);
			root.Content = g;
			return root;
		}
		///// <summary>
		///// obsoleted by dynamic enum casting using reflection
		///// </summary>
		//UIElement MakeAxisElement(string name, Axis value, object CurrentObject, int? fixNameWidth) {
		//	var g = MakeDefaultGrid(fixNameWidth);
		//	g.Children.Add(MakeDefaultTextBlock(name));
		//	var cbValue = SetCP(2, new ComboBox() {
		//	});
		//	cbValue.Items.Add("X");
		//	cbValue.Items.Add("Y");
		//	cbValue.Items.Add("Z");
		//	cbValue.SelectedIndex = (int)value;
		//	cbValue.SelectionChanged += (_, __) => {
		//		value = cbValue.SelectedIndex switch
		//		{
		//			0 => Axis.X,
		//			1 => Axis.Y,
		//			2 => Axis.Z,
		//			_ => Axis.X
		//		};
		//		UpdateCurrentObject(name, value, CurrentObject);
		//		OnChanges();
		//	};
		//	g.Children.Add(cbValue);
		//	return g;
		//}
		/// <summary>
		/// Intelligently create Combo boxes for any enum using reflection
		/// </summary>
		/// <returns></returns>
		public UIElement MakeEnumElement(string name, Enum value, object CurrentObject, int? fixNameWidth) {
			var g = MakeDefaultGrid(fixNameWidth);
			g.Children.Add(MakeDefaultTextBlock(name));
			var cbValue = SetCP(2, new ComboBox() {
			});
			foreach (var n in Enum.GetNames(value.GetType())) {
				cbValue.Items.Add(n);
				if (value.ToString() == n)
					cbValue.SelectedItem = n;
			}
			cbValue.SelectionChanged += (_, __) => {
				value = (Enum)Enum.Parse(value.GetType(), cbValue.SelectedItem as string);
				UpdateCurrentObject(name, value, CurrentObject);
				OnChanges();
			};
			g.Children.Add(cbValue);
			return g;
		}
		public UIElement MakeRecursiveObject(string name, object value, int? fixNameWidth = null) {
			var g = MakeDefaultGrid(fixNameWidth);
			g.Children.Add(MakeDefaultTextBlock(name));
			g.Children.Add(SetCP(2, AddToSP(new StackPanel(), VisualizeObject(value))));
			return g;
		}
		public List<UIElement> VisualizeObject(object target, int? fixNameWidth = null, bool includeTypeName = false) {
			var CurrentType = target.GetType();
			var ret = new List<UIElement>();
			if (includeTypeName)
				ret.Add(new Label() {
					Content = target.GetType().Name,
					HorizontalAlignment = HorizontalAlignment.Center,
					Foreground = white,
					FontWeight= FontWeights.Medium,
				});
			foreach (var f in CurrentType.GetFields()) {
				var field = f.GetValue(target);
				var name = f.Name;
				if (field is Color c)
					ret.Add(MakeColorElement(name, c, target, fixNameWidth));
				else if (field is Vec v)
					ret.Add(MakeVectorElement(name, v, target, fixNameWidth));
				else if (field is double d)
					ret.Add(MakeDoubleElement(name, d, target, fixNameWidth));
				else if (field is ushort us)
					ret.Add(MakeUShortElement(name, us, target, fixNameWidth));
				else if (field is string s)
					ret.Add(MakeStringElement(name, s, target, fixNameWidth));
				else if (field is AMaterial m)
					ret.Add(MakeMaterialElement(name, m, target, fixNameWidth));
				else if (field is List<ATransformation> t)
					ret.Add(MakeTransformListElement(name, t, target, fixNameWidth));
				else if (field is ATransformation at)
					ret.Add(MakeTransformElement(name, at, target, f.FieldType == typeof(ATransformation), fixNameWidth));
				//else if (field is Axis x)
				//	ret.Add(MakeAxisElement(name, x, target, fixNameWidth));
				else if (field is ISerializable r)
					ret.Add(MakeRecursiveObject(name, r));
				else if (field is Enum e)
					ret.Add(MakeEnumElement(name, e, target, fixNameWidth));
			}
			return ret;
		}

		public void VisualizeCamera(StackPanel target, Camera cam, RoutedEventHandler onClick) {
			target.Children.Clear();
			target.Children.Add(new Label() {
				Content = cam.GetType().Name,
				HorizontalAlignment = HorizontalAlignment.Center,
				Foreground = white
			});
			foreach (var e in VisualizeObject(cam)) {
				target.Children.Add(e);
				target.Children.Add(new Separator() { Height = 1.5, Background = new SolidColorBrush(Colors.Black), Margin = new Thickness(0, 5, 0, 5) });
			}
			var bt = new Button() {
				Content = "Ändern",
				Style = BTStyle
			};
			bt.Click += onClick;
			target.Children.Add(bt);
		}
	}
}
