using System;
using System.IO.Ports;
using System.Text;

namespace MotorControl
{
    public class Read_BackEMF : SerialCommand
    {
        private UInt16[] _data;

        public UInt16[] Data
        {
            get { return _data; }
            set { _data = value; }
        }
        
        public Read_BackEMF()
        {
            CommandCode = 0x04;
        }

        public override bool Receive(SerialPort serialPort)
        {
            if (!base.Receive(serialPort))
                return false;
            if (Length % 2 != 0)
                return false;
            _data = new UInt16[Length / 2];
            for (int i = 0; i < Length / 2; i++)
            {
                _data[i] = BitConverter.ToUInt16(_buffer, i * 2);
            }
            return true;
        }

        public override string ToString()
        {
            StringBuilder sb = new StringBuilder();

            sb.AppendLine(base.ToString());
            sb.Append("Data:");
            if (_data != null)
            {
                for (int i = 0; i < _data.Length; i++)
                    sb.AppendFormat(" {0}", _data[i]);
            }
            else
            {
                sb.Append(" null");
            }
            return sb.ToString();
        }
    }
}
