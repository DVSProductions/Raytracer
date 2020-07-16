using System.Collections.Generic;
using System.Text;

namespace RayTracerInterface.GraphClasses {
	public abstract class GraphParent : GraphElement {
		/// <summary>
		/// -1 for infinity
		/// </summary>
		public abstract int MaxChildren { get; }
		protected List<System.UInt64> children = new List<System.UInt64>();
		public IReadOnlyCollection<System.UInt64> Children => children;
		public void AddChild(GraphElement ge) {
			if (ge == null)
				return;
			children.Add(ge.Address);
			ge.parents.Add(Address);
		}
		public string GenXray() {
			var sb = new StringBuilder($"{Address}~");
			foreach (var c in children)
				sb.Append(c).Append("~");
			return sb.ToString();
		}
		public void ResetChildren() => children.Clear();
	}
}
