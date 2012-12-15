using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO.Ports;

namespace MotorControl
{
    [Serializable]
    public class SerialCommand
    {
        public event EventHandler<ErrorEventArgs> OnError;
        public event EventHandler<LogEventArgs> OnSend;
        public event EventHandler<LogEventArgs> OnReceive;
        public byte SlaveAddress;
        protected byte[] _buffer;
        private int _pos;
        private byte _commandCode;

        protected byte CommandCode
        {
            get
            {
                return _commandCode;
            }
            set
            {
                _commandCode = value;
            }
        }

        public byte Length
        {
            get
            {
                return (byte)((_buffer == null) ? 0 : _buffer.Length);
            }
            set
            {
                _buffer = new byte[value];
                _pos = 3;
            }
        }

        public byte DataLength
        {
            get
            {
                return (byte)((_buffer != null) ? 0 : _buffer.Length);
            }
            set
            {
                _buffer = new byte[value + 4];
                _pos = 3;
            }
        }

        public byte Crc8(byte[] buf, int length)
        {
            byte crc = 0xFF;

            for (int k = 0; k < length; k++)
            {
                crc ^= buf[k];

                for (int i = 0; i < 8; ++i)
                    crc = (byte)(((crc & 0x80) != 0) ? (crc << 1) ^ 0x31 : (crc << 1));
            }

            return (byte)(crc & 0xFF);
        }

        public SerialCommand()
        {
        }

        public SerialCommand(byte slaveAddress)
        {
            SlaveAddress = slaveAddress;
        }

        #region Write
        public bool Write(byte value)
        {
            if (_buffer == null)
                return false;
            if (_pos >= _buffer.Length)
                return false;
            _buffer[_pos] = value;
            _pos++;
            return true;
        }

        public bool Write(byte[] value)
        {
            if (_buffer == null)
                return false;
            if (_pos + value.Length >= _buffer.Length)
                return false;
            for (int i = 0; i < value.Length; i++)
                _buffer[_pos++] = value[i];
            return true;
        }

        public bool Write(UInt16 value)
        {
            byte[] val = BitConverter.GetBytes(value);
            if (!Write(val))
                return false;
            return true;
        }

        public bool Write(Int16 value)
        {
            byte[] val = BitConverter.GetBytes(value);
            if (!Write(val))
                return false;
            return true;
        }

        public bool Write(UInt32 value)
        {
            byte[] val = BitConverter.GetBytes(value);
            if (!Write(val))
                return false;
            return true;
        }

        public bool Write(Single value)
        {
            byte[] val = BitConverter.GetBytes(value);
            if (!Write(val))
                return false;
            return true;
        }
        #endregion

        public virtual bool Send(SerialPort serialPort)
        {
            if (serialPort == null)
            {
                if (OnError != null)
                {
                    ErrorEventArgs e = new ErrorEventArgs("Invalid serial port. (null)");
                    OnError(this, e);
                }
                return false;
            }
            if (SlaveAddress == 0)
            {
                if (OnError != null)
                {
                    ErrorEventArgs e = new ErrorEventArgs(String.Format("Invalid slave address. ({0})", SlaveAddress));
                    OnError(this, e);
                }
                return false;
            }
            if (CommandCode == 0)
            {
                if (OnError != null)
                {
                    ErrorEventArgs e = new ErrorEventArgs(String.Format("Invalid command code. (0x{0x2})", CommandCode));
                    OnError(this, e);
                }
                return false;
            }
            if (!serialPort.IsOpen)
            {
                if (OnError != null)
                {
                    ErrorEventArgs e = new ErrorEventArgs("Serial port is not open.");
                    OnError(this, e);
                }
                return false;
            }

            if (_buffer == null)
                DataLength = 0;
            if (_buffer == null)
            {
                if (OnError != null)
                {
                    ErrorEventArgs e = new ErrorEventArgs("Could not initialize buffer.");
                    OnError(this, e);
                }
                return false;
            }
            if (_pos < _buffer.Length - 1)
            {
                if (OnError != null)
                {
                    ErrorEventArgs e = new ErrorEventArgs("Incomplete data. The buffer was not filled.");
                    OnError(this, e);
                }
                return false;
            }
            try
            {
                _buffer[0] = SlaveAddress;
                _buffer[1] = CommandCode;
                _buffer[2] = Length;
                _buffer[Length - 1] = Crc8(_buffer, Length - 1);
                if (OnSend != null)
                {
                    LogEventArgs e = new LogEventArgs(_buffer, Length);
                    OnSend(this, e);
                }
                serialPort.Write(_buffer, 0, _buffer.Length);
            }
            catch (Exception ex)
            {
                if (OnError != null)
                {
                    ErrorEventArgs e = new ErrorEventArgs(ex);
                    OnError(this, e);
                }
                return false;
            }
            return true;
        }

        public virtual bool Receive(SerialPort serialPort)
        {
            if (serialPort == null)
            {
                if (OnError != null)
                {
                    ErrorEventArgs e = new ErrorEventArgs("Invalid serial port. (null)");
                    OnError(this, e);
                }
                return false;
            }
            if (SlaveAddress == 0)
            {
                if (OnError != null)
                {
                    ErrorEventArgs e = new ErrorEventArgs(String.Format("Invalid slave address. ({0})", SlaveAddress));
                    OnError(this, e);
                }
                return false;
            }
            if (CommandCode == 0)
            {
                if (OnError != null)
                {
                    ErrorEventArgs e = new ErrorEventArgs(String.Format("Invalid command code. (0x{0x2})", CommandCode));
                    OnError(this, e);
                }
                return false;
            }
            if (!serialPort.IsOpen)
            {
                if (OnError != null)
                {
                    ErrorEventArgs e = new ErrorEventArgs("Serial port is not open.");
                    OnError(this, e);
                }
                return false;
            }
            byte[] buf = new byte[1];
            try
            {
                if (serialPort.Read(buf, 0, 1) < 1)
                    return false;
            }
            catch (Exception ex)
            {
                if (OnError != null)
                {
                    ErrorEventArgs e = new ErrorEventArgs(ex);
                    OnError(this, e);
                }
                return false;
            }
            if (OnReceive != null)
            {
                LogEventArgs e = new LogEventArgs(buf, 1);
                OnReceive(this, e);
            }
            if (buf[0] != SlaveAddress)
            {
                if (OnError != null)
                {
                    ErrorEventArgs e = new ErrorEventArgs(String.Format("Invalid slave address received. ({0})", buf[0]));
                    OnError(this, e);
                }
                return false;
            }

            try
            {
                if (serialPort.Read(buf, 0, 1) < 1)
                    return false;
            }
            catch (Exception ex)
            {
                if (OnError != null)
                {
                    ErrorEventArgs e = new ErrorEventArgs(ex);
                    OnError(this, e);
                }
                return false;
            }
            if (OnReceive != null)
            {
                LogEventArgs e = new LogEventArgs(buf, 1);
                OnReceive(this, e);
            }
            if (buf[0] != _commandCode + 1)
            {
                if (OnError != null)
                {
                    ErrorEventArgs e = new ErrorEventArgs(String.Format("Invalid command code received. (0x{0x2})", buf[0]));
                    OnError(this, e);
                }
                return false;
            }
            try
            {
                if (serialPort.Read(buf, 0, 1) < 1)
                    return false;
            }
            catch (Exception ex)
            {
                if (OnError != null)
                {
                    ErrorEventArgs e = new ErrorEventArgs(ex);
                    OnError(this, e);
                }
                return false;
            }
            if (OnReceive != null)
            {
                LogEventArgs e = new LogEventArgs(buf, 1);
                OnReceive(this, e);
            }
            byte length = buf[0];
            if (length < 4)
            {
                if (OnError != null)
                {
                    ErrorEventArgs e = new ErrorEventArgs(String.Format("Invalid length received. ({0})", length));
                    OnError(this, e);
                }
                return false;
            }
            Length = length;

            _buffer[0] = SlaveAddress;
            _buffer[1] = (byte)(_commandCode + 1);
            _buffer[2] = length;

            int dataLen = 0;
            try
            {
                dataLen = serialPort.Read(_buffer, 3, Length - 3);
            }
            catch (Exception ex)
            {
                if (OnError != null)
                {
                    ErrorEventArgs e = new ErrorEventArgs(ex);
                    OnError(this, e);
                }
            }
            if (OnReceive != null)
            {
                LogEventArgs e = new LogEventArgs(_buffer, 3, dataLen);
                OnReceive(this, e);
            }
            if (dataLen != Length)
                return false;
            if (_buffer[Length - 1] != Crc8(_buffer, Length - 1))
            {
                if (OnError != null)
                {
                    ErrorEventArgs e = new ErrorEventArgs("Receive CRC error.");
                    OnError(this, e);
                }
                return false;
            }
            return true;
        }

        public override string ToString()
        {
            return "Command Code: 0x" + _commandCode.ToString("x2");
        }
    }
}
