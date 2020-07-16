namespace RayTracerInterface.GraphClasses.Generators {
	public class Dice : Generator {
		public new const int TID = 0;
		public override int MaxChildren => -1;
		public override int TYPEID() => TID;
		protected override string Serialize() =>"";
	}
}
