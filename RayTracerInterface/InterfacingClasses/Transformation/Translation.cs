
namespace RayTracerInterface {
	public class Translation : ATransformation {
		public const int TID = 0;
		public override int TYPEID() => TID;
		public Vec Position = new Vec(0, 0, 0);
		public override string Serialize() => Position.Serialize();
	}
}
