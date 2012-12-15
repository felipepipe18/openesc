using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace MotorControl
{
    public enum DriveParameterType : byte
    {
        pre_commutation = 1,
        Kp = 2,
        Ki = 3,
        Kd = 4,
        add_Uin = 5,
        limit_dec_f_force_comm = 6,
        current_protection = 7,
        level_pwm_start = 8,
        cnt_on_reg_speed = 9,
        level_correct_speed = 10,
        step_add_velocity = 11,
        step_dec_velocity = 12,
        level_detect_stop = 13,
        add_force_time = 14,
        step_dec_f_force_comm = 15,
        level_on_feedback = 16,
        level_pause_detect_ZC = 17,
        n_pair_polus = 18,
        drive_mode = 19,
        Unom = 20,
        current_protect_avg = 21,
        slave_addr = 22
    }

    public enum DriveParameterDataType
    {
        None = 0,
        Byte = 1,
        UInt16 = 2,
        Int16 = 3,
        UInt32 = 4,
        Single = 5
    }

    public class DriveParameter
    {
        private DriveParameterType _type;

        public DriveParameterType Type
        {
            get
            {
                return _type;
            }
            set
            {
                _type = value;
                switch (_type)
                {
                    case DriveParameterType.add_force_time:
                        _dataType = DriveParameterDataType.UInt32;
                        break;
                    case DriveParameterType.add_Uin:
                        _dataType = DriveParameterDataType.Int16;
                        break;
                    case DriveParameterType.Kp:
                    case DriveParameterType.Ki:
                    case DriveParameterType.Kd:
                    case DriveParameterType.current_protection:
                    case DriveParameterType.step_add_velocity:
                    case DriveParameterType.step_dec_velocity:
                    case DriveParameterType.Unom:
                    case DriveParameterType.current_protect_avg:
                    case DriveParameterType.slave_addr:
                        _dataType = DriveParameterDataType.Single;
                        break;
                    default:
                        _dataType = DriveParameterDataType.UInt16;
                        break;
                }
            }
        }

        private DriveParameterDataType _dataType;

        public DriveParameterDataType DataType
        {
            get
            {
                return _dataType;
            }
        }

        private object _value;

        public object Value
        {
            get { return _value; }
            set
            {
                switch (_dataType)
                {
                    case DriveParameterDataType.Byte:
                        _value = Convert.ToByte(value);
                        break;
                    case DriveParameterDataType.Int16:
                        _value = Convert.ToInt16(value);
                        break;
                    case DriveParameterDataType.UInt16:
                        _value = Convert.ToUInt16(value);
                        break;
                    case DriveParameterDataType.UInt32:
                        _value = Convert.ToUInt32(value);
                        break;
                    case DriveParameterDataType.Single:
                        _value = Convert.ToSingle(value);
                        break;
                    default:
                        _value = value;
                        break;
                }
            }
        }


    }
}
