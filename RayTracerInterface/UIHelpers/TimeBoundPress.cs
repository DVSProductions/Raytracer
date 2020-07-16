using System;
using System.Diagnostics;
namespace RayTracerInterface {
	class TimeBoundVariable {
		protected readonly Stopwatch sw = new Stopwatch();
		protected double startValue = 0;
		protected double increment = 0;

		public TimeBoundVariable(double startValue) => this.startValue = startValue;
		public TimeBoundVariable() {
		}
		public double Value => startValue + (increment * sw.ElapsedMilliseconds);
		public bool IsRunning => sw.IsRunning;
		public double Increment => increment;
		public void Start(double incrementPerMs) {
			if (increment != incrementPerMs) {
				sw.Stop();
				startValue += (increment * sw.ElapsedMilliseconds);
				increment = incrementPerMs;
				sw.Restart();
			}
			if (!IsRunning)
				sw.Start();
		}

		public void Stop() {
			startValue = Value;
			increment = 0;
			sw.Reset();
		}
		public void Restart() {
			Stop();
			sw.Restart();
		}
	}
	class TimeBoundPress : TimeBoundVariable {
		public TimeBoundPress() => startValue = 0;
		bool running = false;
		public bool HasBeenMoving { get; private set; } = false;
		public new double Value {
			get {
				var ret = startValue + (increment * sw.ElapsedTicks / TimeSpan.TicksPerMillisecond);
				startValue = 0;
				sw.Restart();
				if (!running)
					HasBeenMoving = false;
				return ret;
			}
		}
		public new void Start(double incrementPerMs) {
			if (increment != incrementPerMs) {
				sw.Stop();
				startValue += (increment * sw.ElapsedTicks / TimeSpan.TicksPerMillisecond);
				increment = incrementPerMs;
				sw.Restart();
			}
			if (!IsRunning) {
				sw.Start();
				startValue = 0;
			}
			running = true;
			HasBeenMoving = true;
		}

		public new void Stop() {
			startValue = 0;
			increment = 0;
			sw.Reset();
			running = false;
		}
		public new void Restart() {
			Stop();
			sw.Restart();
			running = true;
		}
	}

}
