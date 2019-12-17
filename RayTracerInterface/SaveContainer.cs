using System.Collections.Generic;
using System.Xml.Serialization;
namespace RayTracerInterface {
	public class SaveContainer {
		[XmlArray("shapes")]
		[XmlArrayItem("Sphere", typeof(Sphere))]
		[XmlArrayItem("Plain", typeof(Plane))]
		[XmlArrayItem("Group", typeof(Group))]
		[XmlArrayItem("Pipe", typeof(Pipe))]
		[XmlArrayItem("Cylinder", typeof(Cylinder))]
		public Renderable[] shapes;
		public Camera camera;
	}
}
