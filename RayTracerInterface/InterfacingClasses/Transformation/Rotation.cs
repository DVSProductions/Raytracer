using static System.FormattableString;
namespace RayTracerInterface {
	public enum Axis {
		X = 0, Y = 1, Z = 2
	}
	public class Rotation : ATransformation {
		public const int TID = 1;
		public override int TYPEID() => TID;
		public Axis Axis = Axis.X;
		public double Angle = 0.0;
		public override string Serialize() => Invariant($"{(int)Axis}|{Angle}|");
	}
}