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

#include "EoError.h"
#include "EOtheErrorManager.h"

#include "EOMtheEMSrunner.h"

#include "EOemsControllerCfg.h"

#include "AbsEncoder.h"

#include "EOtheMAIS.h"

#include "Motor.h"

/////////////////////////////////////////////////////////
// AbsEncoder


#define AEA_MIN_SPIKE 16 //4 bitsof zero padding(aea use 12 bits)
          
static void send_message(char *message, BOOL warning, uint8_t jid, uint16_t par16, uint64_t par64)
{
    eOerrmanDescriptor_t errdes = {0};

    errdes.code             = eoerror_code_get(eoerror_category_Debug, eoerror_value_DEB_tag01);
    errdes.sourcedevice     = eo_errman_sourcedevice_localboard;
    errdes.sourceaddress    = jid;
    errdes.par16            = par16;
    errdes.par64            = par64;
    eo_errman_Error(eo_errman_GetHandle(), warning ? eo_errortype_warning : eo_errortype_debug, message, NULL, &errdes);

}         

#define DEBUG_MESSAGE(msg,jid,par16,par64) send_message(msg,FALSE,jid,par16,par64)
#define WARNING_MESSAGE(msg,jid,par16,par64) send_message(msg,TRUE,jid,par16,par64)

AbsEncoder* AbsEncoder_new(uint8_t n)
{
    AbsEncoder *o = NEW(AbsEncoder, n);
    
    for (uint8_t i=0; i<n; ++i)
    {
        AbsEncoder_init(&(o[i]));
    }
    
    return o;
}

void AbsEncoder_init(AbsEncoder* o)
{
    o->ID = 0;
    
    o->type = eomc_enc_aea;
    
    o->spike_cnt_limit = 32767;
    o->spike_mag_limit = 32767;
    
    o->sign = 0;
    //o->mul = 0;
    //o->div = 1;
    o->gearbox = 1.0f;
    o->GEARBOX = FALSE;
    o->toleranceCfg = 0.0;
    
    o->fake = FALSE;
    
    o->offset = 0;
    
    o->distance = 0;
    o->position_last = 0;
    o->position_sure = 0;
    
    o->raw_sensor = 0;
    o->joint_angle = 0;
    o->joint_angle_last = 0;
    
    o->motor_delta = 0;
    o->motor_angle = 0;
    
    o->velocity = 0;

    o->delta = 0;

    o->partial_timer = 0;
    o->partial_space = 0;
    
    o->hardware_fault = FALSE;
    o->invalid_cnt = 0;
    o->timeout_cnt = 0;
    
    o->spike_cnt = 0;
    
    o->fault_state_prec.bitmask = 0;
    o->fault_state.bitmask = 0;
    o->diagnostics_refresh = 0;
    
    o->valid_first_data_cnt = 0;
    
    o->state.bits.not_configured  = TRUE;
    o->state.bits.not_calibrated  = TRUE;
    o->state.bits.not_initialized = TRUE;
    o->state.bits.hard_stop_calib = FALSE;
}

void AbsEncoder_destroy(AbsEncoder* o)
{
    DELETE(o);
}
//this function set spikes limits values based of encoder type
void s_AbsEncoder_set_spikes_limis(AbsEncoder* o)
{
    //char message[150];
    switch(o->type)
    {
        case(eomc_enc_mais):
        case(eomc_enc_absanalog):
        {
            o->spike_mag_limit = 0;
            o->spike_cnt_limit = 0;
            //snprintf(message, sizeof(message), "mais or absAnalog");
        }break;

        case(eomc_enc_aea):
        case(eomc_enc_spichainof2):
        case(eomc_enc_spichainof3):
        {
            int32_t toleranceIDeg =(int32_t)((o->toleranceCfg * 65535.0f) / 360.0f) ;
            #define AEA_MIN_SPIKE 16 //iDegree 
            /* Note: AEA has 12 bits of resolution, so we pad with four zero to transform from AEA unit to iDegree */
            if(toleranceIDeg < AEA_MIN_SPIKE)
                o->spike_mag_limit = AEA_MIN_SPIKE / o->gearbox;
            else
                o->spike_mag_limit = toleranceIDeg / o->gearbox;
            
            o->spike_cnt_limit = AEA_DEFAULT_SPIKE_CNT_LIMIT;
            
            //snprintf(message, sizeof(message), "ABSE aea:tol%.3f, div%.3f spikel%lu", o->toleranceCfg, o->div, o->spike_mag_limit);
        }break; 

        // marco.accame on 16 dec 2020: i assume eomc_enc_pos is similar to ... amo and psc
        case(eomc_enc_pos):
        case(eomc_enc_amo):
        case(eomc_enc_psc):
        {
            
            int32_t toleranceIDeg = (int32_t)((o->toleranceCfg * 65535.0f) / 360.0f);
            o->spike_mag_limit = toleranceIDeg / o->gearbox;
            o->spike_cnt_limit = AEA_DEFAULT_SPIKE_CNT_LIMIT; //ALE ??
            //snprintf(message, sizeof(message), "AMO: tol%.3f, div%.3f spikel%lu", o->toleranceCfg, o->div, o->spike_mag_limit);
        }break;        
        
        default:
        {
            o->spike_mag_limit = 0;
            o->spike_cnt_limit = 0;
            //snprintf(message, sizeof(message), "abs type unknown. spike =0 ");
        };
    };
    
//    eOerrmanDescriptor_t errdes = {0};

//    errdes.code             = eoerror_code_get(eoerror_category_Debug, eoerror_value_DEB_tag02);
//    errdes.sourcedevice     = eo_errman_sourcedevice_localboard;
//    errdes.sourceaddress    = o->ID;
//    errdes.par16            = 0;
//    errdes.par64            = 0;
//    eo_errman_Error(eo_errman_GetHandle(), eo_errortype_debug, message, NULL, &errdes);
}

void AbsEncoder_config(AbsEncoder* o, uint8_t ID, int32_t resolution, float32_t tolerance)
{
    o->ID = ID;
    
    AbsEncoder_config_resolution(o, (float)resolution);
    
    if (!o->fake)
    {
        o->toleranceCfg = tolerance;
        s_AbsEncoder_set_spikes_limis(o);
    }
    else
    {
        o->state.bits.not_initialized = FALSE; 
    }
    
    o->state.bits.not_configured = FALSE;
}

void AbsEncoder_config_resolution(AbsEncoder* o, float resolution)
{
    if (!o->fake)
    {
        o->sign = (resolution >= 0.0f) ? 1 : -1;
    }
    else
    {
        //o->mul = o->div = 1;
        o->sign = 1;
        o->gearbox = 1.0f;
        o->GEARBOX = FALSE;
    }
}

extern void AbsEncoder_config_divisor(AbsEncoder* o, float32_t divisor)
{
    //o->div = divisor;
    
    if (divisor == 1.0f || divisor == 0.0f)
    {
        o->gearbox = 1.0f;
        o->GEARBOX = FALSE;
    }
    else
    {
        o->gearbox = 1.0f/divisor;
        o->GEARBOX = TRUE;
    }
    
    //i need to re config spikes limits because they depend on divisor also. (NO...)
    if (!o->fake) s_AbsEncoder_set_spikes_limis(o);
}

void AbsEncoder_calibrate_absolute(AbsEncoder* o, uint16_t offset, int16_t fine_tuning)
{
    o->offset = offset;
    o->fine_tuning = fine_tuning;
        
    if (eomc_enc_amo == o->type)
    {
        //int16_t sensor_angle = (o->raw_sensor - o->offset)*o->sign;
        //o->joint_angle = o->GEARBOX ? o->gearbox*sensor_angle : sensor_angle;
    }
    else
    {
        uint16_t position = o->position_sure;
        position -= o->offset;
        o->distance = position;
    }
    
    o->state.bits.not_calibrated  = FALSE;
    o->state.bits.hard_stop_calib = FALSE;
}

void AbsEncoder_calibrate_fake(AbsEncoder* o)
{
    AbsEncoder_calibrate_absolute(o, 0, 0);
}

int32_t AbsEncoder_position(AbsEncoder* o)
{
    if (eomc_enc_amo == o->type)
    {
        return o->joint_angle - o->fine_tuning;
    }
    
    if (o->GEARBOX) return (o->sign*o->distance)*o->gearbox - o->fine_tuning;
    
    return (o->sign*o->distance) - o->fine_tuning;
}

int32_t AbsEncoder_velocity(AbsEncoder* o)
{
    if (o->GEARBOX) return (o->sign*o->velocity)*o->gearbox;
    
    return o->sign*o->velocity;
}

void AbsEncoder_posvel(AbsEncoder* o, int32_t* position, int32_t* velocity)
{
    if (eomc_enc_amo == o->type)
    {
        *position = o->joint_angle - o->fine_tuning;
    }
    else
    {
        if (o->GEARBOX)
        {
            *position = (o->sign*o->distance)*o->gearbox - o->fine_tuning;
        }
        else 
        {
            *position = (o->sign*o->distance) - o->fine_tuning;
        }
    } 
    
    if (o->GEARBOX)
    { 
        *velocity = (o->sign*o->velocity)*o->gearbox;
    }
    else
    {
        *velocity = o->sign*o->velocity;
    }    
}

static void AbsEncoder_position_init_amo(AbsEncoder* o, int32_t joint_angle, int32_t motor_angle)
{
    if (!o->valid_first_data_cnt)
    {
        o->joint_angle_last = joint_angle;
    }
    
    if (o->joint_angle_last != joint_angle)
    {
        o->valid_first_data_cnt = 0;
        
        return;
    }
    
    if (++o->valid_first_data_cnt >= 3)
    {
        o->joint_angle_last = joint_angle;
        o->joint_angle = joint_angle;
        
        o->motor_offset = joint_angle - motor_angle;

        o->valid_first_data_cnt = 0;
        
        o->state.bits.not_initialized = FALSE;
        
        DEBUG_MESSAGE("AMO INITIALIZED", o->ID, o->motor_offset, (((uint64_t)joint_angle)<<32)|motor_angle);
    }
}

static void AbsEncoder_position_init_aea(AbsEncoder* o, uint16_t position)
{
    if (!o->valid_first_data_cnt)
    {
        o->position_last = position;
    }
    
    if (o->position_last != position)
    {
        o->valid_first_data_cnt = 0;
        
        return;
    }
    
    if (++o->valid_first_data_cnt >= 3)
    {
        o->position_last = position;
        o->position_sure = position;

        position -= o->offset;
        
        o->distance = position;
        
        o->velocity = 0;
        
        o->delta = 0;

        o->valid_first_data_cnt = 0;
        
        o->state.bits.not_initialized = FALSE;
    }
}

static void AbsEncoder_position_init_others(AbsEncoder* o, uint16_t position)
{
    //mais doesn't need an init procedure like aea encoder
    o->position_last = position;
    o->position_sure = position;

    position -= o->offset;
    
    o->distance = position;
    
    o->velocity = 0;
    
    o->delta = 0;

    o->valid_first_data_cnt = 0;
    
    o->state.bits.not_initialized = FALSE;
}

void AbsEncoder_timeout(AbsEncoder* o)
{
    if (!o) return;
    
    if (o->fake) return;
    
    if (o->state.bits.not_configured) return;
    
    if (o->state.bits.not_calibrated) return;
    
    if (o->timeout_cnt > ENCODER_TIMEOUT_LIMIT)
    {
        o->hardware_fault = TRUE;
    }
    else
    {
        ++o->timeout_cnt;
    }
    
    o->fault_state.bits.data_notready = TRUE;
    
    o->valid_first_data_cnt = 0;
}

void AbsEncoder_invalid(AbsEncoder* o, eOencoderreader_errortype_t error_type)
{
    if (!o) return;
    
    if (o->fake) return;
    
    if (o->state.bits.not_configured) return;
    
    if (o->state.bits.not_calibrated) return;

    if (o->invalid_cnt > ENCODER_INVALID_LIMIT)
    {
        o->hardware_fault = TRUE;
    }
    else
    {
        ++o->invalid_cnt;
    }
    
    switch (error_type)
    {
        case encreader_err_NOTCONNECTED:
        case encreader_err_NONE:
            break;
        
        // all other cases are errors: AEA_PARITY, AEA_CHIP, AEA_READING have their tx_error, chip_error, data_error. all others: are data_error. 
        case encreader_err_AEA_PARITY:
            o->fault_state.bits.tx_error = TRUE;
            break;
        case encreader_err_AEA_CHIP:
            o->fault_state.bits.chip_error = TRUE;
            break;        
        case encreader_err_AEA_READING:
            o->fault_state.bits.data_error = TRUE;
            break;
        
        default:
            o->fault_state.bits.data_error = TRUE;
            break;
    }
        
    o->valid_first_data_cnt = 0;
}

// AMOs

static void AbsEncoder_update_amo(AbsEncoder* o, uint16_t raw_sensor, int32_t motor_angle, BOOL motor_position_ok)
{    
    if (!motor_position_ok) return;
    
    o->invalid_cnt = 0;
    o->timeout_cnt = 0;
    
    // calibrated, [-32768,32767] normalized
    int16_t sensor_angle = (raw_sensor - o->offset)*o->sign;
    int32_t joint_angle = o->GEARBOX ? o->gearbox*sensor_angle : sensor_angle;
    
    if (o->state.bits.not_initialized)
    {
        AbsEncoder_position_init_amo(o, joint_angle, motor_angle);
        
        return;
    }
    
    o->raw_sensor = raw_sensor;
    
    o->motor_delta = motor_angle - o->motor_angle;
    o->motor_angle = motor_angle;
    
    motor_angle += o->motor_offset;
    
    BOOL amo_error = o->amo_error;
    
    o->amo_error = abs(motor_angle - joint_angle) > 182; // 1 deg
    
    if (o->amo_error)
    {
        o->joint_angle = motor_angle;
    }
    else
    {
        o->joint_angle = joint_angle;
    }
    
    if (amo_error != o->amo_error)
    {
        if (o->amo_error)
        {
            WARNING_MESSAGE("AMO RECOVERY", o->ID, o->ID, (((uint64_t)joint_angle)<<32) | (((uint64_t)motor_angle) & 0xFFFFFFFF));
        }
        else
        {
            WARNING_MESSAGE("AMO OK", o->ID, o->ID, (((uint64_t)joint_angle)<<32) | (((uint64_t)motor_angle) & 0xFFFFFFFF));
        }
    }
}

static void AbsEncoder_update_aea(AbsEncoder* o, uint16_t position)
{    
    o->invalid_cnt = 0;
    o->timeout_cnt = 0;
    
    if (o->state.bits.not_initialized)
    {
        if (eomc_enc_mais == o->type || eomc_enc_absanalog == o->type) 
        {
            AbsEncoder_position_init_others(o, position);
        }
        else
        {
            AbsEncoder_position_init_aea(o, position);
        }
        
        o->velocity = 0;
        
        return;
    }
    
    o->delta = 0;
    
    int16_t check = position - o->position_last;
    
    o->position_last = position;

    if( (o->spike_mag_limit == 0) || (-o->spike_mag_limit <= check && check <= o->spike_mag_limit))
    {
        int16_t delta = position - o->position_sure;

        if (delta)
        {
            o->position_sure = position;
                
            o->delta = delta;
                
            position -= o->offset;
            
            o->distance += (int32_t)delta;
            
            //o->distance = position;
                
            o->velocity = (7*o->velocity + ((int32_t)CTRL_LOOP_FREQUENCY)*o->delta) >> 3;
        }
        else
        {
            o->velocity = (7*o->velocity) >> 3;
        }
    }
    else
    {
        o->spike_cnt++;
       
        o->velocity = (7*o->velocity) >> 3;
    }
        
    // every second
    uint64_t iteration = eom_emsrunner_Get_IterationNumber(eom_emsrunner_GetHandle());
    eOreltime_t period = eom_emsrunner_Get_Period(eom_emsrunner_GetHandle());
    if ((iteration % period) == 0)
    {
        if (o->spike_cnt > 0)
        {                
            //message "spike encoder error"
            eOerrmanDescriptor_t descriptor = {0};
            descriptor.par16 = o->ID;           
            descriptor.par64 = o->spike_cnt;
            descriptor.sourcedevice = eo_errman_sourcedevice_localboard;
            descriptor.sourceaddress = 0;
            descriptor.code = eoerror_code_get(eoerror_category_MotionControl, eoerror_value_MC_aea_abs_enc_spikes);
            eo_errman_Error(eo_errman_GetHandle(), eo_errortype_warning, NULL, NULL, &descriptor);
                
            if (o->spike_cnt > o->spike_cnt_limit)
            {
                o->fault_state.bits.spikes = TRUE;
                o->hardware_fault = TRUE;
            }
            
            o->spike_cnt = 0;
        }
    }
}

void AbsEncoder_update(AbsEncoder* o, uint16_t raw_sensor, int32_t motor_position, BOOL motor_position_ok)
{
    if (!o) return;
        
    if (o->fake) return;
    
    if (o->state.bits.not_configured) return;
    
    if (o->type == eomc_enc_amo)
    {
        AbsEncoder_update_amo(o, raw_sensor, motor_position, motor_position_ok);
        
        return;
    }
    
    //if (o->type == eomc_enc_aea)
    AbsEncoder_update_aea(o, raw_sensor);
}

BOOL AbsEncoder_is_fake(AbsEncoder* o)
{
    return o->fake;
}

BOOL AbsEncoder_is_ok(AbsEncoder* o)
{
    return (!o->state.not_ready) && (!o->hardware_fault);
}

BOOL AbsEncoder_is_calibrated(AbsEncoder* o)
{
    return !o->state.bits.not_calibrated;
}








static void AbsEncoder_send_error(uint8_t id, eOerror_value_MC_t err_id, uint64_t mask)
{
    static eOerrmanDescriptor_t descriptor = {0};
    descriptor.par16 = id;
    descriptor.par64 = mask;
    descriptor.sourcedevice = eo_errman_sourcedevice_localboard;
    descriptor.sourceaddress = 0;
    descriptor.code = eoerror_code_get(eoerror_category_MotionControl, err_id);
    eo_errman_Error(eo_errman_GetHandle(), eo_errortype_error, NULL, NULL, &descriptor);
}

BOOL AbsEncoder_is_in_fault(AbsEncoder* o)
{
    
    if(eomc_enc_mais == o->type)
    {
        if(!eo_mais_isAlive(eo_mais_GetHandle()))
        {
            o->hardware_fault = TRUE;
        }
    }
    
    if (!o->hardware_fault) return FALSE;
    
    if (++o->diagnostics_refresh > 5*CTRL_LOOP_FREQUENCY_INT)
    {
        o->diagnostics_refresh = 0;
        o->fault_state_prec.bitmask = 0;
    }
    
    if (o->fault_state_prec.bitmask != o->fault_state.bitmask)
    {     
        if ((o->fault_state.bits.tx_error   && !o->fault_state_prec.bits.tx_error)  
         || (o->fault_state.bits.data_error && !o->fault_state_prec.bits.data_error) 
         || (o->fault_state.bits.chip_error && !o->fault_state_prec.bits.chip_error))
        {
            AbsEncoder_send_error(o->ID, eoerror_value_MC_aea_abs_enc_invalid, o->fault_state.bitmask);
        }
        
        if (o->fault_state.bits.data_notready)
        {
            AbsEncoder_send_error(o->ID, eoerror_value_MC_aea_abs_enc_timeout, 0);
        }
        
        if (o->fault_state.bits.spikes)
        {
            AbsEncoder_send_error(o->ID, eoerror_value_MC_aea_abs_enc_spikes, 0);
        }
        
        o->fault_state_prec.bitmask = o->fault_state.bitmask;
    }
    
    return TRUE;
}

void AbsEncoder_clear_faults(AbsEncoder* o)
{
    o->hardware_fault = FALSE;
    
    o->fault_state_prec.bitmask = 0;
    o->fault_state.bitmask = 0;
    
    o->invalid_cnt = 0;
    o->timeout_cnt = 0;
    
    o->spike_cnt = 0;
}



///////////////////////////////////////////////////////////////////////////////////////
//

// caller void JointSet_calibrate(JointSet* o, uint8_t e, eOmc_calibrator_t *calibrator)
void AbsEncoder_start_hard_stop_calibrate(AbsEncoder* o, int32_t hard_stop_zero)
{
    // still check reset
    o->partial_timer = 0;
    o->partial_space = 0;
    
    o->offset = 0;
    o->fine_tuning = 0;
    
    o->hard_stop_zero = hard_stop_zero;
    
    o->distance = o->position_sure;
    //o->joint_angle = ?
    
    o->state.bits.not_calibrated  = TRUE;
    o->state.bits.hard_stop_calib = TRUE;
}

BOOL AbsEncoder_is_still(AbsEncoder* o, int32_t space_window, int32_t time_window)
{
    if(eomc_enc_amo == o->type)
    {
        o->partial_space += (int32_t)o->motor_delta;
    }
    else
    {
        o->partial_space += (int32_t)o->delta;
    }
    
    BOOL still = FALSE;
    
    if (++o->partial_timer > time_window)
    {        
        still = abs(o->partial_space) < space_window;
        
        o->partial_timer = 0;
        o->partial_space = 0;
    }
    
    return still;
}

BOOL AbsEncoder_is_hard_stop_calibrating(AbsEncoder* o)
{
    return o->state.bits.hard_stop_calib;
}

void AbsEncoder_calibrate_in_hard_stop(AbsEncoder* o)
{
    o->offset = 0;

    if(eomc_enc_amo == o->type)
    {
        send_message("HARD STOP CALIBRATED!!!", TRUE, o->ID, o->raw_sensor, o->hard_stop_zero);
        
        o->fine_tuning = (o->sign*o->raw_sensor)*o->gearbox - o->hard_stop_zero;
    }
    else
    {
        //o->fine_tuning = (o->mul*o->distance)/o->div - o->hard_stop_zero;
        o->fine_tuning = (o->sign*o->distance)*o->gearbox - o->hard_stop_zero;    
    }
    
    o->state.bits.not_calibrated  = FALSE;
    o->state.bits.hard_stop_calib = FALSE;
}

//
///////////////////////////////////////////////////////////////////////////////////////




// AbsEncoder
/////////////////////////////////////////////////////////
