using static System.FormattableString;
namespace RayTracerInterface {
	public class Background : ISerializable {
		public Background() { }
		public Background(Color c) => Color = c;  
		public Color Color = new Color(0.25, 0.25, 0.25);
		public string Serialize() => Color.Serialize();
		/// <summary>
		/// Cannot be instantiated
		/// </summary>
		public const int TID = -1;
		public static int TYPEID() => -1;
	}
}