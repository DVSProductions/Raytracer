namespace RayTracerInterface {	
	public class Scaling : ATransformation {
		public const int TID = 2;
		public override int TYPEID() => TID;
		public Vec Sizes = new Vec();
		public override string Serialize() => Sizes.Serialize();
	}
}