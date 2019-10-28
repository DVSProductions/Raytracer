namespace RayTracerInterface {
	internal partial class LibraryHandler {
		public class Renderer {
			public int lodeReturnCode() {
				return returnValue();
			}
			/// <summary>
			/// gets the library info
			/// </summary>
			public string LibraryInfo => LibInfo();
		}
	}
}
