using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RayTracerInterface {
	public interface IRenderPage {
		public Action OnBack { get; set; }
	}
}
