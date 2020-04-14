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
        SeriesCollection series = new SeriesCollection();
        LineSeries lineSeries = new LineSeries();
        int counter = 0;
        Random r = new Random(); 

        public HLBUI(MainWindow main)
        {
            this.main = main;
            InitComponents();
        }

        private void InitComponents()
        {
            //init cartesianChart
            main.ccAltitude.AxisX.Add(new LiveCharts.Wpf.Axis
            {
                Title = "Höhe",
            });
            main.ccAltitude.LegendLocation = LegendLocation.Right;
            lineSeries.Title = "Altitude";
            lineSeries.Values = new ChartValues<double>();
            main.ccAltitude.Series = series;
            series.Add(lineSeries);
            lineSeries.Stroke = Brushes.Green;
            lineSeries.Fill = Brushes.Transparent;
            //init groundspeed and climbrate gauge
            main.gClimbRate.Value = 2;
            main.gGroundSpeed.Value = 15.4;

        }

        public void UpdateHeight(double newPoint)
        {
            
                Application.Current.Dispatcher.Invoke(new Action(() =>
                {
                    if (counter > 20)
                    {
                        lineSeries.Values.RemoveAt(0);
                    }
                    else
                    {
                        counter++;
                    }
                    lineSeries.Values.Add(newPoint);
                    main.ccAltitude.Update();
                }));            
        }







    }
}
