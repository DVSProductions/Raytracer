using Microsoft.Win32;
using System;
using System.IO;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Interop;
namespace RayTracerInterface {
	/// <summary>
	/// Interaktionslogik für "App.xaml"
	/// </summary>
	public partial class App : Application {
		static bool hasDarkMode = false;
		[DllImport("WPFDarkMode.dll")]
#pragma warning disable IDE1006 // Naming Styles
		static extern void init();
		[DllImport("WPFDarkMode.dll")]
		private static extern void apply(IntPtr hwnd);
		[DllImport("WPFDarkMode.dll")]
		private static extern void halfApply(IntPtr hwnd);
		public static async void MakeMeDark(Window window) {
			if (window == null || !hasDarkMode) return;
			while (window.Visibility != Visibility.Visible) await Task.Delay(10);
			apply(new WindowInteropHelper(window).Handle);
		}
		public static async void MakeMeDarkModal(Window wnd) {
			if (wnd == null || !hasDarkMode) return;
			while (wnd.Visibility != Visibility.Visible) await Task.Delay(10);
			halfApply(new WindowInteropHelper(wnd).Handle);
			var orig = wnd.WindowStyle;
			wnd.WindowStyle = WindowStyle.None;
			if (orig == WindowStyle.None)
				wnd.WindowStyle = WindowStyle.SingleBorderWindow;
			wnd.WindowStyle = orig;
		}
		public const string Cleanup = "-cleanup";
		static void cleanup() {
			if (File.Exists(LibraryHandler.dll)) {
				try {
					File.Delete(LibraryHandler.dll);
				}
				catch {
					for (var n = 0; n < 100&&File.Exists(LibraryHandler.dll); n++) {
						Thread.Sleep(100);
						try {
							File.Delete(LibraryHandler.dll);
							break;
						}
						catch { }
					}
				}
			}
			Environment.Exit(0);
		}
		void Preexecution() {
			var para = Environment.GetCommandLineArgs();
			if (para.Length == 1) {
				if (para[0] == Assembly.GetExecutingAssembly().Location && para[0] == Cleanup)
					cleanup();
			}
			else if (para.Length > 1 && para[0] == Assembly.GetExecutingAssembly().Location && para[1] == Cleanup )
				cleanup();
		}
		public App() {
			Preexecution();
			try {				
				if (uint.Parse(Registry.GetValue(@"HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion", "ReleaseId", "0").ToString()) >= 1809) {
					hasDarkMode = true;
					init();
				}
			}
			catch { }
		}
	}
}
#pragma warning restore IDE1006 // Naming Styles
