using System;
using System.Windows;
using System.Windows.Controls;

namespace RayTracerInterface {
	/// <summary>
	/// Interaktionslogik für CompilationSettings.xaml
	/// </summary>
	public partial class CompilationSettings : Page {
		Action<RenderPage> switchToRenderPage;
		double ratio = 16.0 / 9.0;
		public CompilationSettings(Action<RenderPage> switchToRenderPage) {
			InitializeComponent();
			foreach(var s in LibraryHandler.OutputFiles) {
				cbFiles.Items.Add(s);
			}
			this.switchToRenderPage = switchToRenderPage;
		}
		private void CheckBox_Click(object sender, RoutedEventArgs e) {
			if(sender is CheckBox cb && cb.IsChecked == true) {
				try {
					ratio = double.Parse(tbW.Text) / double.Parse(tbH.Text);
				}
				catch {
					cb.IsChecked = false;
				}
			}
		}
		private void TbW_KeyUp(object sender, System.Windows.Input.KeyEventArgs e) {
			if(cbLink.IsChecked == true && int.TryParse(tbW.Text, out var i))
				tbH.Text = ((int) (1 / ratio * i)).ToString();
		}

		private void TbH_KeyUp(object sender, System.Windows.Input.KeyEventArgs e) {
			if(cbLink.IsChecked == true && int.TryParse(tbH.Text, out var i))
				tbW.Text = ((int) (ratio * i)).ToString();
		}
		private void Button_Click(object sender, RoutedEventArgs e) {
			var idx = cbFiles.SelectedIndex;
			if(idx == -1) {
				MessageBox.Show("Please Select a Target File");
			}
			try {
				int w = int.Parse(tbW.Text), h = int.Parse(tbH.Text);
				LibraryHandler.render(idx, w, h).ToString();
				switchToRenderPage(new RenderPage(idx, w, h));
			}
			catch(Exception ex) {
				MessageBox.Show(ex.Message);
			}
		}
	}
}
