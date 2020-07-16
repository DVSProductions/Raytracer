using System;
using System.Diagnostics.Contracts;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
namespace RayTracerInterface.GamePages {
	/// <summary>
	/// Interaktionslogik für GameGraphicSettings.xaml
	/// </summary>
	public partial class GameGraphicSettings : Page {
		readonly Action<Page> GoBack;
		private readonly GameView parent;
		bool initialized = false;
		public GameGraphicSettings(Action<Page> GoBack, GameView parent) {
			Contract.Requires(parent != null);
			this.parent = parent;
			this.GoBack = GoBack;
			InitializeComponent();
			slScale.Value = parent.config.RenderScale;
			slSuper.Value = parent.config.Supersampling;
			slDepth.Value = parent.config.ReflectionDepth;
			slGamma.Value = parent.config.Gamma;
			slThrads.Maximum = Environment.ProcessorCount - 1;
			slThrads.Value = parent.config.Threads;
			slScale.ValueChanged += (_, e) => { if (initialized) parent.config.RenderScale = e.NewValue; };
			slGamma.ValueChanged += (_, e) => { if (initialized) parent.config.Gamma = e.NewValue; };
			slSuper.ValueChanged += (_, e) => { if (initialized) parent.config.Supersampling = (int)e.NewValue; };
			slDepth.ValueChanged += (_, e) => { if (initialized) parent.config.ReflectionDepth = (int)e.NewValue; };
			slThrads.ValueChanged += (_, e) => { if (initialized) parent.config.Threads = (int)e.NewValue; };
			GamePageUtil.SetSliderText(slScale);
			GamePageUtil.SetSliderText(slGamma);
			GamePageUtil.SetSliderText(slSuper);
			GamePageUtil.SetSliderText(slDepth);
			GamePageUtil.SetSliderText(slThrads);
			slScale.ValueChanged += GamePageUtil.Slider_ValueChanged;
			slGamma.ValueChanged += GamePageUtil.Slider_ValueChanged;
			slSuper.ValueChanged += GamePageUtil.SliderInt_ValueChanged;
			slDepth.ValueChanged += GamePageUtil.SliderInt_ValueChanged;
			slThrads.ValueChanged += GamePageUtil.SliderInt_ValueChanged;
			parent.changesSinceLastRender = true;
			initialized = true;
		}



		private void Button_Click(object sender, RoutedEventArgs e) => GoBack(null);
	}
}
