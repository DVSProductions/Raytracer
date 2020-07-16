using System.Collections.Generic;
using System.Runtime.InteropServices;
#pragma warning disable CA1822 // Mark members as static
namespace RayTracerInterface.Renderer {
	public class BasicRenderer {
		/// <summary>
		/// Launches a render Job
		/// </summary>
		/// <param name="Option">File to render</param>
		/// <param name="x">width</param>
		/// <param name="y">height</param>
		/// <returns></returns>
		[DllImport(LibraryHandler.dll, CallingConvention = CallingConvention.Cdecl)]
		[return: MarshalAs(UnmanagedType.U1)]
		private static extern bool render(int Option, int x, int y);
		/// <summary>
		/// Turns a errorCode into a string
		/// </summary>
		/// <param name="errorCode">lodePNG error</param>
		/// <returns></returns>
		[DllImport(LibraryHandler.dll, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
		[return: MarshalAs(UnmanagedType.BStr)]
		private static extern string LodeReturnDecode(int errorCode);
		/// <summary>
		/// gets the lodePNG return code
		/// </summary>
		/// <returns></returns>
		[DllImport(LibraryHandler.dll, CallingConvention = CallingConvention.Cdecl)]
		private static extern int returnValue();
		/// <summary>
		/// Returns the number of rendered columns
		/// </summary>
		/// <returns></returns>
		[DllImport(LibraryHandler.dll, CallingConvention = CallingConvention.Cdecl)]
		private static extern int status();
		/// <summary>
		/// Calls the DLL to receive a output DLL filename
		/// <para>
		///		Returns "_" when the given index is out of range
		/// </para>
		/// </summary>
		/// <param name="file">index in filename array</param>
		/// <returns>filename or "_" on error</returns>
		[DllImport(LibraryHandler.dll, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
		[return: MarshalAs(UnmanagedType.BStr)]
		private static extern string OutputFile(int file);
		public BasicRenderer(uint num) => Libnum = num;
		public int ReturnCode => returnValue();
		public string ReturnString => LodeReturnDecode(ReturnCode);
		/// <summary>
		/// gets the library info
		/// </summary>
		public string LibraryInfo => LibraryHandler.libInfo;
		/// <summary>
		/// Internal storage for dynamically created output-file list
		/// </summary>
		private List<string> outfiles;
		/// <summary>
		/// Dynamically created list containing all the Files that our current DLL supports
		/// </summary>
		public List<string> OutputFiles {
			get {
				if (outfiles != null)
					return outfiles;
				outfiles = new List<string>();
				for (var n = 0; ; n++) {
					var s = OutputFile(n);
					if (s == "_")
						break;
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
#pragma warning restore CA1822 // Mark members as static