﻿using System;
using System.Collections.Generic;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;

namespace RayTracerInterface {
	public partial class SceneBuilder : Page, IRenderPage {
		static byte Scale(double d) => (byte)(d * 255);
		static T SetCP<T>(int CP, T e) where T : UIElement {
			e.SetValue(Grid.ColumnProperty, CP);
			return e;
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
		static System.Windows.Media.Color ConvertColorM(Color c) => System.Windows.Media.Color.FromRgb(Scale(c.r), Scale(c.g), Scale(c.b));
		System.Drawing.Color ConvertColor(Color c) => System.Drawing.Color.FromArgb(255, Scale(c.r), Scale(c.g), Scale(c.b));
		static Color ConvertColor(System.Drawing.Color c) => new Color(c.R, c.G, c.B);
		UIElement MakeColorElement(string name, Color value, object CurrentObject) {
			var g = MakeDefaultGrid();
			g.Children.Add(MakeDefaultTextBlock(name));
			var g2 = SetCP(1, MakeDefaultGrid());
			var box = SetCP(0, new Grid() { Background = new SolidColorBrush(ConvertColorM(value)) });
			var bt = SetCP(1, new Button() {
				Style = FindResource("BTStyle") as Style,
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
					Color = System.Drawing.Color.FromArgb(0, Scale(value.r), Scale(value.g), Scale(value.b))
				};
				if (diag.ShowDialog() == System.Windows.Forms.DialogResult.OK) {
					value = ConvertColor(diag.Color);
					box.Background = new SolidColorBrush(ConvertColorM(value));
					UpdateCurrentObject(name, value, CurrentObject);
					alertChanges();
				}
			};
			g2.Children.Add(box);
			g2.Children.Add(bt);
			g.Children.Add(g2);
			return g;
		}
		UIElement MakeVectorElement(string name, Vec value, object CurrentObject) {
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
					tb.Text=tb.Text.Replace(".", ",");
					if (double.TryParse(tb.Text, out var res)) {
						apply(res);
						UpdateCurrentObject(name, value, CurrentObject);
						alertChanges();
					}
					else if (tb.Text.Trim().Length == 0) {
						if (tb.Text.Length != 0)
							tb.Text = "";
					}
					else if (tb.Text == "-") ;
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
		UIElement MakeDoubleElement(string name, double value, object CurrentObject) {
			var g = MakeDefaultGrid();
			g.Children.Add(MakeDefaultTextBlock(name));
			var tbValue = new TextBox() {
				Text = value.ToString(),
				Style = FindResource("TBStyle") as Style
			};
			tbValue.SetValue(Grid.ColumnProperty, 1);
			tbValue.TextChanged += (_, __) => {
				tbValue.Text = tbValue.Text.Replace(".", ",");
				if (double.TryParse(tbValue.Text, out var res)) {
					UpdateCurrentObject(name, res, CurrentObject);
					alertChanges();
				}
				else if (tbValue.Text.Trim().Length == 0) {
					if (tbValue.Text.Length != 0)
						tbValue.Text = "";
				}
				else if (tbValue.Text == "-") ;
				else
					tbValue.Text = "0";
			};
			g.Children.Add(tbValue);

			return g;
		}
		void UpdateCurrentObject<T>(string fieldName, T value, object CurrentObject) {
			var fi = CurrentObject.GetType().GetField(fieldName);
			if (fi != null && fi.FieldType == typeof(T))
				fi.SetValue(CurrentObject, value);
		}
		List<UIElement> VisualizeObject(object target) {
			var CurrentType = target.GetType();
			var ret = new List<UIElement>();
			foreach (var f in CurrentType.GetFields()) {
				var field = f.GetValue(target);
				var name = f.Name;
				if (field is Color c)
					ret.Add(MakeColorElement(name, c, target));
				else if (field is Vec v)
					ret.Add(MakeVectorElement(name, v, target));
				else if (field is double d)
					ret.Add(MakeDoubleElement(name, d, target));
			}
			return ret;
		}
	}
}