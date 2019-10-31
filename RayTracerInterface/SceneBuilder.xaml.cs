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
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace RayTracerInterface {
	/// <summary>
	/// Interaktionslogik für SceneBuilder.xaml
	/// </summary>
	public partial class SceneBuilder : Page, IRenderPage {
		LibraryHandler.SceneBasedRenderer renderer;
		Action<IRenderPage> OnRender;
		public SceneBuilder(LibraryHandler.SceneBasedRenderer renderer, Action<IRenderPage> moveToRenderer) {
			this.renderer = renderer;
			OnRender = moveToRenderer;
			InitializeComponent();
		}
		/// <summary>
		/// Aspect ratio to keep while the box is checked
		/// </summary>
		double ratio = 16.0 / 9.0;
		/// <summary>
		/// Stores aspect ratio or unchecks itself if one of the given values is invalid
		/// </summary>
		private void CheckBox_Click(object sender, RoutedEventArgs e) {
			if (sender is CheckBox cb && cb.IsChecked == true) {
				try {
					ratio = double.Parse(tbW.Text) / double.Parse(tbH.Text);
				}
				catch {
					cb.IsChecked = false;
				}
			}
		}
		/// <summary>
		/// Handler for applying the set aspect ratio while entering numbers
		/// </summary>
		private void TbW_KeyUp(object sender, System.Windows.Input.KeyEventArgs e) {
			if (cbLink.IsChecked == true && int.TryParse(tbW.Text, out var i))
				tbH.Text = ((int)(1 / ratio * i)).ToString();
		}
		/// <summary>
		/// Handler for applying the set aspect ratio while entering numbers
		/// </summary>
		private void TbH_KeyUp(object sender, System.Windows.Input.KeyEventArgs e) {
			if (cbLink.IsChecked == true && int.TryParse(tbH.Text, out var i))
				tbW.Text = ((int)(ratio * i)).ToString();
		}
		public Action OnBack { get; set; }
		private void Button_Click(object sender, RoutedEventArgs e) {
			var Selector = new ShapeSelector(this.renderer);
			if (Selector.ShowDialog() == true) {

			}

		}
	}
}
