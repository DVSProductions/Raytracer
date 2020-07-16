using System;
using System.IO;
using System.Reflection;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;
namespace RayTracerInterface {
	public partial class SceneBuilder : Page, IRenderPage {
		DateTime lastChange = DateTime.Now;
		/// <summary>
		/// Informs the window that properties of shapes have been modified
		/// <para>
		///		Should trigger a re-render
		/// </para>
		/// </summary>
		void AlertChanges() {
			//if (pbrendering.Value < (pbrendering.Maximum / 2)) aborted = true;
#pragma warning disable IDE0022 // Ausdruckskörper für Methoden verwenden
			lastChange = DateTime.Now;//.AddSeconds(1);
#pragma warning restore IDE0022 // Ausdruckskörper für Methoden verwenden
		}
		string GetSceneString() {
			var scene = new Scene();
			foreach (var elem in Shapes)
				scene.objects.Add(elem as Renderable);
			return scene.Serialize();
		}
		bool rendering = false;
		bool aborted = false;
		static readonly double[] scales = { 0.01, 0.02, 0.04, 0.08, 0.25, 0.40, 0.5, 1 };
		//static readonly int[] WaitTime = {   100,  100,  200,  500, 1000, 3000, 20000, 0 };
		async Task DoRender(double scale) {
			if (!int.TryParse(tbW.Text, out var i_w) || !int.TryParse(tbH.Text, out var i_h)) return;
			lbScale.Content = $"{scale}x";
			var w = (int)(i_w * scale);
			var h = (int)(i_h * scale);
			pbrendering.Maximum = w;
			pbrendering.Value = 0;
			sbr.SetScene(GetSceneString());
			sbr.SetCamera(Camera.SerializeThis(cam));
			//return;
			rendering = true;
			sbr.StartPreviewRender(w, h);
			while (pbrendering.Value != w && !aborted) {
				pbrendering.Value = sbr.Status;
				await Task.Delay(1000 / 60);
			}
			while (sbr.ReturnCode == -1 && !aborted) await Task.Delay(1000 / 60);
			if (aborted) {
				pbrendering.Value = 0;
				rendering = false;
				return;
			}
			var file = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location) + "\\" + sbr.SceneFile;
			while (!File.Exists(file)) await Task.Delay(10);
			rendering = false;
			iResults.Source = (BitmapSource)new ImageSourceConverter().ConvertFrom(File.ReadAllBytes(file));
		}
		async Task<DateTime> RenderRepeater() {
			var start = lastChange;
			if (Shapes.Count == 0) return start;
			for (var n = 0; n < scales.Length && lastChange == start; n++) {
				//var s = System.Diagnostics.Stopwatch.StartNew();
				await DoRender(scales[n]);
				if (aborted) {
					aborted = false;
					return DateTime.Now;
				}
				//s.Stop();
				//var t = DateTime.Now + s.Elapsed;
				//while (t > DateTime.Now && lastChange == start) await Task.Delay(100);
			}
			return start;
		}
		async void RenderLoop() {
			while (Visibility != Visibility.Visible) await Task.Delay(500);
			sbr.Initialize3D();
			var last = DateTime.MinValue;
			while (Visibility == Visibility.Visible) {
				if (cam == null) {
					await Task.Delay(1000);
					continue;
				}
				if (lastChange > last)
					 last = await RenderRepeater();
				await Task.Delay(100);
			}
		}
	}
}
