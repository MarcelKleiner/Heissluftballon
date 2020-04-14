using GCS.HLB_UI;
using GCS.MapControl;
using GCS.SerialPort;
using LiveCharts;
using LiveCharts.Wpf;
using System.Threading;
using System.Windows;
using GCS.Model;




namespace GCS
{
    /// <summary>
    /// Interaktionslogik für MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        HLBUI balloonControl;
        SerialPortHandler sPortHandler;
        GCS.Model.Model model;
        public MainWindow()
        {
            InitializeComponent();
            GmapControl mpaControl = new GmapControl(this);
            balloonControl = new HLBUI(this);
            sPortHandler = new SerialPortHandler(this, this.model);

            /**Delete after end*/
            balloonControl.UpdateHeight(10);
            balloonControl.UpdateHeight(4);
            balloonControl.UpdateHeight(6);
            balloonControl.UpdateHeight(8);
            balloonControl.UpdateHeight(9);
        }


    }
}
