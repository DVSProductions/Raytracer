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
			while(LibraryHandler.returnValue() == -1) await Task.Delay(250);
			pbStatus.IsIndeterminate = false;
			if(LibraryHandler.returnValue() == 0) {
				pbStatus.Visibility = Visibility.Hidden;
				iResults.Source = new BitmapImage(new System.Uri(Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location) + "\\" + LibraryHandler.OutputFiles[idx]));
			}
			else {
				MessageBox.Show($"Image Compression failed: {LibraryHandler.LodeReturnDecode(LibraryHandler.returnValue())}", "Compression Error");
			}
		}
	}
}
