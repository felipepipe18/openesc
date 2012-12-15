using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.Serialization;

namespace MotorControl
{

    public class DriveParameters
    {
        public UInt16 pre_commutation
        {
            get;
            set;
        }
        public VelocityParameters Vel_reg
        {
            get;
            set;
        }
        public UInt16 limit_dec_f_force_comm
        {
            get;
            set;
        }
        public Single current_protection
        {
            get;
            set;
        }
        public UInt16 level_pwm_start
        {
            get;
            set;
        }
        public UInt16 cnt_on_reg_speed
        {
            get;
            set;
        }
        public UInt16 level_correct_speed
        {
            get;
            set;
        }
        public Single step_add_velocity
        {
            get;
            set;
        }
        public Single step_dec_velocity
        {
            get;
            set;
        }
        public UInt16 level_detect_stop
        {
            get;
            set;
        }
        public UInt32 add_force_time
        {
            get;
            set;
        }
        public UInt16 add_Uin
        {
            get;
            set;
        }
        public UInt16 step_dec_f_force_comm
        {
            get;
            set;
        }
        public UInt16 level_on_feedback
        {
            get;
            set;
        }
        public UInt16 level_pause_detect_ZC
        {
            get;
            set;
        }
        public UInt16 n_pair_polus
        {
            get;
            set;
        }
        public UInt16 drive_mode
        {
            get;
            set;
        }
        public Single Unom
        {
            get;
            set;
        }
        public Single current_protect_avg
        {
            get;
            set;
        }
        public Single slave_addr
        {
            get;
            set;
        }

        public DriveParameters()
        {
            Vel_reg = new VelocityParameters();
        }
    }
}
