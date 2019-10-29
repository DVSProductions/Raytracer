using System;
using System.IO;

using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Shapes;

namespace RayTracerInterface {
	/// <summary>
	/// Interaction logic for Abgabe.xaml
	/// </summary>
	public partial class Abgabe : Page, IRenderPage {
		readonly LibraryHandler.Renderer lib;
		public Abgabe(LibraryHandler.Renderer rend,int width, int height) {
			lib = rend;
			InitializeComponent();
			render(width, height);
		}
		/// <summary>
		/// Finds all files in the Render DLL and renders them to the Abgabe directory
		/// </summary>
		/// <param name="w">width of all images</param>
		/// <param name="h">height of all images</param>
		async void render(int w, int h) {
			var target = System.IO.Path.GetFullPath("..\\..\\..\\doc\\");
			if(!Directory.Exists(target)) Directory.CreateDirectory(target);
			for(int n = 0; n < lib.OutputFiles.Count; n++) {
				lib.Render(n, w, h);
				tbConsole.Text += $"Rendering {lib.OutputFiles[n]}...\n";
				while(w != lib.Status) 
					await Task.Delay(33);
				tbConsole.Text += "Exporting png\n";
				while(lib.ReturnCode == -1) await Task.Delay(100);
				tbConsole.Text += "Moving to Output\n";
				var tfile = target + lib.OutputFiles[n];
				if(File.Exists(tfile)) File.Delete(tfile);
				File.Move(lib.OutputFiles[n], target + lib.OutputFiles[n]);
			}
			tbConsole.Text += $"Abgabe complete.\nResults in {System.IO.Path.GetFullPath(target)}\n";
		}
		/// <summary>
		/// Used by mainWindow to allow a page to navigate back
		/// </summary>
		public Action OnBack { get; set; }
		/// <summary>
		/// Opens the Abgabe directory
		/// </summary>
		private void Button_Click(object sender, RoutedEventArgs e) => 
			_ = System.Diagnostics.Process.Start("explorer", $"\"{System.IO.Path.GetFullPath("..\\..\\..\\doc\\")}\"");
		/// <summary>
		/// Handler for the back button. Navigates back
		/// </summary>
		private void Button_Click_1(object sender, RoutedEventArgs e) => OnBack();
	}
}
