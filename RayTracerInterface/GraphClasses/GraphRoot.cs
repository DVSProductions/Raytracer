using System.Diagnostics.Contracts;
using System.Text;

namespace RayTracerInterface.GraphClasses {
	public class GraphRoot : GraphParent {
		public override int MaxChildren => -1;

		public override int TYPEID() => 3;
		protected override string Serialize() => "";
		public static string GetSerial(System.Collections.Generic.List<GraphElement> memory) {
			Contract.Requires(memory != null);
			var sb = new StringBuilder();
			foreach (var ge in memory)
				sb.Append(SerializeThis(ge)).Append("(");
			sb.Append(")");
			foreach (var ge in memory)
				if(ge is GraphParent gp)
				sb.Append(gp.GenXray()).Append(")");
			return sb.ToString();
		}
	}
}
