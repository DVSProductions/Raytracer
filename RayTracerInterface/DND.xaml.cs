using System;
using System.IO;
using System.Windows;
using System.Windows.Controls;

namespace RayTracerInterface {
	/// <summary>
	/// Interaktionslogik für DND.xaml
	/// </summary>
	public partial class DND : Page {
		Action onComplete;
		public DND(Action onComplete) {
			InitializeComponent();
			this.onComplete = onComplete;
		}

		string FlattenArray(string[] arr) {
			var ret = "(";
			foreach(var e in arr) ret += e + ", ";
			return ret.TrimEnd(new[] { ',', ' ' }) + ")";
		}
		private void Grid_Drop(object sender, DragEventArgs e) {
			var a = e.Data.GetData("FileNameW") as string[];
			if(a.Length != 1) {
				MessageBox.Show("This Application requires ONE .dll");
				return;
			}
			var path = a[0];
			var ext = Path.GetExtension(path).ToLower();
			if(ext != ".dll") {
				MessageBox.Show("Please Drag&Drop the Renderer dll", "Error");
				return;
			}
			if(LibraryHandler.TryLoadLib(path))
			onComplete();
		}

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
			if(dlg.ShowDialog() == true) {
				if(LibraryHandler.TryLoadLib(dlg.FileName))
					onComplete();
			}
		}
	}
}
