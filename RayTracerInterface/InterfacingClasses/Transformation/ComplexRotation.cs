using static System.FormattableString;
namespace RayTracerInterface {
	public class ComplexRotation : ATransformation {
		public const int TID = 3;
		public override int TYPEID() => TID;
		public Vec axis = new Vec(0, 1, 0);
		public double Angle = 0.0;
		public override string Serialize() => Invariant($"{axis.Serialize()};{Angle};");
	}
}