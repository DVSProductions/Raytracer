using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace RayTracerInterface {
	/// <summary>
	/// Interaktionslogik für MainWindow.xaml
	/// </summary>
	public partial class MainWindow : Window {
		void OpenPage3(IRenderPage p) {
			pageViewer.Content = p;
			p.OnBack = () => pageViewer.GoBack();
		}
		void OpenPage2() => pageViewer.Content = new CompilationSettings(OpenPage3);
		void Preexecution() {
			var para = Environment.GetCommandLineArgs();
			if(para[0] != Assembly.GetExecutingAssembly().Location) {
				var s = "";
				foreach(var p in para) s += p + "\n";
				MessageBox.Show(s);
			}
			if(para.Length == 1) {
				if(para[0] == Assembly.GetExecutingAssembly().Location) return;
				LibraryHandler.TryLoadLib(para[0]);
			}
			else if(para.Length > 1 && para[0] == Assembly.GetExecutingAssembly().Location)
				LibraryHandler.TryLoadLib(para[1]);
		}
		public MainWindow() {
			Preexecution();
			InitializeComponent();
			if(LibraryHandler.isLoaded) OpenPage2();
			else
				pageViewer.Content = new DND(OpenPage2);
		}
	}
}
