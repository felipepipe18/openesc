using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace MotorControl
{
    public class ErrorEventArgs : EventArgs
    {
        public string Message
        {
            get;
            set;
        }

        public Exception Exception
        {
            get;
            set;
        }

        public ErrorEventArgs(string message)
        {
            Message = message;
        }

        public ErrorEventArgs(Exception ex)
        {
            Exception = ex;
        }
    }
}
