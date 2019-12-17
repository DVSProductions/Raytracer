
namespace RayTracerInterface {
	public class PinholeCamera : Camera {
		public Background Background = new Background();
		public const int TID = 0;
		public override string Serialize() => Background.Serialize() + "[" + Serial(this) + "[";
		public override int TYPEID() => TID;
	}
}