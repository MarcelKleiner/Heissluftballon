using LiveCharts;
using LiveCharts.Wpf;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace GCS.GCS_UI
{
    class GCSUI
    {
        MainWindow main;

        public GCSUI(MainWindow main)
        {
            this.main = main;
            InitComponents();
        }


        private void InitComponents()
        {

        }

        public void UpdateGroundSpeed(double speed)
        {
            Application.Current.Dispatcher.Invoke(new Action(() =>
            {
                main.gGroundSpeedGCS.Value = Math.Round(speed, 2); ;
            }));   
        }

        public void UpdateAltitudeDiff(double altitudeDiff)
        {
            Application.Current.Dispatcher.Invoke(new Action(() =>
            {
                main.gHeightDifference.Value = Math.Round(altitudeDiff, 2); ;
            }));
        }

        public void UpdateDistanceDiff(double distanceDiff)
        {
            Application.Current.Dispatcher.Invoke(new Action(() =>
            {
                main.gDistanceDifference.Value = Math.Round(distanceDiff, 2); ;
            }));
        }





    }
}
