using System.Diagnostics.Contracts;
using System.Xml.Serialization;
using static System.FormattableString;
namespace RayTracerInterface {
	[XmlInclude(typeof(Vanta))]
	[XmlInclude(typeof(Mirror))]
	[XmlInclude(typeof(Chalk))]
	[XmlInclude(typeof(LightSource))]
	[XmlInclude(typeof(Metal))]
	[XmlInclude(typeof(Glass))]
	public abstract class AMaterial : ISerializable {
		private static int ObjectIDCounter = 0;
		private readonly int ObjectID = ObjectIDCounter++;
		public abstract int TYPEID();
		public Color Emission = new Color(0, 0, 0);
		public static AMaterial ConvertIDToObject(int TYPEID) => TYPEID switch
		{
			Vanta.TID => new Vanta(),
			Mirror.TID => new Mirror(),
			Chalk.TID => new Chalk(),
			LightSource.TID => new LightSource(),
			Metal.TID => new Metal(),
			Glass.TID => new Glass(),
			_ => null,
		};
		public abstract string Serialize();
		public static string SerializeThis(AMaterial mat) {
			Contract.Requires(mat != null);
			return mat.TYPEID() != 0 ? Invariant($"{mat.TYPEID()}#{mat.Serialize()}#") : mat.Serialize();
		}
		public override string ToString() => Invariant($"{this.GetType().Name}#{ObjectID}");
	}
}