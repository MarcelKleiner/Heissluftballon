using GCS.Model;
using System;
using GCS.UI_Control;

namespace GCS.UI_Control
{
    class GPScontrol
    {

        public enum GPS_TARGET
        {
            DEVICE,
            GCS
        };

        UIControl control;
        Model_c model;
        public GPScontrol(Model_c model, UIControl control)
        {
            this.control = control;
            this.model = model;
        }

        /// <summary>
        /// Splits the NMEA0183 string in lat, long an heigth
        /// only GPGGA supportet because the altitude is not available in GPRMC
        /// </summary>
        /// <param name="nmea0183"></param>
        public void SplitGPS(string nmea0183, GPS_TARGET target)
        {

            string[] splittedGPS = nmea0183.Split(',');
            if (splittedGPS[0] == "$GPGGA")
            {
                switch (target)
                {
                    case GPS_TARGET.GCS:
                        model.TimeGCS = Convert.ToDouble(splittedGPS[1]);
                        model.LatitudeGCS = LatitudeConverter(splittedGPS[2]);
                        model.LongitudeGCS = LongitudeConverter(splittedGPS[4]);
                        model.AltitudeGCS = Convert.ToDouble(splittedGPS[9]);
                        control.writeTxt("GCS GPS received - GPGGA");
                        break;
                    case GPS_TARGET.DEVICE:
                        model.TimeDevice = Convert.ToDouble(splittedGPS[1]);
                        model.LatitudeDevice = LatitudeConverter(splittedGPS[2]);
                        model.LongitudeDevice = LongitudeConverter(splittedGPS[4]);
                        model.AltitudeDevice = Convert.ToDouble(splittedGPS[9]);
                        control.writeTxt("Device GPS received - GPGGA");
                        break;
                    default:
                        break;
                }
            }
            if(splittedGPS[0] == "$GPRMC")
            {
                switch (target)
                {
                    case GPS_TARGET.GCS:
                        model.TimeGCS = Convert.ToDouble(splittedGPS[1]);
                        model.LatitudeGCS = LatitudeConverter(splittedGPS[3]);
                        model.LongitudeGCS = LongitudeConverter(splittedGPS[5]);
                        control.writeTxt("GCS GPS received - GPRMC");
                        break;
                    case GPS_TARGET.DEVICE:
                        model.TimeDevice = Convert.ToDouble(splittedGPS[1]);
                        model.LatitudeDevice = LatitudeConverter(splittedGPS[3]);
                        model.LongitudeDevice = LongitudeConverter(splittedGPS[5]);
                        control.writeTxt("Device GPS received - GPRMC");
                        break;
                    default:
                        break;
                }
            }
        }


        /// <summary>
        /// Convert latitude from NMEA0183 in latitude in ° ' "
        /// </summary>
        /// <param name="latitude"></param>
        /// <returns>double latitude in ° ' "</returns>
        private double LatitudeConverter(string latitude)
        {
            double lat = Convert.ToDouble(latitude);
            lat /= 100;
            string[] slatitude = lat.ToString().Split('.');
            lat = Convert.ToDouble(slatitude[0] + "." + (Convert.ToDouble(slatitude[1]) / 60).ToString("######"));
            return lat;
        }

        /// <summary>
        /// Convert longitude from NMEA0183 in longitude in ° ' "
        /// </summary>
        /// <param name="longitude"></param>
        /// <returns></returns>
        private double LongitudeConverter(string longitude)
        {
            double lng = Convert.ToDouble(longitude);
            lng /= 100;
            string[] slatitude = lng.ToString().Split('.');
            lng = Convert.ToDouble(slatitude[0] + "." + (Convert.ToDouble(slatitude[1]) / 60).ToString("######"));
            return lng;
        }

        /// <summary>
        /// Calculate the 2D distanze between to LatLong points
        /// </summary>
        /// <param name="lat1"></param>
        /// <param name="lat2"></param>
        /// <param name="lon1"></param>
        /// <param name="lon2"></param>
        /// <returns></returns>
        public double Distance2D(double lat1, double lat2, double lon1, double lon2)
        {
            lon1 = ToRadians(lon1);
            lon2 = ToRadians(lon2);
            lat1 = ToRadians(lat1);
            lat2 = ToRadians(lat2);

            // Haversine formula  
            double dlon = lon2 - lon1;
            double dlat = lat2 - lat1;
            double a = Math.Pow(Math.Sin(dlat / 2), 2) +
                       Math.Cos(lat1) * Math.Cos(lat2) *
                       Math.Pow(Math.Sin(dlon / 2), 2);

            double c = 2 * Math.Asin(Math.Sqrt(a));
            // calculate the result 
            return (c * 6371);
        }

        /// <summary>
        /// Helperfunction for 2D distance calculation
        /// </summary>
        /// <param name="angleIn10thofaDegree"></param>
        /// <returns></returns>
        public double ToRadians(double angleIn10thofaDegree)
        {
            return (angleIn10thofaDegree * Math.PI) / 180;
        }

        /// <summary>
        /// Calculate the 3D distance between the ground (2D) distance an to altitude distance
        /// </summary>
        /// <param name="distance2d"></param>
        /// <param name="altitude1"></param>
        /// <param name="altitude2"></param>
        /// <returns></returns>
        public double Distance3D(double distance2d, double altitude1, double altitude2)
        {
            double altitudeDiff = altitude1 - altitude2;
            double diff = Math.Pow(distance2d*1000, 2) + Math.Pow(altitudeDiff, 2);
            return Math.Sqrt(diff);
        }


        public double GroundSpeed(double timeDiff, double distance2D)
        {
           return distance2D / timeDiff;
        }

        public double ClimbRate(double timeDiff, double altitudeDiff)
        {
           return (altitudeDiff ) / timeDiff;
        }

        public double TimeDiff(double t1, double t2)
        {
            int time1 = (int)t1;
            int time2 = (int)t2;

            int h1 = time1 / 10000;
            int m1 = (time1 - h1 * 10000) / 100;
            int s1 = (time1 - h1 * 1000 - m1 * 100);

            int h2 = time2 / 10000;
            int m2 = (time2 - h2 * 10000) / 100;
            int s2 = (time2 - h2 * 1000 - m2 * 100);

            double time1inS = h1 * 3600 + m1 * 60 + s1;
            double time2inS = h2 * 3600 + m2 * 60 + s2;
            return (time2inS - time1inS);
        }

    }
}
