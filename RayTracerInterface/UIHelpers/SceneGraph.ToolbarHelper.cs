using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;

namespace RayTracerInterface {
	public partial class SceneGraph : Window {
		public static readonly Cursor Eraser = Cursors.No, Pen = Cursors.Pen, Hand = Cursors.Hand, ConfigCur = Cursors.ArrowCD;
		private protected readonly SolidColorBrush toolSel = new SolidColorBrush(System.Windows.Media.Color.FromRgb(100, 0, 0));
		public static bool XOR(bool a, bool b) => (a || b) && (a != b);

		bool IsPen => Graph.Cursor == Pen;
		bool IsEraser => Graph.Cursor == Eraser;
		bool IsHand => Graph.Cursor == Hand;
		bool IsConfig => Graph.Cursor == ConfigCur;
		void ToolHelper(Button sender, Cursor newCursor) {
			var eq = Graph.Cursor == newCursor;
			if (newCursor == Eraser)
				foreach (var dl in Lines)
					dl.ClickSudoku = !eq;
			else if (Graph.Cursor == Eraser)
				foreach (var dl in Lines)
					dl.ClickSudoku = false;
			foreach (Button b in spTools.Children)
				b.Background = b != sender || eq ? null : toolSel;
			Graph.Cursor = eq ? null : newCursor;
		}

		private void btErase_Click(object sender, RoutedEventArgs _) => ToolHelper(sender as Button, Eraser);
		private void btMove_Click(object sender, RoutedEventArgs _) => ToolHelper(sender as Button, Hand);
		private void btDraw_Click(object sender, RoutedEventArgs _) => ToolHelper(sender as Button, Pen);
		private void btConfig_Click(object sender, RoutedEventArgs e) => ToolHelper(sender as Button, ConfigCur);
	}
}
