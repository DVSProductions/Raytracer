namespace RayTracerInterface {
	public class LightSource : AMaterial {
		public const int TID = 3;
		public override string Serialize() => new Color(Emission.r * Overdrive, Emission.g * Overdrive, Emission.b * Overdrive).Serialize();
		public override int TYPEID() => TID;
		public double Overdrive = 1;
	}
}