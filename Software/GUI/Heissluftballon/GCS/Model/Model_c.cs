using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GCS.Model
{
    class Model_c
    {
        private List<char> rawData = new List<char>();

        private List<char> gpsDeviceRaw = new List<char>();
        private List<char> gpsGCSRaw = new List<char>();
        public Model_c()
        {

        }

        //raw data from USB Port

        public void setRawData(char[] rawData)
        {
            this.rawData.Clear();
            this.rawData = rawData.ToList<char>();
        }
        public List<char> getRawData()
        {
            return this.rawData;
        }


        //GPS raw data
        public void setGpsDeviceRaw(List<char> gpsList)
        {
            gpsDeviceRaw = gpsList;
        }
        public List<char> getGpsDeviceRaw()
        {
            return this.gpsDeviceRaw;
        }

        public void setGpsGCSRaw(List<char> gpsList)
        {
            gpsGCSRaw = gpsList;
        }
        public List<char> getGpsGCSRaw()
        {
            return this.gpsGCSRaw;
        }
        //GPS Data
        public int AltitudeDeivce { get; set; }
        public double LongitudeDeivce { get; set; }
        public double LatitudeDeivce { get; set; }

        //Sensor Data
        public uint humidityRaw { get; set; }
        public int tempInsideRaw { get; set; }
        public int tempOutsideRaw { get; set; }
        public uint pressureRaw { get; set; }

        public double humidity { get; set; }
        public double tempInside { get; set; }
        public double tempOutside { get; set; }
        public int pressure { get; set; }

        //Speed Data
        public int GroundSpeed { get; set; }
        public int ClimbRate { get; set; }





    }
}
