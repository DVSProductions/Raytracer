using System;
using System.IO;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Xml;
using System.Xml.Serialization;
namespace RayTracerInterface {
	public partial class SceneBuilder : Page, IRenderPage {
		public void Save(string fileName) {
			try {
				using var fs = new FileStream(fileName, FileMode.Create);
				Save(fs);
			}
			catch (Exception ex) {
				MessageBox.Show($"ERROR WRITING OUTPUT FILE: {ex.ToString()}", ex.GetType().Name);
			}
		}
		public void Save(Stream target) {
			using var writer = new StreamWriter(target, new UTF8Encoding());
			var tmp = new Renderable[Shapes.Count];
			Shapes.CopyTo(tmp, 0);
			new XmlSerializer(typeof(SaveContainer)).Serialize(writer, new SaveContainer() { camera = cam, shapes = tmp });
		}
		/// <summary>
		/// Loads a xml file and ensures compatibility with old version
		/// </summary>
		/// <param name="path"></param>
		public void Load(string path) {
			var xml = File.ReadAllLines(path);
			var hasOldColorElements = false;
			using var ms = new MemoryStream();
			using var sw = new StreamWriter(ms);
			var n = 0;
			for (; n < xml.Length; n++) {
				var line = xml[n];
				if (line.Contains("<camera")) break;
				if (line.Contains("<Color>")) {
					hasOldColorElements = true;
					line = line.Replace("<Color>", $"<Color xsi:type=\"Vanta\">{Environment.NewLine}<Emission>");
				}
				else if (hasOldColorElements)
					line = line.Replace("</Color>", $"</Emission>{Environment.NewLine}</Color>");
				sw.Write(line);
				sw.Write(Environment.NewLine);
			}
			for (; n < xml.Length; n++)
				sw.Write(xml[n]);
			sw.Flush();
			ms.Position = 0;
			Load(ms);
		}
		public void Load(Stream from) {
			using var reader = XmlReader.Create(from);
			Load(reader);
		}
		public void Load(XmlReader reader) {
			var dat = new XmlSerializer(typeof(SaveContainer)).Deserialize(reader) as SaveContainer;
			cam = dat.camera;
			VisualizeCamera();
			Shapes.Clear();
			foreach (var e in dat.shapes)
				Shapes.Add(e);
			Lbshapes.SelectedIndex = 0;
			AlertChanges();
		}
	}
}
