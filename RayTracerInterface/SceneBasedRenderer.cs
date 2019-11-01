using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace RayTracerInterface {
	public static partial class LibraryHandler {
		public class SceneBasedRenderer : Renderer {
			[DllImport(dll, CallingConvention = CallingConvention.Cdecl)]
			static extern int getSupportedClassesAt(int idx);
			/// <summary>
			/// Internal storage for dynamically created supportedClasses list
			/// </summary>
			private List<int> suppclasses;
			/// <summary>
			/// Dynamically created list containing all the Object Types that our current DLL supports
			/// </summary>
			public List<int> SuppportedClasses {
				get {
					if (suppclasses != null) return suppclasses;
					var n = 0;
					suppclasses = new List<int>();
					while (true) {
						var s = getSupportedClassesAt(n++);
						if (s == -1) break;
						suppclasses.Add(s);
					}
					return suppclasses;
				}
			}
		}
	}
}
