using System;
using System.Collections.Generic;
using System.Diagnostics.Contracts;
using System.Xml.Serialization;
using RayTracerInterface.GraphClasses.Generators;
using static System.FormattableString;
namespace RayTracerInterface.GraphClasses {
	[XmlInclude(typeof(GraphRoot))]
	[XmlInclude(typeof(GraphShape))]
	[XmlInclude(typeof(GraphTransform))]
	[XmlInclude(typeof(Dice))]
	[XmlInclude(typeof(Repeater))]
	public abstract class GraphElement {
		public UInt64 Address = 0;
		//private static UInt64 serializationIDs=0;
		//public static string ReserveDelim() => "<" + Anybase.ConvertB64(++serializationIDs) + ">";
		//public static void FreeDelim() => serializationIDs--;
		public abstract int TYPEID();
		private protected static UInt64 counter = 0;
		public UInt64 ID = ++counter;
		protected internal List<UInt64> parents = new List<UInt64>();
		public IReadOnlyCollection<UInt64> Parents => this is GraphRoot ? null : parents;
		/// <summary>
		/// WARNING! !!USE WITH EXTREME CAUTION!!
		/// IDs are supposed to be unique.
		/// Before Resetting all preexisting graphelements should
		/// be dereferenced
		/// </summary>
		public static void ResetCounter() => counter = 0;
		public void ResetParents() => parents?.Clear();
		protected abstract string Serialize();
		public static string SerializeThis(GraphElement target) {
			Contract.Requires(target != null);
			return Invariant($"{target.TYPEID()}@{target.Address}@{(target is Generator g ? Generator.SerializeThis(g) : target.Serialize())}@");
		}
	}
}
