using System.Collections.Generic;
#pragma warning disable CA1822 // Mark members as static
namespace RayTracerInterface {
	public static partial class LibraryHandler {
		public class Renderer {
			public Renderer(uint num) => Libnum = num;
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
					outfiles = new List<string>();
					for (var n = 0; ; n++) {
						var s = OutputFile(n);
						if (s == "_") break;
						outfiles.Add(s);
					}
					return outfiles;
				}
			}
			[System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Naming", "CA1704:IdentifiersShouldBeSpelledCorrectly", MessageId = "y")]
			[System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Naming", "CA1704:IdentifiersShouldBeSpelledCorrectly", MessageId = "x")]
			public bool Render(int option, int x, int y) => render(option, x, y);
			public int Status => status();
			protected uint Libnum { get; private set; }
		}
	}
}
#pragma warning restore CA1822 // Mark members as static