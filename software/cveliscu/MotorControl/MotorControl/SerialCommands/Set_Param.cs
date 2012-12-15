using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace MotorControl
{
    public class Set_Param : SerialCommand
    {
        public DriveParameter Parameter
        {
            get;
            set;
        }

        public Set_Param()
        {
            CommandCode = 0x32;
        }

        public override bool Send(System.IO.Ports.SerialPort serialPort)
        {
            if (Parameter == null)
                return false;

            switch (Parameter.DataType)
            {
                case DriveParameterDataType.Byte:
                    DataLength = 2;
                    Write((byte)Parameter.Type);
                    Write((byte)Parameter.Value);
                    break;
                case DriveParameterDataType.UInt16:
                    DataLength = 3;
                    Write((byte)Parameter.Type);
                    Write((UInt16)Parameter.Value);
                    break;
                case DriveParameterDataType.Int16:
                    DataLength = 3;
                    Write((byte)Parameter.Type);
                    Write((Int16)Parameter.Value);
                    break;
                case DriveParameterDataType.UInt32:
                    DataLength = 5;
                    Write((byte)Parameter.Type);
                    Write((UInt32)Parameter.Value);
                    break;
                case DriveParameterDataType.Single:
                    DataLength = 5;
                    Write((byte)Parameter.Type);
                    Write((Single)Parameter.Value);
                    break;
            }

            return base.Send(serialPort);
        }
    }
}
