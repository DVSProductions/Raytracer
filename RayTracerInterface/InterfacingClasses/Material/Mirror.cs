using static System.FormattableString;
namespace RayTracerInterface {
	public class Mirror : AAlbedoMat {
		public const int TID = 1;
		public Mirror() => Emission = new Color(0, 0, 0);
		public override string Serialize() => Invariant($"{Albedo.Serialize()}}}{Emission.Serialize()}}}");
		public override int TYPEID() => TID;
	}
}