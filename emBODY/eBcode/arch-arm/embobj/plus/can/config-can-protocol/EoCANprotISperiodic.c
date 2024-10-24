/*
 * Copyright (C) 2015 iCub Facility - Istituto Italiano di Tecnologia
 * Author:  Marco Accame
 * email:   marco.accame@iit.it
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
 * Public License for more details
*/

// --------------------------------------------------------------------------------------------------------------------
// - external dependencies
// --------------------------------------------------------------------------------------------------------------------

#include "EOVtheSystem.h"

#include "stdlib.h"
#include "EoCommon.h"

// in here is whatever is required to offer parsing of can frames and copying into protocol data structures.

#include "EoProtocol.h"
#include "EoProtocolAS.h"

// but also to retrieve information of other things ...

#include "EOtheCANmapping.h"

#include "EOtheInertials2.h"

#include "EOtheInertials3.h"

// --------------------------------------------------------------------------------------------------------------------
// - declaration of extern public interface
// --------------------------------------------------------------------------------------------------------------------

#include "EOtheCANprotocol_functions.h" 


// --------------------------------------------------------------------------------------------------------------------
// - declaration of extern hidden interface 
// --------------------------------------------------------------------------------------------------------------------
// empty-section


// --------------------------------------------------------------------------------------------------------------------
// - #define with internal scope
// --------------------------------------------------------------------------------------------------------------------
// empty-section


// --------------------------------------------------------------------------------------------------------------------
// - definition (and initialisation) of extern variables, but better using _get(), _set() 
// --------------------------------------------------------------------------------------------------------------------
// empty-section


// --------------------------------------------------------------------------------------------------------------------
// - typedef with internal scope
// --------------------------------------------------------------------------------------------------------------------



// --------------------------------------------------------------------------------------------------------------------
// - declaration of static functions
// --------------------------------------------------------------------------------------------------------------------

//static void* s_eocanprotISperiodic_get_entity(eOprotEndpoint_t endpoint, eOprot_entity_t entity, eOcanframe_t *frame, eOcanport_t port, uint8_t *index);



// --------------------------------------------------------------------------------------------------------------------
// - definition (and initialisation) of static variables
// --------------------------------------------------------------------------------------------------------------------



// --------------------------------------------------------------------------------------------------------------------
// - definition of extern public functions
// --------------------------------------------------------------------------------------------------------------------


EO_weak extern eObool_t eocanprotINperiodic_redefinable_SkipParsingOf_ANY_PERIODIC_INERTIAL_MSG(eOcanframe_t *frame, eOcanport_t port)
{
    return(eobool_false);
}

EO_weak extern eObool_t eocanprotINperiodic_redefinable_SkipParsingOf_ANY_PERIODIC_INERTIAL3_MSG(eOcanframe_t *frame, eOcanport_t port)
{
    return(eobool_false);
}

extern eOresult_t eocanprotINperiodic_parser_PER_IS_MSG__DIGITAL_GYROSCOPE(eOcanframe_t *frame, eOcanport_t port)
{
    if(eobool_true == eocanprotINperiodic_redefinable_SkipParsingOf_ANY_PERIODIC_INERTIAL_MSG(frame, port))
    {
        return(eores_OK);
    }
    
    eo_inertials2_AcceptCANframe(eo_inertials2_GetHandle(), eoas_inertial_gyros_mtb_ext, frame, port);
    
    return(eores_OK);
    
//    // this can frame is from mtb only ... i dont do the check that the board must be a mbt
//    // i retrieve the inertial entity related to the frame    
//    eOas_inertial_t *inertial = NULL;
//    eOprotIndex_t index = EOK_uint08dummy;
//    
//    if(NULL == (inertial = s_eocanprotISperiodic_get_entity(eoprot_endpoint_analogsensors, eoprot_entity_as_inertial, frame, port, &index)))
//    {
//        return(eores_OK);  
//    }    
//    
//    inertial->status.gyroscope.x = (int16_t)((frame->data[1]<<8) + frame->data[0]);
//    inertial->status.gyroscope.y = (int16_t)((frame->data[3]<<8) + frame->data[2]);
//    inertial->status.gyroscope.z = (int16_t)((frame->data[5]<<8) + frame->data[4]);
//    inertial->status.gyroscope.ffu = 1; // i set it true.
//
//    return(eores_OK);    
}

extern eOresult_t eocanprotINperiodic_parser_PER_IS_MSG__DIGITAL_ACCELEROMETER(eOcanframe_t *frame, eOcanport_t port)
{
    
    if(eobool_true == eocanprotINperiodic_redefinable_SkipParsingOf_ANY_PERIODIC_INERTIAL_MSG(frame, port))
    {
        return(eores_OK);
    }
    
    eo_inertials2_AcceptCANframe(eo_inertials2_GetHandle(), eoas_inertial_accel_mtb_int, frame, port);
    
    return(eores_OK);
    
//    // this can frame is from mtb only ... i dont do the check that the board must be a mbt
//    // i retrieve the inertial entity related to the frame    
//    eOas_inertial_t *inertial = NULL;
//    eOprotIndex_t index = EOK_uint08dummy;
//    
//    if(NULL == (inertial = s_eocanprotISperiodic_get_entity(eoprot_endpoint_analogsensors, eoprot_entity_as_inertial, frame, port, &index)))
//    {
//        return(eores_OK);  
//    }    
//    
//    inertial->status.accelerometer.x = (int16_t)((frame->data[1]<<8) + frame->data[0]);
//    inertial->status.accelerometer.y = (int16_t)((frame->data[3]<<8) + frame->data[2]);
//    inertial->status.accelerometer.z = (int16_t)((frame->data[5]<<8) + frame->data[4]);
//    inertial->status.accelerometer.ffu = 1; // i set it true.
//    
//    return(eores_OK);
}

//typedef struct
//{
//    uint8_t index;
//    uint64_t data[16];      
//    uint64_t delta[16];
//    uint64_t pr;
//} pipe_t;

//void pipe_add(pipe_t *p, uint64_t v)
//{
//    //static uint64_t pr = 0;
//    p->data[p->index] = v;   
//    p->delta[p->index] = v - p->pr;
//    p->pr = v;
//    
//    p->index++;
//    p->index = p->index % 16;    
//}

//static pipe_t pipe = {0, {0}, {0}, {0}};

//static pipe_t timepipe = {0, {0}, {0}, {0}};

//void debugPprint(eOcanframe_t *frame)
//{
//    static uint32_t prevnozerodataindex = 0;
//    static uint32_t nozerodataindex = 0;
//    static uint32_t index = 0;
//    
//    
//    uint64_t msnow = eov_sys_LifeTimeGet(eov_sys_GetHandle());
//    
//    pipe_add(&timepipe, msnow/1000);
//    
//    if(frame->id == 0x513)
//    {
//        uint8_t seq = frame->data[0];
//        int16_t x = (int16_t)(frame->data[2]) | (int16_t)(frame->data[3]) << 8;
//        int16_t y = (int16_t)(frame->data[4]) | (int16_t)(frame->data[5]) << 8;
//        int16_t z = (int16_t)(frame->data[6]) | (int16_t)(frame->data[7]) << 8;
//        if(x != 0)
//        {
//            prevnozerodataindex = nozerodataindex;
//            nozerodataindex = index; 

//            prevnozerodataindex = prevnozerodataindex;
//            
//            pipe_add(&pipe, index);            
//        }
//        
//        index ++;                       
//    }        
//}

extern eOresult_t eocanprotINperiodic_parser_PER_IS_MSG__IMU_TRIPLE(eOcanframe_t *frame, eOcanport_t port)
{
    if(eobool_true == eocanprotINperiodic_redefinable_SkipParsingOf_ANY_PERIODIC_INERTIAL3_MSG(frame, port))
    {
        return(eores_OK);
    }
    
//    debugPprint(frame);
    
    eOas_inertial3_type_t type = eoas_inertial3_canproto_to_imu(frame->data[1]);
    if(eoas_inertial3_unknown != type)
    {
        eo_inertials3_AcceptCANframe(eo_inertials3_GetHandle(), type, frame, port);
    }
    
    return(eores_OK);
}

extern eOresult_t eocanprotINperiodic_parser_PER_IS_MSG__IMU_QUATERNION(eOcanframe_t *frame, eOcanport_t port)
{
    if(eobool_true == eocanprotINperiodic_redefinable_SkipParsingOf_ANY_PERIODIC_INERTIAL3_MSG(frame, port))
    {
        return(eores_OK);
    }
    
    eo_inertials3_AcceptCANframe(eo_inertials3_GetHandle(), eoas_inertial3_imu_qua, frame, port);

    return(eores_OK);
}

extern eOresult_t eocanprotINperiodic_parser_PER_IS_MSG__IMU_STATUS(eOcanframe_t *frame, eOcanport_t port)
{
    if(eobool_true == eocanprotINperiodic_redefinable_SkipParsingOf_ANY_PERIODIC_INERTIAL3_MSG(frame, port))
    {
        return(eores_OK);
    }
    

    eo_inertials3_AcceptCANframe(eo_inertials3_GetHandle(), eoas_inertial3_imu_status, frame, port);

    return(eores_OK);
}

// --------------------------------------------------------------------------------------------------------------------
// - definition of extern hidden functions 
// --------------------------------------------------------------------------------------------------------------------
// empty-section



// --------------------------------------------------------------------------------------------------------------------
// - definition of static functions 
// --------------------------------------------------------------------------------------------------------------------

//static void* s_eocanprotISperiodic_get_entity(eOprotEndpoint_t endpoint, eOprot_entity_t entity, eOcanframe_t *frame, eOcanport_t port, uint8_t *index)
//{
//    void * ret = NULL;
//    uint8_t ii = 0;
//    eObrd_canlocation_t loc = {0};
//    
//    loc.port = port;
//    loc.addr = EOCANPROT_FRAME_GET_SOURCE(frame);    
//    loc.insideindex = eobrd_caninsideindex_none;
//    
//    ii = eo_canmap_GetEntityIndex(eo_canmap_GetHandle(), loc, endpoint, entity);
//    if(EOK_uint08dummy == ii)
//    {     
//        #warning -> TODO: add diagnostics about not found board as in s_eo_icubCanProto_mb_send_runtime_error_diagnostics()
//        return(NULL);
//    }
//    
//    ret = eoprot_entity_ramof_get(eoprot_board_localboard, endpoint, entity, ii);
//    
//    if(NULL != index)
//    {
//        *index = ii;        
//    }  

//    return(ret);   
//}



// --------------------------------------------------------------------------------------------------------------------
// - end-of-file (leave a blank line after)
// --------------------------------------------------------------------------------------------------------------------





