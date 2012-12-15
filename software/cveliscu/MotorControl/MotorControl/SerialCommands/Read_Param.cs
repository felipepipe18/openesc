using System;
using System.IO.Ports;

namespace MotorControl
{
    public class Read_Param : SerialCommand
    {
        public DriveParameter Parameter
        {
            get;
            set;
        }

        public Read_Param()
        {
            CommandCode = 0x30;
        }

        public override bool Send(System.IO.Ports.SerialPort serialPort)
        {
            if (Parameter == null)
                return false;
            DataLength = 1;
            Write((byte)Parameter.Type);

            return base.Send(serialPort);
        }

        public override bool Receive(SerialPort serialPort)
        {
            if (!base.Receive(serialPort))
                return false;
            if ((Length != 7) && (Length != 9))
                return false;

            Parameter = new DriveParameter();
            Parameter.Type = (DriveParameterType)_buffer[0];
            switch (Parameter.DataType)
            {
                case DriveParameterDataType.Byte:
                    {
                        byte value = _buffer[1];
                        Parameter.Value = value;
                    }
                    break;
                case DriveParameterDataType.UInt16:
                    {
                        UInt16 value = BitConverter.ToUInt16(_buffer, 1);
                        Parameter.Value = value;
                    }
                    break;
                case DriveParameterDataType.Int16:
                    {
                        Int16 value = BitConverter.ToInt16(_buffer, 1);
                        Parameter.Value = value;
                    }
                    break;
                case DriveParameterDataType.UInt32:
                    {
                        UInt32 value = BitConverter.ToUInt32(_buffer, 1);
                        Parameter.Value = value;
                    }
                    break;
                case DriveParameterDataType.Single:
                    {
                        Single value = BitConverter.ToSingle(_buffer, 1);
                        Parameter.Value = value;
                    }
                    break;
            }
            return true;
        }
    }
}
