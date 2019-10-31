using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RayTracerInterface {
	interface ISerializable {
		string Serialize();
	}
	class Vec : ISerializable {
		public double x=0, y=0, z=0;
		public string Serialize() => $"{x}|{y}|{z}";
	}
	class Color : ISerializable {
		public double r=0, g=0, b=0;
		public string Serialize() => $"{r}|{g}|{b}";
	}
	abstract class Renderable : ISerializable {
		protected abstract int TYPEID();
		public Vec p=new Vec();
		/// <summary>
		/// use <see cref="Renderable.SerializeThis(Renderable)"/> for actual serialization
		/// </summary>
		/// <returns></returns>
		public abstract string Serialize();
		public static string SerializeThis(Renderable r) => $"{r.Serialize()}!{r.TYPEID()}";
	}
	class Sphere : Renderable {
		protected override int TYPEID() => 0;
		public double radius=0;
		public Color c=new Color();
		public override string Serialize() => $"{radius}&{c.Serialize()}&{p.Serialize()}";
	}
	class Scene : ISerializable {
		public List<Renderable> objects;
		public string Serialize() {
			var sb = new StringBuilder();
			bool first = true;
			foreach (var o in objects) {
				if (first) {
					first = false;
					sb.Append("$");
				}
				sb.Append(o.Serialize());
			}
			return sb.ToString();
		}
	}
	abstract class Camera : ISerializable {
		public double angle=0;
		public Vec position=new Vec();
		public string Serialize() => $"{angle}&{position.Serialize()}";
	}
	class PinholeCamera : Camera {
		public Color background;

		public new string Serialize() => background.Serialize() + "[" + base.Serialize();
	}
}
