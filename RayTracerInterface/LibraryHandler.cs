#pragma warning disable IDE1006 // Naming Styles
using System;
using System.Diagnostics;
using System.IO;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Threading;
using System.Windows;

namespace RayTracerInterface {
	/// <summary>
	/// This class contains the basic interface with a renderer DLL
	/// </summary>
	public static partial class LibraryHandler {
		public static bool IsLoaded { get; private set; } = false;
		/// <summary>
		/// Location of the local dll copy
		/// </summary>
		public const string dll = "intenalLib.dll";
		/// <summary>
		/// get library info string
		/// </summary>
		/// <returns></returns>
		[DllImport(dll, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
		[return: MarshalAs(UnmanagedType.BStr)]
		private static extern string LibInfo();
		/// <summary>
		/// Turns a errorCode into a string
		/// </summary>
		/// <param name="errorCode">lodePNG error</param>
		/// <returns></returns>
		[DllImport(dll, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
		[return: MarshalAs(UnmanagedType.BStr)]
		private static extern string LodeReturnDecode(int errorCode);
		/// <summary>
		/// Calls the DLL to receive a output DLL filename
		/// <para>
		///		Returns "_" when the given index is out of range
		/// </para>
		/// </summary>
		/// <param name="file">index in filename array</param>
		/// <returns>filename or "_" on error</returns>
		[DllImport(dll, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
		[return: MarshalAs(UnmanagedType.BStr)]
		private static extern string OutputFile(int file);

		/// <summary>
		/// Launches a render Job
		/// </summary>
		/// <param name="Option">File to render</param>
		/// <param name="x">width</param>
		/// <param name="y">height</param>
		/// <returns></returns>
		[DllImport(dll, CallingConvention = CallingConvention.Cdecl)]
		[return: MarshalAs(UnmanagedType.U1)]
		private static extern bool render(int Option, int x, int y);
		/// <summary>
		/// Returns the number of rendered columns
		/// </summary>
		/// <returns></returns>
		[DllImport(dll, CallingConvention = CallingConvention.Cdecl)]
		private static extern int status();
		/// <summary>
		/// gets the lodePNG return code
		/// </summary>
		/// <returns></returns>
		[DllImport(dll, CallingConvention = CallingConvention.Cdecl)]
		private static extern int returnValue();
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
		public static Renderer TryLoadLib(string path) {
			if (IsLoaded) Reboot(path);
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
				while (!File.Exists(dll)) Thread.Sleep(50);
				IsLoaded = true;
				string libStr = LibInfo();
				try {
					int libnum = (int)(double.Parse(libStr.Replace('.', ',')) * 10.0);//removes floating point errors
					if (libnum == 10)
						return new Renderer();
					else if (libnum == 20)
						return new SceneBasedRenderer();
					else if (libnum > 20 && libnum < 30)
						return new MaterialRenderer();
					else
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