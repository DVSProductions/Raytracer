using System.Windows;
namespace RayTracerInterface {
	class MaterialSelector : ShapeSelector {
		public new AMaterial result = null;
		public MaterialSelector(LibraryHandler.MaterialRenderer sbr) : base(sbr) => Title = "MaterialSelector";
		public new void Init() {
			foreach (var mats in (sbr as LibraryHandler.MaterialRenderer).SupportedMaterials)
				shapes.Add(mats.GetType().Name);
			lbshapes.ItemsSource = shapes;
			btAdd.Click += Button_Click;
		}
		private void Button_Click(object sender, RoutedEventArgs e) {
			if (lbshapes.SelectedIndex == -1) return;
			result = AMaterial.ConvertIDToObject((sbr as LibraryHandler.MaterialRenderer).SupportedMaterials[lbshapes.SelectedIndex].TYPEID());
			DialogResult = true;
		}
	}
}
