using System;
using System.Collections.Generic;
using System.IO;
using System.IO.Compression;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using System.Xml;
using System.Xml.Serialization;
using RayTracerInterface.GraphClasses;
using RayTracerInterface.UIHelpers;

namespace RayTracerInterface {
	/// <summary>
	/// Interaktionslogik für SceneGraph.xaml
	/// </summary>
	public partial class SceneGraph : Window {
		private readonly UIHelpers.VisualizationHelper visHelper;
		private readonly Renderer.TransformableRenderer rend;
		public static readonly SolidColorBrush white = new SolidColorBrush(Colors.White);
		private protected Point? canvasDragPos = null;
		private protected Point startoffset = new Point();
		public static Action<string> DoLog { get; private set; }
#pragma warning disable CA1044 // Eigenschaften dürfen nicht lesegeschützt sein
		public string Log { set => LogView.Text = value + "\n" + LogView.Text; }
		public string DragLog { set => DragView.Text = value + "\n" + DragView.Text; }
#pragma warning restore CA1044 // Eigenschaften dürfen nicht lesegeschützt sein
		public static double GetWindowsScaling() => System.Windows.Forms.Screen.PrimaryScreen.Bounds.Width / SystemParameters.PrimaryScreenWidth;
		public static GraphElement FindGeOfLabel(Label lb) => lb?.Content == null ? null : ((lb.Content as Grid).Children[0] as VisualStorage<GraphElement>).Storage;
		public SceneGraph(Renderer.TransformableRenderer renderer) {
			App.MakeMeDark(this);
			rend = renderer;
			InitializeComponent();
			//GraphScroller.PreviewMouseWheel +=(_,e)=>Graph_MouseWheel(e);
			Graph.RenderTransform = new TranslateTransform(0, 0);
			GraphScroller.PreviewMouseMove += GraphScroller_PreviewMouseMove;
			DoLog = (s) => Log = s;
			visHelper = new UIHelpers.VisualizationHelper(this, renderer);
		}
		private void GraphScroller_PreviewMouseMove(object sender, MouseEventArgs e) {
			if (!IsEraser && !IsHand) {
				if (e.LeftButton == MouseButtonState.Pressed && !dragging) {
					//var t = (Graph.RenderTransform as TranslateTransform);
					var p = e.GetPosition(GraphScroller);
					if (!canvasDragPos.HasValue) {
						canvasDragPos = p;
						startoffset = e.GetPosition(Graph);
					}
					var offset = -(p - canvasDragPos.Value) + (startoffset - canvasDragPos.Value);
					/*t.X = startoffset.X + offset.Value.X;	*/
					/*t.Y = startoffset.Y + offset.Value.Y;	*/
					GraphScroller.ScrollToVerticalOffset(offset.Y);
					GraphScroller.ScrollToHorizontalOffset(offset.X);
					//var re = new RoutedEventArgs(ScrollViewer.ScrollChangedEvent, (object)GraphScroller);
					//re.RoutedEvent
					//GraphScroller.RaiseEvent(re);
					//GraphScroller.InvalidateScrollInfo();
					//GraphScroller.
				}
				else if (canvasDragPos.HasValue)
					canvasDragPos = null;
			}
			else if (canvasDragPos.HasValue)
				canvasDragPos = null;
		}

		//double zoom = 1;
		//private void Graph_MouseWheel(MouseWheelEventArgs e) {
		//	if (Keyboard.IsKeyDown(Key.LeftCtrl)|| Keyboard.IsKeyDown(Key.RightCtrl)) {
		//		var tmp = zoom + e.Delta / 5000.0;
		//		if (tmp < 0.1)
		//			tmp = 0.1;
		//		zoom = tmp;
		//		Log = "" + zoom;
		//			var p=e.GetPosition(Graph);
		//		//Graph.RenderTransform = new ScaleTransform(zoom, zoom);
		//		Graph.LayoutTransform = new ScaleTransform(zoom, zoom,p.X,p.Y);
		//		//Graph.RenderTransformOrigin = new Point(p.X/Graph.ActualWidth,p.Y/Graph.ActualHeight);
		//		e.Handled = true;
		//	}
		//}




		private void AddR() {
			Graph.ColumnDefinitions.Add(new ColumnDefinition() { MinWidth = 60 });
			Graph.ColumnDefinitions.Add(new ColumnDefinition() { Width = new GridLength(20) });
			for (var n = 0; n < Graph.RowDefinitions.Count; n++) {
				if (Graph.RowDefinitions[n].Height.Value == 20)
					continue;
				CreateLabel(n, Graph.ColumnDefinitions.Count - 2);
			}
			ApplyLightness();
		}
		private void AddL() {
			Graph.ColumnDefinitions.Insert(0, new ColumnDefinition() { MinWidth = 60 });
			Graph.ColumnDefinitions.Insert(0, new ColumnDefinition() { Width = new GridLength(20) });
			foreach (Label l in Graph.Children) {
				var col = (int)l.GetValue(Grid.ColumnProperty);
				l.SetValue(Grid.ColumnProperty, col + 2);
			}
			for (var n = 0; n < Graph.RowDefinitions.Count; n++) {
				if (Graph.RowDefinitions[n].Height.Value == 20)
					continue;
				CreateLabel(n, 1);
			}
			ApplyLightness();
		}

		private void AddB() {
			Graph.RowDefinitions.Add(new RowDefinition() { MinHeight = 30, MaxHeight = 100 });
			Graph.RowDefinitions.Add(new RowDefinition() { Height = new GridLength(20) });
			for (var n = 0; n < Graph.ColumnDefinitions.Count; n++) {
				if (Graph.ColumnDefinitions[n].Width.Value == 20)
					continue;
				CreateLabel(Graph.RowDefinitions.Count - 2, n);
			}
			ApplyLightness();
		}
		private void Compass_MouseEnter(object sender, RoutedEventArgs _) {
			var snd = sender as FrameworkElement;
			var p = snd.PointToScreen(new Point(snd.ActualWidth / 2, snd.ActualHeight / 2));
			var source = PresentationSource.FromVisual(this);
			var scaling = GetWindowsScaling();
			var modp = new Point(p.X / scaling, p.Y / scaling);
			var c = new Compass(AddB, AddL, AddR, () => Focus()) { ShowActivated = false };
			c.Top = modp.Y - c.Height / 2.0;
			c.Left = modp.X - c.Width / 2.0;
			c.Show();
		}
		private GraphElement BuildGraph(Label container) {
			var graphElement = FindGeOfLabel(container);
			if (graphElement is GraphParent gp) {
				foreach (var ln in Lines) {
					if (ln.StartLabel == container) {
						var childCont = ln.StopLabel;
						var result = BuildGraph(childCont);
						gp.AddChild(result);
					}
				}
			}
			return graphElement;
		}
		private async void BTParse_Click(object sender, RoutedEventArgs e) {
			btParse.IsEnabled = false;
			//1. Find Root
			//try {
			var memory = new List<GraphElement>();
			Label RootContainer = null;
			UInt64 addr = 0;
			foreach (Label lb in Graph.Children) {
				if (lb.Content != null) {
					var ge = FindGeOfLabel(lb);
					ge.ResetParents();
					if (ge is GraphRoot)
						RootContainer = lb;
					if (ge is GraphParent gp)
						gp.ResetChildren();
					memory.Add(ge);
					ge.Address = addr++;
				}
			}
			await Task.Delay(100);
			BuildGraph(RootContainer);
			await Task.Delay(100);
			var serial = GraphRoot.GetSerial(memory);
			await Task.Delay(100);
			Clipboard.SetText(serial);
			MessageBox.Show("Parsed Successfully");
			//}
			//catch (Exception ex) {
			//	MessageBox.Show($"Parsing failed because:\n{ex.Message}");
			//}
			btParse.IsEnabled = true;
		}

		private void btLoad_Click(object sender, RoutedEventArgs e) {
			var dlg = new Microsoft.Win32.OpenFileDialog {
				DefaultExt = "*.xml;",
				CheckFileExists = true,
				CheckPathExists = true,
				Multiselect = false,
				RestoreDirectory = true,
				DereferenceLinks = true,
				Title = "Please select the Tree file",
				Filter = "Scene Definition Graph *.sdg|*.sdg"
			};
			if (dlg.ShowDialog() == true)
				Load(dlg.FileName);
		}
		public static IEnumerable<string> ReadAllLines(Stream stream) {
			using var reader = new StreamReader(stream);
			string line;
			while ((line = reader.ReadLine()) != null)
				yield return line;
		}
		private void Load(string path) {
			using var fs = File.OpenRead(path);
			using var ds = new DeflateStream(fs, CompressionMode.Decompress);
			Load(ds);
		}
		public void Load(Stream from) {
			using var reader = XmlReader.Create(from);
			Load(reader);
		}
		public async void Load(XmlReader reader) {
			var dat = new XmlSerializer(typeof(ReflectedGraph)).Deserialize(reader) as ReflectedGraph;
			Graph.Children.Clear();
			Graph.ColumnDefinitions.Clear();
			Graph.RowDefinitions.Clear();
			for (var x = 0; x < dat.x; x++) {
				Graph.ColumnDefinitions.Insert(0, new ColumnDefinition() { MinWidth = 60 });
				Graph.ColumnDefinitions.Insert(0, new ColumnDefinition() { Width = new GridLength(20) });
			}
			for (var y = 0; y < dat.y; y++) {
				Graph.RowDefinitions.Add(new RowDefinition() { MinHeight = 30, MaxHeight = 100 });
				Graph.RowDefinitions.Add(new RowDefinition() { Height = new GridLength(20) });
			}
			var labelsWithContent = new List<Label>();
			FillGraph((r, c, lb) => {
				foreach (var f in dat.Fields) {
					if (f.x == c && f.y == r) {
						labelsWithContent.Add(lb);
						lb.Content = MakeContentSub(f.name, f.e);
						return;
					}
				}
			});
			await Task.Delay(100);
			while (Lines.Count != 0)
				Lines[0].AbortDrag();
			foreach (var lna in dat.Lines) {
				Label source = null, end = null;
				foreach (var lb in labelsWithContent) {
					var id = FindGeOfLabel(lb).ID;
					if (id == lna.Source.ID)
						source = lb;
					else if (id == lna.Target.ID)
						end = lb;
				}
				AddLine(new Point(0, 0), source);
				currDL.LinkTo(end);
			}

		}

		private void btSave_Click(object sender, RoutedEventArgs e) {
			var dlg = new Microsoft.Win32.SaveFileDialog {
				DefaultExt = "*.xml;",
				CheckPathExists = true,
				RestoreDirectory = true,
				DereferenceLinks = true,
				Title = "Please select the Tree file",
				Filter = "Scene Definition Graph *.sdg|*.sdg"
			};
			if (dlg.ShowDialog() == true)
				Save(dlg.FileName);
		}
		private ReflectedGraph GenerateReflection() {
			var geaLst = new List<GraphElementAbstraction>();
			foreach (Label lb in Graph.Children)
				if (lb.Content != null) {
					geaLst.Add(new GraphElementAbstraction() {
						x = Grid.GetColumn(lb),
						y = Grid.GetRow(lb),
						e = FindGeOfLabel(lb),
						name = ((lb.Content as Grid).Children[1] as Label).Content as string
					});
				}
			var g = new ReflectedGraph {
				Lines = new DynamicLineAbstraction[Lines.Count],
				Fields = geaLst.ToArray(),
				x = Graph.ColumnDefinitions.Count,
				y = Graph.RowDefinitions.Count
			};
			var index = 0;
			foreach (var l in Lines)
				g.Lines[index++] = l.DumbDown();
			return g;
		}

		void Save(string fileName) {
			try {
				using var fs = new FileStream(fileName, FileMode.Create);
				using var ds = new DeflateStream(fs, CompressionLevel.Optimal);
				Save(ds, GenerateReflection());
			}
			catch (Exception ex) {
				MessageBox.Show($"ERROR WRITING OUTPUT FILE: {ex.ToString()}", ex.GetType().Name);
			}
		}
		static void Save(Stream target, ReflectedGraph source) {
			using var writer = new StreamWriter(target, new UTF8Encoding());
			new XmlSerializer(typeof(ReflectedGraph)).Serialize(writer, source);
		}
		public static string DecompressFile(string compressedFilePath) {
			using var fs = File.OpenRead(compressedFilePath);
			using var ds = new DeflateStream(fs, CompressionMode.Decompress);
			var newFilename = compressedFilePath + ".xml";
			var decompressedFileStream = File.Create(newFilename);
			ds.CopyTo(decompressedFileStream);
			decompressedFileStream.Close();
			return newFilename;
		}
	}
}
