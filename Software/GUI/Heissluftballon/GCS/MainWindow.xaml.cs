
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using GCS.MapControl;
using LiveCharts;
using LiveCharts.Wpf;

namespace GCS
{
    /// <summary>
    /// Interaktionslogik für MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
            GmapControl mpaControl = new GmapControl(this);


            cChart.AxisX.Add(new LiveCharts.Wpf.Axis
            {
                Title = "Höhe",
                Labels = new[] {"1","2", "3", "4", "5", "6", "7", "8", "9", "10"}
             
            });
            cChart.LegendLocation = LiveCharts.LegendLocation.Right;
            







            cChart.Series.Clear();
            SeriesCollection series = new SeriesCollection();
            series.Add(new LineSeries() { Title = "Höhe Device", Values = new ChartValues<double> { 1, 2, 3, 3, 5, 6,8,5,1,1,4,6,7,2,3 } });

            cChart.Series = series;

        }
    }
}
