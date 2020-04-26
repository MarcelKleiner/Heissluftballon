
using GCS.HLB_UI;
using GCS.Model;
using GCS.SerialPort;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Windows.Threading;

namespace GCS.UI_Control
{
    class UIControl
    {

        MainWindow main;
        SerialPortHandler sPortHandler;
        Model_c model;
        HLBUI deviceGui;

        bool update = false;
        public UIControl(MainWindow main, SerialPortHandler sPortHandler, Model_c model, HLBUI deviceGui)
        {
            this.sPortHandler = sPortHandler;
            this.main = main;
            this.model = model;
            this.deviceGui = deviceGui;
            addListener();
        }

        private void addListener()
        {
            this.sPortHandler.MsgReceived += new SerialPortHandler.MessageReceivedHandler(this.calculateData);
        }
          
        private void calculateData(object sender)
        {
            model.pressure = Convert.ToInt32(((double)(model.pressureRaw) - (-1566.6)) / 3.498);
            model.tempInside = (((((double)model.tempInsideRaw * 390 / 32768)/100)-1));
            model.tempOutside = -46.85+175.75*((double)model.tempOutsideRaw / 65536);
            model.humidity = -6 + 125 * ((double)model.humidityRaw / 65536);
            update = true;
        }

        public void updateGui()
        {
            while (true)
            {
                if (update)
                {

                    deviceGui.UpdateHeight(100);
                    deviceGui.UpdateHumidity(model.humidity);
                    deviceGui.UpdatePressure(model.pressure);
                    deviceGui.UpdateTempInside(model.tempInside);
                    deviceGui.UpdateTempOutisde(model.tempOutside);

                    update = false;
                }
                Thread.Sleep(200);
            }


        }



    }
}
