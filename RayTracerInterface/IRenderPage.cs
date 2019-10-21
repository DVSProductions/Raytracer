using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RayTracerInterface {
	/// <summary>
	/// This is just to allow <see cref="RenderPage"/> and <see cref="Abgabe"/> to be abstracted.<para>
	/// This allows us to send either one to the <see cref="MainWindow"/> for processing</para>
	/// </summary>
	public interface IRenderPage {
		/// <summary>
		/// Used by mainWindow to allow a page to navigate back
		/// </summary>
		Action OnBack { get; set; }
	}
}
