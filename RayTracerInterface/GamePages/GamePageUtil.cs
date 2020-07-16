using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using static System.FormattableString;
namespace RayTracerInterface.GamePages {
	static class GamePageUtil {
		public static void SetSliderText(Slider sl) {
			var g = sl.Parent as Grid;
			var mult = 1 / sl.SmallChange;
			var nv = ((int)(sl.Value * mult)) / mult;
			(g.Children[2] as Label).Content = sl.SmallChange == 1 ? Invariant($"{(g.Children[0] as VisualStorage).Storage}{nv}") : string.Format(
				System.Globalization.CultureInfo.InvariantCulture,
				"{0}{1:0." + mult.ToString().Substring(1) + "}",
				(g.Children[0] as VisualStorage).Storage,
				nv);
		}
		public static void Slider_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e) {
			var snd = sender as Slider;
			if (e.OldValue < snd.Minimum)
				return;
			var mult = 1 / snd.SmallChange;
			var nv = ((int)(e.NewValue * mult)) / mult;
			snd.Value = nv;
			SetSliderText(snd);
		}
		public static void SliderInt_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e) {
			var snd = sender as Slider;
			if (e.OldValue < snd.Minimum)
				return;
			var nv = (int)e.NewValue;
			snd.Value = nv;
			SetSliderText(snd);
		}
	}
}
