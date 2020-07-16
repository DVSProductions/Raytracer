namespace RayTracerInterface.GraphClasses {
	public class GraphShape : GraphElement {
		public const int TID = 2;
		public override int TYPEID() => TID;
		public Renderable Shape;
		public GraphShape() { }
		public GraphShape(Renderable shp) => Shape = shp;
		protected override string Serialize() => Renderable.SerializeThis(Shape);
	}
}
