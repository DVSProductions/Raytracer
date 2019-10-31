using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace RayTracerInterface {
	/// <summary>
	/// Interaction logic for ShapeSelector.xaml
	/// </summary>
	public partial class ShapeSelector : Window {
		Renderable result=null;
		List<string> shapes = new List<string>{ "Sphere", "Yo mama", "Test" };
		public ShapeSelector(LibraryHandler.SceneBasedRenderer sbr) {
			App.makeMeDarkModal(this);
			InitializeComponent();
			this.lbshapes.ItemsSource = shapes;
		}

		private void Button_Click(object sender, RoutedEventArgs e) {
			
			DialogResult = true;
		}
	}
}
