using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Shapes;
using Point = System.Windows.Point;
namespace RayTracerInterface.UIHelpers {
	class DynamicLine {
		protected Point dragStart, dragEnd;
		protected readonly Canvas DrawTarget;
		protected readonly Grid RectangleSource;
		protected readonly Line myLine;
		protected readonly Polygon triangle;
		protected readonly ScrollViewer SourceScroller;
		protected readonly PointCollection triangleShape = new PointCollection(){
			new Point(0,0),
			new Point(8,5),
			new Point(0,10)
		};
		protected bool isHittable = false;
		protected static readonly Brush red = new SolidColorBrush(Colors.Red);
		public Label StartLabel { get; private set; }
		public Label StopLabel { get; private set; }
		public bool IsHittable { get => isHittable; set => myLine.IsHitTestVisible = isHittable = value; }
		//public bool
		public bool IsLinked { get; private set; } = false;
		public delegate void Murder(DynamicLine victim);
		public Murder Sudoku { get; set; }
		public double StrokeThickness { get => myLine.StrokeThickness; set => myLine.StrokeThickness = value; }
		public Brush Stroke { get => myLine.Fill; set => triangle.Stroke = triangle.Fill = myLine.Stroke = myLine.Fill = value; }
		private void SetTrianglePosition(Point p) {
			Canvas.SetLeft(triangle, p.X);
			Canvas.SetTop(triangle, p.Y);
		}
		static double Angle_trunc(double a) {
			while (a < 0.0)
				a += Math.PI * 2;
			return a;
		}

		static double GetAngleBetweenPoints(Point orig, Point landmark) {
			var deltaY = landmark.Y - orig.Y;
			var deltaX = landmark.X - orig.X;
			return Angle_trunc(Math.Atan2(deltaY, deltaX));
		}
		private void UpdateLine(Point p) {
			dragEnd = p;
			SetTrianglePosition(p);
			myLine.X2 = dragEnd.X;
			myLine.Y2 = dragEnd.Y;
			var corr = GetAngleBetweenPoints(dragStart, dragEnd) * (360.0 / (2 * Math.PI));
			//SceneGraph.doLog($"angle: {angle} | or :{corr}");
			triangle.RenderTransform = new TransformGroup() {
				Children = new TransformCollection(){
					new TranslateTransform(0,-5),
					new TransformGroup() {
						Children= new TransformCollection() {
							new RotateTransform(corr),
						}
					}
				}
			};
		}
		public DynamicLine(Canvas DrawTarget, Grid RectangleSource, Label source, Point start, ScrollViewer SourceScroller = null) {
			this.DrawTarget = DrawTarget;
			this.RectangleSource = RectangleSource;
			this.SourceScroller = SourceScroller;
			StartLabel = source;
			myLine = new Line() {
				X1 = start.X,
				Y1 = start.Y,
				StrokeThickness = 10,
				IsHitTestVisible = false,
				StrokeStartLineCap = PenLineCap.Round,
				StrokeEndLineCap = PenLineCap.Flat
			};
			triangle = new Polygon() {
				Points = triangleShape,
				IsHitTestVisible = false,
			};
			SetTrianglePosition(start);
			dragStart = start;
			UpdateLine(start);
			this.DrawTarget.Children.Add(myLine);
			this.DrawTarget.Children.Add(triangle);
		}
		public void Indicate(bool isInvalid) => triangle.Fill = triangle.Stroke = myLine.Stroke = (isInvalid ? red : Stroke);
		public void DrawTo(Point newEnd) {
			UpdateLine(newEnd);
			Indicate(newEnd.Y < dragStart.Y);
		}
		public void ReLink() {
			var newline = SearchConnection();
			dragStart = newline.Item1;
			myLine.X1 = dragStart.X;
			myLine.Y1 = dragStart.Y;
			UpdateLine(newline.Item2);

			IsLinked = true;
		}

		private Tuple<Point, Point> SearchConnection() {
			var endpos = StopLabel.TranslatePoint(new Point(), DrawTarget);
			var startpos = StartLabel.TranslatePoint(new Point(), DrawTarget);
			//find end corner
			/* a--b      |  a---b|       a---b
			 * |S |      |  |S  ||       |S  |
			 * c--d     1|8 c---d|7      c---d
			 *-----------A-------B----------------------------------
			 *          2|E      |6
			 *           |       |
			 *-----------C-------D----------------------------------
			 * a---b    3|      4|5        a---b
			 * |S  |     a---b   |         |S  |
			 * c---d     |S  |   |         c---d
			 * 			 c---d	 | 
			 */
			//source Label (nocaps)
			Point
				SA = new Point(startpos.X, startpos.Y),
				SB = new Point(SA.X + StartLabel.ActualWidth, startpos.Y),
				SC = new Point(startpos.X, startpos.Y + StartLabel.ActualHeight),
				SD = new Point(SB.X, SC.Y);
			//Target rectangle (allcaps)
			Point
				EA = new Point(endpos.X, endpos.Y),
				EB = new Point(EA.X + StopLabel.ActualWidth, endpos.Y),
				EC = new Point(endpos.X, endpos.Y + StopLabel.ActualHeight),
				ED = new Point(EB.X, EC.Y);
			//Start -> end
			///Rules:
			/// *Rectangles cannot touch each other
			/// *Rectangles cannot intersect
			/// *Rectangles are not flipped and conform to the diagram
			//is in the first 3 sectors
			if (SD.X < EA.X) {
				//Sector 1
				if (SD.Y <= EA.Y)
					return new Tuple<Point, Point>(SD, EA);
				//Sector 2
				else if (SD.Y <= EC.Y)
					return new Tuple<Point, Point>(SD, EC);
				//Sector 3
				else
					return new Tuple<Point, Point>(SB, EC);
			}
			//Sector 8 or 4
			else if (SD.X <= EB.X) {
				//Sector 8
				if (SD.Y < EB.Y)
					return new Tuple<Point, Point>(SD, EB);
				//Sector 4
				else
					return new Tuple<Point, Point>(SB, ED);
			}
			//Sector 5,6,7
			else {
				//Sector 7
				if (SB.Y < EC.Y)
					return new Tuple<Point, Point>(SC, EB);
				//Sector 6
				else if (SD.Y < EC.Y)
					return new Tuple<Point, Point>(SC, ED);
				//Sector 5
				else
					return new Tuple<Point, Point>(SA, ED);
			}
		}
		/// <summary>
		/// just for lulz
		/// </summary>
		private Tuple<Point, Point> SearchConnectionConditional() {
			var endpos = StopLabel.TranslatePoint(new Point(), DrawTarget);
			var startpos = StartLabel.TranslatePoint(new Point(), DrawTarget);
			Point
				SA = new Point(startpos.X, startpos.Y),
				SB = new Point(SA.X + StartLabel.ActualWidth, startpos.Y),
				SC = new Point(startpos.X, startpos.Y + StartLabel.ActualHeight),
				SD = new Point(SB.X, SC.Y);
			Point
				EA = new Point(endpos.X, endpos.Y),
				EB = new Point(EA.X + StopLabel.ActualWidth, endpos.Y),
				EC = new Point(endpos.X, endpos.Y + StopLabel.ActualHeight),
				ED = new Point(EB.X, EC.Y);
			return
				SD.X < EA.X ?
					SD.Y <= EA.Y ?
						new Tuple<Point, Point>(SD, EA) :
						SD.Y <= EC.Y ?
							new Tuple<Point, Point>(SD, EC) :
							new Tuple<Point, Point>(SB, EC) :
					SD.X < EB.X ?
						SD.Y < EB.Y ?
							new Tuple<Point, Point>(SD, EB) :
							new Tuple<Point, Point>(SB, ED) :
						SB.Y < EC.Y ?
							new Tuple<Point, Point>(SC, EB) :
							SD.Y < EC.Y ?
								new Tuple<Point, Point>(SC, ED) :
								new Tuple<Point, Point>(SA, ED);
		}
		public bool IsBelowSource(Label newStop) => newStop != StartLabel && (int)newStop.GetValue(Grid.RowProperty) > (int)StartLabel.GetValue(Grid.RowProperty);
		public bool IsAboveStop(Label newStart) => newStart != StopLabel && (int)StopLabel.GetValue(Grid.RowProperty) > (int)newStart.GetValue(Grid.RowProperty);
		public bool LinkTo(Label end) {
			if (!IsBelowSource(end)) {
				AbortDrag();
				return false;
			}
			StopLabel = end;
			if (!IsLinked) {
				RectangleSource.SizeChanged += (_, __) => ReLink();
				if (SourceScroller != null)
					SourceScroller.ScrollChanged += (_, __) => ReLink();
			}
			ReLink();
			Indicate(false);
			return true;
		}
		public void AbortDrag() {
			Sudoku?.Invoke(this);
			DrawTarget.Children.Remove(myLine);
			DrawTarget.Children.Remove(triangle);
		}
		/// <summary>
		/// Only use if you can undo what <see cref="Murder"/> did
		/// </summary>
		public void Revive() {
			DrawTarget.Children.Add(myLine);
			DrawTarget.Children.Add(triangle);
		}
		private bool enableClickSudoku = false;
		public bool ClickSudoku {
			get => enableClickSudoku;
			set {
				if (enableClickSudoku = value) {
					myLine.IsHitTestVisible = true;
					myLine.Cursor = System.Windows.Input.Cursors.Cross;
					myLine.MouseMove += MyLine_SudokuMouse;
					myLine.MouseLeftButtonUp += MyLine_MouseLeftButtonUp;
				}
				else {
					myLine.IsHitTestVisible = IsHittable;
					myLine.MouseMove -= MyLine_SudokuMouse;
					myLine.MouseLeftButtonUp -= MyLine_MouseLeftButtonUp;
				}
			}
		}

		private void MyLine_MouseLeftButtonUp(object _, System.Windows.Input.MouseButtonEventArgs __) => AbortDrag();

		private void MyLine_SudokuMouse(object _, System.Windows.Input.MouseEventArgs me) {
			if (me.LeftButton == System.Windows.Input.MouseButtonState.Pressed)
				AbortDrag();
		}

		public bool MoveStart(Label newStart) {
			if (!IsAboveStop(newStart)) {
				AbortDrag();
				return false;
			}
			StartLabel = newStart;
			ReLink();
			return true;
		}
		public DynamicLineAbstraction DumbDown() => new DynamicLineAbstraction() { Source = SceneGraph.FindGeOfLabel(StartLabel), Target = SceneGraph.FindGeOfLabel(StopLabel) };
	}
}
