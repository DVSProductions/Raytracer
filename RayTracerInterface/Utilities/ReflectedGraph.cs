using RayTracerInterface.GraphClasses;
using RayTracerInterface.UIHelpers;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;

namespace RayTracerInterface {
	public class DynamicLineAbstraction {
		public GraphElement Source, Target;
	}
	public class GraphElementAbstraction {
		public int x, y;

		public GraphElement e;
		public string name;
	}
	public class ReflectedGraph {
		public int x, y;
		[XmlArray("Makeup")]		
		public GraphElementAbstraction[] Fields;
		[XmlArray("Lines")]
		public DynamicLineAbstraction[] Lines;
	}
}
