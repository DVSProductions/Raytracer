using System;
using System.IO;
using System.Reflection;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media.Imaging;

namespace RayTracerInterface {
	/// <summary>
	/// Interaktionslogik für RenderPage.xaml
	/// </summary>
	public partial class RenderPage : Page {
		int idx;
		public Action onBack;
		public RenderPage(int outputIDX, int width, int height) {
			idx = outputIDX;
			InitializeComponent();
			pbStatus.Maximum = width;
			pbStatus.Value = 0;
			wait();
		}
		async void wait() {
			while(pbStatus.Maximum != pbStatus.Value) {
				var s = LibraryHandler.status();
				pbStatus.Value = s;
				await Task.Delay(100);
			}
			pbStatus.IsIndeterminate = true;
			lbStatus.Content = "Exporting png";
			while(LibraryHandler.returnValue() == -1) await Task.Delay(250);
			pbStatus.IsIndeterminate = false;
			pbStatus.Visibility = Visibility.Hidden;
			if(LibraryHandler.returnValue() == 0) {
				iResults.Source = new BitmapImage(new System.Uri(Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location) + "\\" + LibraryHandler.OutputFiles[idx]));
				lbStatus.Visibility = Visibility.Hidden;
			}
			else {
				btExport.Visibility = Visibility.Hidden;
				lbStatus.Content = $"Image Compression failed\n{LibraryHandler.LodeReturnDecode(LibraryHandler.returnValue())}";
			}
		}

		private void btBack_Click(object sender, RoutedEventArgs e) =>onBack();

		private void btExport_Click(object sender, RoutedEventArgs e) => _ = System.Diagnostics.Process.Start("explorer", $"/select,\"{Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location) + "\\" + LibraryHandler.OutputFiles[idx]}\"");
	}
}
