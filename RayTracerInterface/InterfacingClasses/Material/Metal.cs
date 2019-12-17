using static System.FormattableString;
namespace RayTracerInterface {
	public class Metal : AAlbedoMat {
		public const int TID = 4;
		public double ScatterFactor = 0.1;
		public override string Serialize() => Invariant($"{ScatterFactor}}}{Albedo.Serialize()}}}{Emission.Serialize()}}}");
		public override int TYPEID() => TID;
	}
}