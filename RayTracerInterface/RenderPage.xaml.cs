using System;
using System.IO;
using System.Reflection;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;

namespace RayTracerInterface {
	/// <summary>
	/// Interaktionslogik für RenderPage.xaml
	/// </summary>
	public partial class RenderPage : Page, IRenderPage {
		/// <summary>
		/// index of the outputFile
		/// </summary>
		readonly int idx;

		public Action OnBack { get; set; }

		public RenderPage(int outputIDX, int width, int height) {
			idx = outputIDX;
			InitializeComponent();
			pbStatus.Maximum = width;
			pbStatus.Value = 0;
			Wait();
		}
		/// <summary>
		/// Waits until the image has been rendered and then displays it
		/// <para>
		/// This functions reads the states reported by the DLL in order to display a graph on the render progress.
		/// After the image has been rendered sucessfully it will read the image from disk and show it in <see cref="iResults"/></para>
		/// </summary>
		async void Wait() {
			var sw=System.Diagnostics.Stopwatch.StartNew();
			while (pbStatus.Maximum != pbStatus.Value) {
				var s = LibraryHandler.status();
				pbStatus.Value = s;
				await Task.Delay(33);
			}
			sw.Stop();
			lbTime.Content = sw.ElapsedMilliseconds + "ms";
			pbStatus.IsIndeterminate = true;
			lbStatus.Content = "Exporting png";
			while(LibraryHandler.returnValue() == -1) await Task.Delay(100);
			pbStatus.IsIndeterminate = false;
			pbStatus.Visibility = Visibility.Hidden;
			btBack.Visibility = Visibility.Visible;
			if(LibraryHandler.returnValue() == 0) {
				iResults.Source = (BitmapSource)new ImageSourceConverter().ConvertFrom(File.ReadAllBytes(Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location) + "\\" + LibraryHandler.OutputFiles[idx]));
				lbStatus.Visibility = Visibility.Hidden;
			}
			else {
				btExport.Visibility = Visibility.Hidden;
				lbStatus.Content = $"Image Compression failed\n{LibraryHandler.LodeReturnDecode(LibraryHandler.returnValue())}";
			}
		}
		/// <summary>
		/// Calls the back function provided by <see cref="MainWindow"/>
		/// </summary>
		private void btBack_Click(object sender, RoutedEventArgs e) => OnBack();
		/// <summary>
		/// Opens a explorer instance highlighting the rendered file
		/// </summary>
		private void btExport_Click(object sender, RoutedEventArgs e) => _ = System.Diagnostics.Process.Start("explorer", $"/select,\"{Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location) + "\\" + LibraryHandler.OutputFiles[idx]}\"");
	}
}
