using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Windows;

namespace RayTracerInterface {
	class LibraryHandler {
		public static bool isLoaded = false;
		public const string dll = "intenalLib.dll";
		[DllImport(dll, CallingConvention = CallingConvention.Cdecl)]
		[return: MarshalAs(UnmanagedType.BStr)]
		private static extern string LibInfo();
		[DllImport(dll, CallingConvention = CallingConvention.Cdecl)]
		[return: MarshalAs(UnmanagedType.BStr)]
		public static extern string LodeReturnDecode(int Option);
		public static string LibraryInfo => LibInfo();
		private static void Reboot(string p) {
			Process.Start(Assembly.GetExecutingAssembly().Location, $"\"{p}\"");
			Environment.Exit(0);
		}
		public static bool TryLoadLib(string path) {
			if(isLoaded) Reboot(path);
			try {
				if(File.Exists(dll)) {
					for(var n = 0; n < 10; n++) {
						try {
							File.Delete(dll);
							break;
						}
						catch {
							System.Threading.Thread.Sleep(200);
						}
					}
				}
				File.Copy(path, dll);
				isLoaded = true;
				Console.WriteLine(LibraryInfo);
				return true;
			}
			catch(Exception ex) {
				Console.Error.WriteLine(ex.Message);
				return false;
			}
		}
		[DllImport(dll, CallingConvention = CallingConvention.Cdecl)]
		[return: MarshalAs(UnmanagedType.BStr)]
		private static extern string OutputFile(int file);
		private static List<string> outfiles;
		public static List<string> OutputFiles {
			get {
				if(outfiles != null) return outfiles;
				var n = 0;
				outfiles = new List<string>();
				while(true) {
					var s = OutputFile(n++);
					if(s == "_") break;
					outfiles.Add(s);
				}
				return outfiles;
			}
		}
		[DllImport(dll, CallingConvention = CallingConvention.Cdecl)]
		public static extern bool render(int Option, int x, int y);
		[DllImport(dll, CallingConvention = CallingConvention.Cdecl)]
		public static extern int status();
		[DllImport(dll, CallingConvention = CallingConvention.Cdecl)]
		public static extern int returnValue();

		

	}
}
