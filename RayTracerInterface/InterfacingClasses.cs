using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;
#pragma warning disable CA1051 // Do not declare visible instance fields

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
		public Color() { }
	}
	public class Sphere : Renderable {
		public const int TID = 0;
		public override int TYPEID() => TID;
		public double Radius = 1;
		public AMaterial Color = new Vanta(new Color(0.5, 0.5, 0.5));
		public override string Serialize() => $"{Radius}&{AMaterial.SerializeThis(Color)}&{Position.Serialize()}&";
	}
	public class Plane : Renderable {
		public const int TID = 1;
		public override int TYPEID() => TID;
		public double Radius = -1;
		public AMaterial Color = new Vanta(new Color(0.9, 0.9, 0.9));
		public Vec Direction = new Vec(0, 1, 0);
		public Plane() => Position = new Vec(0, -3, 0);
		public override string Serialize() => $"{Radius}&{Direction.Serialize()}&{AMaterial.SerializeThis(Color)}&{Position.Serialize()}&";
	}
	public class Background : ISerializable {
		public Color Color = new Color(0.25, 0.25, 0.25);
		public string Serialize() => $"{Color.Serialize()}";
		/// <summary>
		/// Cannot be instantiated
		/// </summary>
		public const int TID = -1;
		public static int TYPEID() => -1;
	}
	public class Group : Renderable {
		public const int TID = 2;
		public override int TYPEID() => TID;
		public List<Renderable> objects = new List<Renderable>();
		public override string Serialize() {
			var sb = new StringBuilder();
			sb.Append(Position.Serialize() + "$");
			foreach (var o in objects)
				sb.Append(Renderable.SerializeThis(o) + "$");
			return sb.ToString();
		}
	}
	public class Scene : ISerializable {
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
	[XmlInclude(typeof(PinholeCamera))]
	public abstract class Camera : ISerializable {
		public double angle = Math.PI / 2;
		public Vec Position = new Vec();
		public ushort Reflections = 1;
		public abstract int TYPEID();
		public abstract string Serialize();
		protected static string Serial(Camera c) => $"{c.angle}&{c.Position.Serialize()}&{c.Reflections}&";
		public static Camera ConvertIDToObject(int TYPEID) {
			switch (TYPEID) {
				case PinholeCamera.TID:
					return new PinholeCamera();

			}
			return null;
		}
		public static string SerializeThis(Camera c) => $"{c.TYPEID()}!{c.Serialize()}!";

	}
	public class PinholeCamera : Camera {
		public Background Background = new Background();
		public const int TID = 0;
		public override string Serialize() => Background.Serialize() + "[" + Camera.Serial(this) + "[";
		public override int TYPEID() => TID;
	}
	[XmlInclude(typeof(Vanta))]
	[XmlInclude(typeof(Mirror))]
	[XmlInclude(typeof(Chalk))]
	[XmlInclude(typeof(LightSource))]
	[XmlInclude(typeof(Metal))]
	[XmlInclude(typeof(Glass))]
	public abstract class AMaterial : ISerializable {
		private static int ObjectIDCounter = 0;
		private readonly int ObjectID = ObjectIDCounter++;
		public abstract int TYPEID();
		public Color Emission = new Color(0, 0, 0);
		public static AMaterial ConvertIDToObject(int TYPEID) {
			switch (TYPEID) {
				case Vanta.TID:
					return new Vanta();
				case Mirror.TID:
					return new Mirror();
				case Chalk.TID:
					return new Chalk();
				case LightSource.TID:
					return new LightSource();
				case Metal.TID:
					return new Metal();
				case Glass.TID:
					return new Glass();
			}
			return null;
		}
		public abstract string Serialize();
		public static string SerializeThis(AMaterial r) => r.TYPEID() != 0 ? $"{r.TYPEID()}#{r.Serialize()}#" : r.Serialize();
		public override string ToString() => $"{this.GetType().Name}#{ObjectID}";

	}

	public class Vanta : AMaterial {
		public const int TID = 0;
		public override string Serialize() => Emission.Serialize();
		public override int TYPEID() => TID;
		public Vanta() => Emission = new Color(0.5, 0.5, 0.5);
		public Vanta(Color c) => Emission = c;
	}
	public class Mirror : AMaterial {
		public const int TID = 1;
		public Color Albedo = new Color(0.95, 0.95, 0.95);
		public Mirror() => Emission = new Color(0, 0, 0);
		public override string Serialize() => $"{Albedo.Serialize()}}}{Emission.Serialize()}}}";
		public override int TYPEID() => TID;
	}
	public class Chalk : AMaterial {
		public const int TID = 2;
		public Color Albedo = new Color(0.9, 0.9, 0.9);
		public override string Serialize() => $"{Albedo.Serialize()}}}{Emission.Serialize()}}}";
		public override int TYPEID() => TID;
	}
	public class LightSource : AMaterial {
		public const int TID = 3;
		public override string Serialize() => new Color(Emission.r * Overdrive, Emission.g * Overdrive, Emission.b * Overdrive).Serialize();
		public override int TYPEID() => TID;
		public double Overdrive = 1;
	}
	public class Metal : AMaterial {
		public const int TID = 4;
		public Color Albedo = new Color(0.95, 0.95, 0.95);
		public double ScatterFactor = 0.1;
		public override string Serialize() => $"{ScatterFactor}}}{Albedo.Serialize()}}}{Emission.Serialize()}}}";
		public override int TYPEID() => TID;
	}
	public class Glass : AMaterial {
		public const int TID = 5;
		public Color Albedo = new Color(0.95, 0.95, 0.95);
		public double Refraction = 1.5;
		public override string Serialize() => $"{Refraction}}}{Albedo.Serialize()}}}{Emission.Serialize()}}}";
		public override int TYPEID() => TID;
	}
}
#pragma warning restore CA1051 // Do not declare visible instance fields