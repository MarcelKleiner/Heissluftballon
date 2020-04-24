using System;
using System.Timers;
using System.IO.Ports;
using System.Windows;
using System.Windows.Controls;


namespace GCS.SerialPort
{
    class SerialPortHandler
    {
        /*Global Instance declaration*/
        MainWindow main;
        GCS.Model.Model model;

        System.IO.Ports.SerialPort sPort;
        Timer connectionTimer;



        /*Global Variable declaration*/
        Boolean portOpen = false;
        int connectionFailCounter = 0;
        char[] data;


        public SerialPortHandler(MainWindow main,GCS.Model.Model model)
        {
            this.main = main;
            this.model = model;
            AddMouseListener();
            TimerConfig();
            InitCOMPort();
        }

        private void TimerConfig()
        {
            connectionTimer = new Timer(2000);
            connectionTimer.Elapsed += OnTimedEvent;
            connectionTimer.AutoReset = true;
            connectionTimer.Enabled = true;
            connectionTimer.Stop();
        }

        private void AddMouseListener()
        {
            main.cmdConnect.Click += new RoutedEventHandler(CmdConnect_Click);
            main.cmdDisconnect.Click += new RoutedEventHandler(CmdDisconnect_Click);
            main.cmdRefresh.Click += new RoutedEventHandler(CmdRefresh_Click);
            main.txtCMD.TextChanged += new TextChangedEventHandler(TxtCMD_TextChanged);
        }

        private void InitCOMPort()
        {
            string[] serialPorts = System.IO.Ports.SerialPort.GetPortNames();
            main.cbComPort.Items.Clear();
            foreach (string portName in serialPorts)
            {
                main.cbComPort.Items.Add(portName);
            }
        }


        public void CmdConnect_Click(object sender, RoutedEventArgs e)
        {
            if (!portOpen)
            {
                try
                {
                    sPort = new System.IO.Ports.SerialPort
                    {
                        BaudRate = 115200,
                        PortName = main.cbComPort.Text,
                        Parity = Parity.None,
                        StopBits = StopBits.One,
                        DataBits = 8,
                        Handshake = Handshake.None,
                        RtsEnable = true
                    };
                    sPort.DataReceived += new SerialDataReceivedEventHandler(DataReceive_Event);
                    sPort.Open();
                    portOpen = true;
                    main.txtCMD.AppendText(" \r\n Connected with " + sPort.PortName);
                    connectionTimer.Start();
                }
                catch (Exception)
                {
                    main.txtCMD.AppendText(" \r\n Connection to Target failed");
                    if (portOpen)
                    {
                        sPort.Close();
                        portOpen = false;
                    }

                }
            }
           
        }

        public void CmdDisconnect_Click(object sender, RoutedEventArgs e)
        {
            if (portOpen)
            {
                try
                {
                    string portName = sPort.PortName;       //get actual comport name
                    sPort.Close();                          //close COM port
                    main.txtCMD.AppendText(" \r\n Port " + portName + " disconnected");
                    portOpen = false;                       //reset portOpen flag
                    connectionTimer.Stop();
                }
                catch
                {
                    main.txtCMD.AppendText(" \r\n Disconnection failed");
                }
            }
            else
            {
                main.txtCMD.AppendText(" \r\n No Open Port");
            }
        }

        public void CmdRefresh_Click(object sender, RoutedEventArgs e)
        {
            InitCOMPort();  //refresch Comports by calling InitCOMPort
        }


        public void TxtCMD_TextChanged(object sender, TextChangedEventArgs e)
        {
            main.txtCMD.ScrollToEnd();
        }

        /// <summary>
        /// Periodic connection check
        /// </summary>
        /// <param name="source"></param>
        /// <param name="e"></param>
        private void OnTimedEvent(Object source, ElapsedEventArgs e)
        {
            if(connectionFailCounter > 4)
            {
                Application.Current.Dispatcher.Invoke(new Action(() =>
                {
                    main.txtCMD.AppendText(" \r\n target disconnected...");
                }));
                connectionTimer.Stop();
                sPort.Close();
                portOpen = false;
            }
            else
            {
                Application.Current.Dispatcher.Invoke(new Action(() =>
                {
                    main.txtCMD.AppendText(" \r\n target is not responding...");
                }));
                connectionFailCounter++;
            }

        }


        //*****************Eventhandling****************************************
        public delegate void MessageReceivedHandler(Object sender);
        public event MessageReceivedHandler MsgReceived;

        protected virtual void  OnMsgReceived()
        {
            MsgReceived(this);
        }
        //**********************************************************************


        private void DataReceive_Event(object sender, SerialDataReceivedEventArgs e)
        {
            connectionFailCounter = 0;
            connectionTimer.Stop();     //restart Timer
            connectionTimer.Start();

            System.IO.Ports.SerialPort sp = (System.IO.Ports.SerialPort)sender;

            int bytes = sp.BytesToRead;
            char[] buffer = new char[bytes];
            sp.Read(buffer, 0, bytes);

          //  model.setRawData(buffer);
            OnMsgReceived();

        }





        }
}
