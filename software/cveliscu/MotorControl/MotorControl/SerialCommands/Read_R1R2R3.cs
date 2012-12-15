using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace MotorControl
{
    public class Read_R1R2R3 : SerialCommand
    {
        public Single R1
        {
            get;
            set;
        }

        public Single R2
        {
            get;
            set;
        }

        public Single R3
        {
            get;
            set;
        }

        public Read_R1R2R3()
        {
            CommandCode = 0x08;
        }

        public override bool Receive(System.IO.Ports.SerialPort serialPort)
        {
            if (!base.Receive(serialPort))
                return false;
            if (Length != 12)
                return false;

            R1 = BitConverter.ToSingle(_buffer, 0);
            R2 = BitConverter.ToSingle(_buffer, 4);
            R3 = BitConverter.ToSingle(_buffer, 8);
            return true;
        }

        public override string ToString()
        {
            StringBuilder sb = new StringBuilder();

            sb.AppendLine(base.ToString());
            sb.AppendFormat("R1: {0:G9}" + Environment.NewLine, R1);
            sb.AppendFormat("R2: {0:G9}" + Environment.NewLine, R2);
            sb.AppendFormat("R3: {0:G9}" + Environment.NewLine, R3);
            return sb.ToString();
        }
    }
}
