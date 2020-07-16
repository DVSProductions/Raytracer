using System.Text;

namespace RayTracerInterface.GraphClasses {
	public class GraphTransform : GraphParent {
		public override int MaxChildren => -1;
		public ATransformation trans;
		public GraphTransform() { }
		public GraphTransform(ATransformation content) => trans = content;
		public const int TID = 1;
		public override int TYPEID() => TID;
		protected override string Serialize() => $"{ATransformation.SerializeThis(trans)}";
	}
}
