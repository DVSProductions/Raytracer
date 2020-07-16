using System;
using System.Globalization;
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
		public Action GoBack { get; set; }
		readonly Renderer.BasicRenderer renderer;
		public CompilationSettings(Action<IRenderPage> switchToRenderPage, Renderer.BasicRenderer renderer) {
			System.Diagnostics.Contracts.Contract.Requires(renderer != null);
			this.renderer = renderer;
			InitializeComponent();
			foreach (var s in renderer.OutputFiles)
				cbFiles.Items.Add(s);
			if (cbFiles.Items.Count == 1)
				cbFiles.SelectedIndex = 0;
			gbScene.Visibility = renderer is Renderer.SceneBasedRenderer ? Visibility.Visible : Visibility.Collapsed;
			this.switchToRenderPage = switchToRenderPage;
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
					ratio = double.Parse(tbW.Text, CultureInfo.InvariantCulture) / double.Parse(tbH.Text, CultureInfo.InvariantCulture);
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
				if (renderer.Render(idx, w, h))
					switchToRenderPage(new RenderPage(renderer, idx, w));
				else
					MessageBox.Show("Returned False!");
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
				switchToRenderPage(new Abgabe(renderer, int.Parse(tbW.Text), int.Parse(tbH.Text)));
			}
			catch (Exception ex) {
				MessageBox.Show(ex.Message);
			}
		}
		private void Button_Click_2(object sender, RoutedEventArgs e) {
			if (renderer is Renderer.SceneBasedRenderer sbr)
				switchToRenderPage(new SceneBuilder(sbr, switchToRenderPage));
			else
				MessageBox.Show("ERROR THIS IS NOT A SCENE BASED RENDERER");
		}
		private void Button_Click_3(object sender, RoutedEventArgs e) => GoBack();

		private void Button_Click_4(object sender, RoutedEventArgs e) {
			var dlg = new Microsoft.Win32.OpenFileDialog {
				DefaultExt = "*.xml;",
				CheckFileExists = true,
				CheckPathExists = true,
				Multiselect = false,
				RestoreDirectory = true,
				DereferenceLinks = true,
				Title = "Please select the Scene Definition to Decompress",
				Filter = "Scene Definition Graph *.sdg|*.sdg"
			};
			if (dlg.ShowDialog() == true) {
				try {
					var fn = SceneGraph.DecompressFile(dlg.FileName);
					var oldf = new System.IO.FileInfo(dlg.FileName);
					var newf = new System.IO.FileInfo(fn);
					MessageBox.Show($"File Decompression ok!\nSaved {((int)(1000 - (oldf.Length / (double)newf.Length * 1000))) / 10.0}%", "Decompression Sucessfull", MessageBoxButton.OK, MessageBoxImage.Information);
				}
				catch (Exception ex) {
					MessageBox.Show(ex.Message, "Decompression Failed", MessageBoxButton.OK, MessageBoxImage.Error);
				}
			}
		}
	}
}
