using System.Collections.Generic;
using System.Windows;
namespace RayTracerInterface {
	/// <summary>
	/// Interaction logic for ShapeSelector.xaml
	/// </summary>
	public partial class ShapeSelector : Window {
#pragma warning disable CA1051 // Sichtbare Instanzfelder nicht deklarieren
		public Renderable result = null;
		protected readonly List<string> shapes = new List<string>();
		protected LibraryHandler.SceneBasedRenderer sbr;
#pragma warning restore CA1051 // Sichtbare Instanzfelder nicht deklarieren
		public ShapeSelector(LibraryHandler.SceneBasedRenderer sbr) {
			this.WindowStartupLocation = WindowStartupLocation.CenterOwner;
			App.MakeMeDarkModal(this);
			this.sbr = sbr;
			InitializeComponent();
		}
		public void Init() {
			foreach (var cl in sbr.SuppportedClass)
				shapes.Add(cl.GetType().Name);
			btAdd.Click += Button_Click;
			this.lbshapes.ItemsSource = shapes;
		}
		private void Button_Click(object sender, RoutedEventArgs e) {
			if (lbshapes.SelectedIndex == -1) return;
			result = Renderable.ConvertIDToObject(sbr.SuppportedClass[lbshapes.SelectedIndex].TYPEID());
			DialogResult = true;
		}
	}
}
