using System;
using System.Diagnostics.Contracts;
using System.Xml.Serialization;
using static System.FormattableString;
namespace RayTracerInterface {
	[XmlInclude(typeof(PinholeCamera))]
	[XmlInclude(typeof(MovablePinholeCamera))]
	public abstract class Camera : ISerializable {
		public double angle = Math.PI / 2;
		public Vec Position = new Vec(0,0,0);
		public ushort Reflections = 1;
		public abstract int TYPEID();
		public abstract string Serialize();
		protected static string Serial(Camera cam) {
			Contract.Requires(cam != null);
			return Invariant($"{cam.angle}&{cam.Position.Serialize()}&{cam.Reflections}&");
		}
		public static Camera ConvertIDToObject(int TYPEID) => TYPEID switch
		{
			PinholeCamera.TID => new PinholeCamera(),
			MovablePinholeCamera.TID => new MovablePinholeCamera(),
			_ => null,
		};
		public static string SerializeThis(Camera cam) {
			Contract.Requires(cam != null);
			return Invariant($"{cam.TYPEID()}!{cam.Serialize()}!");
		}
	}
}