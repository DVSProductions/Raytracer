#pragma warning disable CA1051 // Do not declare visible instance fields
using System.ComponentModel;
using System.Diagnostics.Contracts;

namespace RayTracerInterface {
	public abstract class Renderable : ISerializable, INotifyPropertyChanged {

		private static int ObjectIDCounter = 0;
		private readonly int ObjectID = ObjectIDCounter++;

		public static Renderable ConvertIDToObject(int TYPEID) {
			switch (TYPEID) {
				case Sphere.TID:
					return new Sphere();
				case Plane.TID:
					return new Plane();
				case Group.TID:
					return new Group();
				default:
					return null;
			};
		}
		public abstract int TYPEID();
		public Vec Position = new Vec(0, 0, -3);
		public string name;
		public string Name { get => name; set => name = value; }

		public event PropertyChangedEventHandler PropertyChanged;
		public void Trigger(string targetName) {
			Contract.Requires(targetName != null);
			PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(targetName));
		}

		protected Renderable() => Name = $"{this.GetType().Name}#{ObjectID}";
		/// <summary>
		/// use <see cref="Renderable.SerializeThis(Renderable)"/> for actual serialization
		/// </summary>
		/// <returns></returns>
		public abstract string Serialize();
		public static string SerializeThis(Renderable target) {
			Contract.Requires(target != null);
			return target.TYPEID() != -1 ? $"{target.TYPEID()}!{target.Serialize()}!" : target.Serialize();
		}
		public override string ToString() => Name;
	}
}

#pragma warning restore CA1051 // Do not declare visible instance fields