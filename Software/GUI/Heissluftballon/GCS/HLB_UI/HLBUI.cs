
using GMap.NET;
using GMap.NET.WindowsForms;
using LiveCharts;
using LiveCharts.Wpf;
using System;
using System.Collections.Generic;

using System.Windows;
using System.Windows.Media;

namespace GCS.HLB_UI
{
    class HLBUI
    {
        readonly MainWindow main;

        LineSeries lsAltitude = new LineSeries();
        LineSeries lsHumidity = new LineSeries();
        LineSeries lsTempOutside = new LineSeries();
        LineSeries lsTempInside = new LineSeries();
        LineSeries lsPressure = new LineSeries();


       // List<PointLatLng> pointlatlang = new List<PointLatLng>();

        GMapOverlay overlayGCS = new GMapOverlay("routeGCS");
        GMapOverlay overlayDevice = new GMapOverlay("routeDevice");
        List<PointLatLng> pointsGCS = new List<PointLatLng>();
        List<PointLatLng> pointsDevice = new List<PointLatLng>();
        GMapRoute trackGCS;
        GMapRoute trackDevice;

        int humidityCounter = 0;
        int tempInsideCounter = 0;
        int tempOutsideCounter = 0;
        int pressureCounter = 0;
        int altitudeCounter = 0;

        public enum TARGET
        {
            GCS,
            DEVICE
        };

        public HLBUI(MainWindow main)
        {
            this.main = main;
            initHumidity();
            initAltitude();
            initPressure();
            initTempInside();
            initTempOutside();
            initGmap();
        }


        private void initGmap()
        {
            trackDevice = new GMapRoute(pointsDevice, "trackDevice");
            trackGCS = new GMapRoute(pointsDevice, "trackGCS");

            trackDevice.Stroke = new System.Drawing.Pen(System.Drawing.Brushes.Red, 3);
            trackGCS.Stroke = new System.Drawing.Pen(System.Drawing.Brushes.Red, 3);

            overlayDevice.Routes.Add(trackDevice);
            overlayGCS.Routes.Add(trackGCS);
            main.gmap.Overlays.Add(overlayDevice);
            main.gmap.Overlays.Add(overlayGCS);

        }

        //---------------------Init Lineseries an cartesian charts-------------------------------
        private void initTempOutside()
        {
            SeriesCollection series = new SeriesCollection();
            main.ccTempOutside.AxisX.Add(new Axis{});
            lsTempOutside.Title = "Humidity";
            lsTempOutside.Values = new ChartValues<double>();
            main.ccTempOutside.Series = series;
            series.Add(lsTempOutside);
            lsTempOutside.Stroke = Brushes.Blue;
            lsTempOutside.Fill = Brushes.Transparent;
            lsTempOutside.PointGeometry = null;
        }

        private void initHumidity ()
        {
            SeriesCollection series = new SeriesCollection();
            main.ccHumidity.AxisX.Add(new Axis { });
            lsHumidity.Title = "Humidity";
            lsHumidity.Values = new ChartValues<double>();
            main.ccHumidity.Series = series;
            series.Add(lsHumidity);
            lsHumidity.Stroke = Brushes.Blue;
            lsHumidity.Fill = Brushes.Transparent;
            lsHumidity.PointGeometry = null;
        }

        private void initTempInside()
        {
            SeriesCollection series = new SeriesCollection();
            main.ccTempInside.AxisX.Add(new Axis { });
            lsTempInside.Title = "Humidity";
            lsTempInside.Values = new ChartValues<double>();
            main.ccTempInside.Series = series;
            series.Add(lsTempInside);
            lsTempInside.Stroke = Brushes.Blue;
            lsTempInside.Fill = Brushes.Transparent;
            lsTempInside.PointGeometry = null;
        }

        private void initPressure()
        {
            SeriesCollection series = new SeriesCollection();
            main.ccAirPressure.AxisX.Add(new Axis { });
            lsPressure.Title = "Humidity";
            lsPressure.Values = new ChartValues<double>();
            main.ccAirPressure.Series = series;
            series.Add(lsPressure);
            lsPressure.Stroke = Brushes.Blue;
            lsPressure.Fill = Brushes.Transparent;
            lsPressure.PointGeometry = null;
        }

        private void initAltitude()
        {
            SeriesCollection series = new SeriesCollection();
            main.ccAltitude.AxisX.Add(new LiveCharts.Wpf.Axis
            {
                Title = "Höhe",
            });
            main.ccAltitude.LegendLocation = LegendLocation.Right;
            lsAltitude.Title = "Altitude";
            lsAltitude.Values = new ChartValues<double>();
            main.ccAltitude.Series = series;
            series.Add(lsAltitude);
            lsAltitude.Stroke = Brushes.Green;
            lsAltitude.Fill = Brushes.Transparent;
        }

        public void UpdateHeight(double newPoint)
        {
            
            Application.Current.Dispatcher.Invoke(new Action(() =>
                {
                    if (altitudeCounter > 80)
                    {
                        altitudeCounter = 81;
                        lsAltitude.Values.RemoveAt(0);
                    }
                    else
                    {
                        altitudeCounter++;
                    }
                    lsAltitude.Values.Add(newPoint);
                    main.ccAltitude.Update();
                }));            
        }

        public void UpdateHumidity(double newPoint)
        {
            Application.Current.Dispatcher.Invoke(new Action(() =>
            {
                if (humidityCounter > 80)
                {
                    humidityCounter = 81;
                    lsHumidity.Values.RemoveAt(0);
                }
                else
                {
                    humidityCounter++;
                }
                lsHumidity.Values.Add(newPoint);
                main.ccHumidity.Update();
                main.lblHumidity.Content = newPoint.ToString("0.##");
            }));
        }

        public void UpdateTempOutisde(double newPoint)
        {
            Application.Current.Dispatcher.Invoke(new Action(() =>
            {
                if (tempOutsideCounter > 80)
                {
                    tempOutsideCounter = 81;
                    lsTempOutside.Values.RemoveAt(0);
                }
                else
                {
                    tempOutsideCounter++;
                }
                lsTempOutside.Values.Add(newPoint);
                main.ccTempOutside.Update();
                main.lblTempOutside.Content = newPoint.ToString("0.##");
            }));
        }

        public void UpdateTempInside(double newPoint)
        {
            Application.Current.Dispatcher.Invoke(new Action(() =>
            {
                if (tempInsideCounter > 80)
                {
                    tempInsideCounter = 81;
                    lsTempInside.Values.RemoveAt(0);
                }
                else
                {
                    tempInsideCounter++;
                }
                lsTempInside.Values.Add(newPoint);
                main.ccTempInside.Update();
                main.lblTempInside.Content = newPoint.ToString("0.##");
                
            }));
        }

        public void UpdatePressure(double newPoint)
        {
            Application.Current.Dispatcher.Invoke(new Action(() =>
            {
                if (pressureCounter > 80)
                {
                    pressureCounter = 81;
                    lsPressure.Values.RemoveAt(0);
                }
                else
                {
                    pressureCounter++;
                }
                lsPressure.Values.Add(newPoint);
                main.ccAirPressure.Update();
                main.lblPressure.Content = newPoint.ToString("0.##");
            }));
        }

        public void UpdateGroundSpeed(double speed)
        {
            Application.Current.Dispatcher.Invoke(new Action(() =>
            {
                main.gGroundSpeed.Value = Math.Round(speed, 2);
            }));      
        }

        public void UpdateClimbRate(double climbRate)
        {
            Application.Current.Dispatcher.Invoke(new Action(() =>
            {
                main.gClimbRate.Value = Math.Round(climbRate, 2);
            }));      
        }

        public void UpdateMap(double longitude, double latitude, TARGET target)
        {
            if(latitude != 0 && longitude != 0)
            {
                Application.Current.Dispatcher.Invoke(new Action(() =>
                {

                if (target == TARGET.DEVICE)
                {
                    trackDevice.Points.Add(new PointLatLng(latitude, longitude));
                    if (main.cbDevice.IsChecked == true)
                    {
                            overlayDevice.IsVisibile = true;
                    }
                    else
                    {
                            overlayDevice.IsVisibile = false;
                    }

                    if (main.rbDevice.IsChecked == true)
                    {
                            main.gmap.Position = new PointLatLng(latitude, longitude);
                    }
                }
                else if(target == TARGET.GCS)
                {

                    trackGCS.Points.Add(new PointLatLng(latitude, longitude));
                    if (main.cbGCS.IsChecked == true)
                    {
                            overlayGCS.IsVisibile = true;
                    }
                    else
                    {
                            overlayGCS.IsVisibile = false;
                    }
                    if (main.rbGCS.IsChecked == true)
                    {
                            main.gmap.Position = new PointLatLng(latitude, longitude);
                    }
                }
                }));
            }

        }





        public void resetGraphic()
        {
            lsAltitude.Values.Clear();
            lsPressure.Values.Clear();
            lsHumidity.Values.Clear();
            lsTempInside.Values.Clear();
            lsTempOutside.Values.Clear();
        }
    }
}
