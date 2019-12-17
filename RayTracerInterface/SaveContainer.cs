using System.Collections.Generic;
using System.Xml.Serialization;
namespace RayTracerInterface {
	public class SaveContainer {
		[XmlArray("shapes")]
		[XmlArrayItem("Sphere", typeof(Sphere))]
		[XmlArrayItem("Plain", typeof(Plane))]
		[XmlArrayItem("Group", typeof(Group))]
		public Renderable[] shapes ;
		public Camera camera;
	}
}
