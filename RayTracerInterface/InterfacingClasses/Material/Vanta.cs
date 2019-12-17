
namespace RayTracerInterface {
	public class Vanta : AMaterial {
		public const int TID = 0;
		public override string Serialize() => Emission.Serialize();
		public override int TYPEID() => TID;
		public Vanta() => Emission = new Color(0.5, 0.5, 0.5);
		public Vanta(Color color) => Emission = color;
	}
}
