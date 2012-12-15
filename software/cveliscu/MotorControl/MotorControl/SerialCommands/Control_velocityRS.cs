using System;
using System.IO.Ports;

namespace MotorControl
{
    public class Control_velocityRS : SerialCommand
    {
        public UInt16 VelocityRS
        {
            get;
            set;
        }

        public Control_velocityRS()
        {
            CommandCode = 0x12;
        }

        public override bool Send(SerialPort serialPort)
        {
            base.DataLength = 2;
            Write(VelocityRS);

            return base.Send(serialPort);
        }

        public override string ToString()
        {
            return base.ToString() + Environment.NewLine + "Velocity RS: " + VelocityRS.ToString() + " (0x" + VelocityRS.ToString("x2") + ")";
        }

    }
}
