#pragma warning disable IDE1006 // Naming Styles
using RayTracerInterface.Renderer;
using System;
using System.Diagnostics;
using System.Globalization;
using System.IO;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Threading;
using System.Windows;
namespace RayTracerInterface {
	/// <summary>
	/// This class contains the basic interface with a renderer DLL
	/// </summary>
	public static class LibraryHandler {
		public static bool IsLoaded { get; private set; } = false;
		/// <summary>
		/// Location of the local dll copy
		/// </summary>
		public const string dll = "intenalLib.dll";
		/// <summary>
		/// get library info string
		/// </summary>
		/// <returns></returns>
		[DllImport(dll, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
		[return: MarshalAs(UnmanagedType.BStr)]
		private static extern string LibInfo();
		public static string libInfo => LibInfo();
		/// <summary>
		/// Restarts the application in order to unload the old dll and then load in the new version
		/// </summary>
		/// <param name="p">path to new dll</param>
		private static void Reboot(string p) {
			Process.Start(Assembly.GetExecutingAssembly().Location, $"\"{p}\"");
			Environment.Exit(0);
		}
		/// <summary>
		/// Attempts to load the DLL at the given location
		/// </summary>
		/// <param name="path">Full path to DLL</param>
		/// <returns></returns>
		public static BasicRenderer TryLoadLib(string path) {
			if (IsLoaded)
				Reboot(path);
			try {
				if (File.Exists(dll)) {
					for (var n = 0; n < 10; n++) {
						try {
							File.Delete(dll);
							break;
						}
						catch {
							Thread.Sleep(200);
						}
					}
				}
				File.Copy(path, dll);
				while (!File.Exists(dll))
					Thread.Sleep(50);
				IsLoaded = true;
				var libStr = LibInfo();
				try {
					var libnum = (uint)(double.Parse(libStr, CultureInfo.InvariantCulture) * 10.0);//removes floating point errors
					return libnum == 10 ? new BasicRenderer(libnum) :
						libnum == 20 ? new SceneBasedRenderer(libnum) :
						libnum > 20 && libnum < 30 ? new MaterialRenderer(libnum) :
						libnum == 30 ? new TransformableRenderer(libnum) :
						libnum > 31 && libnum < 40 ? new GraphableRenderer(libnum):
						throw new Exception("Unknown Lib");
				}
				catch {
#if TRACE  //Exploiting TRACE constant in project to switch between UI and Console errors
					Console.Error.WriteLine($"Incompatible Library Version \"{LibInfo()}\"");
#else
					MessageBox.Show($"Unknown Library Version \"{LibInfo()}\"", "Renderer Error", MessageBoxButton.OK, MessageBoxImage.Error);
#endif
					return null;
				}
			}
			catch (Exception ex) {
#if TRACE  //Exploiting TRACE constant in project to switch between UI and Console errors
				Console.Error.WriteLine(ex.Message);
#else
				MessageBox.Show(Environment.CurrentDirectory + "\n" + ex.Message);
#endif
				return null;
			}
		}
	}
}
#pragma warning restore IDE1006 // Naming Styles
