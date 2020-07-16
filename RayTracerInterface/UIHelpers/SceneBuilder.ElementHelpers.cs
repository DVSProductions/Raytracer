using RayTracerInterface.UIHelpers;
using System;
using System.Collections.Generic;
using System.Globalization;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
namespace RayTracerInterface {
	public partial class SceneBuilder : Page, IRenderPage {
		VisualizationHelper VisHelper;
		void VisualizeCamera() => VisHelper.VisualizeCamera(spCam, cam,SelectCameraClick);
	}
}
