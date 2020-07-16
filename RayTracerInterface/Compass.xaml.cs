using System;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media.Animation;
namespace RayTracerInterface {
	public partial class Compass : Window {
		private readonly Action B, L, R;
		bool? suicide;
		public Compass(Action B, Action L, Action R, Action Refocus) {
			InitializeComponent();
			this.B = B;
			this.R = R;
			this.L = L;
			foreach (Button b in ButtonGrid.Children)
				b.Click += (_, __) => Refocus();
		}
		private async void Window_MouseLeave(object _, MouseEventArgs __) {
			if (suicide.HasValue)
				return;
			suicide = true;
			MouseEnter += Compass_MouseEnter;
			var duration = TimeSpan.FromMilliseconds(250);
			await Task.Delay(duration);
			if (!suicide.Value) {
				MouseEnter -= Compass_MouseEnter;
				suicide = null;
				return;
			}
			BeginAnimation(OpacityProperty, new DoubleAnimation() {
				From = 0.85,
				To = 0.01,
				Duration = new Duration(duration),
				EasingFunction = new ExponentialEase() { EasingMode = EasingMode.EaseIn }
			});
			await Task.Delay(duration);
			MouseEnter -= Compass_MouseEnter;
			if (suicide.Value)
				Close();
			suicide = null;
		}
		private void Compass_MouseEnter(object _, MouseEventArgs __) {
			BeginAnimation(OpacityProperty, null);
			suicide = false;
		}
		private void Left_Click(object _, RoutedEventArgs __) => L();

		private void Right_Click(object _, RoutedEventArgs __) => R();

		private void Bottom_Click(object _, RoutedEventArgs __) => B();

		private void BL_Click(object _, RoutedEventArgs __) {
			B();
			L();
		}

		private void BR_Click(object _, RoutedEventArgs __) {
			B();
			R();
		}
	}
}
