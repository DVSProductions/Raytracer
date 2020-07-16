using System;
using System.Diagnostics;
using System.Diagnostics.Contracts;
using System.IO;
using System.Reflection;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Effects;
using System.Windows.Media.Imaging;
namespace RayTracerInterface {
	public partial class RenderPage : Page, IRenderPage {
		/// <summary>
		/// index of the outputFile
		/// </summary>
		public string Ofile { get; set; }
		public Action OnBack { get; set; }
		readonly Renderer.BasicRenderer renderer;
		int s = 0;
		Stopwatch sw;
		void updateBlur() {
			var w = ActualWidth!=0 ? ActualWidth : 1000;
			var m = (Environment.ProcessorCount / pbStatus.Maximum) * w;
			pbStatus.Margin = new Thickness(-m);
			pbStatus.Effect = new BlurEffect() {
				Radius = m,
				KernelType = KernelType.Box,
				RenderingBias = RenderingBias.Quality
			};
		}
		public RenderPage(Renderer.BasicRenderer rend, int outputIndex, int width) {
			sw = Stopwatch.StartNew();
			Contract.Requires(rend != null);
			renderer = rend;
			InitializeComponent();
			pbStatus.Maximum = width;
			pbStatus.Value = 0;
			updateBlur();
			if (outputIndex != -1)
				Ofile = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location) + "\\" + renderer.OutputFiles[outputIndex];
			if (renderer is Renderer.MaterialRenderer r && r.CanAbort)
				btAbort.Visibility = Visibility.Visible;
			Wait();
			SizeChanged += (_, __) => updateBlur();
			ShowEstimation();
		}
		static string TsToString(TimeSpan ts) => $"{(ts.Days != 0 ? $"{ts.Days} " : " ")}{ts.Hours:00}:{ts.Minutes:00}:{ts.Seconds:00}";
		async void ShowEstimation() {
			var max = (long)pbStatus.Maximum;
			while (pbStatus.Maximum != pbStatus.Value) {
				if (s != 0) {
					var swT = sw.Elapsed;
					lbTotal.Content = TsToString(swT);
					lbEstimation.Content = TsToString(new TimeSpan(swT.Ticks / s * (max - s)));
				}
				await Task.Delay(1000);
			}
		}
		/// <summary>
		/// Waits until the image has been rendered and then displays it
		/// <para>
		/// This functions reads the states reported by the DLL in order to display a graph on the render progress.
		/// After the image has been rendered successfully it will read the image from disk and show it in <see cref="iResults"/></para>
		/// </summary>
		async void Wait() {			
			while (pbStatus.Maximum != pbStatus.Value) {				
				pbStatus.Value = s = renderer.Status;
				await Task.Delay(33);
			}
			sw.Stop();
			lbTime.Content = sw.Elapsed.TotalSeconds >= 100 ? TsToString(sw.Elapsed) : (sw.ElapsedMilliseconds + "ms");
			pbStatus.IsIndeterminate = true;
			lbStatus.Content = "Exporting png";
			spTime.Visibility = Visibility.Collapsed;
			while (renderer.ReturnCode == -1) await Task.Delay(100);
			pbStatus.IsIndeterminate = false;
			pbStatus.Visibility = Visibility.Hidden;
			btBack.Visibility = Visibility.Visible;
			btAbort.Visibility = Visibility.Hidden;
			if (renderer.ReturnCode == 0) {
				iResults.Source = (BitmapSource)new ImageSourceConverter().ConvertFrom(File.ReadAllBytes(Ofile));
				lbStatus.Visibility = Visibility.Hidden;
				btExport.Visibility = Visibility.Visible;
				lbTime.Visibility = Visibility.Visible;
			}
			else {
				btExport.Visibility = Visibility.Hidden;
				lbStatus.Content = $"Image Compression failed\n{renderer.ReturnString}";
			}
		}
		/// <summary>
		/// Calls the back function provided by <see cref="MainWindow"/>
		/// </summary>
		private void BtBack_Click(object sender, RoutedEventArgs e) => OnBack();
		/// <summary>
		/// Opens a explorer instance highlighting the rendered file
		/// </summary>
		private void BtExport_Click(object sender, RoutedEventArgs e) => _ = Process.Start("explorer", $"/select,\"{Ofile}\"");
		private void btAbort_Click(object sender, RoutedEventArgs e) {
			if (renderer is Renderer.MaterialRenderer mr && mr.CanAbort) {
				mr.AbortRender();
				OnBack();
			}
		}
	}
}
