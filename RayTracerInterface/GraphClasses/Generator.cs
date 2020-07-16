using System.Diagnostics.Contracts;

namespace RayTracerInterface.GraphClasses.Generators {
	public abstract class Generator : GraphParent {
		public const int TID = 0;
		public static Generator ConvertIDToObject(int TYPEID) => TYPEID switch
		{
			Dice.TID => new Dice(),
			Repeater.TID => new Repeater(),
			_ => null,
		};
		public static string SerializeThis(Generator target) {
			Contract.Requires(target != null);
			return $"{target.TYPEID()}?{target.Serialize()}?";
		}
	}
}
