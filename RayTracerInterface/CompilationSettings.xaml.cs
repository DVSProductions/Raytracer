using System;
using System.Windows;
using System.Windows.Controls;

namespace RayTracerInterface {
	/// <summary>
	/// Interaktionslogik für CompilationSettings.xaml
	/// </summary>
	public partial class CompilationSettings : Page {
		/// <summary>
		/// Handler to <see cref="MainWindow"/> for opening a render page
		/// </summary>
		readonly Action<IRenderPage> switchToRenderPage;
		/// <summary>
		/// Aspect ratio to keep while the box is checked
		/// </summary>
		double ratio = 16.0 / 9.0;

		public CompilationSettings(Action<IRenderPage> switchToRenderPage) {
			InitializeComponent();
			foreach (var s in LibraryHandler.OutputFiles)
				cbFiles.Items.Add(s);
			this.switchToRenderPage = switchToRenderPage;
		}
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
		/// <summary>
		/// Render button click. Starts renderer
		/// </summary>
		private void Button_Click(object sender, RoutedEventArgs e) {
			var idx = cbFiles.SelectedIndex;
			if (idx == -1) {
				MessageBox.Show("Please Select a Target File");
				return;
			}
			try {
				int w = int.Parse(tbW.Text), h = int.Parse(tbH.Text);
				if (LibraryHandler.render(idx, w, h))
					switchToRenderPage(new RenderPage(idx, w, h));
			}
			catch (Exception ex) {
				MessageBox.Show(ex.Message);
			}
		}
		/// <summary>
		/// Abgabe modus. Opens Abgabe page with required parameters
		/// </summary>
		private void Button_Click_1(object sender, RoutedEventArgs e) {
			try {
				switchToRenderPage(new Abgabe(int.Parse(tbW.Text), int.Parse(tbH.Text)));
			}
			catch (Exception ex) {
				MessageBox.Show(ex.Message);
			}
		}
	}
}
