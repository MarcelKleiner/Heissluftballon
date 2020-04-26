
using LiveCharts;
using LiveCharts.Wpf;
using System;
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

        int humidityCounter = 0;
        int tempInsideCounter = 0;
        int tempOutsideCounter = 0;
        int pressureCounter = 0;
        int altitudeCounter = 0;

        Random r = new Random(); 

        public HLBUI(MainWindow main)
        {
            this.main = main;
            initHumidity();
            initAltitude();
            initPressure();
            initTempInside();
            initTempOutside();
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
                    main.gClimbRate.Value = 2;
                    main.gGroundSpeed.Value = 15.4;
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





    }
}
