using System;
using System.IO.Ports;
using System.Text;

namespace MotorControl
{
    [Serializable]
    public class Comm_Command : SerialCommand
    {
        public Single Uin
        {
            get;
            set;
        }

        public Single Current
        {
            get;
            set;
        }

        public UInt16 TempPWM
        {
            get;
            set;
        }

        public UInt32 ECStatus
        {
            get;
            set;
        }

        public UInt16 ADC_Iin
        {
            get;
            set;
        }

        public UInt16 ECWdrive
        {
            get;
            set;
        }

        public UInt16 State
        {
            get;
            set;
        }

        public UInt16 ECcnt_miss_zc
        {
            get;
            set;
        }

        public Comm_Command()
        {
            CommandCode = 0x02;
        }

        public override bool Receive(SerialPort serialPort)
        {
            if (!base.Receive(serialPort))
                return false;
            if (Length != 22)
                return false;

            // decode
            Uin = BitConverter.ToSingle(_buffer, 0);
            Current = BitConverter.ToSingle(_buffer, 4);
            TempPWM = BitConverter.ToUInt16(_buffer, 8);
            ECStatus = BitConverter.ToUInt32(_buffer, 10);
            ADC_Iin = BitConverter.ToUInt16(_buffer, 14);
            ECWdrive = BitConverter.ToUInt16(_buffer, 16);
            State = BitConverter.ToUInt16(_buffer, 18);
            ECcnt_miss_zc = BitConverter.ToUInt16(_buffer, 20);

            return true;
        }

        public override string ToString()
        {
            StringBuilder sb = new StringBuilder();

            sb.AppendLine(base.ToString());
            sb.AppendFormat("Uin: {0}" + Environment.NewLine, Uin);
            sb.AppendFormat("Current: {0}" + Environment.NewLine, Current);
            sb.AppendFormat("TempPWM: {0}" + Environment.NewLine, TempPWM);
            sb.AppendFormat("ECStatus: {0}" + Environment.NewLine, ECStatus);
            sb.AppendFormat("ADC_Iin: {0}" + Environment.NewLine, ADC_Iin);
            sb.AppendFormat("ECWdrive: {0}" + Environment.NewLine, ECWdrive);
            sb.AppendFormat("State: {0}" + Environment.NewLine, State);
            sb.AppendFormat("ECcnt_miss_zc: {0}", ECcnt_miss_zc);
            return sb.ToString();
        }
    }
}
