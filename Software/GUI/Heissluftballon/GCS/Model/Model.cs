using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GCS.Model
{
    class Model
    {
        private List<char> rawData = new List<char>();
        public Model()
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



        //GPS Data
        public int Altitude { get; set; }
        public double Longitude { get; set; }
        public double Latitude { get; set; }

        //Sensor Data
        public uint humidity { get; set; }
        public int tempInside { get; set; }
        public int tempOutside { get; set; }

        //Speed Data
        public int GroundSpeed { get; set; }
        public int ClimbRate { get; set; }





    }
}
