using System.Collections.Generic;
using System.Runtime.InteropServices;
using RayTracerInterface.GraphClasses.Generators;
namespace RayTracerInterface.Renderer {
	class GraphableRenderer : TransformableRenderer {
		public GraphableRenderer(uint num) : base(num) { }
		[DllImport(LibraryHandler.dll, CallingConvention = CallingConvention.Cdecl)]
		static extern int GetSupportedGeneratorsAt(int idx);
		private List<int> suppGeneratorIDs;
		public List<int> SuppportedGeneratorIDs => suppGeneratorIDs ?? LoadGeneratorsIDs();
		private List<int> LoadGeneratorsIDs() {
			suppGeneratorIDs = new List<int>();
			for (var n = 0; ; n++) {
				var s = GetSupportedGeneratorsAt(n);
				if (s == -1)
					break;
				suppGeneratorIDs.Add(s);
			}
			return suppGeneratorIDs;
		}

		/// <summary>
		/// Internal storage for dynamically created supportedGenerators list
		/// </summary>
		private List<Generator> suppGenerator;
		public List<Generator> SuppportedGenerators => suppGenerator ?? LoadGenerators();
		private List<Generator> LoadGenerators() {
			suppGenerator = new List<Generator>();
			foreach (var id in SuppportedGeneratorIDs)
				suppGenerator.Add(Generator.ConvertIDToObject(id));
			return suppGenerator;
		}
	}
}
