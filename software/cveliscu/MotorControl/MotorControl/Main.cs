using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO.Ports;
using System.Threading;
using System.IO;

namespace MotorControl
{
    public partial class Main : Form
    {
        static bool _continue;
        static SerialPort _serialPort;

        public Main()
        {
            InitializeComponent();
        }

        private void Main_Load(object sender, EventArgs e)
        {
            btnDisconnect.Visible = false;

            string[] ports = SerialPort.GetPortNames();
            if (ports != null)
            {
                cmbPort.Items.Clear();
                foreach (string port in ports)
                    cmbPort.Items.Add(port);
            }
            if (cmbPort.Items.Count > 0)
                cmbPort.SelectedIndex = 0;

            cmbSpeed.Items.Clear();
            cmbSpeed.Items.Add("9600");
            cmbSpeed.Items.Add("19200");
            cmbSpeed.Items.Add("38400");
            cmbSpeed.Items.Add("57600");
            cmbSpeed.Items.Add("115200");
            cmbSpeed.SelectedIndex = 4;

            cmbBits.Items.Clear();
            cmbBits.Items.Add("5");
            cmbBits.Items.Add("6");
            cmbBits.Items.Add("7");
            cmbBits.Items.Add("8");
            cmbBits.SelectedIndex = 3;

            cmbParity.Items.Clear();
            cmbParity.Items.Add("None");
            cmbParity.Items.Add("Even");
            cmbParity.Items.Add("Odd");
            cmbParity.Items.Add("Mark");
            cmbParity.Items.Add("Space");
            cmbParity.SelectedIndex = 0;

            cmbStopBits.Items.Clear();
            cmbStopBits.Items.Add("None");
            cmbStopBits.Items.Add("1");
            cmbStopBits.Items.Add("1.5");
            cmbStopBits.Items.Add("2");
            cmbStopBits.SelectedIndex = 0;

            cmbHandshake.Items.Clear();
            cmbHandshake.Items.Add("None");
            cmbHandshake.Items.Add("RTS");
            cmbHandshake.Items.Add("RTS / XOn-XOff");
            cmbHandshake.Items.Add("XOn-XOff");
            cmbHandshake.SelectedIndex = 0;

            cmbParameter.Items.AddRange(Enum.GetNames(typeof(DriveParameterType)));
        }

        public static void Read()
        {
            while (_continue)
            {
                try
                {
                    string message = _serialPort.ReadLine();
                    Console.WriteLine(message);
                }
                catch (TimeoutException) { }
            }
        }

        private void btnConnect_Click(object sender, EventArgs e)
        {
            _serialPort = new SerialPort();

            if (cmbPort.SelectedIndex >= 0)
                _serialPort.PortName = cmbPort.SelectedItem.ToString();
            else
            {
                Log("Error: Invalid COM port.", Color.Red);
                return;
            }
            if (cmbSpeed.SelectedIndex >= 0)
            {
                int speed;
                if (Int32.TryParse(cmbSpeed.SelectedItem.ToString(), out speed))
                    _serialPort.BaudRate = speed;
            }
            if (cmbParity.SelectedIndex >= 0)
            {
                try
                {
                    _serialPort.Parity = (Parity)Enum.Parse(typeof(Parity), cmbParity.SelectedItem.ToString());
                }
                catch
                { }
            }
            if (cmbBits.SelectedIndex >= 0)
            {
                int bits;
                if (Int32.TryParse(cmbBits.SelectedItem.ToString(), out bits))
                    _serialPort.DataBits = bits;
            }
            if (cmbStopBits.SelectedIndex >= 0)
            {
                try
                {
                    switch (cmbStopBits.SelectedItem.ToString())
                    {
                        case "1":
                            _serialPort.StopBits = StopBits.One;
                            break;
                        case "1.5":
                            _serialPort.StopBits = StopBits.OnePointFive;
                            break;
                        case "2":
                            _serialPort.StopBits = StopBits.Two;
                            break;
                        default:
                            _serialPort.StopBits = StopBits.None;
                            break;
                    }
                }
                catch (Exception ex)
                {
                    Log(ex.Message, Color.Red);
                }
            }
            if (cmbHandshake.SelectedIndex >= 0)
            {
                try
                {
                    switch (cmbStopBits.SelectedItem.ToString())
                    {
                        case "RTS":
                            _serialPort.Handshake = Handshake.RequestToSend;
                            break;
                        case "RTS / XOn-XOff":
                            _serialPort.Handshake = Handshake.RequestToSendXOnXOff;
                            break;
                        case "XOn-XOff":
                            _serialPort.Handshake = Handshake.XOnXOff;
                            break;
                        default:
                            _serialPort.Handshake = Handshake.None;
                            break;
                    }
                }
                catch (Exception ex)
                {
                    Log(ex.Message, Color.Red);
                }
            }

            int timeout;
            if (!Int32.TryParse(txtTimeout.Text, out timeout))
                timeout = 500;
            _serialPort.ReadTimeout = timeout;
            _serialPort.WriteTimeout = timeout;

            try
            {
                _serialPort.Open();
                lblConnected.Text = "Connected";
                btnConnect.Visible = false;
                btnDisconnect.Visible = true;

                cmbPort.Enabled = false;
                cmbSpeed.Enabled = false;
                cmbBits.Enabled = false;
                cmbParity.Enabled = false;
                cmbStopBits.Enabled = false;
                cmbHandshake.Enabled = false;
                txtTimeout.Enabled = false;
            }
            catch (Exception ex)
            {
                Log(ex.Message, Color.Red);
            }

        }

        private void btnDisconnect_Click(object sender, EventArgs e)
        {
            if (_serialPort != null)
            {
                _serialPort.Close();
                _serialPort = null;
            }
            lblConnected.Text = "Not connected";
            btnConnect.Visible = true;
            btnDisconnect.Visible = false;

            cmbPort.Enabled = true;
            cmbSpeed.Enabled = true;
            cmbBits.Enabled = true;
            cmbParity.Enabled = true;
            cmbStopBits.Enabled = true;
            cmbHandshake.Enabled = true;
            txtTimeout.Enabled = true;
        }

        private bool InitCommand(SerialCommand command)
        {
            Byte slaveAddress;
            if (!Byte.TryParse(txtSlaveAddress.Text, out slaveAddress))
            {
                Log("Error: Invalid slave address.", Color.Red);
                return false;
            }

            command.SlaveAddress = slaveAddress;
            command.OnSend += new EventHandler<LogEventArgs>(LogSend);
            command.OnReceive += new EventHandler<LogEventArgs>(LogReceive);
            command.OnError += new EventHandler<ErrorEventArgs>(LogError);
            return true;
        }

        #region Log
        private void LogError(object sender, ErrorEventArgs e)
        {
            if (!String.IsNullOrEmpty(e.Message))
                Log(e.Message, Color.Red);
            if (e.Exception != null)
            {
                Log(e.Exception.Message, Color.Red);
            }
        }

        private void LogSend(object sender, LogEventArgs e)
        {
            StringBuilder sb = new StringBuilder("Sent: ", e.Buffer.Length * 5 + 10);
            for (int i = 0; i < e.Buffer.Length; i++)
            {
                sb.AppendFormat(" 0x{0:x2}", e.Buffer[i]);
            }
            Log(sb.ToString(), Color.Green);
        }

        private void LogReceive(object sender, LogEventArgs e)
        {
            StringBuilder sb = new StringBuilder("Received: ", e.Buffer.Length * 5 + 10);
            for (int i = 0; i < e.Buffer.Length; i++)
            {
                sb.AppendFormat(" 0x{0:x2}", e.Buffer[i]);
            }
            Log(sb.ToString(), Color.Blue);
        }

        private void Log(string message, Color color)
        {
            int start = logBox.TextLength;
            logBox.AppendText(message);
            logBox.AppendText(Environment.NewLine);
            int end = logBox.TextLength;

            logBox.Select(start, end - start);
            logBox.SelectionColor = color;
            logBox.SelectionLength = 0;
        }
        #endregion

        private void btnControlVelocityRS_Click(object sender, EventArgs e)
        {
            if (_serialPort == null)
            {
                Log("Serial port is not connected.", Color.Red);
                return;
            }

            UInt16 data;
            if (!UInt16.TryParse(txtInput.Text, out data))
            {
                Log("Invalid data.", Color.Red);
                return;
            }

            try
            {
                Control_velocityRS command = new Control_velocityRS();
                if (!InitCommand(command))
                    return;
                command.VelocityRS = data;

                Log(command.ToString(), Color.Black);
                command.Send(_serialPort);
                if (!command.Receive(_serialPort))
                    return;
            }
            catch (Exception ex)
            {
                Log(ex.Message, Color.Red);
                Log(ex.StackTrace, Color.Red);
            }
        }

        private void btnCommCommand_Click(object sender, EventArgs e)
        {
            if (_serialPort == null)
            {
                Log("Serial port is not connected.", Color.Red);
                return;
            }

            try
            {
                Comm_Command command = new Comm_Command();
                if (!InitCommand(command))
                    return;

                command.Send(_serialPort);
                if (!command.Receive(_serialPort))
                    return;
                Log(command.ToString(), Color.Black);
            }
            catch (Exception ex)
            {
                Log(ex.Message, Color.Red);
                Log(ex.StackTrace, Color.Red);
            }
        }

        private void btnReadBackEMF_Click(object sender, EventArgs e)
        {
            if (_serialPort == null)
            {
                Log("Serial port is not connected.", Color.Red);
                return;
            }

            try
            {
                Read_BackEMF command = new Read_BackEMF();
                if (!InitCommand(command))
                    return;

                command.Send(_serialPort);
                if (!command.Receive(_serialPort))
                    return;
                Log(command.ToString(), Color.Black);
            }
            catch (Exception ex)
            {
                Log(ex.Message, Color.Red);
                Log(ex.StackTrace, Color.Red);
            }
        }

        private void btnControlONOFF_Click(object sender, EventArgs e)
        {
            if (_serialPort == null)
            {
                Log("Serial port is not connected.", Color.Red);
                return;
            }

            try
            {
                Control_ON_OFF command = new Control_ON_OFF();
                if (!InitCommand(command))
                    return;

                Log(command.ToString(), Color.Black);
                command.Send(_serialPort);
                if (!command.Receive(_serialPort))
                    return;
            }
            catch (Exception ex)
            {
                Log(ex.Message, Color.Red);
                Log(ex.StackTrace, Color.Red);
            }
        }

        private void btnReadR1R2R3_Click(object sender, EventArgs e)
        {
            if (_serialPort == null)
            {
                Log("Serial port is not connected.", Color.Red);
                return;
            }

            try
            {
                Read_R1R2R3 command = new Read_R1R2R3();
                if (!InitCommand(command))
                    return;

                command.Send(_serialPort);
                if (!command.Receive(_serialPort))
                    return;

                Log(command.ToString(), Color.Black);
            }
            catch (Exception ex)
            {
                Log(ex.Message, Color.Red);
                Log(ex.StackTrace, Color.Red);
            }
        }

        private void btnReadAccTab_Click(object sender, EventArgs e)
        {
            if (_serialPort == null)
            {
                Log("Serial port is not connected.", Color.Red);
                return;
            }

            try
            {
                ReadAccTab command = new ReadAccTab();
                if (!InitCommand(command))
                    return;

                command.Send(_serialPort);
                if (!command.Receive(_serialPort))
                    return;

                Log(command.ToString(), Color.Black);
            }
            catch (Exception ex)
            {
                Log(ex.Message, Color.Red);
                Log(ex.StackTrace, Color.Red);
            }
        }

        private void btnWriteAccTab_Click(object sender, EventArgs e)
        {
            if (_serialPort == null)
            {
                Log("Serial port is not connected.", Color.Red);
                return;
            }

            try
            {
                WriteAccTab command = new WriteAccTab();
                if (!InitCommand(command))
                    return;

                string[] data = txtInput.Text.Split(',');
                command.Data = new UInt16[data.Length];
                for (int i = 0; i < data.Length; i++)
                {
                    UInt16 intData;
                    if (!UInt16.TryParse(data[i], out intData))
                    {
                        Log("Invalid data. Use a comma to separate multiple values.", Color.Red);
                        return;
                    }
                    command.Data[i] = intData;
                }

                Log(command.ToString(), Color.Black);
                command.Send(_serialPort);
                if (!command.Receive(_serialPort))
                    return;
            }
            catch (Exception ex)
            {
                Log(ex.Message, Color.Red);
                Log(ex.StackTrace, Color.Red);
            }
        }

        private void btnReadReqDefaultParam_Click(object sender, EventArgs e)
        {
            if (_serialPort == null)
            {
                Log("Serial port is not connected.", Color.Red);
                return;
            }

            try
            {
                Req_Read_DefaultParam command = new Req_Read_DefaultParam();
                if (!InitCommand(command))
                    return;

                Log(command.ToString(), Color.Black);
                command.Send(_serialPort);
                if (!command.Receive(_serialPort))
                    return;
            }
            catch (Exception ex)
            {
                Log(ex.Message, Color.Red);
                Log(ex.StackTrace, Color.Red);
            }
        }

        private void btnSetReqWriteParam_Click(object sender, EventArgs e)
        {
            if (_serialPort == null)
            {
                Log("Serial port is not connected.", Color.Red);
                return;
            }

            try
            {
                Set_Req_Write_Param command = new Set_Req_Write_Param();
                if (!InitCommand(command))
                    return;

                Log(command.ToString(), Color.Black);
                command.Send(_serialPort);
                if (!command.Receive(_serialPort))
                    return;
            }
            catch (Exception ex)
            {
                Log(ex.Message, Color.Red);
                Log(ex.StackTrace, Color.Red);
            }
        }

        private void btnReadParam_Click(object sender, EventArgs e)
        {
            if (_serialPort == null)
            {
                Log("Serial port is not connected.", Color.Red);
                return;
            }
            if (cmbParameter.SelectedIndex < 0)
            {
                Log("Select a parameter.", Color.Red);
                return;
            }

            try
            {
                Read_Param command = new Read_Param();
                if (!InitCommand(command))
                    return;
                try
                {
                    command.Parameter = new DriveParameter();
                    command.Parameter.Type = (DriveParameterType)Enum.Parse(typeof(DriveParameterType), cmbParameter.SelectedItem.ToString());
                }
                catch (Exception ex)
                {
                    Log(ex.Message, Color.Red);
                    return;
                }

                command.Send(_serialPort);
                if (!command.Receive(_serialPort))
                    return;
                Log(command.ToString(), Color.Black);
            }
            catch (Exception ex)
            {
                Log(ex.Message, Color.Red);
                Log(ex.StackTrace, Color.Red);
            }
        }

        private void btnSetParam_Click(object sender, EventArgs e)
        {
            if (_serialPort == null)
            {
                Log("Serial port is not connected.", Color.Red);
                return;
            }
            if (cmbParameter.SelectedIndex < 0)
            {
                Log("Select a parameter.", Color.Red);
                return;
            }
            if (String.IsNullOrEmpty(txtInput.Text))
            {
                Log("Please enter the parameter value.", Color.Red);
                return;
            }

            try
            {
                Set_Param command = new Set_Param();
                if (!InitCommand(command))
                    return;
                try
                {
                    command.Parameter = new DriveParameter();
                    command.Parameter.Type = (DriveParameterType)Enum.Parse(typeof(DriveParameterType), cmbParameter.SelectedItem.ToString());
                    command.Parameter.Value = txtInput.Text;
                }
                catch (Exception ex)
                {
                    Log(ex.Message, Color.Red);
                    return;
                }

                Log(command.ToString(), Color.Black);
                command.Send(_serialPort);
                if (!command.Receive(_serialPort))
                    return;
            }
            catch (Exception ex)
            {
                Log(ex.Message, Color.Red);
                Log(ex.StackTrace, Color.Red);
            }
        }
    }
}
