
namespace MotorControl
{
    public class Set_Req_Write_Param : SerialCommand
    {
        public Set_Req_Write_Param()
        {
            CommandCode = 0x18;
        }
    }
}
