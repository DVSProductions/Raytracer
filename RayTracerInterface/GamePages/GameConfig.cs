namespace RayTracerInterface.GamePages {
	public struct GameConfig : System.IEquatable<GameConfig> {
		public static readonly double defaultMouseSensitivity = 0.1, defaultMovementPerMS=0.001;
		public double Aperature, RenderScale, Gamma, MouseSensitivity, MovementPerMS;
		public int Supersampling, ReflectionDepth,Threads;
		public GameConfig(double aperature) {
			Aperature = aperature;
			RenderScale = 1;
			Supersampling = 1;
			ReflectionDepth = 5;
			Gamma = 2.2;
			MouseSensitivity = defaultMouseSensitivity;
			MovementPerMS = defaultMovementPerMS;
			Threads = System.Environment.ProcessorCount - 1;
		}
		public override bool Equals(object obj) => obj is GameConfig gc ? Equals(gc) : false;

		public override int GetHashCode() => $"{Aperature}{RenderScale}{Supersampling}{ReflectionDepth}{Gamma}{MouseSensitivity}".GetHashCode();

		public static bool operator ==(GameConfig left, GameConfig right) => left.Equals(right);

		public static bool operator !=(GameConfig left, GameConfig right) => !(left == right);

		public bool Equals(GameConfig gc) =>
			gc.Aperature == Aperature &&
			gc.ReflectionDepth == ReflectionDepth &&
			gc.Supersampling == Supersampling &&
			gc.RenderScale == RenderScale &&
			gc.MouseSensitivity == MouseSensitivity &&
			gc.Gamma == Gamma;
	}
}
