using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Text;
namespace RayTracerInterface {
	class TiteledTimeLog {
		readonly List<TimeSpan> times = new List<TimeSpan>();
		readonly List<string> logNames = new List<string>();

		List<TimeSpan> fullTimes = null;
		readonly Stopwatch curr = new Stopwatch();
		int timeidx = 0;
		int maxLen = 0;
		public void StartNew(string firstName) {
			timeidx = 0;
			if (logNames.Count == 0) {
				maxLen = firstName.Length;
				logNames.Add(firstName);
			}
			curr.Restart();
		}
		public void Next(string NextEventName) {
			if (times.Count == timeidx) {
				times.Add(curr.Elapsed);
				logNames.Add(NextEventName);
				if (NextEventName.Length > maxLen)
					maxLen = NextEventName.Length;
			}
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
		public IReadOnlyCollection<string> Names => logNames;
		public string Output() {
			var sb = new StringBuilder();
			if (fullTimes == null) {
				for (var n = 0; n < times.Count; n++)
					sb.AppendFormat($"{{0,{maxLen}}}: {times[n]}\n", logNames[n]);
			}
			else {
				for (var n = 0; n < fullTimes.Count; n++)
					sb.AppendFormat($"{{0,{maxLen}}}: {fullTimes[n]}\n", logNames[n]);
			}
			return sb.ToString();
		}
	}
}
