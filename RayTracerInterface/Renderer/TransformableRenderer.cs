#pragma warning disable CA1822 // Member als statisch markieren
#pragma warning disable IDE1006 // Naming Styles
// Member als statisch markieren
using System.Collections.Generic;
using System.Runtime.InteropServices;
using RayTracerInterface;
namespace RayTracerInterface.Renderer {
	public class TransformableRenderer : MaterialRenderer {
		public TransformableRenderer(uint num) : base(num) { }
		[DllImport(LibraryHandler.dll, CallingConvention = CallingConvention.Cdecl)]
		static extern int GetSupportedTransformsAt(int idx);
		private List<int> suppTransformIDs;
		public List<int> SuppportedTransformsIDs => suppTransformIDs ?? loadTransformsIDs();
		private List<int> loadTransformsIDs() {
			suppTransformIDs = new List<int>();
			for (var n = 0; ; n++) {
				var s = GetSupportedTransformsAt(n);
				if (s == -1)
					break;
				suppTransformIDs.Add(s);
			}
			return suppTransformIDs;
		}

		/// <summary>
		/// Internal storage for dynamically created supportedTransforms list
		/// </summary>
		private List<ATransformation> suppTransform;
		public List<ATransformation> SuppportedTransforms => suppTransform ?? loadTransforms();
		private List<ATransformation> loadTransforms() {
			suppTransform = new List<ATransformation>();
			foreach (var id in SuppportedTransformsIDs)
				suppTransform.Add(ATransformation.ConvertIDToObject(id));
			return suppTransform;
		}
	}
}
#pragma warning restore IDE1006 // Naming Styles
#pragma warning restore CA1822 // Member als statisch markieren
// Member als statisch markieren
