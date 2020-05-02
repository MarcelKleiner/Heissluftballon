using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GCS.Model
{
    class Logger
    {
        StreamWriter fsw;
        Model_c model;

        string logHeader;
        int logCounter = 0;
        public Logger(Model_c model)
        {
            this.model = model;
            this.logHeader = ("DateTimeNow; Pressure; TempInside; TempOutside; Humidity; Time Device;Latitude Device;Longitude Device;Altitude Device;Time GCS;Latitude GCS;Longitude GCS;Altitude GCS");
        }

        public void logg()
        {
            fsw = new StreamWriter("dataLog" + "_" + logCounter +".log");
            fsw.WriteLine(logHeader);
 
                foreach(string s in model.getLogger())
                {
                    fsw.Write(s);
                }
            
            fsw.Close();
            logCounter++;
        }






    }
}
