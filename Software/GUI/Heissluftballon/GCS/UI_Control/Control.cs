
using GCS.GCS_UI;
using GCS.HLB_UI;
using GCS.Model;
using GCS.SerialPort;
using System;
using System.Collections.Generic;
using System.Text.RegularExpressions;
using System.Threading;
using System.Windows;

namespace GCS.UI_Control
{
    class UIControl
    {

        //------------GPS variable---------------


        string rawString;


        //----------------
        readonly MainWindow main;
        readonly SerialPortHandler sPortHandler;
        readonly Model_c model;
        readonly HLBUI deviceGui;
        readonly GCSUI gcsGui;
        readonly GPScontrol gpsCtrl;

        int timeCounter = 0;
        bool update = false;
        public UIControl(MainWindow main, SerialPortHandler sPortHandler, Model_c model)
        {
            this.sPortHandler = sPortHandler;
            this.main = main;
            this.model = model;

            deviceGui = new HLBUI(main);
            gcsGui = new GCSUI(main);
            gpsCtrl = new GPScontrol(model, this);
            AddListener();
            ResetGraphic();
          //  initLogger();
        }

        private void AddListener()
        {
            this.sPortHandler.MsgReceived += new SerialPortHandler.MessageReceivedHandler(this.CalculateData);
            main.cmdResetGraphic.Click += new System.Windows.RoutedEventHandler(this.ResetGraphic_click);
        }

        private void ResetGraphic()
        {
            deviceGui.UpdateClimbRate(0);
            deviceGui.UpdateGroundSpeed(0);
            gcsGui.UpdateGroundSpeed(0);
            gcsGui.UpdateDistanceDiff(0);
            gcsGui.UpdateAltitudeDiff(0);
        }

        private void initLogger()
        {
            model.getLogger().Add("DateTimeNow;");
            model.getLogger().Add("Pressure;");
            model.getLogger().Add("TempInside;");
            model.getLogger().Add("TempOutside;");
            model.getLogger().Add("Humidity;");
            model.getLogger().Add("Time Device;");
            model.getLogger().Add("Latitude Device;");
            model.getLogger().Add("Longitude Device;");
            model.getLogger().Add("Altitude Device;");
            model.getLogger().Add("Time GCS;");
            model.getLogger().Add("Latitude GCS;");
            model.getLogger().Add("Longitude GCS;");
            model.getLogger().Add("Altitude GCS");
            
        }

        private void CalculateData(object sender)
        {
            //String aufteilen
            rawString = new string(model.getRawData().ToArray());

            string[] splittedRawData = Regex.Split(rawString, @"\$\!");

            char[] humidity     = splittedRawData[0].ToCharArray();
            char[] tempOutside  = splittedRawData[1].ToCharArray();
            char[] pressure     = splittedRawData[2].ToCharArray();
            char[] tempInside   = splittedRawData[3].ToCharArray();
            string gpsDevice    = splittedRawData[4];
            string gpsGCS       = splittedRawData[5];


            model.HumidityRaw       = Convert.ToUInt32(((byte)humidity[1])*256      + (byte)humidity[0]);
            model.TempOutsideRaw    = Convert.ToInt32(((byte)tempOutside[1]) * 256  + (byte)tempOutside[0]);
            model.PressureRaw       = Convert.ToUInt32(((byte)pressure[1]) * 256    + (byte)pressure[0]);
            model.TempInsideRaw     = Convert.ToInt32(((byte)tempInside[1]) * 256   + (byte)tempInside[0]);

            //split GPS Data
            gpsCtrl.SplitGPS(gpsDevice,    GPScontrol.GPS_TARGET.DEVICE);
            gpsCtrl.SplitGPS(gpsGCS,       GPScontrol.GPS_TARGET.GCS);

            //data Device
            double timeDiffD        =  gpsCtrl.TimeDiff(model.TimeDevice_1, model.TimeDevice);
            double dist2DD          = gpsCtrl.Distance2D(model.LatitudeDevice, model.LatitudeDevice_1, model.LongitudeDevice, model.LongitudeDevice_1);

            if(timeDiffD != 0)
            {
                double groundSpeedD = gpsCtrl.GroundSpeed(timeDiffD, dist2DD);
                double climbRateD = gpsCtrl.ClimbRate(timeDiffD, model.AltitudeDevice - model.AltitudeDevice_1);
                model.GroundSpeedDevice = groundSpeedD;
                model.ClimbRateDevice = climbRateD;
            }


            //data GCS
            double timeDiffG        = gpsCtrl.TimeDiff(model.TimeGCS_1, model.TimeGCS);
            double dist2DG          = gpsCtrl.Distance2D(model.LatitudeGCS, model.LatitudeGCS_1, model.LongitudeGCS, model.LongitudeGCS_1);
            if(timeDiffG != 0)
            {
                double groundSpeedG = gpsCtrl.GroundSpeed(timeDiffG, dist2DG);
                model.GroundSpeedGCS = groundSpeedG;
            }

            
            //data between device and GCS
            model.AltitudeDiff = model.AltitudeDevice - model.AltitudeGCS;
            model.Distance = gpsCtrl.Distance3D(gpsCtrl.Distance2D(model.LatitudeDevice, model.LatitudeGCS, model.LongitudeDevice, model.LongitudeGCS), model.AltitudeDevice, model.AltitudeGCS);

            UpdateModelData();
            update = true;
        }

        private void UpdateModelData()
        {
            model.Pressure = Convert.ToInt32(((double)(model.PressureRaw) - (-1566.6)) / 3.498);
            model.TempInsideRaw = (double)model.TempInsideRaw / 5;
            model.TempInside = (((((double)model.TempInsideRaw * 430 / 32768) / 100) - 1)/0.003851);
            model.TempOutside = -46.85 + 175.75 * ((double)model.TempOutsideRaw / 65536);
            model.Humidity = -6 + 125 * ((double)model.HumidityRaw / 65536);

            if(timeCounter == 0)
            {
            //update old GPS data
                model.TimeDevice_1 = model.TimeDevice;
                model.LatitudeDevice_1 = model.LatitudeDevice;
                model.LongitudeDevice_1 = model.LongitudeDevice;
                model.AltitudeDevice_1 = model.AltitudeDevice;

                model.TimeGCS_1 = model.TimeGCS;
                model.LatitudeGCS_1 = model.LatitudeGCS;
                model.LongitudeGCS_1 = model.LongitudeGCS;
                model.AltitudeGCS_1 = model.AltitudeGCS;

                //Add datat to Logger
                model.getLogger().Add(DateTime.Now.ToString());
                model.getLogger().Add(";");
                model.getLogger().Add(Convert.ToString(model.Pressure));
                model.getLogger().Add(";");
                model.getLogger().Add(Convert.ToString(model.TempInside));
                model.getLogger().Add(";");
                model.getLogger().Add(Convert.ToString(model.TempOutside));
                model.getLogger().Add(";");
                model.getLogger().Add(Convert.ToString(model.Humidity));
                model.getLogger().Add(";");
                model.getLogger().Add(Convert.ToString(model.TimeDevice));
                model.getLogger().Add(";");
                model.getLogger().Add(Convert.ToString(model.LatitudeDevice));
                model.getLogger().Add(";");
                model.getLogger().Add(Convert.ToString(model.LongitudeDevice));
                model.getLogger().Add(";");
                model.getLogger().Add(Convert.ToString(model.AltitudeDevice));
                model.getLogger().Add(";");
                model.getLogger().Add(Convert.ToString(model.TimeGCS));
                model.getLogger().Add(";");
                model.getLogger().Add(Convert.ToString(model.LatitudeGCS));
                model.getLogger().Add(";");
                model.getLogger().Add(Convert.ToString(model.LongitudeGCS));
                model.getLogger().Add(";");
                model.getLogger().Add(Convert.ToString(model.AltitudeGCS));
                model.getLogger().Add("\n");

            timeCounter++;
            }
            else
            {
                timeCounter++;
                if (timeCounter > 5)
                {
                    timeCounter = 0;
                }
            }
        }
        

        /// <summary>
        /// Periodic GUI update from other thread
        /// </summary>
        public void UpdateGui()
        {
            while (true)
            {
                if (update)
                {
                    deviceGui.UpdateHeight(model.AltitudeDevice);
                    deviceGui.UpdateMap(model.LongitudeGCS, model.LatitudeGCS, HLBUI.TARGET.GCS);
                    deviceGui.UpdateMap(model.LongitudeDevice, model.LatitudeDevice, HLBUI.TARGET.DEVICE);
                    deviceGui.UpdateHumidity(model.Humidity);
                    deviceGui.UpdatePressure(model.Pressure);
                    deviceGui.UpdateTempInside(model.TempInside);
                    deviceGui.UpdateTempOutisde(model.TempOutside);
                    deviceGui.UpdateClimbRate(model.ClimbRateDevice);
                    deviceGui.UpdateGroundSpeed(model.GroundSpeedDevice);

                    gcsGui.UpdateAltitudeDiff(model.AltitudeDiff);
                    gcsGui.UpdateDistanceDiff(model.Distance);
                    gcsGui.UpdateGroundSpeed(model.GroundSpeedGCS);
 
                    update = false;
                }
               Thread.Sleep(500);
            }
        }

        private void ResetGraphic_click(object sender, EventArgs e)
        {
            deviceGui.resetGraphic();
        }

        public void WriteTxt(string txt)
        {

            Application.Current.Dispatcher.Invoke(new Action(() =>
            {
                main.txtCMD.AppendText(txt + "\n");
            }));
        }


    }
}
