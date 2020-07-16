using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Diagnostics.Contracts;
using System.Runtime.InteropServices;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Effects;
using System.Windows.Media.Imaging;
using RayTracerInterface.GamePages;
using RayTracerInterface.Renderer;
using static System.FormattableString;
namespace RayTracerInterface {
	/// <summary>
	/// Interaktionslogik für GameView.xaml
	/// </summary>
	public partial class GameView : Window {
		readonly TransformableRenderer rend;
		readonly TiteledTimeLog tl = new TiteledTimeLog();
		public GameConfig config = new GameConfig();
		bool menuOpen = false;
		public bool changesSinceLastRender = true;
		int height = 0, width = 0;
		bool showDebug = true;
		public Int64 Framenum { get; private set; }= 0;
		int cShift = 0, cA = 0;
		bool isFullScreen = false;
		WindowState oldWS;
		readonly TimeBoundPress
			X = new TimeBoundPress(),
			Y = new TimeBoundPress(),
			Z = new TimeBoundPress();
		//movement per Milli Second
		void BlurBG() {
			iResults.Effect = new BlurEffect() { Radius = 10 };
			Rshadow.Visibility = Visibility.Visible;
			pageViewer.Visibility = Visibility.Visible;
			ReleaseMouse();
		}
		void ShowBG() {
			iResults.Effect = null;
			Rshadow.Visibility = Visibility.Hidden;
			pageViewer.Visibility = Visibility.Hidden;
			captureMouse();
		}
		bool settingsChangedSinceLastRender = true;
		readonly Stack<Page> pageStack = new Stack<Page>();
		public void ChangeMenu(Page p) {
			if (p == null) {
				if (pageStack.Count > 1)
					pageViewer.Content = pageStack.Pop();
				else 
					HideMenu();
			}
			else {

					pageStack.Push(pageViewer.Content as Page);
				pageViewer.Content = p;
			}
		}
		async void WriteDebug() {
			var startFrame = Framenum;
			var sw = Stopwatch.StartNew();
			var lastframe = startFrame;
			var lastfps = 0.0;
			if (showDebug)
				do {
					var framecount = Framenum - startFrame;
					if (framecount == 0)
						framecount = 1;
					var elapsed = (sw.ElapsedMilliseconds / 1000.0);
					if (elapsed == 0)
						elapsed = 1;
					if (lastframe != Framenum) {
						lastframe = Framenum;
						lastfps = framecount / elapsed;
					}
					var scaling = SceneGraph.GetWindowsScaling();
					debug.Content =
						$"ViewPort Height: {GContent.ActualHeight * scaling}\n" +
						$"ViewPort Width : {GContent.ActualWidth * scaling}\n" +
						$"Render   Height: {height}\n" +
						$"Render   Width : {width}\n" +
						$"Rendered Frames: {Framenum}\n" +
						Invariant($"AvgFPS         : {lastfps:0.00}\n") +
						$"cShif: {cShift}\n" +
						"Durations: \n" +
						tl.Output()



					;
					await Task.Delay(33);
					if (menuOpen) {
						while (menuOpen)
							await Task.Delay(50);
						WriteDebug();
						return;
					}
				} while (Visibility == Visibility.Visible && showDebug);
			debug.Content = "";
		}

		[DllImport("User32.dll")]
		private static extern bool SetCursorPos(int X, int Y);

		readonly string bgstring;
		public GameView(TransformableRenderer rend, string sceneString, Camera sourceCamera) {
			Contract.Requires(rend != null);
			Contract.Requires(sourceCamera != null);
			Contract.Requires(!string.IsNullOrEmpty(sceneString));
			this.rend = rend;
			config = new GameConfig(sourceCamera.angle);
			var bg = new Background();
			if (sourceCamera is PinholeCamera pc)
				bg = pc.Background;
			if (sourceCamera is MovablePinholeCamera mpc)
				bg = mpc.Background;
			bgstring = bg.Serialize();
			rend.Initialize3D();
			rend.SetScene(sceneString);
			InitializeComponent();
			App.MakeMeDarkModal(this);
			WriteDebug();
			RenderTask();
			CheckMovementKeys();
			iResults.MouseMove += IResults_MouseMove;
			CaptureMouseLater();
			CheckLostFocus();
		}
		//public static bool ApplicationIsActivated() {
		//	var activatedHandle = GetForegroundWindow();
		//	if (activatedHandle == IntPtr.Zero) {
		//		return false;       // No window is currently activated
		//	}

		//	var procId = Process.GetCurrentProcess().Id;
		//	GetWindowThreadProcessId(activatedHandle, out var activeProcId);

		//	return activeProcId == procId;
		//}


		//[DllImport("user32.dll", CharSet = CharSet.Auto, ExactSpelling = true)]
		//private static extern IntPtr GetForegroundWindow();

		//[DllImport("user32.dll", CharSet = CharSet.Auto, SetLastError = true)]
		//private static extern int GetWindowThreadProcessId(IntPtr handle, out int processId);
		async void CheckLostFocus() {
			while (Visibility != Visibility.Visible)
				await Task.Delay(300);
			while (Visibility == Visibility.Visible) {
				if (!IsActive&& !menuOpen) {
					ShowMenu();
				}
				await Task.Delay(333);
			}
		}
		async void CaptureMouseLater() { await Task.Delay(300); captureMouse(); }
		double rotationX = 0, rotationY = 0;
		bool acceptMovement = false;
		void captureMouse() {
			CenterMouse();
			iResults.IsHitTestVisible = true;
			iResults.Cursor = Cursors.None;
			Focus();
			acceptMovement = true;
			ignoreNext = true;
		}

		private void CenterMouse() {
			var offset = new Point(iResults.ActualWidth / 2, iResults.ActualHeight / 2);
			var targetpos = iResults.PointToScreen(offset);
			SetCursorPos((int)targetpos.X, (int)targetpos.Y);
		}

		void ReleaseMouse() {
			acceptMovement = false;
			iResults.IsHitTestVisible = false;
			iResults.Cursor = null;
		}
		double Limit(double v, double min, double max) => v > max ? max : v < min ? min : v;
		bool ignoreNext = false;
		private void IResults_MouseMove(object sender, MouseEventArgs e) {
			if (!acceptMovement)
				return;
			if (ignoreNext) {
				ignoreNext = false;
				return;
			}
			var snd = sender as FrameworkElement;
			var absolutePos = e.GetPosition(snd);
			CenterMouse();
			rotationX -= (absolutePos.X - (snd.ActualWidth / 2)) * config.MouseSensitivity;
			rotationY = Limit(rotationY - ((absolutePos.Y - (snd.ActualHeight / 2)) * config.MouseSensitivity), -90, 90);
			changesSinceLastRender = true;
		}
		private async void CheckMovementKeys() {
			//if (!IsFocused)
			//	return;
			while (Visibility != Visibility.Visible)
				await Task.Delay(33);
			while (Visibility == Visibility.Visible) {
				var speed = Keyboard.IsKeyDown(Key.LeftShift) ? config.MovementPerMS * 5 : config.MovementPerMS;
				if (Keyboard.IsKeyDown(Key.S))
					Z.Start(speed);
				if (Keyboard.IsKeyDown(Key.W))
					Z.Start(-speed);
				else if (Keyboard.IsKeyUp(Key.S)) {
					Z.Stop();
					changesSinceLastRender = true;
				}
				if (Keyboard.IsKeyDown(Key.D))
					X.Start(speed);
				if (Keyboard.IsKeyDown(Key.A))
					X.Start(-speed);
				else if (Keyboard.IsKeyUp(Key.D)) {
					X.Stop();
					changesSinceLastRender = true;
				}
				if (Keyboard.IsKeyDown(Key.Space))
					Y.Start(speed);
				if (Keyboard.IsKeyDown(Key.C) || Keyboard.IsKeyDown(Key.RightCtrl) || Keyboard.IsKeyDown(Key.LeftCtrl))
					Y.Start(-speed);
				else if (Keyboard.IsKeyUp(Key.Space)) {
					Y.Stop();
					changesSinceLastRender = true;
				}
				await Task.Delay(33);
			}
		}
		private void Window_KeyDown(object sender, KeyEventArgs e) {

			switch (e.Key) {
				case Key.Escape:
					//if (!menuOpen)
					//	rend.AbortRender();
					if (menuOpen) 
						HideMenu();
					else 
						ShowMenu();
					break;
				case Key.F3:
					showDebug = !showDebug;
					WriteDebug();
					break;
				case Key.F11:
					isFullScreen = !isFullScreen;
					WindowStyle = isFullScreen ? WindowStyle.None : WindowStyle.SingleBorderWindow;
					Topmost = isFullScreen;
					if (isFullScreen)
						oldWS = WindowState;
					WindowState = isFullScreen ? WindowState.Maximized : oldWS;
					break;
			}
		}

		private void HideMenu() {
			menuOpen = false;
			ShowBG();
			pageViewer.Content = null;
			pageStack.Clear();
			captureMouse();
		}

		private void ShowMenu() {
			settingsChangedSinceLastRender = true;
			menuOpen = true;
			ChangeMenu(new GameMenu(ChangeMenu, this));
			BlurBG();
		}

		[DllImport(LibraryHandler.dll, CallingConvention = CallingConvention.Cdecl)]
		private static extern void BlastImage(byte[] Image);
		//private static extern void BlastImage(ref IntPtr Image);
		[DllImport(LibraryHandler.dll, CallingConvention = CallingConvention.Cdecl)]
		//private static extern void StartGameRender(int w, int h, int FSAA, double gamma, int threads);
		private static extern void StartGameRender(int w, int h, double gamma);
		[DllImport(LibraryHandler.dll, CallingConvention = CallingConvention.Cdecl)]
		private static extern void PrepareGameRender(int FSAA, int threads);
		[DllImport(LibraryHandler.dll, CallingConvention = CallingConvention.Cdecl)]
		private static extern void SetGameCamera(double angle, ushort reflections, string serialBG);
		[DllImport(LibraryHandler.dll, CallingConvention = CallingConvention.Cdecl)]
		private static extern void MoveGameCamera(double x, double y, double z);
		[DllImport(LibraryHandler.dll, CallingConvention = CallingConvention.Cdecl)]
		private static extern void RotateGameCamera(double x, double y, double z);
		private async void RenderTask() {
			await Task.Delay(100);
			while (Visibility == Visibility.Visible) {
				while (menuOpen)
					await Task.Delay(10);
				await RenderFrame();
			}
		}
		byte[] imageData;
		int arrlen = 0;
		public async void RenderOneFrame() {
			settingsChangedSinceLastRender = true;
			await RenderFrame();
		}
		private async Task RenderFrame() {
			tl.StartNew("Movement");
			if (settingsChangedSinceLastRender) {
				SetGameCamera(config.Aperature, (ushort)config.ReflectionDepth, bgstring);
				settingsChangedSinceLastRender = false;
			}
			if (changesSinceLastRender || X.Increment != 0 || Y.Increment != 0 || Z.Increment != 0) {
				MoveGameCamera(X.Value, Y.Value, Z.Value);
				RotateGameCamera(rotationY, rotationX, 0);//X and Y are intentionally flipped here!
														  //rend.SetCamera(Camera.SerializeThis(MPC));
														  //
				changesSinceLastRender = false;
				PrepareGameRender(config.Supersampling, config.Threads);
			}
			tl.Next("Scaling");
			var scaling = SceneGraph.GetWindowsScaling();
			height = (int)(scaling * config.RenderScale * GContent.ActualHeight);
			width = (int)(scaling * config.RenderScale * GContent.ActualWidth);
			tl.Next("Render launch");
			StartGameRender(width, height, config.Gamma);
			tl.Next("Allocation");
			if (arrlen != height * width * 3) {
				imageData = new byte[height * width * 3];
				arrlen = height * width * 3;
			}
			//if (arrlen != height * width * 4) {
			//	imageData = new byte[height * width * 4];
			//	arrlen = height * width * 4;
			//}
			//var imageData = new byte[height * width * 4];
			//var arrlen = height * width * 4;

			tl.Next("Render completion");
			while (rend.Status != width) {
				await Task.Delay(TimeSpan.FromMilliseconds(1));
			}
			tl.Next("Blasting");


			BlastImage(imageData);
			//var ip = new IntPtr();
			//BlastImage(ref ip);

			tl.Next("Displpaying");
			iResults.Source = /*MakeBitmapSource.FromArray(imageData, width, height, 3); //*/BitmapSource.Create(width, height, 96, 96, PixelFormats.Rgb24, null, imageData, 3 * width);// 		

			//Marshal.Copy(ip, imageData, 0, arrlen);
			//iResults.Source = BitmapSource.Create(width, height, 96, 96, PixelFormats.Bgra32, null, imageData, 4 * width);


			//Marshal.Copy(ip, imageData, 0, arrlen);
			//iResults.Source = BitmapSource.Create(width, height, 96, 96, PixelFormats.Bgra32, null, imageData, 4 * width);

			tl.Stop();
			Framenum++;
		}
	}
}
