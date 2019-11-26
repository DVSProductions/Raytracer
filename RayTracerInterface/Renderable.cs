#pragma warning disable CA1051 // Do not declare visible instance fields
using System.ComponentModel;

namespace RayTracerInterface {
	public abstract class Renderable : ISerializable, INotifyPropertyChanged {

		private static int ObjectIDCounter = 0;
		private int ObjectID = ObjectIDCounter++;

		public static Renderable convertIDToObject(int TYPEID) {
			switch (TYPEID) {
				case Sphere.TID:
					return new Sphere();
				case Plane.TID:
					return new Plane();
				case Group.TID:
					return new Group();
			}
			return null;
		}
		public abstract int TYPEID();
		public Vec Position = new Vec(0, 0, -3);
		public string name;
		public string Name { get => name; set => name = value; }

		public event PropertyChangedEventHandler PropertyChanged;
		public void Trigger(string name) => PropertyChanged?.Invoke(this, new System.ComponentModel.PropertyChangedEventArgs(name));
		public Renderable() => Name = $"{this.GetType().Name}#{ObjectID}";
		/// <summary>
		/// use <see cref="Renderable.SerializeThis(Renderable)"/> for actual serialization
		/// </summary>
		/// <returns></returns>
		public abstract string Serialize();
		public static string SerializeThis(Renderable r) => r.TYPEID() != -1 ? $"{r.TYPEID()}!{r.Serialize()}!" : r.Serialize();
		public override string ToString() => Name;
	}
}

#pragma warning restore CA1051 // Do not declare visible instance fields