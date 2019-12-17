using System.Collections.Generic;
using System.Runtime.InteropServices;
namespace RayTracerInterface {
	public static partial class LibraryHandler {
		public class MaterialRenderer : SceneBasedRenderer {
			public MaterialRenderer(uint num):base(num) {	}
			[DllImport(dll, CallingConvention = CallingConvention.Cdecl)]
			static extern int getSupportedMaterialsAt(int idx);
			/// <summary>
			/// Internal storage for dynamically created supportedClasses list
			/// </summary>
			private List<int> suppmatIDs;
			/// <summary>
			/// Dynamically created list containing all the Object Types that our current DLL supports
			/// </summary>
			public List<int> SupportedMaterialIDs {
				get {
					if (suppmatIDs != null) return suppmatIDs;
					var n = 0;
					suppmatIDs = new List<int>();
					while (true) {
						var s = getSupportedMaterialsAt(n++);
						if (s == -1) break;
						suppmatIDs.Add(s);
					}
					return suppmatIDs;
				}
			}
			private List<AMaterial> suppmat;
			public List<AMaterial> SupportedMaterials {
				get {
					if (suppmat != null) return suppmat;
					suppmat = new List<AMaterial>();
					foreach (var id in SupportedMaterialIDs)
						suppmat.Add(AMaterial.ConvertIDToObject(id));
					return suppmat;
				}
			}
			[DllImport(dll, CallingConvention = CallingConvention.Cdecl)]
			static extern void Abort();
			public bool CanAbort => Libnum > 20;
			public void AbortRender() {
				if (CanAbort) 
					Abort();
			}
		}
	}
}
