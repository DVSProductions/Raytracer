﻿using System;
using System.Diagnostics;
using System.IO;
using System.Reflection;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;

namespace RayTracerInterface {
	public partial class RenderPage : Page, IRenderPage {
		/// <summary>
		/// index of the outputFile
		/// </summary>
		public string ofile;

		public Action OnBack { get; set; }

		readonly LibraryHandler.Renderer renderer;
		public RenderPage(LibraryHandler.Renderer rend, int outputIdx, int width) {
			renderer = rend;
			InitializeComponent();
			pbStatus.Maximum = width;
			pbStatus.Value = 0;
			if (outputIdx != -1) 
				ofile = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location) + "\\" + renderer.OutputFiles[outputIdx];
			Wait();
			ShowEstimation();
		}
		int s = 0;
		Stopwatch sw;
		async void ShowEstimation() {
			long max = (int)pbStatus.Maximum;
			while (pbStatus.Maximum != pbStatus.Value) {
				if (s != 0) {
					var ts = new TimeSpan(sw.ElapsedTicks / s * (max - s));
					lbEstimation.Content = $"{ts.Hours:00}:{ts.Minutes:00}:{ts.Seconds:00} Remaining";
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
			sw = Stopwatch.StartNew();
			while (pbStatus.Maximum != pbStatus.Value) {
				s = renderer.Status;
				pbStatus.Value = s;
				await Task.Delay(33);
			}
			sw.Stop();
			lbTime.Content = sw.ElapsedMilliseconds + "ms";
			pbStatus.IsIndeterminate = true;
			lbStatus.Content = "Exporting png";
			lbEstimation.Visibility = Visibility.Hidden;
			while (renderer.ReturnCode == -1) await Task.Delay(100);
			pbStatus.IsIndeterminate = false;
			pbStatus.Visibility = Visibility.Hidden;
			btBack.Visibility = Visibility.Visible;
			if (renderer.ReturnCode == 0) {
				iResults.Source = (BitmapSource)new ImageSourceConverter().ConvertFrom(File.ReadAllBytes(ofile));
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
		private void btBack_Click(object sender, RoutedEventArgs e) => OnBack();
		/// <summary>
		/// Opens a explorer instance highlighting the rendered file
		/// </summary>
		private void btExport_Click(object sender, RoutedEventArgs e) => _ = Process.Start("explorer", $"/select,\"{ofile}\"");
	}
}
