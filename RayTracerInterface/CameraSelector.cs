using System.Windows;

namespace RayTracerInterface {
	class CameraSelector : ShapeSelector {
		public new Camera result = null;
		public CameraSelector(LibraryHandler.SceneBasedRenderer sbr) : base(sbr) => Title = "CameraSelector";
		public new void Init() {
			foreach (var cams in sbr.SupportedCams)
				shapes.Add(cams.GetType().Name);
			lbshapes.ItemsSource = shapes;
			btAdd.Click += Button_Click;
		}
		private void Button_Click(object sender, RoutedEventArgs e) {
			if (lbshapes.SelectedIndex == -1) return;
			result = Camera.ConvertIDToObject(sbr.SupportedCams[lbshapes.SelectedIndex].TYPEID());
			DialogResult = true;
		}
	}
}
