using System;
using System.IO;
using System.Windows;
using System.Windows.Controls;
namespace RayTracerInterface {
	/// <summary>
	/// Interaktionslogik für DND.xaml
	/// </summary>
	public partial class DND : Page {
		/// <summary>
		/// Handler to <see cref="MainWindow"/> for switching to <see cref="CompilationSettings"/>
		/// </summary>
		readonly Action<LibraryHandler.Renderer> openNext;
		public DND(Action<LibraryHandler.Renderer> onComplete) {
			InitializeComponent();
			this.openNext = onComplete;
		}
		//string FlattenArray(string[] arr) {
		//	var ret = "(";
		//	foreach(var e in arr) ret += e + ", ";
		//	return ret.TrimEnd(new[] { ',', ' ' }) + ")";
		//}
		/// <summary>
		/// Handles Drag and drop events
		/// <para>
		/// if a proper file is given it will switch to the next page
		/// </para>
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void Grid_Drop(object sender, DragEventArgs e) {
			var a = e.Data.GetData("FileNameW") as string[];
			if (a.Length != 1) {
				MessageBox.Show("This Application requires ONE .dll");
				return;
			}
			var path = a[0];
			var ext = Path.GetExtension(path).ToLower();
			if (ext != ".dll") {
				MessageBox.Show("Please Drag&Drop the Renderer dll", "Error");
				return;
			}
			var rend = LibraryHandler.TryLoadLib(path);
			if (rend != null)
				openNext(rend);
			else MessageBox.Show("Could not load dll");
		}
		/// <summary>
		/// Shows filepicker Modal Dialog and opens library
		/// </summary>
		private void Button_Click(object sender, RoutedEventArgs e) {
			var dlg = new Microsoft.Win32.OpenFileDialog {
				DefaultExt = "*.dll;",
				CheckFileExists = true,
				CheckPathExists = true,
				Multiselect = false,
				RestoreDirectory = true,
				DereferenceLinks = true,
				Title = "Please select the renderer file",
				Filter = "Renderer *.dll|*.dll"
			};
			if (dlg.ShowDialog() == true) {
				var rend = LibraryHandler.TryLoadLib(dlg.FileName);
				if (rend != null)
					openNext(rend);
			}
		}
	}
}
