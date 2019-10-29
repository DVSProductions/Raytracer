using System.Collections.Generic;

namespace RayTracerInterface {
	public static partial class LibraryHandler {
		public class Renderer {
			public int ReturnCode => returnValue();
			public string ReturnString => LodeReturnDecode(ReturnCode);
			/// <summary>
			/// gets the library info
			/// </summary>
			public string LibraryInfo => LibInfo();
			/// <summary>
			/// Internal storage for dynamically created output-file list
			/// </summary>
			private List<string> outfiles;
			/// <summary>
			/// Dynamically created list containing all the Files that our current DLL supports
			/// </summary>
			public List<string> OutputFiles {
				get {
					if (outfiles != null) return outfiles;
					var n = 0;
					outfiles = new List<string>();
					while (true) {
						var s = OutputFile(n++);
						if (s == "_") break;
						outfiles.Add(s);
					}
					return outfiles;
				}
			}
			public bool Render(int option, int x, int y) => render(option, x, y);
			public int Status => status();
		}
	}
}
