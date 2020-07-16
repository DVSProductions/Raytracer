using System;
using System.Windows;
using System.Windows.Controls;

namespace RayTracerInterface.GamePages {
	/// <summary>
	/// Interaktionslogik für GameMenu.xaml
	/// </summary>
	public partial class GameMenu : Page {
		readonly Action<Page> changeMenu;
		readonly GameView parent;
		public GameMenu(Action<Page> changeMenu, GameView parent) {
			this.changeMenu = changeMenu;
			this.parent = parent;
			InitializeComponent();
		}

		private void Button_Click(object _, RoutedEventArgs __) => changeMenu(null);

		private void Button_Click_1(object _, RoutedEventArgs __) => changeMenu(new GameOptions(changeMenu, parent));

		private void Button_Click_2(object sender, RoutedEventArgs e) => parent.Close();
	}
}
