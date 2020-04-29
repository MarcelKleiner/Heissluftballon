
using GCS.GCS_UI;
using GCS.HLB_UI;
using GCS.Model;
using GCS.SerialPort;
using System;
using System.Text.RegularExpressions;
using System.Threading;
using System.Windows;

namespace GCS.UI_Control
{
    class UIControl
    {

        //------------GPS variable---------------


        string rawString;

        string gpsFormat;

        double time = 0;
        double latitude = 0;    //Breitengrad
        double longitude = 0;   //Längengrad
        double altitude = 0;    //höhe über Meer


        //----------------
        readonly MainWindow main;
        readonly SerialPortHandler sPortHandler;
        readonly Model_c model;
        readonly HLBUI deviceGui;
        readonly GCSUI gcsGui;
        GPScontrol gpsCtrl;

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
            model.TempInside = (((((double)model.TempInsideRaw * 390 / 32768) / 100) - 1));
            model.TempOutside = -46.85 + 175.75 * ((double)model.TempOutsideRaw / 65536);
            model.Humidity = -6 + 125 * ((double)model.HumidityRaw / 65536);

            //update old GPS data
            model.TimeDevice_1 = model.TimeDevice;
            model.LatitudeDevice_1 = model.LatitudeDevice;
            model.LongitudeDevice_1 = model.LongitudeDevice;
            model.AltitudeDevice_1 = model.AltitudeDevice;

            model.TimeGCS_1 = model.TimeGCS;
            model.LatitudeGCS_1 = model.LatitudeGCS;
            model.LongitudeGCS_1 = model.LongitudeGCS;
            model.AltitudeGCS_1 = model.AltitudeGCS;
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

        public void writeTxt(string txt)
        {

            Application.Current.Dispatcher.Invoke(new Action(() =>
            {
                main.txtCMD.AppendText(txt + "\n");
            }));
        }


    }
}
