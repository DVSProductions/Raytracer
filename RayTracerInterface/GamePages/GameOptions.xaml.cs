using System;
using System.Collections.Generic;
using System.Diagnostics.Contracts;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace RayTracerInterface.GamePages {
	/// <summary>
	/// Interaktionslogik für GameOptions.xaml
	/// </summary>
	public partial class GameOptions : Page {
		private readonly bool initialized = false;
		readonly Action<Page> Goto;
		private readonly GameView parent;
		public GameOptions(Action<Page> GoTo, GameView parent) {
			Contract.Requires(parent != null);
			this.parent = parent;
			Goto = GoTo;
			InitializeComponent();

			slAperature.Value = parent.config.Aperature;
			var requestedFrame = parent.Framenum;
			slAperature.ValueChanged += (_, e) => {
				if (initialized) {
					parent.config.Aperature = e.NewValue;
					if (parent.Framenum >= requestedFrame) {
						requestedFrame = parent.Framenum + 1;
						parent.RenderOneFrame();
					}
				}
			};
			slAperature.ValueChanged += GamePageUtil.Slider_ValueChanged;
			GamePageUtil.SetSliderText(slAperature);

			parent.changesSinceLastRender = true;
			initialized = true;
		}

		private void Button_Click(object sender, RoutedEventArgs e) => Goto(null);

		private void Button_Click_1(object sender, RoutedEventArgs e) => Goto(new GameGraphicSettings(Goto, parent));

		private void Button_Click_2(object sender, RoutedEventArgs e) => Goto(new GameKeybinds(Goto, parent));
	}
}
