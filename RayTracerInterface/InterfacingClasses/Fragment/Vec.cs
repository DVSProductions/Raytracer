using static System.FormattableString;
namespace RayTracerInterface {
	public class Vec : ISerializable {
		public double x = 0, y = 0, z = 0;
		public Vec() {
		}
		public Vec(double x, double y, double z) {
			this.x = x;
			this.y = y;
			this.z = z;
		}
		public string Serialize() => Invariant($"{x}|{y}|{z}|");
	}
}