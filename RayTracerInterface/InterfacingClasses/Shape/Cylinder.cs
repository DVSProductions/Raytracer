using static System.FormattableString;

namespace RayTracerInterface {
	public class Cylinder : Renderable {
		public const int TID = 4;
		public override int TYPEID() => TID;
		public double Radius = 1;
		public double Height = 3;
		public AMaterial Color = new Chalk();
		public override string Serialize() => Invariant($"{Radius}]{Height}]{AMaterial.SerializeThis(Color)}]{Position.Serialize()}]");
	}
}
