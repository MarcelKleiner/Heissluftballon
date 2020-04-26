
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

        //------------GPS variable---------------
        enum GPS_FORMAT
        {
            GPRMC,
            GPGGA
        };
        char[] buffer = new char[20];
        int counter = 0;


        //----------------
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
            this.sPortHandler.MsgReceived += new SerialPortHandler.MessageReceivedHandler(this.updateGPS);
        }
          
        private void calculateData(object sender)
        {
            model.pressure = Convert.ToInt32(((double)(model.pressureRaw) - (-1566.6)) / 3.498);
            model.tempInside = (((((double)model.tempInsideRaw * 390 / 32768)/100)-1));
            model.tempOutside = -46.85+175.75*((double)model.tempOutsideRaw / 65536);
            model.humidity = -6 + 125 * ((double)model.humidityRaw / 65536);
            update = true;
        }

        private void updateGPS(object sender)
        {
            int state = 1;
            GPS_FORMAT format = GPS_FORMAT.GPGGA;

            foreach(char data in model.getGpsGCSRaw())
            {
                switch (state)
                {
                    case 1:
                        if(data == 'G')
                        {
                            state = 2;
                        }
                        break;
                    case 2:
                        if (data == 'P'){
                            state = 3;
                        }
                        break;
                    case 3:
                        if (data == 'R')
                        {
                            format = GPS_FORMAT.GPRMC;
                            state = 4;
                        }
                        else if(data == 'G')
                        {
                            format = GPS_FORMAT.GPGGA;
                            state = 4;
                        }
                        break;
                    case 4:
                        if(data == 'C' ||data == 'A')
                        {
                            state = 5; //daten beginnen
                        }
                        break;
                    case 5:
                        //--------------Zeit ermitteln---------------
                        if(data == ',')
                        {
                            if(counter > 0)
                            {
                                if(data == ',')
                                {
                                    counter = 0;
                                    state = 6;
                                    //Daten in model speichern
                                }
                                buffer[counter - 1] = data;
                            }
                            counter++;
                        }
                        break;
                    case 6:
                        //------------------Breitengrad------------------------
                        if(format == GPS_FORMAT.GPGGA)
                        {
                            if(data == ',')
                            {
                                state = 7;
                            }
                            else
                            {
                                buffer[counter] = data;
                            }
                        }else if(format == GPS_FORMAT.GPRMC)
                        {

                        }
                        break;
                    case 7:
                        break;
                    case 8:
                        break;
                    case 9:
                        break;
                    case 10:
                        break;
                    case 11:
                        break;
                    case 12:
                        break;
                    default:
                        break;
                }
            }
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
