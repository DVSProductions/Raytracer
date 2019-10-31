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
		static void TestOnce(LibraryHandler.Renderer rend ) {
			int scaling = 1;
			rend.Render(0, 16*scaling, 9 * scaling);
			Console.WriteLine("Rendering");
			while(true) {
				//Console.WriteLine("\r" + LibraryHandler.status());
				Thread.Sleep(200);
			}
		}
		static void TestTwice(LibraryHandler.Renderer rend) {
			int x = 16, y = 9;
			rend.Render(1, x, y);
			Console.WriteLine("Rendering");
			while(rend.Status != x) {
				Console.WriteLine("\r" + rend.Status);
				Thread.Sleep(200);
			}
			Thread.Sleep(200);
			Console.WriteLine("Redoing...");
			Thread.Sleep(200);
			rend.Render(1, x, y);
			Console.WriteLine("Rendering");
			Thread.Sleep(200);
			while(rend.Status != x) {
				Console.WriteLine("\r" + rend.Status);
				Thread.Sleep(200);
			}
			Console.WriteLine("Done");
		}
		
		static void Main() {
			//var rend=LibraryHandler.TryLoadLib(@"..\..\..\x64\Release\Aufgabe3.dll");
			//TestOnce(rend);
			init();
			apply(Process.GetCurrentProcess().MainWindowHandle);
			while (true) Thread.Sleep(999);
		}
	}
}
