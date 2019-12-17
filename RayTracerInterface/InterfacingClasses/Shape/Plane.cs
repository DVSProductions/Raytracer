using static System.FormattableString;
namespace RayTracerInterface {
	public class Plane : Renderable {
		public const int TID = 1;
		public override int TYPEID() => TID;
		public double Radius = -1;
		public AMaterial Color = new Vanta(new Color(0.9, 0.9, 0.9));
		public Vec Direction = new Vec(0, 1, 0);
		public Plane() => Position = new Vec(0, -3, 0);
		public override string Serialize() => Invariant($"{Radius}&{Direction.Serialize()}&{AMaterial.SerializeThis(Color)}&{Position.Serialize()}&");
	}
}