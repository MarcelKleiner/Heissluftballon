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
        GCS.Model.Model model;
        UIControl guiControl;
        public MainWindow()
        {
            InitializeComponent();
            GmapControl mpaControl = new GmapControl(this);
            guiControl = new UIControl(this);
            balloonControl = new HLBUI(this);
            sPortHandler = new SerialPortHandler(this, this.model);

            /**Delete after end*/
            balloonControl.UpdateHeight(10);
            balloonControl.UpdateHeight(4);
            balloonControl.UpdateHeight(6);
            balloonControl.UpdateHeight(8);
            balloonControl.UpdateHeight(9);
        }



        

        public void main(){
            while (true)
            {
                txtCMD.AppendText
            }
        }
    }





}
