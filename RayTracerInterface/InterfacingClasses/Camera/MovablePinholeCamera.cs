using System.Collections.Generic;
using System.Text;

namespace RayTracerInterface {
	public class MovablePinholeCamera : Camera {
		public Background Background = new Background(new Color(1.0,1.0,1.0));
		public const int TID = 1;
		public List<ATransformation> Transformations = new List<ATransformation>();
		public MovablePinholeCamera() => Reflections = 5;
		private string Listtostr() {
			var sb = new StringBuilder();
			foreach (var t in Transformations)
				sb.Append(ATransformation.SerializeThis(t)).Append('{');
			return sb.ToString();
		}
		public override string Serialize() => $"{Background.Serialize()}[{Serial(this)}[{Listtostr()}[";
		public override int TYPEID() => TID;
	}
}