using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GCS.Model
{
    class Model
    {

        public Model()
        {

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
