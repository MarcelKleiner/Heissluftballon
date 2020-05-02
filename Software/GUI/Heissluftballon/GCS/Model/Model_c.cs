using System.Collections.Generic;

namespace GCS.Model
{
    class Model_c
    {
        private List<char> rawData = new List<char>();

       // private List<string> logger = new List<string>();
        private List<string> logger = new List<string>();
        public Model_c()
        {

        }

        //raw data from USB Port

        public void SetRawData(List<char> rawData)
        {
          //  this.rawData.Clear();
            this.rawData = rawData;
        }
        public List<char> getRawData()
        {
            return this.rawData;
        }

        public List<string> getLogger()
        {
            return this.logger;
        }




        //GPS Data - Device
        public double TimeDevice { get; set; }            //Zeit
        public double AltitudeDevice { get; set; }         //Höhe
        public double LongitudeDevice { get; set; }     //Längengrad
        public double LatitudeDevice { get; set; }      //Breitengrad

        public double TimeDevice_1 { get; set; }            //Zeit_1
        public double AltitudeDevice_1 { get; set; }         //Höhe_1
        public double LongitudeDevice_1 { get; set; }     //Längengrad_1
        public double LatitudeDevice_1 { get; set; }      //Breitengrad_1
        //GPS Data - GCS
        public double TimeGCS { get; set; }            //Zeit
        public double AltitudeGCS { get; set; }         //Höhe
        public double LongitudeGCS { get; set; }       //Längengrad
        public double LatitudeGCS { get; set; }        //Breitengrad

        public double TimeGCS_1 { get; set; }            //Zeit_1
        public double AltitudeGCS_1 { get; set; }         //Höhe_1
        public double LongitudeGCS_1 { get; set; }       //Längengrad_1
        public double LatitudeGCS_1 { get; set; }        //Breitengrad_1

        // Distance / Speed

        public double GroundSpeedDevice { get; set; }
        public double ClimbRateDevice { get; set; }

        public double GroundSpeedGCS { get; set; }

        public double AltitudeDiff { get; set; }
        public double Distance { get; set; }

        //Sensor Data
        public uint HumidityRaw { get; set; }
        public double TempInsideRaw { get; set; }
        public int TempOutsideRaw { get; set; }
        public uint PressureRaw { get; set; }

        public double Humidity { get; set; }
        public double TempInside { get; set; }
        public double TempOutside { get; set; }
        public int Pressure { get; set; }






    }
}
