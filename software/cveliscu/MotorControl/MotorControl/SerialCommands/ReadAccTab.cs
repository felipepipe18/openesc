using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace MotorControl
{
    public class ReadAccTab : Read_BackEMF
    {
        public ReadAccTab()
        {
            CommandCode = 0x10;
        }
    }
}
