
using GCS.SerialPort;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Windows.Threading;

namespace GCS.UI_Control
{
    class UIControl
    {

        MainWindow main;
        SerialPortHandler sPortHandler;
        public UIControl(MainWindow main, SerialPortHandler sPortHandler)
        {
            this.sPortHandler = sPortHandler;
            this.main = main;
            addListener();
        }

        private void addListener()
        {
            this.sPortHandler.MsgReceived += new SerialPortHandler.MessageReceivedHandler(this.updateGui);
        }
          

        public void updateGui(object sender)
        {
            main.getTxtCom().Dispatcher.Invoke(() =>
            {
                main.getTxtCom().AppendText("hallo\n");
            });
        }



    }
}
