using static System.FormattableString;
namespace RayTracerInterface {
	public class Glass : AAlbedoMat {
		public const int TID = 5;
		public double Refraction = 1.5;
		public override string Serialize() => Invariant($"{Refraction}}}{Albedo.Serialize()}}}{Emission.Serialize()}}}");
		public override int TYPEID() => TID;
	}
}