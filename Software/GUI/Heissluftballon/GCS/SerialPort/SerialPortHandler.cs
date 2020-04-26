using System;
using System.Timers;
using System.IO.Ports;
using System.Windows;
using System.Windows.Controls;
using System.Collections.Generic;
using System.Threading;

namespace GCS.SerialPort
{
    class SerialPortHandler
    {
        /*Global Instance declaration*/
        MainWindow main;
        GCS.Model.Model_c model;

        System.IO.Ports.SerialPort sPort;
        System.Timers.Timer connectionTimer;



        /*Global Variable declaration*/
        Boolean portOpen = false;
        int connectionFailCounter = 0;
        char[] data;
        Thread serialThread;

        public SerialPortHandler(MainWindow main,GCS.Model.Model_c model)
        {
            this.main = main;
            this.model = model;
            AddMouseListener();
            TimerConfig();
            InitCOMPort();
            serialThread = new Thread(readMsg);
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
                    serialThread.Start();
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
                    portOpen = false;
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



        private void readMsg()
        {
            byte msgByte;
            int state = 0;

            int bufCounter = 0;
            int packetCounter = 0;

            byte[] buffer = new byte[2];
            List<char> gpsGcs = new List<char>();
            List<char> gpsDevice = new List<char>();
            while (portOpen)
            {
                   msgByte = (byte)sPort.ReadByte();


                switch (state)
                {
                    case 0:
                        if(msgByte == '%')
                        {
                            state = 1;
                        }
                        break;
                    case 1:
                        if (msgByte == '*')
                        {
                            state = 2;
                        }
                        break;
                    case 2:
                        if (msgByte == '!')
                        {
                            state = 3;
                        }
                        break;
                    case 3:
                        //---------------------Humidity------------------------------
                        if(bufCounter == 0)
                        {
                            buffer[bufCounter] = msgByte;
                            bufCounter++;
                        }
                        else
                        {
                            buffer[bufCounter] = msgByte;
                            model.humidityRaw = buffer[0] + ((uint)buffer[1] << 8);
                            bufCounter = 0;
                            state = 4;
                        }
                        break;
                    case 4:
                        //---------------------Temp Outside------------------------------
                        if (bufCounter == 0)
                        {
                            buffer[bufCounter] = msgByte;
                            bufCounter++;
                        }
                        else
                        {
                            buffer[bufCounter] = msgByte;
                            model.tempOutsideRaw = buffer[0] + ((int)buffer[1] << 8);
                            bufCounter = 0;
                            state = 5;
                        }
                        break;
                    case 5:
                        //---------------------Pressure------------------------------
                        if (bufCounter == 0)
                        {
                            buffer[bufCounter] = msgByte;
                            bufCounter++;
                        }
                        else
                        {
                            buffer[bufCounter] = msgByte;
                            model.pressureRaw = buffer[0] + ((uint)buffer[1] << 8);
                            bufCounter = 0;
                            state = 6;
                        }
                        break;
                    case 6:
                        //---------------------Temp Inside------------------------------
                        if (bufCounter == 0)
                        {
                            buffer[bufCounter] = msgByte;
                            bufCounter++;
                        }
                        else
                        {
                            buffer[bufCounter] = msgByte;
                            model.tempInsideRaw = buffer[0] + ((int)buffer[1] << 8);
                            bufCounter = 0;
                            state = 7;
                        }
                        break;
                    case 7:
                        if((bufCounter > 0 && msgByte == '$') ||(bufCounter > 80))
                        {
                            model.setGpsGCSRaw(gpsGcs);
                            bufCounter=0;
                            state = 8;
                        }
                        else
                        {
                            bufCounter++;
                            gpsGcs.Add((char)msgByte);
                        }
                        break;
                    case 8:
                        if ((bufCounter > 0 && msgByte == '$' )||( bufCounter > 80))
                        {
                            model.setGpsDeviceRaw(gpsDevice);
                            bufCounter = 0;
                            state = 0;
                            OnMsgReceived();
                        }
                        else
                        {
                            bufCounter++;
                            gpsDevice.Add((char)msgByte);
                        }
                        break;       
                    default:
                        break;
                }


                packetCounter++;
                if(packetCounter > 190)
                {
                    OnMsgReceived();
                    state = 0;
                    bufCounter = 0;
                    packetCounter = 0;
                }


            }
        }

        private void DataReceive_Event(object sender, SerialDataReceivedEventArgs e)
        {
            connectionFailCounter = 0;
            connectionTimer.Stop();     //restart Timer
            connectionTimer.Start();

       
            

        }





        }
}
