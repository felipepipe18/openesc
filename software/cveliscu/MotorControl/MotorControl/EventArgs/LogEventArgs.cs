using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace MotorControl
{
    public class LogEventArgs : EventArgs
    {
        public byte[] Buffer;

        public LogEventArgs(byte[] buffer, int length)
        {
            Buffer = new byte[length];
            Array.Copy(buffer, Buffer, length);
        }

        public LogEventArgs(byte[] buffer, int start, int length)
        {
            Buffer = new byte[length];
            Array.Copy(buffer, start, Buffer, 0, length);
        }
    }
}
