using RayTracerInterface.GraphClasses;
using RayTracerInterface.UIHelpers;
using System;
using System.Collections.Generic;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using RayTracerInterface.GraphClasses.Generators;

namespace RayTracerInterface {
	public partial class SceneGraph : Window {
		private protected Grid newElement = null;
		private protected Label fallbackLabel = null;
		private protected bool treedrag = false;
		private protected void TVDragContainer_MouseLeftButtonUp(object _, MouseButtonEventArgs __) => RemoveTVDCBindings();

		static List<GraphParent> GetGenerators => new List<GraphParent>() {
					new Dice(),
					new Repeater()
				};
		IEnumerable<Renderable> FilterGroups(List<Renderable> lst) {
			foreach(var t in lst) {
				if (t.TYPEID() != Group.TID)
					yield return t;
			}
		}
		private void TreeView_Initialized(object sender, EventArgs e) {
			var tv = sender as TreeView;
			tv.Items.Add(CreateTreeFromList("Transforms", rend.SuppportedTransforms));
			tv.Items.Add(CreateTreeFromList("Shapes", FilterGroups(rend.SuppportedClass)));
			tv.Items.Add(CreateTreeFromList("Generators", GetGenerators));
		}
		private protected TreeViewItem CreateTreeFromList<T>(string header, IEnumerable<T> objs) where T : class {
			var ret = new TreeViewItem() { Header = header };
			foreach (var o in objs)
				ret.Items.Add(MakeTreeViewItem(o));
			return ret;
		}
		private protected TreeViewItem MakeTreeViewItem<T>(T element) where T : class {
			var ret = new TreeViewItem() { Header = element.GetType().Name };
			ret.AllowDrop = true;
			ret.MouseMove += Tvi_MouseMove;
			ret.SetValue(ContentProperty, new Func<object>(() => {
				if (element is Renderable r)
					return Renderable.ConvertIDToObject(r.TYPEID());
				else if (element is ATransformation t)
					return ATransformation.ConvertIDToObject(t.TYPEID());
				else if (element is GraphParent) {
					foreach (var ge in GetGenerators) {
						if (ge.GetType() == element.GetType())
							return ge;
					}
				}
				return element;
			}));
			return ret;
		}
		Brush SetBrushOpacity(Brush b, double opacity) {
			b.Opacity = opacity;
			return b;
		}
		private void Tvi_MouseMove(object sender, MouseEventArgs e) {
			if (!treedrag && e.LeftButton == MouseButtonState.Pressed) {
				var snd = sender as TreeViewItem;
				var p = e.GetPosition(TVDragContainer);
				TVDragContainer.Children.Add(new Label() {
					Content = snd.Header,
					Background = SetBrushOpacity(new SolidColorBrush(Colors.Red), 0.75),
					Foreground = white,
					Width = snd.Width,
					Height = snd.Height,
					Margin = new Thickness(p.X, p.Y, 0, 0),
					VerticalAlignment = VerticalAlignment.Top,
					HorizontalAlignment = HorizontalAlignment.Left,
					Padding = new Thickness(0),
					VerticalContentAlignment = VerticalAlignment.Center,
					HorizontalContentAlignment = HorizontalAlignment.Center
				});
				MakeContent(snd);
				AddTVDCBindings();
			}
		}
		private protected void MakeContent(TreeViewItem snd) {
			var elem = (snd.GetValue(ContentProperty) as Func<object>)();
			GraphElement ge = null;
			if (elem is ATransformation t)
				ge = new GraphTransform(t);
			else if (elem is Renderable r)
				ge = new GraphShape(r);
			else if (elem is GraphParent gp)
				ge = gp;
			newElement = MakeContentSub(snd.Header as string, ge);
		}
		protected SolidColorBrush _LightRed = null;
		protected SolidColorBrush LightRed => _LightRed ??= (SolidColorBrush)FindResource("LightRed");
		private Grid MakeContentSub(string Header, GraphElement value) {
			var ret = new Grid() {
				VerticalAlignment = VerticalAlignment.Stretch,
				HorizontalAlignment = HorizontalAlignment.Stretch,
			};
			ret.Children.Add(new VisualStorage<GraphElement>() {
				Storage = value
			});
			ret.Children.Add(new Label() {
				Background = new SolidColorBrush(
					value is GraphRoot ? System.Windows.Media.Color.FromRgb(153, 112, 41) :
					value is GraphShape ? System.Windows.Media.Color.FromRgb(153, 145, 41) :
					value is GraphTransform ? System.Windows.Media.Color.FromRgb(41, 132, 153) :
					value is GraphParent ? System.Windows.Media.Color.FromRgb(41, 153, 41)
					: Colors.Green),
				VerticalAlignment = VerticalAlignment.Stretch,
				HorizontalAlignment = HorizontalAlignment.Stretch,
				VerticalContentAlignment = VerticalAlignment.Center,
				HorizontalContentAlignment = HorizontalAlignment.Center,
				Content = Header,
			});
			ret.MouseMove += NewElement_MouseMove;
			ret.MouseRightButtonDown += NewElement_MouseRightButtonDown;
			ret.IsHitTestVisible = true;
			ret.MouseEnter += (_, me) => {
				if (IsConfig) {
					if (ret.Children.Count == 2)
						ret.Children.Add(new Border() {
							BorderBrush = LightRed,//new SolidColorBrush(Colors.Red),
							BorderThickness = new Thickness(1)
						});
				}
			};
			ret.MouseLeave += (_, me) => {
				if (ret.Children.Count == 3) {
					if (((ret.Children[2] as Border).BorderBrush as SolidColorBrush).Color == Colors.Red) {

					}
					else
						ret.Children.RemoveAt(2);
				}
			};
			ret.MouseLeftButtonDown += (_, me) => {
				if (IsConfig) {
					foreach (Label lb in Graph.Children) {
						if (lb.Content != null) {
							var c = (lb.Content as Grid).Children;
							if (c.Count == 3)
								c.RemoveAt(2);
						}
					}
					if (ret.Children.Count == 2)
						ret.Children.Add(new Border() {
							BorderBrush = LightRed,
							BorderThickness = new Thickness(1)
						});
					(ret.Children[2] as Border).BorderBrush = new SolidColorBrush(Colors.Red);
					spProperties.Children.Clear();
					//if (scea.AddedItems.Count == 0) {
					//	spProperties.Children.Add(new TextBlock() {
					//		Foreground = white,
					//		TextWrapping = TextWrapping.Wrap,
					//		Text = "No Element Selected"
					//	});
					//	return;
					//}
					if (value is GraphShape gs)
						VisualizationHelper.AddToSP(spProperties, visHelper.VisualizeObject(gs.Shape, null, true));
					else if (value is GraphTransform gt)
						VisualizationHelper.AddToSP(spProperties, visHelper.VisualizeObject(gt.trans, null, true));
					else
						VisualizationHelper.AddToSP(spProperties, visHelper.VisualizeObject(value, null, true));
				}
			};
			return ret;
		}

		private void NewElement_MouseRightButtonDown(object sender, MouseButtonEventArgs e) {
			if (IsEraser) {
				var snd = sender as Grid;
				if ((snd.Children[0] as VisualStorage<GraphElement>).Storage is GraphRoot)
					return;
				else if (snd.Children.Count == 3) {
					spProperties.Children.Clear();
					spProperties.Children.Add(new TextBlock() {
						Foreground = white,
						TextWrapping = TextWrapping.Wrap,
						Text = "No Element Selected"
					});
				}
				var parent = SceneBuilder.FindParentT<Label>(snd);
				parent.Content = null;
				var targets = new List<DynamicLine>();
				foreach (var l in Lines) {
					if (l.StartLabel == parent || l.StopLabel == parent)
						targets.Add(l);
				}
				foreach (var l in targets)
					l.AbortDrag();
			}
		}

		private void NewElement_MouseMove(object sender, MouseEventArgs e) {
			if (IsHand) {
				if (!treedrag && e.LeftButton == MouseButtonState.Pressed) {
					newElement = sender as Grid;
					fallbackLabel = SceneBuilder.FindParentT<Label>(newElement);
					var snd = (sender as Grid).Children[1] as Label;
					var p = e.GetPosition(TVDragContainer);
					var bbrush = snd.Background.Clone();
					bbrush.Opacity = 0.75;
					TVDragContainer.Children.Add(new Label() {
						Content = snd.Content,
						Background = bbrush,
						Width = snd.ActualWidth,
						Height = snd.ActualHeight,
						Margin = new Thickness(p.X, p.Y, 0, 0),
						VerticalAlignment = VerticalAlignment.Top,
						HorizontalAlignment = HorizontalAlignment.Left,
						Padding = new Thickness(0),
						VerticalContentAlignment = VerticalAlignment.Center,
						HorizontalContentAlignment = HorizontalAlignment.Center
					});
					AddTVDCBindings();
					newElement.MouseMove += NewElement_MouseMove;
				}
			}
		}

		private protected void AddTVDCBindings() {
			treedrag = true;
			TVDragContainer.IsHitTestVisible = true;
			TVDragContainer.Background = new SolidColorBrush(System.Windows.Media.Color.FromArgb(1, 0, 0, 0));
			TVDragContainer.MouseMove += TVDragContainer_MouseMove;
			TVDragContainer.MouseLeftButtonUp += TVDragContainer_MouseLeftButtonUp;
		}

		private protected bool isPlaced = false;
		private protected void RemoveTVDCBindings() {
			if (fallbackLabel != null) {
				if (!isPlaced)
					fallbackLabel.Content = newElement;
				else
					LinkToNewLabel();
				fallbackLabel = null;
			}
			treedrag = false;
			TVDragContainer.IsHitTestVisible = false;
			TVDragContainer.Background = null;
			TVDragContainer.MouseMove -= TVDragContainer_MouseMove;
			TVDragContainer.MouseLeftButtonUp -= TVDragContainer_MouseLeftButtonUp;
			TVDragContainer.Children.Clear();
		}

		private void LinkToNewLabel() {
			var newParent = SceneBuilder.FindParentT<Label>(newElement);
			if (!IsValid(newParent)) {
				fallbackLabel.Content = newElement;
				return;
			}
			foreach (var l in Lines) {
				if (!(l.StartLabel == fallbackLabel ? l.MoveStart(newParent) : l.StopLabel != fallbackLabel || l.LinkTo(newParent)))
					throw new StackOverflowException("Previous location was invalidated!");
			}
		}

		private bool IsValid(Label newParent) {
			foreach (var l in Lines) {
				if (l.StartLabel == fallbackLabel) {
					if (!l.IsAboveStop(newParent))
						return false;
				}
				else if (l.StopLabel == fallbackLabel && !l.IsBelowSource(newParent))
					return false;
			}
			return true;
		}

		private protected void TVDragContainer_MouseMove(object _, MouseEventArgs e) {
			if (e.LeftButton != MouseButtonState.Pressed) {
				RemoveTVDCBindings();
				return;
			}
			var lb = TVDragContainer.Children[0] as Label;
			var p = e.GetPosition(TVDragContainer);
			//Log = $"{p.X}|{p.Y}";
			lb.Margin = new Thickness(p.X - (lb.ActualWidth / 2), p.Y - (lb.ActualHeight / 2), 0, 0);
			isPlaced = false;
			//is even in Graph?
			var gsPos = e.GetPosition(GraphScroller);
			if (gsPos.Y < 0 || gsPos.X < 0 || gsPos.Y >= GraphScroller.ActualHeight || gsPos.X >= GraphScroller.ActualWidth)
				return;
			//find GraphTarget
			foreach (var rect in GraphTargets) {
				var p2 = e.GetPosition(rect);
				if (p2.X > 0 && p2.Y > 0 && rect.ActualWidth - p2.X > 0 && rect.ActualHeight - p2.Y > 0) {
					if (rect.Content == null) {
						rect.Content = newElement;
						isPlaced = true;
						return;
					}
					else if (rect.Content == newElement) {
						isPlaced = true;
						return;
					}
					else if (VisualTreeHelper.GetChildrenCount(rect) == 0) {
						rect.Name = "BROKEN";
						rect.Content = newElement;
						isPlaced = true;
						return;
					}
				}
				else if (rect.Content == newElement)
					rect.Content = null;
			}
		}

		private void Tvi_QueryContinueDrag(object sender, QueryContinueDragEventArgs e) {
			e.Action = DragAction.Continue;
			e.Handled = true;
		}
	}
}
