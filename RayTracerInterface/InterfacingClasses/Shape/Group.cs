using System.Collections.Generic;
using System.Text;
namespace RayTracerInterface {
	public class Group : Renderable {
		public const int TID = 2;
		public override bool IsAtomic => false;
		public override int TYPEID() => TID;
		public List<Renderable> objects = new List<Renderable>();
		public override string Serialize() {
			var sb = new StringBuilder();
			sb.Append(Position.Serialize() + "$");
			foreach (var o in objects)
				sb.Append(SerializeThis(o) + "$");
			return sb.ToString();
		}
	}
}