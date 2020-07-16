#pragma warning disable CA1822 // Member als statisch markieren
#pragma warning disable IDE1006 // Naming Styles
// Member als statisch markieren
using System.Collections.Generic;
using System.Diagnostics.Contracts;
using System.Runtime.InteropServices;
namespace RayTracerInterface.Renderer {
	public class SceneBasedRenderer : BasicRenderer {
		public SceneBasedRenderer(uint num) : base(num) { }
		[DllImport(LibraryHandler.dll, CallingConvention = CallingConvention.Cdecl)]
		static extern int getSupportedClassesAt(int idx);
		/// <summary>
		/// Internal storage for dynamically created supportedClasses list
		/// </summary>
		private List<int> suppclassIDs;
		private List<int> loadClassIDs() {
			suppclassIDs = new List<int>();
			for (var n = 0; ; n++) {
				var s = getSupportedClassesAt(n);
				if (s == -1)
					break;
				suppclassIDs.Add(s);
			}
			return suppclassIDs;
		}
		/// <summary>
		/// Dynamically created list containing all the Object Types that our current DLL supports
		/// </summary>
		public List<int> SuppportedClassIDs => suppclassIDs ?? loadClassIDs();
		private List<Renderable> suppclass;
		private List<Renderable> loadClasses() {
			suppclass = new List<Renderable>();
			foreach (var id in SuppportedClassIDs)
				suppclass.Add(Renderable.ConvertIDToObject(id));
			return suppclass;
		}
		public List<Renderable> SuppportedClass => suppclass ?? loadClasses();
		//-----------------Cameras-----------------
		[DllImport(LibraryHandler.dll, CallingConvention = CallingConvention.Cdecl)]
		static extern int getSupportedCamsAt(int idx);
		private List<int> suppcamIDs;
		private List<int> loadCamIDs() {
			suppcamIDs = new List<int>();
			for (var n = 0; ; n++) {
				var s = getSupportedCamsAt(n);
				if (s == -1)
					break;
				suppcamIDs.Add(s);
			}
			return suppcamIDs;
		}
		/// <summary>
		/// Dynamically created list containing all the Object Types that our current DLL supports
		/// </summary>
		public List<int> SupportedCamIDs => suppcamIDs ?? loadCamIDs();
		private List<Camera> suppcam;
		private List<Camera> loadCams() {
			suppcam = new List<Camera>();
			foreach (var id in SupportedCamIDs)
				suppcam.Add(Camera.ConvertIDToObject(id));
			return suppcam;
		}
		public List<Camera> SupportedCams => suppcam ?? loadCams();
		[DllImport(LibraryHandler.dll, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
		static extern void setScene(string serializedData);
		public void SetScene(string serializedData) {
			Contract.Requires(serializedData != null);
			setScene(serializedData);
		}
		[DllImport(LibraryHandler.dll, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
		static extern void setCamera(string serializedData);
		public void SetCamera(string serializedData) {
			Contract.Requires(serializedData != null);
			setCamera(serializedData);
		}
		[DllImport(LibraryHandler.dll, CallingConvention = CallingConvention.Cdecl)]
		static extern void initialize3d();
		public void Initialize3D() => initialize3d();
		[DllImport(LibraryHandler.dll, CallingConvention = CallingConvention.Cdecl)]
		static extern void startPreviewRender(int x, int y);
		public void StartPreviewRender(int x, int y) => startPreviewRender(x, y);
		[DllImport(LibraryHandler.dll, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
		static extern void startSuperRender(int x, int y, int FSAA, string outputFilePath);
		public void StartSuperRender(int x, int y, int fsaa, string outputFilePath) => startSuperRender(x, y, fsaa, outputFilePath);
		[DllImport(LibraryHandler.dll, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
		[return: MarshalAs(UnmanagedType.BStr)]
		static extern string sceneFile();
		private string scf;
		public string SceneFile => scf ?? (scf = sceneFile());
	}
}
#pragma warning restore IDE1006 // Naming Styles
#pragma warning restore CA1822 // Member als statisch markieren
// Member als statisch markieren
