using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using RayTracerInterface;
namespace DLL_Tester {
	class Program {
		[DllImport("WPFDarkMode.dll")]
		static extern void init();
		[DllImport("WPFDarkMode.dll")]
		private static extern void apply(IntPtr hwnd);
		static void TestOnce(LibraryHandler.Renderer rend) {
			int scaling = 1;
			rend.Render(0, 16 * scaling, 9 * scaling);
			Console.WriteLine("Rendering");
			while (true) {
				Console.WriteLine("\r" + rend.Status);
				Thread.Sleep(200);
			}
		}
		static void TestTwice(LibraryHandler.Renderer rend) {
			int x = 16, y = 9;
			rend.Render(1, x, y);
			Console.WriteLine("Rendering");
			while (rend.Status != x) {
				Console.WriteLine("\r" + rend.Status);
				Thread.Sleep(200);
			}
			Thread.Sleep(200);
			Console.WriteLine("Redoing...");
			Thread.Sleep(200);
			rend.Render(1, x, y);
			Console.WriteLine("Rendering");
			Thread.Sleep(200);
			while (rend.Status != x) {
				Console.WriteLine("" + rend.Status);
				Thread.Sleep(200);
			}
			Console.WriteLine("Done");
		}
		void testDarkMode() {
			init();
			apply(Process.GetCurrentProcess().MainWindowHandle);
		}
		static void testV3(LibraryHandler.SceneBasedRenderer sbr) {
			sbr.Initialize3d();
			var scene = new Scene() {
				objects ={
					new Sphere() {
						Color = new Color(1.0, 0.0, 0.0),
						Radius=1,
						Position=new Vec(0,0,-1.5)
					},
					new Sphere() {
						Color = new Color(0.0, 0.0, 1.0),
						Radius=0.5,
						Position=new Vec(1,0,-1.5)
					}
				}
			};
			var ser = scene.Serialize();
			sbr.SetScene(ser);
			ser = Camera.SerializeThis(new PinholeCamera() {
				angle = Math.PI / 2,
				Position = new Vec(0, 0, 0),
				background = new Color(0.5, 0.5, 0.5)
			});
			sbr.SetCamera(ser);
			int width = 16 * 1;
			int height = 9 * 1;
			sbr.StartPreviewRender(width, height);
			while (sbr.Status != width) {
				//Console.WriteLine(sbr.Status);
				Task.Delay(250);
			}
			Console.WriteLine(sbr.SceneFile);
		}
		static void Main() {
			var rend = LibraryHandler.TryLoadLib(@"..\..\..\x64\Release\Aufgabe4.dll");
			//TestOnce(rend);
			testV3(rend as LibraryHandler.SceneBasedRenderer);
			while (true) Thread.Sleep(999);
		}
	}
}
