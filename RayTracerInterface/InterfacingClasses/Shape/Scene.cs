using System.Collections.Generic;
using System.Text;
namespace RayTracerInterface {
	public class Scene : ISerializable {
		public List<Renderable> objects = new List<Renderable>();
		public string Serialize() {
			var sb = new StringBuilder();
			foreach (var o in objects) {
				sb.Append(Renderable.SerializeThis(o));
				sb.Append("$");
			}
			return sb.ToString();
		}
	}
}