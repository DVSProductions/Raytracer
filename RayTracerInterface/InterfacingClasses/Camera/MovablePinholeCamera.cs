using System.Collections.Generic;
namespace RayTracerInterface {
	public class MovablePinholeCamera : Camera {
		public Background Background = new Background(new Color(1,1,1));
		public const int TID = 1;
		public List<ATransformation> Transformations = new List<ATransformation>();
		public MovablePinholeCamera() => Reflections = 5;
		private string Listtostr() {
			var s = "";
			foreach (var t in Transformations) 
				s += ATransformation.SerializeThis(t) + "{";
			return s;
		}
		public override string Serialize() => Background.Serialize() + "[" + Serial(this) + "[" + Listtostr() + "[";
		public override int TYPEID() => TID;
	}
}