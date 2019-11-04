#pragma warning disable CA1822 // Member als statisch markieren
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
			private List<int> suppclassIDs;
			/// <summary>
			/// Dynamically created list containing all the Object Types that our current DLL supports
			/// </summary>
			public List<int> SuppportedClassIDs {
				get {
					if (suppclassIDs != null) return suppclassIDs;
					var n = 0;
					suppclassIDs = new List<int>();
					while (true) {
						var s = getSupportedClassesAt(n++);
						if (s == -1) break;
						suppclassIDs.Add(s);
					}
					return suppclassIDs;
				}
			}
			private List<Renderable> suppclass;
			public List<Renderable> SuppportedClass {
				get {
					if (suppclass != null) return suppclass;
					suppclass = new List<Renderable>();
					foreach (var id in SuppportedClassIDs)
						suppclass.Add(Renderable.convertIDToObject(id));
					return suppclass;
				}
			}
			//-----------------Cameras-----------------
			[DllImport(dll, CallingConvention = CallingConvention.Cdecl)]
			static extern int getSupportedCamsAt(int idx);
			private List<int> suppcamIDs;
			/// <summary>
			/// Dynamically created list containing all the Object Types that our current DLL supports
			/// </summary>
			public List<int> SuppportedCamIDs {
				get {
					if (suppcamIDs != null) return suppcamIDs;
					var n = 0;
					suppcamIDs = new List<int>();
					while (true) {
						var s = getSupportedCamsAt(n++);
						if (s == -1) break;
						suppcamIDs.Add(s);
					}
					return suppcamIDs;
				}
			}
			private List<Camera> suppcam;
			public List<Camera> SuppportedCams {
				get {
					if (suppcam != null) return suppcam;
					suppcam = new List<Camera>();
					foreach (var id in SuppportedCamIDs)
						suppcam.Add(Camera.ConvertIDToObject(id));
					return suppcam;
				}
			}

			[DllImport(dll, CallingConvention = CallingConvention.Cdecl)]
			static extern void setScene(string serializedData);
			public void SetScene(string serializedData) => setScene(serializedData.Replace(",", "."));
			[DllImport(dll, CallingConvention = CallingConvention.Cdecl)]
			static extern void setCamera(string serializedData);
			public void SetCamera(string serializedData) => setCamera(serializedData.Replace(",", "."));
			[DllImport(dll, CallingConvention = CallingConvention.Cdecl)]
			static extern void initialize3d();
			public void Initialize3d() => initialize3d();
			[DllImport(dll, CallingConvention = CallingConvention.Cdecl)]
			static extern void startPreviewRender(int x, int y);
			public void StartPreviewRender(int x, int y) => startPreviewRender(x, y);
			[DllImport(dll, CallingConvention = CallingConvention.Cdecl)]
			static extern void startSuperRender(int x, int y, int FSAA, string outputFilePath);
			public void StartSuperRender(int x, int y,int FSAA, string outputFilePath) => startSuperRender(x, y, FSAA, outputFilePath);
			[DllImport(dll, CallingConvention = CallingConvention.Cdecl)]
			[return: MarshalAs(UnmanagedType.BStr)]
			static extern string sceneFile();
			private string scf;
			public string SceneFile {
				get {
					if (scf == null)
						scf = sceneFile();
					return scf;
				}
			}

		}
	}
}

#pragma warning restore CA1822 // Member als statisch markieren