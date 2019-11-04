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
#pragma warning disable CA1051 // Sichtbare Instanzfelder nicht deklarieren
		public Renderable result = null;
		protected readonly List<string> shapes = new List<string>();
		protected LibraryHandler.SceneBasedRenderer sbr;
#pragma warning restore CA1051 // Sichtbare Instanzfelder nicht deklarieren
		public ShapeSelector(LibraryHandler.SceneBasedRenderer sbr) {			
			App.makeMeDarkModal(this);
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
			result = Renderable.convertIDToObject(sbr.SuppportedClass[lbshapes.SelectedIndex].TYPEID());
			DialogResult = true;
		}
	}
}
