using System;
using System.Windows;
namespace RayTracerInterface {
	class VisualStorage : FrameworkElement {
		public static readonly DependencyProperty StorageProperty =
			DependencyProperty.Register("Storage", typeof(object), typeof(VisualStorage),
			new FrameworkPropertyMetadata(null));
		/// <summary>
		/// Gets or sets the Content.
		/// </summary>
		/// <value>The Content.</value>
		public object Storage {
			get => GetValue(StorageProperty);
			set => SetValue(StorageProperty, value);
		}
		protected override void OnInitialized(EventArgs e) => base.OnInitialized(e);
	}
	class VisualStorage<T> : FrameworkElement where T : class {
		public static readonly DependencyProperty StorageProperty =
			DependencyProperty.Register("Storage", typeof(T), typeof(VisualStorage),
			new FrameworkPropertyMetadata(null));
		/// <summary>
		/// Gets or sets the Content.
		/// </summary>
		/// <value>The Content.</value>
		public T Storage {
			get => GetValue(StorageProperty) as T;
			set => SetValue(StorageProperty, value);
		}
		protected override void OnInitialized(EventArgs e) => base.OnInitialized(e);
	}
}
