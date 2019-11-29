using System.Windows;
using System.Windows.Controls;

namespace RayTracerInterface {
	public class ShapeTemplateSelector : DataTemplateSelector {
		public DataTemplate GroupTemplate { get; set; }

		public ShapeTemplateSelector(DataTemplate @default, DataTemplate groupTemplate) {
			this.GroupTemplate = groupTemplate;
			DefaultTemplate = @default;

		}

		public DataTemplate DefaultTemplate { get; set; }

		public override DataTemplate SelectTemplate(object item, DependencyObject container) => item is Group ? GroupTemplate : DefaultTemplate;
	}
}
