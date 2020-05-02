using GCS.HLB_UI;
using GCS.MapControl;
using GCS.SerialPort;
using GCS.UI_Control;
using LiveCharts;
using LiveCharts.Wpf;
using System.Threading;
using System.Windows;
using GCS.Model;
using System.Windows.Controls;

namespace GCS
{
    /// <summary>
    /// Interaktionslogik für MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {

        SerialPortHandler sPortHandler;
        Model_c model;
        Logger logger;
        UIControl guiControl;
        Thread guiUpdate;
        public GMap.NET.WindowsForms.GMapControl gmap;

        public MainWindow()
        {
            InitializeComponent();
            gmap = new GMap.NET.WindowsForms.GMapControl();
            model = new Model_c();
            logger = new Logger(model);
            GmapControl mpaControl = new GmapControl(this);
            sPortHandler = new SerialPortHandler(this, model);
            guiControl = new UIControl(this, sPortHandler, model);

            guiUpdate = new Thread(guiControl.UpdateGui);
            guiUpdate.Start();
        }

        private void CmdLog_Click(object sender, RoutedEventArgs e)
        {
            logger.logg();
        }
    }





}
