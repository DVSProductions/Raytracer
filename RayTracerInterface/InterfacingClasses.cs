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

		public Vec() {
		}

		public Vec(double x, double y, double z) {
			this.x = x;
			this.y = y;
			this.z = z;
		}

		public string Serialize() => $"{x}|{y}|{z}|";
	}
	public class Color : ISerializable {
		public double r = 0, g = 0, b = 0;
		public string Serialize() => $"{r}|{g}|{b}|";
		public Color(int r, int g, int b) {
			this.r = r / 255.0;
			this.g = g / 255.0;
			this.b = b / 255.0;
		}
		public Color(double r, double g, double b) {
			this.r = r;
			this.g = g;
			this.b = b;
		}
	}
	class Sphere : Renderable {
		public const int TID = 0;
		public override int TYPEID() => TID;
		public double Radius = 1;
		public Color Color = new Color(0, 0, 0);
		public override string Serialize() => $"{Radius}&{Color.Serialize()}&{Position.Serialize()}&";
	}
	class Scene : ISerializable {
		public List<Renderable> objects = new List<Renderable>();
		public string Serialize() {
			var sb = new StringBuilder();
			bool first = true;
			foreach (var o in objects) {
				if (first) {
					first = false;
				}
				else
					sb.Append("$");
				sb.Append(Renderable.SerializeThis(o));
			}
			sb.Append("$");
			return sb.ToString();
		}
	}
	public abstract class Camera : ISerializable {
		public double angle = Math.PI/2;
		public Vec Position = new Vec();
		public abstract int TYPEID();
		public abstract string Serialize();
		protected static string serial(Camera c)=> $"{c.angle}&{c.Position.Serialize()}&";
		public static Camera ConvertIDToObject(int TYPEID) {
			switch (TYPEID) {
				case 0:
					return new PinholeCamera();

			}
			return null;
		}
		public static string SerializeThis(Camera c) => $"{c.TYPEID()}!{c.Serialize()}!";

	}
	class PinholeCamera : Camera {
		public Color background=new Color(0.5,0.5,0.5);
		public const int TID = 0;
		public override string Serialize() => background.Serialize() + "[" + Camera.serial(this)+"[";
		public override int TYPEID() => TID;
	}
}
