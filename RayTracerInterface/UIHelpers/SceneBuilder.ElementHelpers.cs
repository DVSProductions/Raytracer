using System;
using System.Collections.Generic;
using System.Globalization;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
namespace RayTracerInterface {
	public partial class SceneBuilder : Page, IRenderPage {
		int[] customColors = new int[16];
		Style _btstyle = null, _tbstyle = null;
		SolidColorBrush _bgbrush = null, _lrbrush = null;
		Style BTStyle => _btstyle ?? (_btstyle = FindResource("BTStyle") as Style);
		Style TBStyle => _tbstyle ?? (_tbstyle = FindResource("TBStyle") as Style);
		SolidColorBrush BGBrush => _bgbrush ?? (_bgbrush = FindResource("BGColor") as SolidColorBrush);
		SolidColorBrush LRBrush => _lrbrush ?? (_lrbrush = FindResource("LightRed") as SolidColorBrush);
		void UpdateCurrentObject<T>(string fieldName, T value, object CurrentObject) {
			var fi = CurrentObject.GetType().GetField(fieldName);
			if (fi != null && fi.FieldType == typeof(T))
				fi.SetValue(CurrentObject, value);
		}
		static StackPanel AddToSP(StackPanel target, List<UIElement> elems) {
			foreach (var e in elems) {
				target.Children.Add(e);
				target.Children.Add(new Separator() { Height = 1.5, Background = new SolidColorBrush(Colors.Black), Margin = new Thickness(0, 5, 0, 5) });
			}
			return target;
		}
		
		static byte Scale(double d) => (byte)(d * 255);
		static T SetCP<T>(int CP, T e) where T : UIElement {
			e.SetValue(Grid.ColumnProperty, CP);
			return e;
		}
		static TextBlock MakeDefaultTextBlock(string name) =>
			SetCP(0, new TextBlock() {
				Text = name,
				TextWrapping = TextWrapping.NoWrap,
				Foreground = white,
				VerticalAlignment = VerticalAlignment.Center
			});
		static Grid MakeDefaultGrid(int? fixNameWidth = null) {
			var g = new Grid();
			g.ColumnDefinitions.Add(fixNameWidth.HasValue ?
				new ColumnDefinition() { Width = new GridLength(fixNameWidth.Value) } :
				new ColumnDefinition()
				);

			g.ColumnDefinitions.Add(new ColumnDefinition());
			return g;
		}
		static System.Windows.Media.Color ConvertColorM(Color c) => System.Windows.Media.Color.FromRgb(Scale(c.r), Scale(c.g), Scale(c.b));
		static System.Drawing.Color ConvertColor(Color c) => System.Drawing.Color.FromArgb(255, Scale(c.r), Scale(c.g), Scale(c.b));
		static Color ConvertColor(System.Drawing.Color c) => new Color(c.R, c.G, c.B);

		UIElement MakeMaterialElement(string name, AMaterial value, object CurrentObject, int? fixNameWidth) {
			var g = MakeDefaultGrid(fixNameWidth);
			g.Children.Add(MakeDefaultTextBlock(name));
			g.Children.Add(SetCP(1, AddToSP(new StackPanel(), VisualizeObject(value, null, true))));
			if (sbr is LibraryHandler.MaterialRenderer) {
				g.RowDefinitions.Add(new RowDefinition());
				g.RowDefinitions.Add(new RowDefinition());
				var bt = SetCP(1, new Button() {
					Style = BTStyle,
					Content = "Change Mat",
					HorizontalAlignment = HorizontalAlignment.Center
				});
				bt.Click += (_, __) => {
					var diag = new MaterialSelector(sbr as LibraryHandler.MaterialRenderer);
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
						SetCP(1, AddToSP(g.Children[1] as StackPanel, VisualizeObject(value, null, true)));
						AlertChanges();
					}
				};
				bt.SetValue(Grid.RowProperty, 1);
				//bt.SetValue(Grid.ColumnSpanProperty, 2);
				g.Children.Add(bt);
			}
			return g;
		}
		UIElement MakeColorElement(string name, Color value, object CurrentObject, int? fixNameWidth) {
			var g = MakeDefaultGrid(fixNameWidth);
			g.Children.Add(MakeDefaultTextBlock(name));
			var g2 = SetCP(1, MakeDefaultGrid());
			var box = SetCP(0, new Grid() { Background = new SolidColorBrush(ConvertColorM(value)) });
			var bt = SetCP(1, new Button() {
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
					AlertChanges();
					customColors = diag.CustomColors;
				}
			};
			g2.Children.Add(box);
			g2.Children.Add(bt);
			g.Children.Add(g2);
			return g;
		}
		UIElement MakeVectorElement(string name, Vec value, object CurrentObject, int? fixNameWidth) {
			var g = MakeDefaultGrid(fixNameWidth);
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
					Style = TBStyle
				};
				box.TextChanged += (obj, _) => {
					var tb = obj as TextBox;
					if (double.TryParse(tb.Text, NumberStyles.Any, CultureInfo.InvariantCulture, out var res)) {
						apply(res);
						UpdateCurrentObject(name, value, CurrentObject);
						AlertChanges();
					}
					else if (tb.Text.Trim().Length == 0) {
						if (tb.Text.Length != 0)
							tb.Text = "";
					}
					else if (tb.Text == "-") return;
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
		UIElement MakeTBBasedElement(string name, object value, Action<TextBox> validation, int? fixNameWidth) {
			var g = MakeDefaultGrid(fixNameWidth);
			g.Children.Add(MakeDefaultTextBlock(name));
			var tbValue = SetCP(1, new TextBox() {
				Text = value.ToString(),
				Style = TBStyle
			});
			tbValue.TextChanged += (_, __) => validation(tbValue);
			g.Children.Add(tbValue);
			return g;
		}
		UIElement MakeDoubleElement(string name, double value, object CurrentObject, int? fixNameWidth) {
			return MakeTBBasedElement(name, value, (tbValue) => {
				var cidx = tbValue.CaretIndex;
				tbValue.Text = tbValue.Text.Replace(',', '.');
				tbValue.CaretIndex = cidx;
				if (tbValue.Text == "-") return;
				else if (tbValue.Text.Trim().Length == 0) {
					if (tbValue.Text.Length != 0)
						tbValue.Text = "";
				}
				else if (double.TryParse(tbValue.Text, NumberStyles.Any, CultureInfo.InvariantCulture, out var res)) {
					UpdateCurrentObject(name, res, CurrentObject);
					AlertChanges();
				}
				else
					tbValue.Text = "0";
			}, fixNameWidth);
		}
		UIElement MakeUShortElement(string name, ushort value, object CurrentObject, int? fixNameWidth) {
			var previous = "0";
			return MakeTBBasedElement(name, value, (tbValue) => {
				if (ushort.TryParse(tbValue.Text, NumberStyles.Integer, CultureInfo.InvariantCulture, out var res)) {
					UpdateCurrentObject(name, res, CurrentObject);
					AlertChanges();
				}
				else if (tbValue.Text.Trim().Length == 0) {
					if (tbValue.Text.Length != 0)
						tbValue.Text = "";
				}
				else if (tbValue.Text == "-") return;
				else
					tbValue.Text = previous;
				previous = tbValue.Text;
			}, fixNameWidth);
		}
		UIElement MakeStringElement(string name, string value, object CurrentObject, int? fixNameWidth) {
			return MakeTBBasedElement(name, value, (tbValue) => {
				if (tbValue.Text.Length != 0) {
					UpdateCurrentObject(name, tbValue.Text, CurrentObject);
					AlertChanges();
					if (CurrentObject is Renderable r)
						r.Trigger(name);
				}
			}, fixNameWidth);
		}
		UIElement MakeTransformListElement(string name, List<ATransformation> value, object CurrentObject, int? fixNameWidth) {
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
				var b = SetCP(1, new Button() {
					Content = "x",
					Style = BTStyle,
					VerticalAlignment = VerticalAlignment.Center,
					Height = 20
				});
				b.Click += (_, __) => {
					content.Children.Remove(ng);
					value.Remove(t);
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
				var selecta = new TransformSelector(sbr as LibraryHandler.TransformableRenderer);
				selecta.Init();
				if (selecta.ShowDialog() == true) 
					addTransform(selecta.result);
			};
			g.Children.Add(content);
			g.Children.Add(btAddTransform);
			root.Content = g;
			return root;
		}
		UIElement MakeRecursiveObject(string name, object value, int? fixNameWidth = null) {
			var g = MakeDefaultGrid(fixNameWidth);
			g.Children.Add(MakeDefaultTextBlock(name));
			g.Children.Add(SetCP(1, AddToSP(new StackPanel(), VisualizeObject(value))));
			return g;
		}
		List<UIElement> VisualizeObject(object target, int? fixNameWidth = null, bool includeTypeName = false) {
			var CurrentType = target.GetType();
			var ret = new List<UIElement>();
			if (includeTypeName)
				ret.Add(new Label() {
					Content = target.GetType().Name,
					HorizontalAlignment = HorizontalAlignment.Center,
					Foreground = white
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
				else if (field is ISerializable r)
					ret.Add(MakeRecursiveObject(name, r));
			}
			return ret;
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
				Style = BTStyle
			};
			bt.Click += SelectCameraClick;
			spCam.Children.Add(bt);
		}
	}
}
