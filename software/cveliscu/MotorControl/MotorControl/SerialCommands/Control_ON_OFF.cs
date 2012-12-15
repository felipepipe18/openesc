using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace MotorControl
{
    public class Control_ON_OFF : SerialCommand
    {
        public Control_ON_OFF()
        {
            CommandCode = 0x06;
        }
    }
}
