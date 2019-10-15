using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Threading.Tasks;
using System.Windows;

namespace RayTracerInterface {
	/// <summary>
	/// Interaktionslogik für "App.xaml"
	/// </summary>
	public partial class App : Application {
		public App() {
			//if(File.Exists(LibraryHandler.dll)) File.Delete(LibraryHandler.dll);
		}
	}
}
