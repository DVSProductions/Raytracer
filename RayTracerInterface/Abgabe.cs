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
		public Abgabe(int w, int h) {
			InitializeComponent();
			render(w, h);
		}
		async void render(int w, int h) {
			var target = System.IO.Path.GetFullPath("..\\..\\..\\doc\\");
			if(!Directory.Exists(target)) Directory.CreateDirectory(target);
			for(int n = 0; n < LibraryHandler.OutputFiles.Count; n++) {
				LibraryHandler.render(n, w, h);
				tbConsole.Text += $"Rendering {LibraryHandler.OutputFiles[n]}...\n";
				int s = 0;
				while(w != s) {
					s = LibraryHandler.status();
					await Task.Delay(33);
				}
				tbConsole.Text += "Exporting png\n";
				while(LibraryHandler.returnValue() == -1) await Task.Delay(100);
				tbConsole.Text += "Moving to Output\n";
				var tfile = target + LibraryHandler.OutputFiles[n];
				if(File.Exists(tfile)) File.Delete(tfile);
				File.Move(LibraryHandler.OutputFiles[n], target + LibraryHandler.OutputFiles[n]);
			}
			tbConsole.Text += $"Abgabe complete.\nResults in {System.IO.Path.GetFullPath(target)}\n";
		}
		Action onBack;
		public Action OnBack { get => onBack; set => onBack = value; }

		private void Button_Click(object sender, RoutedEventArgs e) => 
			_ = System.Diagnostics.Process.Start("explorer", $"\"{System.IO.Path.GetFullPath("..\\..\\..\\doc\\")}\"");

		private void Button_Click_1(object sender, RoutedEventArgs e) => onBack();
	}
}
