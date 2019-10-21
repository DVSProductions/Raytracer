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
		/// <summary>
		/// Allows the <see cref="CompilationSettings"/> page to open <see cref="IRenderPage"/> pages
		/// </summary>
		/// <param name="p">The page to open</param>
		void OpenPage3(IRenderPage p) {
			pageViewer.Content = p;
			p.OnBack = () => pageViewer.GoBack();
		}
		/// <summary>
		/// Allows the drag&drop page <see cref="DND"/> to open the next page
		/// </summary>
		void OpenPage2() => pageViewer.Content = new CompilationSettings(OpenPage3);
		/// <summary>
		/// Detects if this should immediatly open the <see cref="CompilationSettings"/> page based on the command line parameters
		/// <para>
		/// <see cref="LibraryHandler"/> will relaunch  the Application if required. When is does so, it will pass the name of the target DLL as a parameter.
		/// But depending on the execution environment the path to our executable might be the first parameter. To ignore this we check for such options.
		/// After checking all this this function will cause <see cref="LibraryHandler"/> to load the passed DLL.
		/// Since <see cref="LibraryHandler"/> remembers this, the <see cref="MainWindow()"/> constructor will detect that a library has been loaded and trigger the <see cref="CompilationSettings"/>
		/// Page instead of the <see cref="DND"/> page
		/// </para>
		/// </summary>
		void Preexecution() {
			var para = Environment.GetCommandLineArgs();
			if(para[0] != Assembly.GetExecutingAssembly().Location) {
				////For debugging purposes: List all command line parameters
				//var s = "";
				//foreach(var p in para) s += p + "\n";
				//MessageBox.Show(s);
			}
			if(para.Length == 1) {
				if(para[0] == Assembly.GetExecutingAssembly().Location) return;
				LibraryHandler.TryLoadLib(para[0]);
			}
			else if(para.Length > 1 && para[0] == Assembly.GetExecutingAssembly().Location)
				LibraryHandler.TryLoadLib(para[1]);
		}
		/// <summary>
		/// Creates the window and switches to the correct page
		/// </summary>
		public MainWindow() {
			Preexecution();
			InitializeComponent();
			if(LibraryHandler.isLoaded) OpenPage2();
			else
				pageViewer.Content = new DND(OpenPage2);
		}
	}
}
