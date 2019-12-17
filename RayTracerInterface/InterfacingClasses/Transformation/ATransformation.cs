using System.Diagnostics.Contracts;
using System.Xml.Serialization;
using static System.FormattableString;
namespace RayTracerInterface {
	[XmlInclude(typeof(Translation))]
	[XmlInclude(typeof(Rotation))]
	[XmlInclude(typeof(Scaling))]
	[XmlInclude(typeof(ComplexRotation))]

	public abstract class ATransformation : ISerializable {
		private static int ObjectIDCounter = 0;
		private readonly int ObjectID = ObjectIDCounter++;
		public abstract int TYPEID();
		public static ATransformation ConvertIDToObject(int TYPEID) {
			return TYPEID switch
			{
				Translation.TID => new Translation(),
				Rotation.TID => new Rotation(),
				Scaling.TID => new Scaling(),
				ComplexRotation.TID=>new ComplexRotation(),
				_ => null,
			};
		}
		public abstract string Serialize();
		public static string SerializeThis(ATransformation mat) {
			Contract.Requires(mat != null);
			return Invariant($"{mat.TYPEID()}#{mat.Serialize()}#");
		}
		public override string ToString() => Invariant($"{GetType().Name}#{ObjectID}");
	}
}