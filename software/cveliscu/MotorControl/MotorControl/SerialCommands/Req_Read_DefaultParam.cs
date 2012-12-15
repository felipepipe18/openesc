
namespace MotorControl
{
    public class Req_Read_DefaultParam : SerialCommand
    {
        public Req_Read_DefaultParam()
        {
            CommandCode = 0x16;
        }
    }
}
