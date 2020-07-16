using System.ComponentModel;
using System.Diagnostics.Contracts;
using System.Xml.Serialization;

namespace RayTracerInterface {
	[XmlInclude(typeof(Sphere))]
	[XmlInclude(typeof(Plane))]
	[XmlInclude(typeof(Group))]
	[XmlInclude(typeof(Pipe))]
	[XmlInclude(typeof(Cylinder))]
	public abstract class Renderable : ISerializable, INotifyPropertyChanged {
		public abstract bool IsAtomic { get; }
		private static int ObjectIDCounter = 0;
		private readonly int ObjectID = ObjectIDCounter++;
		public static Renderable ConvertIDToObject(int TYPEID) => TYPEID switch
		{
			Sphere.TID => new Sphere(),
			Plane.TID => new Plane(),
			Group.TID => new Group(),
			Pipe.TID => new Pipe(),
			Cylinder.TID => new Cylinder(),
			_ => null,
		};
		public abstract int TYPEID();
		public Vec Position = new Vec(0, 0, -3);
		public string name;
		public string Name { get => name; set => name = value; }
		public event PropertyChangedEventHandler PropertyChanged;
		public void Trigger(string targetName) {
			Contract.Requires(targetName != null);
			PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(targetName));
		}
		protected Renderable() => name = $"{GetType().Name}#{ObjectID}";
		/// <summary>
		/// use <see cref="Renderable.SerializeThis(Renderable)"/> for actual serialization
		/// </summary>
		/// <returns></returns>
		public abstract string Serialize();
		public static string SerializeThis(Renderable target) {
			Contract.Requires(target != null);
			return target.TYPEID() != -1 ? $"{target.TYPEID()}!{target.Serialize()}!" : target.Serialize();
		}
		public override string ToString() => name;
	}
}