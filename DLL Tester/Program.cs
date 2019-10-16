using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using RayTracerInterface;
namespace DLL_Tester {
	class Program {
		static void TestOnce() {
			int scaling = 1;
			LibraryHandler.render(0, 16*scaling, 9 * scaling);
			Console.WriteLine("Rendering");
			while(true) {
				//Console.WriteLine("\r" + LibraryHandler.status());
				Thread.Sleep(200);
			}
		}
		static void TestTwice() {
			int x = 16, y = 9;
			LibraryHandler.render(1, x, y);
			Console.WriteLine("Rendering");
			while(LibraryHandler.status() != x) {
				Console.WriteLine("\r" + LibraryHandler.status());
				Thread.Sleep(200);
			}
			Thread.Sleep(200);
			Console.WriteLine("Redoing...");
			Thread.Sleep(200);
			LibraryHandler.render(1, x, y);
			Console.WriteLine("Rendering");
			Thread.Sleep(200);
			while(LibraryHandler.status() != x) {
				Console.WriteLine("\r" + LibraryHandler.status());
				Thread.Sleep(200);
			}
			Console.WriteLine("Done");
		}
		static void Main(string[] args) {
			LibraryHandler.TryLoadLib(@"..\..\..\x64\Release\Aufgabe2.dll");
			TestOnce();
		}
	}
}
