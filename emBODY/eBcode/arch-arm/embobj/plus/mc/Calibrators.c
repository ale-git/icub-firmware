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

#include "Calibrators.h"
#include "JointSet.h"
#include "CalibrationHelperData.h"
#include "hal_adc.h"

BOOL JointSet_do_wait_wrist_calibration(JointSet* o)
{
    return TRUE;
}

#if 0
BOOL JointSet_do_wait_calibration_8(JointSet* o)
{    
    BOOL calibrated = TRUE;
    
    int32_t pos[3];
    
    for (int ms=0; ms<*(o->pN); ++ms)
    {
        int m = o->motors_of_set[ms];

        if (hal_adc_get_hall_sensor_analog_input_mV(o->motor[m].actuatorPort) < 1500)
        {
            o->motor[m].not_calibrated = FALSE;
        }
        
        if (Motor_is_calibrated(o->motor+m))
        {
            Motor_set_pwm_ref(o->motor+m, 0);
            
            pos[ms] = 0x7FFFFFFF;
        }
        else
        {
            pos[ms] = o->motor[m].pos_fbk - o->tripod_calib.start_pos[ms];
            
            //Motor_set_pwm_ref(o->motor+m, o->tripod_calib.pwm);
            
            calibrated = FALSE;
        }
    }
    
    if (calibrated)
    {        
        o->motor[o->motors_of_set[0]].pos_calib_offset += o->motor[o->motors_of_set[0]].pos_fbk - o->tripod_calib.zero;
        o->motor[o->motors_of_set[1]].pos_calib_offset += o->motor[o->motors_of_set[1]].pos_fbk - o->tripod_calib.zero;
        o->motor[o->motors_of_set[2]].pos_calib_offset += o->motor[o->motors_of_set[2]].pos_fbk - o->tripod_calib.zero;
        
        o->motor[o->motors_of_set[0]].pos_fbk = o->tripod_calib.zero;
        o->motor[o->motors_of_set[1]].pos_fbk = o->tripod_calib.zero;
        o->motor[o->motors_of_set[2]].pos_fbk = o->tripod_calib.zero;

        o->motor[o->motors_of_set[0]].not_init = FALSE;
        o->motor[o->motors_of_set[1]].not_init = FALSE;
        o->motor[o->motors_of_set[2]].not_init = FALSE;
        
        o->motor[o->motors_of_set[0]].pos_fbk_old = o->motor[o->motors_of_set[0]].pos_fbk;
        o->motor[o->motors_of_set[1]].pos_fbk_old = o->motor[o->motors_of_set[1]].pos_fbk;
        o->motor[o->motors_of_set[2]].pos_fbk_old = o->motor[o->motors_of_set[2]].pos_fbk;


        
        return TRUE;
    }
    
    float pwm[3];
    
    if (pos[0]<0) pos[0] = -pos[0];
    if (pos[1]<0) pos[1] = -pos[1];
    if (pos[2]<0) pos[2] = -pos[2];
    
    int32_t posL = pos[0];
    if (pos[1] < posL) posL = pos[1];
    if (pos[2] < posL) posL = pos[2];
    
    float pwm_calib = (float)o->tripod_calib.pwm;
    
    if (pwm_calib < 0.0f) pwm_calib = -pwm_calib;
    
    pwm[0] = pwm_calib * (1.0f - (float)(pos[0] - posL)/(float)o->tripod_calib.max_delta);
    pwm[1] = pwm_calib * (1.0f - (float)(pos[1] - posL)/(float)o->tripod_calib.max_delta);
    pwm[2] = pwm_calib * (1.0f - (float)(pos[2] - posL)/(float)o->tripod_calib.max_delta);
    
    if (pwm[0] < 0.0f) pwm[0] = 0.0f;
    if (pwm[1] < 0.0f) pwm[1] = 0.0f;
    if (pwm[2] < 0.0f) pwm[2] = 0.0f;
    
    float pwm_min = pwm[0];
    if (pwm[1] < pwm_min) pwm_min = pwm[1];
    if (pwm[2] < pwm_min) pwm_min = pwm[2];

    if (o->tripod_calib.pwm < 0)
    {
        pwm[0] = -pwm[0];
        pwm[1] = -pwm[1];
        pwm[2] = -pwm[2];
    }
    
    Motor_set_pwm_ref(o->motor+o->motors_of_set[0], (int32_t)pwm[0]);
    Motor_set_pwm_ref(o->motor+o->motors_of_set[1], (int32_t)pwm[1]);
    Motor_set_pwm_ref(o->motor+o->motors_of_set[2], (int32_t)pwm[2]);

    return FALSE;
}

BOOL JointSet_do_wait_calibration_12(JointSet* o)
{
    BOOL calibrated = TRUE;
    
    for (int ms=0; ms<*(o->pN); ++ms)
    {
        if (!Motor_is_calibrated(o->motor+o->motors_of_set[ms])) 
        {
            calibrated = FALSE;
        }
    }
    
    return calibrated;
}
#endif


