namespace RayTracerInterface {
	public abstract class Renderable : ISerializable {

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
#pragma warning disable CA1051 // Do not declare visible instance fields
		public Vec Position = new Vec(0, 0, -3);
#pragma warning restore CA1051 // Do not declare visible instance fields
		/// <summary>
		/// use <see cref="Renderable.SerializeThis(Renderable)"/> for actual serialization
		/// </summary>
		/// <returns></returns>
		public abstract string Serialize();
		public static string SerializeThis(Renderable r) {
			return r.TYPEID() != -1 ? $"{r.TYPEID()}!{r.Serialize()}!" : r.Serialize();
		}
		public override string ToString() => $"{this.GetType().Name}#{ObjectID}";
}
}
