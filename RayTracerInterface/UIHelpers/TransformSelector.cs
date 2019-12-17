using System.Windows;
namespace RayTracerInterface {
	class TransformSelector : ShapeSelector {
		public new ATransformation result = null;
		public TransformSelector(LibraryHandler.TransformableRenderer sbr) : base(sbr) => Title = "TransformSelector";
		public new void Init() {
			foreach (var mats in (sbr as LibraryHandler.TransformableRenderer).SuppportedTransforms)
				shapes.Add(mats.GetType().Name);
			lbshapes.ItemsSource = shapes;
			btAdd.Click += Button_Click;
		}
		private void Button_Click(object sender, RoutedEventArgs e) {
			if (lbshapes.SelectedIndex == -1) return;
			result = ATransformation.ConvertIDToObject((sbr as LibraryHandler.TransformableRenderer).SuppportedTransforms[lbshapes.SelectedIndex].TYPEID());
			DialogResult = true;
		}
	}
}
