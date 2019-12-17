using static System.FormattableString;
namespace RayTracerInterface {
	public class Color : ISerializable {
		public double r = 0, g = 0, b = 0;
		public string Serialize() => Invariant($"{r}|{g}|{b}|");
		public Color(int r, int g, int b) {
			this.r = r / 255.0;
			this.g = g / 255.0;
			this.b = b / 255.0;
		}
		public Color(double r, double g, double b) {
			this.r = r;
			this.g = g;
			this.b = b;
		}
		public Color() { }
	}
}