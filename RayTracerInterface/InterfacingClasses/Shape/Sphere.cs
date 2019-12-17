using static System.FormattableString;
namespace RayTracerInterface {
	public class Sphere : Renderable {
		public const int TID = 0;
		public override int TYPEID() => TID;
		public double Radius = 1;
		public AMaterial Color = new Vanta(new Color(0.5, 0.5, 0.5));
		public override string Serialize() => Invariant($"{Radius}&{AMaterial.SerializeThis(Color)}&{Position.Serialize()}&");
	}
}