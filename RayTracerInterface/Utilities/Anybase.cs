using System.Text;
namespace RayTracerInterface {
	class Anybase {
		public static readonly char[] charset = "abcdefghijklmnopqrstuvwxyz0123456789".ToCharArray();
		public static readonly char[] charsetB64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/".ToCharArray();
		public static string Convert(ulong num, uint b, char[] charset, int len) {
			var s = new StringBuilder();
			while (num != 0) {
				s.Append(charset[num % b]);
				num /= b;
			}
			while (s.Length < len)
				s.Append(charset[0]);
			return s.ToString();
		}
		public static string Convert(ulong num, uint b, char[] charset) {
			var s = new StringBuilder();
			while (num != 0) {
				s.Append(charset[num % b]);
				num /= b;
			}
			return s.ToString();
		}
		public static string Convert(ulong num, char[] charset) =>
				Convert(num, (uint)charset.Length, charset);
		public static string ConvertB64(ulong num) => Convert(num, 64, charsetB64);
		public static string ConvertB64(ulong num, int len) {
			var s = new StringBuilder();
			while (num != 0) {
				s.Append(charsetB64[num % 64u]);
				num /= 64u;
			}
			while (s.Length < len)
				s.Append('=');
			return s.ToString();
		}

	}
}
