using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RayTracerInterface {
	public interface ISerializable {
		string Serialize();
	}
	public class Vec : ISerializable {
		public double x = 0, y = 0, z = 0;
		public string Serialize() => $"{x}|{y}|{z}";
	}
	public class Color : ISerializable {
		public double r = 0, g = 0, b = 0;
		public string Serialize() => $"{r}|{g}|{b}";
		public Color(int r, int g ,int b) {
			this.r = r / 255.0;
			this.g = g / 255.0;
			this.b = b / 255.0;
		}
		public Color(double r, double g , double b) {
			this.r = r;
			this.g = g;
			this.b = b;
		}
	}
	public abstract class Renderable : ISerializable {

		private static int ObjectIDCounter = 0;
		private int ObjectID = ObjectIDCounter++;

		public static Renderable convertIDToObject(int TYPEID) {
			switch (TYPEID) {
				case 0:
					return new Sphere();

			}
			return null;
		}
		protected abstract int TYPEID();
#pragma warning disable CA1051 // Do not declare visible instance fields
		public Vec Position = new Vec();
#pragma warning restore CA1051 // Do not declare visible instance fields
		/// <summary>
		/// use <see cref="Renderable.SerializeThis(Renderable)"/> for actual serialization
		/// </summary>
		/// <returns></returns>
		public abstract string Serialize();
		public static string SerializeThis(Renderable r) => $"{r.TYPEID()}!{r.Serialize()}";
		public override string ToString() => $"{this.GetType().Name}#{ObjectID}";
	}
	class Sphere : Renderable {
		protected override int TYPEID() => 0;
		public double Radius = 0;
		public Color Color = new Color(0,0,0);
		public override string Serialize() => $"{Radius}&{Color.Serialize()}&{Position.Serialize()}";
	}
	class Scene : ISerializable {
		public List<Renderable> objects=new List<Renderable>();
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
		public double angle = 0;
		public Vec Position = new Vec();
		public string Serialize() => $"{angle}&{Position.Serialize()}";
	}
	class PinholeCamera : Camera {
		public Color background;

		public new string Serialize() => background.Serialize() + "[" + base.Serialize();
	}
}
