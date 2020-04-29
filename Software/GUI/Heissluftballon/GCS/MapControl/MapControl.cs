using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Input;

namespace GCS.MapControl
{
    class GmapControl
    {
        
        private MainWindow main;
        public GmapControl(MainWindow main)
        {
            this.main = main;
            InitMap();
            AddMouseListener();
        }


        private void InitMap()
        {
            main.gmap.MapProvider = GMap.NET.MapProviders.GoogleMapProvider.Instance;
            GMap.NET.GMaps.Instance.Mode = GMap.NET.AccessMode.ServerAndCache;
            main.gmap.MouseWheelZoomType = GMap.NET.MouseWheelZoomType.MousePositionWithoutCenter;

            main.gmap.MaxZoom = 22;
            main.gmap.MinZoom = 1;
            main.gmap.ShowCenter = false;
            main.gmap.CanDragMap = true;
            main.gmap.DragButton = System.Windows.Forms.MouseButtons.Left;

            main.gmap.Zoom = 10;
            main.gmap.Position = new GMap.NET.PointLatLng(47.26505, 8.43224);
            main.winFormHost.Child = main.gmap;
        }

        private void AddMouseListener()
        {
            main.rbSatelliteMap.Checked += new RoutedEventHandler(this.RbSatellitCard_Checked);
            main.rbRoadMap.Checked += new RoutedEventHandler(this.RbStreetCard_Checked);
        }

        private void RbSatellitCard_Checked(object sender, RoutedEventArgs e)
        {
                main.gmap.MapProvider = GMap.NET.MapProviders.GoogleSatelliteMapProvider.Instance;
        }

        private void RbStreetCard_Checked(object sender, RoutedEventArgs e)
        {
                 main.gmap.MapProvider = GMap.NET.MapProviders.GoogleMapProvider.Instance;
        }



    }
}
