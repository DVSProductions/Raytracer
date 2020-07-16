using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Text;
namespace RayTracerInterface {
	class TimeLog {
		readonly List<TimeSpan> times = new List<TimeSpan>();
		List<TimeSpan> fullTimes = null;
		readonly Stopwatch curr = new Stopwatch();
		int timeidx = 0;
		public void StartNew() {
			timeidx = 0;
			curr.Restart();
		}
		public void Next() {
			if (times.Count == timeidx)
				times.Add(curr.Elapsed);
			else
				times[timeidx] = curr.Elapsed;
			timeidx++;
			curr.Restart();
		}
		public void Stop() {
			if (times.Count == timeidx)
				times.Add(curr.Elapsed);
			else
				times[timeidx] = curr.Elapsed;
			fullTimes = times;
		}
		public IReadOnlyCollection<TimeSpan> Values => times;
		public string Output() {
			var sb = new StringBuilder();
			if (fullTimes == null) {
				var len = times.Count.ToString().Length;
				for (var n = 0; n < times.Count; n++)
					sb.AppendFormat($"{{0,{len}}}: {times[n]}\n", n);
			}
			else {
				var len = fullTimes.Count.ToString().Length;
				for (var n = 0; n < fullTimes.Count; n++)
					sb.AppendFormat($"{{0,{len}}}: {fullTimes[n]}\n", n);
			}
			return sb.ToString();
		}
	}
}
