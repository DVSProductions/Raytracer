using System;
using System.Runtime.InteropServices;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Interop;

namespace RayTracerInterface {
	/// <summary>
	/// Interaktionslogik für "App.xaml"
	/// </summary>
	public partial class App : Application {
		[DllImport("WPFDarkMode.dll")]
		static extern void init();
		[DllImport("WPFDarkMode.dll")]
		private static extern void apply(IntPtr hwnd);
  [DllImport("WPFDarkMode.dll")]
		private static extern void halfApply(IntPtr hwnd);
		public static async void makeMeDark(Window w) {
			if (w == null) return;
			while (w.Visibility != Visibility.Visible) await Task.Delay(10);
			apply(new WindowInteropHelper(w).Handle);
		}
		public static async void makeMeDarkModal(Window w) {
			if (w == null) return;
			while (w.Visibility != Visibility.Visible) await Task.Delay(10);
			halfApply(new WindowInteropHelper(w).Handle);
			w.Visibility = Visibility.Hidden;
			w.Visibility = Visibility.Visible;
		}
		public App() {
			init();
			//if(File.Exists(LibraryHandler.dll)) File.Delete(LibraryHandler.dll);
		}
	}
}
