using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RayTracerInterface {
	public interface IRenderPage {
		Action OnBack { get; set; }
	}
}
