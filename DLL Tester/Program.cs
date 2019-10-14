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
		static void Main(string[] args) {
			LibraryHandler.TryLoadLib("C:\\Users\\DVSProductions\\OneDrive\\Uni\\Medieninformatik\\Semester 3\\Computergrafik Grundlagen\\Aufgabe1\\x64\\Release\\Renderer1.dll");
			LibraryHandler.render(0, 16000, 9000);
			Console.WriteLine("Rendering");
			while(true) {
				Console.WriteLine("\r"+LibraryHandler.status());
				Thread.Sleep(200);
			}
		}
	}
}
