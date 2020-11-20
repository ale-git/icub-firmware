/*
 * Copyright (C) 2016 iCub Facility - Istituto Italiano di Tecnologia
 * Author:  Alessandro Scalzo
 * email:   alessandro.scalzo@iit.it
 * website: www.robotcub.org
 * Permission is granted to copy, distribute, and/or modify this program
 * under the terms of the GNU General Public License, version 2 or any
 * later version published by the Free Software Foundation.
 *
 * A copy of the license can be found at
 * http://www.robotcub.org/icub/license/gpl.txt
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or  FOR A PARTICULAR PURPOSE. See the GNU General
 * Public License foFITNESSr more details
*/

#include "EoCommon.h"

#include "EOtheMemoryPool.h"

#include "EOemsControllerCfg.h"
#include "EOtheErrorManager.h"
#include "EoError.h"
#include "EOappEncodersReader.h"
#include "EOtheEntities.h"

#include "Joint.h"
#include "Motor.h"
#include "AbsEncoder.h"
#include "Pid.h"

#include "JointSet.h"

#include "Calibrators.h"

static void JointSet_set_inner_control_flags(JointSet* o);

JointSet* JointSet_new(uint8_t n) //
{
    JointSet* o = NEW(JointSet, n);
    
    for (int i=0; i<n; ++i)
    {   
        JointSet_init(o+i);
    }
    
    return o;
}

void JointSet_init(JointSet* o) //
{   
    o->pN = NULL;
    o->pE = NULL;

    o->joints_of_set = NULL;
    o->motors_of_set = NULL;
    
    o->joint = NULL;
    o->motor = NULL;
       
    o->Jjm = NULL; o->Sjm = NULL;
    o->Jmj = NULL; o->Smj = NULL;
    
    o->Sje = NULL;
    
    
    o->absEncoder = NULL;
    
    o->control_mode = eomc_controlmode_notConfigured;
    o->interaction_mode = eOmc_interactionmode_stiff;
    
    o->torque_ctrl_out_type = eomc_ctrl_out_type_n_a;
    o->olooop_ctrl_out_type = eomc_ctrl_out_type_n_a;
    o->curent_ctrl_out_type = eomc_ctrl_out_type_n_a;
    o->postrj_ctrl_out_type = eomc_ctrl_out_type_n_a;
    o->veltrj_ctrl_out_type = eomc_ctrl_out_type_n_a;
    o->mixtrj_ctrl_out_type = eomc_ctrl_out_type_n_a;
    o->posdir_ctrl_out_type = eomc_ctrl_out_type_n_a;
    o->veldir_ctrl_out_type = eomc_ctrl_out_type_n_a;
    
    o->pos_control_active = TRUE;
    o->trq_control_active = FALSE; 
    o->USE_SPEED_FBK_FROM_MOTORS = TRUE;
    
    o->is_calibrated = FALSE;
    
    o->special_constraint = eomc_jsetconstraint_none;
    
    o->calibration_in_progress = eomc_calibration_typeUndefined;
    
    o->wrist_decoupler.initialize();
    
    Trajectory_init(&o->park_trajectory[0], 0, 0, 0);
    Trajectory_init(&o->park_trajectory[0], 0, 0, 0);
    Trajectory_init(&o->park_trajectory[0], 0, 0, 0);
    
    o->parking = FALSE;
}

void JointSet_config //
(
    JointSet* o,
    uint8_t* pN,
    uint8_t* pE,
    uint8_t* joints_of_set,
    uint8_t* motors_of_set,
    uint8_t* encoders_of_set,
    Joint* joint, 
    Motor* motor,
    AbsEncoder *absEncoder,
    float** Jjm, float** Sjm,
    float** Jmj, float** Smj,
    float** Sje
)
{
    o->pN = pN;
    o->pE = pE;
    o->joints_of_set = joints_of_set;
    o->motors_of_set = motors_of_set;
    o->encoders_of_set = encoders_of_set;
    o->joint = joint;
    o->motor = motor;
    o->absEncoder = absEncoder;
    o->Jjm = Jjm; o->Sjm = Sjm;
    o->Jmj = Jmj; o->Smj = Smj;
    o->Sje = Sje;
}

void JointSet_do_wrist_odometry(JointSet* o) //
{
    int js, j;
    int N = *(o->pN);
    
    for (js=0; js<N; ++js)
    {    
        j = o->encoders_of_set[js];
        
        o->wrist_motor_theta[js] = AbsEncoder_position(o->absEncoder+j);
    }
    
    //o->joint[j].pos_fbk = AbsEncoder_position(o->absEncoder+j);
    
//    // accelerations
//    for (js=0; js<N; ++js)
//    {
//        j = o->joints_of_set[js];
//        o->joint[j].acc_fbk = CTRL_LOOP_FREQUENCY*(o->joint[j].vel_fbk - o->joint[j].vel_fbk_old);
//        o->joint[j].vel_fbk_old = o->joint[j].vel_fbk;
//    }
}

BOOL JointSet_do_check_faults(JointSet* o)
{
    int N = *(o->pN);
    int E = *(o->pE);
    
    BOOL fault = FALSE;
    o->external_fault = FALSE;
    
    for (int k=0; k<N; ++k)
    {
        if (Joint_check_faults(o->joint+o->joints_of_set[k]))
        {
            fault = TRUE;
        }
        
        if (Motor_check_faults(o->motor+o->motors_of_set[k]))
        {
            fault = TRUE;
            o->joint[o->joints_of_set[k]].control_mode = eomc_controlmode_hwFault;
        }
        
        if (Motor_is_external_fault(o->motor+o->motors_of_set[k]))
        {
            o->external_fault = TRUE;
        }
    }
    BOOL encoder_fault = FALSE;
    for (int k=0; k<E; ++k)
    {
        AbsEncoder* enc = o->absEncoder+o->encoders_of_set[k];
        if (AbsEncoder_is_in_fault(enc))
        {
            fault = TRUE;
            encoder_fault = TRUE;
        }
    }
    //if an encoder of this set is in fault ten set hw fault on each joint of this set.
    if(encoder_fault)
    {
        for (int k=0; k<N; ++k)
        {
            o->joint[o->joints_of_set[k]].control_mode = eomc_controlmode_hwFault;
        }
    }
    
    if (fault)
    {
        for (int k=0; k<N; ++k)
        {
            Joint_set_control_mode(o->joint+o->joints_of_set[k], eomc_controlmode_cmd_idle);
            
            if (Motor_is_running(o->motor+o->motors_of_set[k]))
            {
                Motor_set_idle(o->motor+o->motors_of_set[k]);
            }
        }
        
        o->control_mode = eomc_controlmode_hwFault;
        
        JointSet_set_inner_control_flags(o);
    }
    else if (o->external_fault)
    {
        for (int k=0; k<N; ++k)
        {
            Joint_set_control_mode(o->joint+o->joints_of_set[k], eomc_controlmode_cmd_idle);
            
            if (Motor_is_running(o->motor+o->motors_of_set[k]))
            {
                Motor_set_idle(o->motor+o->motors_of_set[k]);
            }
        }
        
        o->control_mode = eomc_controlmode_idle;
        
        JointSet_set_inner_control_flags(o);
    }
    
    return fault;
}

static void JointSet_do_wait_calibration(JointSet* o);

void JointSet_do(JointSet* o)
{
    JointSet_do_wrist_odometry(o);
    
    JointSet_do_check_faults(o);
    
    if (o->is_calibrated)
    {                
        JointSet_do_wrist_control(o);
    }
    else
    {
        JointSet_do_wait_calibration(o);
    }
}

static int control_output_type(JointSet* o, int16_t control_mode)
{
    if (control_mode == eomc_controlmode_cmd_force_idle) return eomc_ctrl_out_type_off;
    
    if (control_mode == eomc_controlmode_cmd_idle) return eomc_ctrl_out_type_off;
    
    if (o->interaction_mode == eOmc_interactionmode_stiff)
    {
        switch (control_mode)
        {
            case eomc_controlmode_openloop:
                return o->olooop_ctrl_out_type;

            case eomc_controlmode_current:
                return o->curent_ctrl_out_type;
            
            case eomc_controlmode_torque:
                return o->torque_ctrl_out_type;
            
            case eomc_controlmode_direct:
                return o->posdir_ctrl_out_type;
            
            case eomc_ctrlmval_velocity_pos:
            case eomc_controlmode_mixed:
                return o->mixtrj_ctrl_out_type;
            
            case eomc_controlmode_position:
                return o->postrj_ctrl_out_type;
            
            case eomc_controlmode_velocity: //
                return o->veltrj_ctrl_out_type;
            
            case eomc_controlmode_vel_direct:
                return o->veldir_ctrl_out_type;
            
            default:
                return eomc_ctrl_out_type_n_a;
        }
    }
    else
    {
        return o->torque_ctrl_out_type;
    }
}

BOOL JointSet_set_control_mode(JointSet* o, eOmc_controlmode_command_t control_mode_cmd)
{
    if (control_mode_cmd != eomc_controlmode_cmd_force_idle)
    {
        if ((eOmc_controlmode_t)control_mode_cmd == o->control_mode) return TRUE;
    
        if (o->control_mode == eomc_controlmode_calib) return FALSE;
    
        if (o->control_mode == eomc_controlmode_notConfigured) return FALSE;
    
        if ((control_mode_cmd == eomc_controlmode_cmd_torque) && (o->torque_ctrl_out_type == eomc_ctrl_out_type_n_a)) return FALSE;
    }
    
    int N = *(o->pN);
    int E = *(o->pE);
    
    if (o->control_mode == eomc_controlmode_hwFault)
    {
        if (control_mode_cmd == eomc_controlmode_cmd_force_idle)
        {
            for (int k=0; k<E; ++k)
            {   
                AbsEncoder_clear_faults(o->absEncoder+o->encoders_of_set[k]);
            }
            
            for (int k=0; k<N; ++k)
            {   
                Motor_force_idle(o->motor+o->motors_of_set[k]);
                
                Joint_set_control_mode(o->joint+o->joints_of_set[k], eomc_controlmode_cmd_force_idle);
            }
        }
        else
        {
            return FALSE;
        }
    }
    
    int motor_input_type = control_output_type(o, control_mode_cmd);
        
    if (motor_input_type == eomc_ctrl_out_type_n_a)
    {
        return FALSE;
    }
        
    o->motor_input_type = motor_input_type;
    
    switch (control_mode_cmd)
    {
    case eomc_controlmode_cmd_force_idle:
    case eomc_controlmode_cmd_idle:
        for (int k=0; k<N; ++k)
        { 
            Motor_motion_reset(o->motor+o->motors_of_set[k]);
            Joint_motion_reset(o->joint+o->joints_of_set[k]);
            
            Motor_set_idle(o->motor+o->motors_of_set[k]);
            Joint_set_control_mode(o->joint+o->joints_of_set[k], control_mode_cmd);
        }
        break;
    
    case eomc_controlmode_cmd_openloop:
    case eomc_controlmode_cmd_current:    
    case eomc_controlmode_cmd_torque:
    case eomc_controlmode_cmd_direct:
    case eomc_controlmode_cmd_mixed:
    case eomc_controlmode_cmd_velocity_pos:
    case eomc_controlmode_cmd_position:
    case eomc_controlmode_cmd_velocity:
    case eomc_controlmode_cmd_vel_direct:
    {        
        //if (o->external_fault) return FALSE;
                
        for (int k=0; k<N; ++k)
        { 
            Motor_motion_reset(o->motor+o->motors_of_set[k]);
            Joint_motion_reset(o->joint+o->joints_of_set[k]);

            if (!Motor_set_run(o->motor+o->motors_of_set[k], o->motor_input_type)) return FALSE;
        }
        
        for (int k=0; k<N; ++k)
        { 
            Joint_set_control_mode(o->joint+o->joints_of_set[k], control_mode_cmd);
        }
        break;
    }    
    default:
        return FALSE;
    }
    
    switch (control_mode_cmd)
    {
        case eomc_controlmode_cmd_velocity_pos:
            o->control_mode = (eOmc_controlmode_t)eomc_controlmode_cmd_mixed;
            break;
        //case eomc_controlmode_cmd_velocity:
        //    o->control_mode = (eOmc_controlmode_t)eomc_controlmode_cmd_vel_direct;
        //    break;
        default:
            o->control_mode = (eOmc_controlmode_t)control_mode_cmd;
            break;
    }
    
    //JointSet_send_debug_message("SET CONTROLMODE", 0, control_mode_cmd, o->control_mode);
    
    JointSet_set_inner_control_flags(o);
    
    return TRUE;
}

void JointSet_set_interaction_mode(JointSet* o, eOmc_interactionmode_t interaction_mode)
{
    if (interaction_mode == o->interaction_mode) return;
    
    if ((interaction_mode == eOmc_interactionmode_compliant) && (o->torque_ctrl_out_type == eomc_ctrl_out_type_n_a)) return;
    
    o->interaction_mode = interaction_mode;
    
    int motor_input_type = control_output_type(o, o->control_mode);
    
    JointSet_set_inner_control_flags(o);
    
    int N = *(o->pN);
    
    if (interaction_mode == eOmc_interactionmode_stiff)
    {        
        for (int k=0; k<N; ++k)
        {
            Motor_motion_reset(o->motor+o->motors_of_set[k]);
            Joint_motion_reset(o->joint+o->joints_of_set[k]);
        }
    }
    
    for (int k=0; k<N; ++k)
    {
        Joint_set_interaction_mode(o->joint+o->joints_of_set[k], interaction_mode);
    }
}

//////////////////////////////////////////////////////////////////////////
// statics

void JointSet_do_wrist_control(JointSet* o)
{
    const CTRL_UNITS ICUB2DEG = 1.0f/182.044f; 
    const CTRL_UNITS DEG2ICUB = 182.044f;
    
    int N = *(o->pN);
    
    BOOL control_active = TRUE;
        
    for (int js=0; js<N; ++js)
    {
        int j = o->joints_of_set[js];
        int m = o->motors_of_set[js];
        
        Joint *pJoint = o->joint+j;
        
        if (!Joint_do_wrist_control(pJoint)) control_active = FALSE;
        
        o->wrist_decoupler.rtU.ypr[j] = ICUB2DEG*pJoint->pos_ref;
        o->wrist_decoupler.rtU.theta_meas[m] = ICUB2DEG*o->wrist_motor_theta[m];
    }
    
    //////////////////////////
    o->wrist_decoupler.step();
    //////////////////////////
    
    if (control_active)
    {
        if (o->parking)
        {
            CTRL_UNITS pos_ref, vel_ref, acc_ref;
            CTRL_UNITS motor_pwm_ref;
            
            BOOL parked = TRUE;
            
            for (int j = 0; j<3; ++j)
            {
                Trajectory_do_step(o->park_trajectory+j, &pos_ref, &vel_ref, &acc_ref);
                
                motor_pwm_ref = Motor_do_pos_control(o->motor+j, pos_ref, o->wrist_motor_theta[j]);
                
                Motor_set_pwm_ref(o->motor+j, motor_pwm_ref);
                
                parked = parked && (fabs(pos_ref - o->wrist_motor_theta[j])<DEG2ICUB);
            }
            
            if (parked)
            {
                o->parking = FALSE;
                
                for (int j = 0; j<3; ++j)
                {
                    Joint_stop(o->joint+j);
                }
            }
        }
        else
        {
            if (o->wrist_decoupler.rtY.singularity)
            {
                for (int ms=0; ms<N; ++ms)
                {
                    int m = o->motors_of_set[ms];

                    Motor_set_pwm_ref(o->motor+m, ZERO);
                    
                    Trajectory_stop(o->park_trajectory+ms, o->wrist_motor_theta[ms]);
                    Trajectory_set_pos_end(o->park_trajectory+ms, ZERO, 20.0f*DEG2ICUB);
                }
                
                o->parking = TRUE;
            }
            else
            {
                CTRL_UNITS motor_pos_ref[3];
    
                for (int js=0; js<N; ++js)
                {
                    Joint *pJoint = o->joint+o->joints_of_set[js];
        
                    pJoint->pos_fbk = DEG2ICUB*(o->wrist_decoupler.rtY.ypr_meas[js]);
        
                    motor_pos_ref[js] = DEG2ICUB*(o->wrist_decoupler.rtY.theta_star[js]);
                }
    
                CTRL_UNITS motor_pwm_ref = ZERO;
    
                for (int ms=0; ms<N; ++ms)
                {
                    int m = o->motors_of_set[ms];
            
                    motor_pwm_ref = Motor_do_pos_control(o->motor+m, motor_pos_ref[m], o->wrist_motor_theta[m]);

                    Motor_set_pwm_ref(o->motor+m, motor_pwm_ref);
                }
            }
        }
    }
}

static void JointSet_set_inner_control_flags(JointSet* o)
{
    switch (o->control_mode)
    {
        case eomc_controlmode_position:
        case eomc_controlmode_velocity: //
        case eomc_controlmode_vel_direct:
        case eomc_ctrlmval_velocity_pos:
        case eomc_controlmode_mixed:
        case eomc_controlmode_direct:
            o->pos_control_active = TRUE;
        break;
        
        default:
            o->pos_control_active = FALSE;
    }
    
    if (o->control_mode==eomc_controlmode_torque)
    {
        o->trq_control_active = TRUE;
    }
    else if (o->pos_control_active && (o->interaction_mode==eOmc_interactionmode_compliant))
    {
        o->trq_control_active = TRUE;
    }
    else
    {
        o->trq_control_active = FALSE;
    }
}

static void JointSet_do_wait_calibration(JointSet* o)
{
    int N = *(o->pN);
    int E = *(o->pE);
    
    if (o->calibration_in_progress != eomc_calibration_typeUndefined)
    {
        if (o->calibration_timeout < CALIBRATION_TIMEOUT)
        {
            ++o->calibration_timeout;
        }
        else
        {    
            o->calibration_in_progress = eomc_calibration_typeUndefined;
        
            o->control_mode = eomc_controlmode_notConfigured;
            
            o->is_calibrated = FALSE;
            
            for (int k=0; k<N; ++k)
            {
                o->joint[o->joints_of_set[k]].control_mode = eomc_controlmode_notConfigured;
            
                Motor_set_pwm_ref(o->motor+o->motors_of_set[k], 0);
                Motor_set_idle(o->motor+o->motors_of_set[k]);
                Motor_uncalibrate(o->motor+o->motors_of_set[k]);
            }    
            
            return;
        }
    }

    o->is_calibrated = JointSet_do_wait_wrist_calibration(o);
        
    if (!o->is_calibrated) return;
    
    for (int es=0; es<E; ++es)
    {
        if (!AbsEncoder_is_calibrated(o->absEncoder+o->encoders_of_set[es])) 
        {
            o->is_calibrated = FALSE;
            return;
        }
    }
    
    o->calibration_in_progress = eomc_calibration_typeUndefined;
    
    JointSet_do_wrist_odometry(o);
    
    o->control_mode = eomc_controlmode_idle;

    for (int js=0; js<N; ++js)
    {
        o->joint[o->joints_of_set[js]].control_mode = eomc_controlmode_idle;
    }
    
    JointSet_set_control_mode(o, eomc_controlmode_cmd_position);
}

void JointSet_park(JointSet* o, uint8_t e)
{
}

void JointSet_calibrate(JointSet* o, uint8_t e, eOmc_calibrator_t *calibrator)
{
//    for (int js=0; js<*(o->pN); ++js)
//    {
//        o->joint[o->joints_of_set[js]].control_mode = eomc_controlmode_calib;
//    }
    
    eOmc_controlmode_t joint_controlMode_old = o->joint[e].control_mode;
    eOmc_controlmode_t jointSet_controlMode_old = o->control_mode;
    
    o->joint[e].control_mode = eomc_controlmode_calib;
    
    o->control_mode = eomc_controlmode_calib;
    
    o->is_calibrated = FALSE;
    
    switch (calibrator->type)
    {        
        case eomc_calibration_type12_absolute_sensor:
        {
            int32_t offset;
            int32_t zero;
            eOmc_joint_config_t *jointcfg = eo_entities_GetJointConfig(eo_entities_GetHandle(), e);
            //1) Take absolute value of calibation parametr
            int32_t abs_raw = (calibrator->params.type12.rawValueAtZeroPos > 0) ? calibrator->params.type12.rawValueAtZeroPos : -calibrator->params.type12.rawValueAtZeroPos;
            // 1.1) update abs_raw with gearbox_E2J
            abs_raw = abs_raw * jointcfg->gearbox_E2J;
            // 2) calculate offset
            if(abs_raw >= TICKS_PER_HALF_REVOLUTION)
                offset = abs_raw - TICKS_PER_HALF_REVOLUTION;
            else
                offset = abs_raw + TICKS_PER_HALF_REVOLUTION;
            
            // 3) find out sign of zero
            
            if(jointcfg->jntEncoderResolution > 0)
                zero = TICKS_PER_HALF_REVOLUTION / jointcfg->gearbox_E2J;
            else
                zero = -TICKS_PER_HALF_REVOLUTION / jointcfg->gearbox_E2J;
            
            zero+=calibrator->params.type12.calibrationDelta;  //this parameter should contain only the delta
            // 4) call calibration function
            
            ////debug code
            char info[80];
            snprintf(info, sizeof(info), "CALIB 12 j %d: offset=%d zero=%d ", e, offset, zero);
            JointSet_send_debug_message(info, e, 0, 0);
            ////debug code ended
            AbsEncoder_calibrate_absolute(o->absEncoder+e, offset, zero);
            
            Motor_calibrate_withOffset(o->motor+e, 0);
            Motor_set_run(o->motor+e, o->postrj_ctrl_out_type);
            o->calibration_in_progress = (eOmc_calibration_type_t)calibrator->type;

            break;
        }
        
        
        
        default:
            break;
    }
}

void JointSet_send_debug_message(char *message, uint8_t jid, uint16_t par16, uint32_t par64)
{

    eOerrmanDescriptor_t errdes = {0};

    errdes.code             = eoerror_code_get(eoerror_category_Debug, eoerror_value_DEB_tag01);
    errdes.sourcedevice     = eo_errman_sourcedevice_localboard;
    errdes.sourceaddress    = jid;
    errdes.par16            = par16;
    errdes.par64            = par64;
    eo_errman_Error(eo_errman_GetHandle(), eo_errortype_debug, message, NULL, &errdes);

}
