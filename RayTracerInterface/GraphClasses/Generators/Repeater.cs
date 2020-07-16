using System.Text;
using static System.FormattableString;
namespace RayTracerInterface.GraphClasses.Generators {
	public class Repeater : Generator {
		public new const int TID = 1;
		public override int MaxChildren => -1;
		public Vec Position = new Vec(0, 0, 0);
		public Vec Offset = new Vec();
		public double Steplimit = 0, Stepsize = 0;
		public override int TYPEID() => TID;
		protected override string Serialize() => Invariant($"{Position.Serialize()}/{Offset.Serialize()}/{Steplimit}/{Stepsize}/");
	}
}
