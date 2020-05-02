using System;
using System.Timers;
using System.IO.Ports;
using System.Windows;
using System.Windows.Controls;
using System.Collections.Generic;
using System.Threading;
using System.Windows.Media;
using ASYD_Projekt;

namespace GCS.SerialPort
{
    class SerialPortHandler
    {
        /*Global Instance declaration*/
        MainWindow main;

        System.IO.Ports.SerialPort sPort;
        System.Timers.Timer connectionTimer;

        bool init = false;


        /*Global Variable declaration*/
        Boolean portOpen = false;
        int connectionFailCounter = 0;
        Thread serialThread;

        public SerialPortHandler(MainWindow main)
        {
            this.main = main;
            AddMouseListener();
            TimerConfig();
            InitCOMPort();
            
        }

        private void TimerConfig()
        {
            connectionTimer = new System.Timers.Timer(2000);
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

            if(init == false)
            {
                sPort = new System.IO.Ports.SerialPort
                {
                    BaudRate = 115200,
                    
                    Parity = Parity.None,
                    StopBits = StopBits.One,
                    DataBits = 8,
                    Handshake = Handshake.None,
                    RtsEnable = true
                };
                sPort.DataReceived += new SerialDataReceivedEventHandler(DataReceive_Event);
                init = true;
            }

        }


        public void CmdConnect_Click(object sender, RoutedEventArgs e)
        {
            if (!portOpen)
            {
                try
                {

                    sPort.PortName  = main.cbComPort.Text;
                    sPort.Open();
                    portOpen = true;
                    main.txtCMD.AppendText(" \r\n Connected with " + sPort.PortName);
                    connectionTimer.Start();
                    serialThread = new Thread(readMsg);
                    sPort.DataReceived += new SerialDataReceivedEventHandler(DataReceive_Event);
                    serialThread.Start();
                }
                catch (Exception exp)
                {
                    MessageBox.Show(exp.ToString());
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
                    connectionTimer.Stop();
                }
            }
            else
            {
                main.txtCMD.AppendText(" \r\n No Open Port");
                connectionTimer.Stop();
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
        /*    if(connectionFailCounter > 10)
            {
                Application.Current.Dispatcher.Invoke(new Action(() =>
                {
                    main.txtCMD.AppendText(" \r\n target disconnected...");
                    connectionTimer.Stop();
                }));
            }
            else
            {
                Application.Current.Dispatcher.Invoke(new Action(() =>
                {
                    main.txtCMD.AppendText(" \r\n target is not responding...");
                }));
                connectionFailCounter++;
            }*/

        }


        //*****************Eventhandling****************************************
        public delegate void MessageReceivedHandler(Object sender);
        public event MessageReceivedHandler MsgReceived;

        protected virtual void  OnMsgReceived()
        {
            MsgReceived(this);
        }
        //**********************************************************************



        private void readMsg()
        {
            byte msgByte;
            int state = 0;
            int packetCounter = 0;
            int stringCounter = 0;
            List<char> rawString = new List<char>();

            while (portOpen)
            {
                try
            {
 
                    msgByte = (byte)sPort.ReadByte();

                    Application.Current.Dispatcher.Invoke(new Action(() =>
                    {
                        //  main.txtCMD.AppendText("Packet error");
                        main.txtCMD.AppendText(Convert.ToString(msgByte) + "\n");
                        main.txtCMD.ScrollToEnd();
                    }));

                }
            catch(Exception ex)
            {
                Application.Current.Dispatcher.Invoke(new Action(() =>
                {
                  //  main.txtCMD.AppendText("Packet error");
                    main.txtCMD.AppendText(ex.ToString());
                }));
            }
        }

    }

        private void DataReceive_Event(object sender, SerialDataReceivedEventArgs e)
        {
            connectionFailCounter = 0;
            connectionTimer.Stop();     //restart Timer
           // connectionTimer.Start();
            Application.Current.Dispatcher.Invoke(new Action(() =>
            {
                //  main.txtCMD.AppendText("Packet error");
                main.txtCMD.AppendText(sPort.ReadExisting());
            }));
        }

     }
}
