using System.IO.Ports;

namespace MotorControl
{
    public class WriteAccTab : Read_BackEMF
    {
        //private UInt16[] _data;

        //public UInt16[] Data
        //{
        //    get { return _data; }
        //    set { _data = value; }
        //}

        public WriteAccTab()
        {
            CommandCode = 0x14;
        }

        public override bool Send(SerialPort serialPort)
        {
            byte length;
            if (Data.Length > 125)
                length = 125;
            else
                length = (byte)Data.Length;
            base.DataLength = (byte)(length * 2);
            for (int i = 0; i < length; i++)
                Write(Data[i]);

            return base.Send(serialPort);
        }
    }
}
