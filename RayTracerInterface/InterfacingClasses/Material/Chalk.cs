using static System.FormattableString;
namespace RayTracerInterface {
	public class Chalk : AAlbedoMat {
		public const int TID = 2;
		public override string Serialize() => Invariant($"{Albedo.Serialize()}}}{Emission.Serialize()}}}");
		public override int TYPEID() => TID;
	}
}