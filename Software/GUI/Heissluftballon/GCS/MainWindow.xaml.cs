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
        HLBUI balloonControl;
        SerialPortHandler sPortHandler;
        GCS.Model.Model_c model;



        UIControl guiControl;
        Thread guiUpdate;
        public MainWindow()
        {
            InitializeComponent();
            this.model = new Model_c();
            GmapControl mpaControl = new GmapControl(this);
            sPortHandler = new SerialPortHandler(this, model);
            
            balloonControl = new HLBUI(this);
            guiControl = new UIControl(this, sPortHandler, model, balloonControl);

            guiUpdate = new Thread(guiControl.updateGui);
            guiUpdate.Start();
            /**Delete after end*/
            balloonControl.UpdateHeight(10);
            balloonControl.UpdateHeight(4);
            balloonControl.UpdateHeight(6);
            balloonControl.UpdateHeight(8);
            balloonControl.UpdateHeight(9);

        }

        private void addListener()
        {
         
        }

        
        public TextBox getTxtCom()
        {
            return txtCMD;
        }


  
    }





}
