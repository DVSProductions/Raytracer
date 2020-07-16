using RayTracerInterface.UIHelpers;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Shapes;

namespace RayTracerInterface {
	public partial class SceneGraph : Window {
		bool dragging = false;
		readonly List<DynamicLine> Lines = new List<DynamicLine>();
		private protected DynamicLine currDL = null;
		protected List<Label> GraphTargets = new List<Label>();
		private protected Brush linebrush = new SolidColorBrush(Colors.AliceBlue);
		public void UpdateLastLine() => currDL = Lines.Count == 0 ? null : Lines.Last();
		private void Graph_Initialized(object sender, EventArgs e) {
			if ((sender as Grid).Children != null) {
				var targets = new List<Rectangle>();
				foreach (Rectangle r in (sender as Grid).Children)
					targets.Add(r);
				foreach (var t in targets)
					(sender as Grid).Children.Remove(t);
			}
			Graph.MouseLeftButtonUp += (_, me) => {
				if (me.LeftButton != MouseButtonState.Pressed && dragging) {
					dragging = false;
					currDL.AbortDrag();
				}
			};
			Graph.MouseMove += DrawDrag;
			Graph.MouseLeave += Graph_MouseLeave;
			var centercount = CalculateCenterCount();
			FillGraph((r, c, rect) => {
				if (r == 0 && c == centercount)
					rect.Content = MakeContentSub("Scene Root", new GraphClasses.GraphRoot());
			});
		}

		private int CalculateCenterCount() {
			var validCounts = 0;
			foreach (var c in Graph.ColumnDefinitions)
				if (c.Width.Value != 20)
					validCounts++;
			var centercount = ((Graph.ColumnDefinitions.Count - validCounts) / 2) + (validCounts / 2);
			while (Graph.ColumnDefinitions[centercount].Width.Value == 20)
				centercount++;
			return centercount;
		}

		private void FillGraph(Action<int,int,Label> CustomModifier) {
			//var bgRectCol = new SolidColorBrush(Colors.Transparent);
			var rc = Graph.RowDefinitions.Count;
			
			for (var r = 0; r < rc; r++) {
				var row = Graph.RowDefinitions[r];
				if (row.Height.Value == 20)
					continue;
				for (var c = 0; c < Graph.ColumnDefinitions.Count; c++) {
					if (Graph.ColumnDefinitions[c].Width.Value == 20)
						continue;
					var rect = CreateLabel(r, c);
					CustomModifier(r, c, rect);
				}
			}
			ApplyLightness();
		}

		[System.Diagnostics.CodeAnalysis.SuppressMessage("Performance", "CA1814:Jagged Arrays mehrdimensionalen Arrays vorziehen", Justification = "This is is an actual 2D array so Jaggered arrays are slower")]
		private void ApplyLightness() {
			var rc = Graph.RowDefinitions.Count;
			var cc = Graph.ColumnDefinitions.Count;
			var rand = new Random((int)System.Diagnostics.Process.GetCurrentProcess().StartTime.Ticks);
			var storage = new Label[rc, cc];
			foreach (Label l in Graph.Children) {
				var r = l.GetValue(Grid.RowProperty);
				var c = l.GetValue(Grid.ColumnProperty);
				storage[(int)r, (int)c] = l;
			}
			byte gen() => (byte)rand.Next(50, 100);
			for (var v = 0; v < rc || v < cc; v++) {
				if (v < rc) {
					for (var n = 0; n < v && n < cc; n++) {
						var l = gen();
						if (storage[v, n] != null)
							storage[v, n].Background = new SolidColorBrush(System.Windows.Media.Color.FromRgb(l, l, l));
					}
				}
				if (v < cc) {
					for (var n = 0; n < v && n < rc; n++) {
						var l = gen();
						if (storage[n, v] != null)
							storage[n, v].Background = new SolidColorBrush(System.Windows.Media.Color.FromRgb(l, l, l));
					}
				}
			}
			//foreach (Label l in Graph.Children) {
			//	var lightness = (byte)(120 - ((((double)(int)l.GetValue(Grid.ColumnProperty)) / cc * 60) + (((double)(int)l.GetValue(Grid.RowProperty)) / rc * 60)));
			//	l.Background = new SolidColorBrush(System.Windows.Media.Color.FromRgb(lightness, lightness, lightness));
			//}
		}
		private Label CreateLabel(int r, int c) {
			var lb = new Label {
				VerticalAlignment = VerticalAlignment.Stretch,
				HorizontalAlignment = HorizontalAlignment.Stretch,
				VerticalContentAlignment = VerticalAlignment.Stretch,
				HorizontalContentAlignment = HorizontalAlignment.Stretch,
				Padding = new Thickness(0),
				AllowDrop = true,
				Content = null,
				Name = "R_" + r + "_C_" + c//For identification while Debugging
			};

			//rect.MouseEnter += Rect_MouseEnter;
			//rect.MouseLeave += Rect_MouseLeave;
			lb.MouseLeftButtonDown += (_, me) => {
				if (IsPen && lb.Content != null) {
					if (FindGeOfLabel(lb) is GraphClasses.GraphShape)
						return;
					dragging = true;
					//var rng = new Random();
					AddLine(me.GetPosition(LineCanvas as UIElement), lb);
				}
			};
			lb.MouseLeftButtonUp += (_, me) => {
				if (dragging) {
					dragging = false;
					if (IsValidLine(lb))
						currDL.LinkTo(lb);
					else
						currDL.AbortDrag();
				}
				me.Handled = true;
			};

			lb.MouseMove += DrawDrag;
			lb.SetValue(Grid.ColumnProperty, c);
			lb.SetValue(Grid.RowProperty, r);
			GraphTargets.Add(lb);
			Graph.Children.Add(lb);
			return lb;
		}

		private void AddLine(Point p, Label lb) {
			Lines.Add(new DynamicLine(LineCanvas, MainGrid, lb, p, GraphScroller) {
				Stroke = linebrush, //new SolidColorBrush(System.Windows.Media.Color.FromRgb((byte)rng.Next(0, 256), (byte)rng.Next(0, 256), (byte)rng.Next(0, 256))),
				StrokeThickness = 5,// rng.NextDouble() * 5 + 2,
				Sudoku = (l) => { Lines.Remove(l); UpdateLastLine(); }
			});
			currDL = Lines.Last();
		}

		private void Graph_MouseLeave(object sender, MouseEventArgs e) {
			if (dragging) {
				dragging = false;
				currDL.AbortDrag();
			}
		}

		bool HaveLabelsBeenConnectedBefore(Label intendedTarget) {
			foreach (var dl in Lines)
				if (dl.StartLabel == currDL.StartLabel && dl.StopLabel == intendedTarget)
					return true;
			return false;
		}
		bool IsValidLine(Label target) =>
			target.Content != null
			&& currDL.IsBelowSource(target)
			&& !HaveLabelsBeenConnectedBefore(target)
			&& !(FindGeOfLabel(target) is GraphClasses.GraphRoot)
			 ;
		private protected void DrawDrag(object o, MouseEventArgs mm) {
			mm.Handled = true;
			if (dragging) {
				if (mm.LeftButton != MouseButtonState.Pressed) {
					dragging = false;
					currDL.AbortDrag();
					return;
				}
				currDL.DrawTo(mm.GetPosition(LineCanvas));
				if (o == Graph || (o is Label l && !IsValidLine(l)))
					currDL.Indicate(true);
			}
		}

		//private void Rect_MouseLeave(object sender, MouseEventArgs e) {
		//	var r = sender as Rectangle;
		//	var s = r.Fill as SolidColorBrush;
		//	r.Fill = new SolidColorBrush(System.Windows.Media.Color.FromArgb(255, s.Color.R, s.Color.G, s.Color.B));
		//}

		//private void Rect_MouseEnter(object sender, MouseEventArgs e) {
		//	var r = sender as Rectangle;
		//	var s = r.Fill as SolidColorBrush;
		//	r.Fill = new SolidColorBrush(System.Windows.Media.Color.FromArgb(150, s.Color.R, s.Color.G, s.Color.B));
		//}

	}
}
