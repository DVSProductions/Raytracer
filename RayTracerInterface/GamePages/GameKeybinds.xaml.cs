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
	/// Interaktionslogik für GameKeybinds.xaml
	/// </summary>
	public partial class GameKeybinds : Page {
		private readonly bool initialized = false;
		readonly Action<Page> GoBack;
		private readonly GameView parent;
		public GameKeybinds(Action<Page> GoBack, GameView parent) {
			Contract.Requires(parent != null);
			this.parent = parent;
			this.GoBack = GoBack;
			InitializeComponent();

			//slAperature.Value = parent.config.Aperature;
			slMouse.Value = parent.config.MouseSensitivity/GameConfig.defaultMouseSensitivity;
			slMovement.Value = parent.config.MovementPerMS/GameConfig.defaultMovementPerMS;
			//slSuper.Value = parent.config.Supersampling;
			//slDepth.Value = parent.config.ReflectionDepth;
			//slGamma.Value = parent.config.Gamma;
			//slThrads.Maximum = Environment.ProcessorCount - 1;
			//slThrads.Value = parent.config.Threads;
			//slAperature.ValueChanged += (_, e) => { if (initialized) parent.config.Aperature = e.NewValue; };
			slMouse.ValueChanged += (_, e) => { if (initialized) parent.config.MouseSensitivity = e.NewValue * GameConfig.defaultMouseSensitivity; };
			slMovement.ValueChanged += (_, e) => { if (initialized) parent.config.MovementPerMS = e.NewValue * GameConfig.defaultMovementPerMS; };
			slMouse.ValueChanged += GamePageUtil.Slider_ValueChanged;
			slMovement.ValueChanged += GamePageUtil.Slider_ValueChanged;
			//slGamma.ValueChanged += (_, e) => { if (initialized) parent.config.Gamma = e.NewValue; };
			//slSuper.ValueChanged += (_, e) => { if (initialized) parent.config.Supersampling = (int)e.NewValue; };
			//slDepth.ValueChanged += (_, e) => { if (initialized) parent.config.ReflectionDepth = (int)e.NewValue; };
			//slThrads.ValueChanged += (_, e) => { if (initialized) parent.config.Threads = (int)e.NewValue; };
			GamePageUtil.SetSliderText(slMouse);
			GamePageUtil.SetSliderText(slMovement);
			//SetSliderText(slScale);
			//SetSliderText(slGamma);
			//SetSliderText(slSuper);
			//SetSliderText(slDepth);
			//SetSliderText(slThrads);
			parent.changesSinceLastRender = true;
			initialized = true;
		}

		private void Button_Click(object sender, RoutedEventArgs e) => GoBack(null);
	}
}
