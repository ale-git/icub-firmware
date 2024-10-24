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


#include "stdlib.h"
#include "EoCommon.h"

// in here is whatever is required to offer parsing of can frames and copying into protocol data structures.

#include "EoProtocol.h"
#include "EoProtocolAS.h"

// but also to retrieve information of other things ...
#include "EOtheErrorManager.h"
#include "EoError.h"

#include "EOtheCANmapping.h"
#include "EOtheMAIS.h"
#include "EOtheSTRAIN.h"
#include "EOtheTemperatures.h"
#include "EOthePSC.h"

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

typedef enum 
{
    processForce    = 0,    // keep it 0 so that we index teh array in position 0*3 = 0
    processTorque   = 1     // keep it 1 so taht we index teh array in position 1*3 = 3
} strainProcessMode_t;


typedef enum 
{
    processHES0TO6      = 0,    
    processHES7TO14     = 1     
} maisProcessMode_t;

// --------------------------------------------------------------------------------------------------------------------
// - declaration of static functions
// --------------------------------------------------------------------------------------------------------------------

static void* s_eocanprotASperiodic_get_entity(eOprotEndpoint_t endpoint, eOprot_entity_t entity, eOcanframe_t *frame, eOcanport_t port, uint8_t *index);

static eOresult_t s_eocanprotASperiodic_parser_process_forcetorque(eOcanframe_t *frame, eOcanport_t port, strainProcessMode_t mode);

static eOresult_t s_eocanprotASperiodic_parser_process_maisvalue(eOcanframe_t *frame, eOcanport_t port, maisProcessMode_t mode);

static void s_former_PER_AS_prepare_frame(eOcanprot_descriptor_t *descriptor, eOcanframe_t *frame, uint8_t len, uint8_t type);

static void s_eocanprotASperiodic_strain_saturation_handler(eOcanframe_t *frame, eOcanport_t port, strainProcessMode_t mode);

// --------------------------------------------------------------------------------------------------------------------
// - definition (and initialisation) of static variables
// --------------------------------------------------------------------------------------------------------------------



// --------------------------------------------------------------------------------------------------------------------
// - definition of extern public functions
// --------------------------------------------------------------------------------------------------------------------


extern eOresult_t eocanprotASperiodic_parser_PER_AS_MSG__USERDEF(eOcanframe_t *frame, eOcanport_t port)
{
    //  marco.accame on 08apr2019: here is support for reception of a userdef message  
    return(eores_NOK_generic); 
}


extern eOresult_t eocanprotASperiodic_parser_PER_AS_MSG__POS(eOcanframe_t *frame, eOcanport_t port)
{
    eo_psc_AcceptCANframe(eo_psc_GetHandle(), frame, port);    
    return(eores_OK);  
}


extern eOresult_t eocanprotASperiodic_parser_PER_AS_MSG__UNCALIBFORCE_VECTOR_DEBUGMODE(eOcanframe_t *frame, eOcanport_t port)
{
    // this can frame is from strain only ... i dont do the check that the board must be a strain
    // i retrieve the strain entity related to the frame    
    eOas_strain_t *strain = NULL;
    eOprotIndex_t index = EOK_uint08dummy;
    
    if(NULL == (strain = (eOas_strain_t*) s_eocanprotASperiodic_get_entity(eoprot_endpoint_analogsensors, eoprot_entity_as_strain, frame, port, &index)))
    {
        return(eores_OK);  
    }    
    
    // copy into status... it should be done using the EOarray ....
    // memcpy(&(strain->status.uncalibratedvalues.data[0]), &frame->data[0], 6);   
    eo_array_Assign((EOarray*)(&strain->status.uncalibratedvalues), 0, &(frame->data[0]), 3);
    return(eores_OK);    
}

extern eOresult_t eocanprotASperiodic_parser_PER_AS_MSG__UNCALIBTORQUE_VECTOR_DEBUGMODE(eOcanframe_t *frame, eOcanport_t port)
{
    // this can frame is from strain only ... i dont do the check that the board must be a strain
    // i retrieve the strain entity related to the frame    
    eOas_strain_t *strain = NULL;
    eOprotIndex_t index = EOK_uint08dummy;
    
    if(NULL == (strain = (eOas_strain_t*) s_eocanprotASperiodic_get_entity(eoprot_endpoint_analogsensors, eoprot_entity_as_strain, frame, port, &index)))
    {
        return(eores_OK);  
    }    
    
    // copy into status... it should be done using the EOarray ....
    // memcpy(&(status->uncalibratedvalues.data[6]), &frame->data[0], 6); 
    eo_array_Assign((EOarray*)(&strain->status.uncalibratedvalues), 3, &(frame->data[0]), 3);
    return(eores_OK);    
}


extern eOresult_t eocanprotASperiodic_former_PER_AS_MSG__FORCE_VECTOR(eOcanprot_descriptor_t *descriptor, eOcanframe_t *frame)
{
    s_former_PER_AS_prepare_frame(descriptor, frame, 6, ICUBCANPROTO_PER_AS_MSG__FORCE_VECTOR); 
    memcpy(&frame->data[0], descriptor->cmd.value, 6);      
    return(eores_OK);                
}

extern eOresult_t eocanprotASperiodic_parser_PER_AS_MSG__FORCE_VECTOR(eOcanframe_t *frame, eOcanport_t port)
{
    // this can frame is from strain only ... i dont do the check that the board must be a strain
    // process force
    s_eocanprotASperiodic_parser_process_forcetorque(frame, port, processForce);
    return(eores_OK);
}


extern eOresult_t eocanprotASperiodic_former_PER_AS_MSG__TORQUE_VECTOR(eOcanprot_descriptor_t *descriptor, eOcanframe_t *frame)
{
    s_former_PER_AS_prepare_frame(descriptor, frame, 6, ICUBCANPROTO_PER_AS_MSG__TORQUE_VECTOR); 
    memcpy(&frame->data[0], descriptor->cmd.value, 6);      
    return(eores_OK);                
}


extern eOresult_t eocanprotASperiodic_parser_PER_AS_MSG__TORQUE_VECTOR(eOcanframe_t *frame, eOcanport_t port)
{
    // this can frame is from strain only ... i dont do the check that the board must be a strain
    // process torque
    s_eocanprotASperiodic_parser_process_forcetorque(frame, port, processTorque);
    return(eores_OK);
}


extern eOresult_t eocanprotASperiodic_parser_PER_AS_MSG__HES0TO6(eOcanframe_t *frame, eOcanport_t port)
{
    // this can frame is from mais only ... i dont do the check that the board must be a mais
    // process values
    s_eocanprotASperiodic_parser_process_maisvalue(frame, port, processHES0TO6);
    return(eores_OK);    
}


extern eOresult_t eocanprotASperiodic_parser_PER_AS_MSG__HES7TO14(eOcanframe_t *frame, eOcanport_t port)
{
    // this can frame is from mais only ... i dont do the check that the board must be a mais
    // process values
    s_eocanprotASperiodic_parser_process_maisvalue(frame, port, processHES7TO14);
    return(eores_OK);    
}


extern eOresult_t eocanprotASperiodic_parser_PER_AS_MSG__THERMOMETER_MEASURE(eOcanframe_t *frame, eOcanport_t port)
{
    if(eobool_true == eocanprotASperiodic_redefinable_SkipParsingOf_ANY_PERIODIC_THERMOMETER_MSG(frame, port))
    {
        return(eores_OK);
    }    

    eo_temperatures_AcceptCANframe(eo_temperatures_GetHandle(), eoas_temperature_t1, frame, port);
    
    return(eores_OK);    
}





// --------------------------------------------------------------------------------------------------------------------
// - definition of extern hidden functions 
// --------------------------------------------------------------------------------------------------------------------
// empty-section



// --------------------------------------------------------------------------------------------------------------------
// - definition of static functions 
// --------------------------------------------------------------------------------------------------------------------

static void* s_eocanprotASperiodic_get_entity(eOprotEndpoint_t endpoint, eOprot_entity_t entity, eOcanframe_t *frame, eOcanport_t port, uint8_t *index)
{
    void * ret = NULL;
    uint8_t ii = 0;
    eObrd_canlocation_t loc = {0};
    
    loc.port = port;
    loc.addr = EOCANPROT_FRAME_GET_SOURCE(frame);    
    loc.insideindex = eobrd_caninsideindex_none;
    
    ii = eo_canmap_GetEntityIndex(eo_canmap_GetHandle(), loc, endpoint, entity);
    
    if(EOK_uint08dummy == ii)
    {     
        //#warning -> TODO: add diagnostics about not found board as in s_eo_icubCanProto_mb_send_runtime_error_diagnostics()
        return(NULL);
    }
    
    ret = eoprot_entity_ramof_get(eoprot_board_localboard, endpoint, entity, ii);
    
    if(NULL != index)
    {
        *index = ii;        
    }  

    return(ret);   
}


static eOresult_t s_eocanprotASperiodic_parser_process_forcetorque(eOcanframe_t *frame, eOcanport_t port, strainProcessMode_t mode)
{
    // this can frame is from strain only ... i dont do the check that the board must be a strain
    // i retrieve the strain entity related to the frame    
    eOas_strain_t *strain = NULL;
    eOprotIndex_t index = EOK_uint08dummy;
    
    if(NULL == (strain = (eOas_strain_t*) s_eocanprotASperiodic_get_entity(eoprot_endpoint_analogsensors, eoprot_entity_as_strain, frame, port, &index)))
    {
        return(eores_OK);  
    }    
    
    eObool_t update_watchdog = eobool_false;
    
    // set incoming force values
    switch(strain->config.mode)
    {
        case eoas_strainmode_txcalibrateddatacontinuously:
        case eoas_strainmode_txalldatacontinuously:
        {
            eo_array_Assign((EOarray*)(&strain->status.calibratedvalues), 3*mode, &(frame->data[0]), 3);
            update_watchdog = eobool_true;
        } break;

        case eoas_strainmode_txuncalibrateddatacontinuously:
        {
            eo_array_Assign((EOarray*)(&strain->status.uncalibratedvalues), 3*mode, &(frame->data[0]), 3);
            update_watchdog = eobool_true;
        } break;
        
        case eoas_strainmode_acquirebutdonttx:
        {
            // i dont do anything in here. but i dont return nok. because it may be that we must empty a rx buffer of canframes rx just before
            // that we have silenced the strain.
        } break;
        
        default:
        {
            //i must never be here
            //#warning -> TODO: add diagnostics about unknown mode as in s_eo_icubCanProto_mb_send_runtime_error_diagnostics()
        }
    }
    
    if(update_watchdog)
    {
        eo_strain_notifymeOnNewReceivedData(eo_strain_GetHandle());
    }
        
    
    //check saturation
//#define SIMPLE_SATURATION_DIAGNOSTIC
#if defined (SIMPLE_SATURATION_DIAGNOSTIC)
    static uint16_t count_message = 0;
    if (frame->size == 7)
    {
        //check 7th byte, which should include the saturation bit
        if (frame->data[6] != 0x00)
        //send dedicated diagnostics
        {
            if ((count_message == 0) || (count_message == 300)) //if it's the first time or every 300ms, if it's continuosly saturating
            {              
                eOerrmanDescriptor_t errdes = {0};
                errdes.sourcedevice         = (eOcanport1 == port) ? (eo_errman_sourcedevice_canbus1) : (eo_errman_sourcedevice_canbus2);
                errdes.sourceaddress        = EOCANPROT_FRAME_GET_SOURCE(frame);                
                errdes.code                 = eoerror_code_get(eoerror_category_HardWare, eoerror_value_HW_strain_saturation);
                errdes.par16                = frame->size;
                errdes.par64                = eo_common_canframe_data2u64((eOcanframe_t*)frame);
                eo_errman_Error(eo_errman_GetHandle(), eo_errortype_error, NULL, NULL, &errdes);
            }
            
            if (count_message == 300)
                count_message = 0;
            
            count_message++;
        }
    }
    else
    {
       count_message = 0; 
    }
#else
//    static uint16_t counter = 0;
//    counter++;
//    
//    if (counter > 2000) // stays for 1 second...
//        counter = 0;
   
    s_eocanprotASperiodic_strain_saturation_handler(frame, port, mode);
#endif
    
    return(eores_OK);
}

static eOresult_t s_eocanprotASperiodic_parser_process_maisvalue(eOcanframe_t *frame, eOcanport_t port, maisProcessMode_t mode)
{
    // this can frame is from strain only ... i dont do the check that the board must be a strain
    // i retrieve the strain entity related to the frame    
    eOas_mais_t *mais = NULL;
    eOprotIndex_t index = EOK_uint08dummy;
    
    if(NULL == (mais = (eOas_mais_t*) s_eocanprotASperiodic_get_entity(eoprot_endpoint_analogsensors, eoprot_entity_as_mais, frame, port, &index)))
    {
        return(eores_OK);  
    }  

    EOarray* array = (EOarray*)&mais->status.the15values;
    if(processHES0TO6 == mode)
    {
        eo_array_Assign(array, 0, &(frame->data[0]), 7); // 7 bytes of frame->data starting from array position 0 (0, 1, .. , 6)
    }
    else //if(processHES7TO14 == mode)
    {
        eo_array_Assign(array, 7, &(frame->data[0]), 8); // 8 bytes of frame->data starting from array position 7 (7, 8, .. , 14)
    }
        
    eo_mais_notifymeOnNewReceivedData(eo_mais_GetHandle());
    
    return(eores_OK);       
}

static void s_former_PER_AS_prepare_frame(eOcanprot_descriptor_t *descriptor, eOcanframe_t *frame, uint8_t len, uint8_t type)
{   // for periodic the descriptor->address contains ... the origin
    uint8_t origin = descriptor->loc.addr;
    frame->id           = EOCANPROT_CREATE_CANID_PERIODIC(eocanprot_msgclass_periodicAnalogSensor, origin, type);
    frame->id_type      = eocanframeID_std11bits;
    frame->frame_type   = eocanframetype_data; 
    frame->size         = len;
}

static void s_eocanprotASperiodic_strain_saturation_handler(eOcanframe_t *frame, eOcanport_t port, strainProcessMode_t mode)
{
    static uint16_t upper_saturations[6] = {0};
    static uint16_t lower_saturations[6] = {0};
    
    static uint32_t counter = 0;
    
    counter ++;
    
    uint8_t strainTXrate = eo_strain_GetDataRate(eo_strain_GetHandle()); // in ms. get it from strain object ....
    uint32_t numberofmessagesin1second = 2000*strainTXrate; // strai sends 2 msgs (1 for force and 1 for torque) every strainTXrate milli.
    
    //there's saturation
    if (frame->size == 7)
    {
        uint8_t info = frame->data[6]; //byte containing info about saturation
    
        if (info != 0)
        {
            switch (mode)
            {
                case processForce:
                {
                    icubCanProto_strain_forceSaturationInfo_t* force_info = (icubCanProto_strain_forceSaturationInfo_t*) &info; 
                    
                    if (force_info->saturationInChannel_0 == saturationLOW)
                        lower_saturations[0]++;
                    else if (force_info->saturationInChannel_0 == saturationHIGH)
                        upper_saturations[0]++;
            
                    if (force_info->saturationInChannel_1 == saturationLOW)
                        lower_saturations[1]++;
                    else if (force_info->saturationInChannel_1 == saturationHIGH)
                        upper_saturations[1]++;
                   
                    if (force_info->saturationInChannel_2 == saturationLOW)
                         lower_saturations[2]++;
                    else if (force_info->saturationInChannel_2 == saturationHIGH)
                         upper_saturations[2]++;            
                } break;                 
                case processTorque:
                {
                    icubCanProto_strain_torqueSaturationInfo_t* torque_info = (icubCanProto_strain_torqueSaturationInfo_t*) &info;
                 
                    if (torque_info->saturationInChannel_3 == saturationLOW)
                        lower_saturations[3]++;
                    else if (torque_info->saturationInChannel_3 == saturationHIGH)
                        upper_saturations[3]++;
                    
                    if (torque_info->saturationInChannel_4 == saturationLOW)
                        lower_saturations[4]++;
                    else if (torque_info->saturationInChannel_4 == saturationHIGH)
                        upper_saturations[4]++;
                    
                    if (torque_info->saturationInChannel_5 == saturationLOW)
                        lower_saturations[5]++;
                    else if (torque_info->saturationInChannel_5 == saturationHIGH)
                        upper_saturations[5]++;
                } break;                
                
            }
        }
        else
        {
            // send diag message about malformed message
            // uncomment if you need it for debugging
            /*
            eOerrmanDescriptor_t errdes = {0};
            errdes.sourcedevice         = (eOcanport1 == port) ? (eo_errman_sourcedevice_canbus1) : (eo_errman_sourcedevice_canbus2);
            errdes.sourceaddress        = EOCANPROT_FRAME_GET_SOURCE(frame);                
            errdes.code                 = eoerror_code_get(eoerror_category_Debug, eoerror_value_DEB_tag01);
            errdes.par16                = 0;
            errdes.par64                = 0;
            eo_errman_Error(eo_errman_GetHandle(), eo_errortype_debug, "strain saturation byte 7 (if sent) should be different from 0!", NULL, &errdes);
            */
        }    
    
    }
    
 
    if((numberofmessagesin1second > 0) && (counter >= numberofmessagesin1second))
    {   // ok, 1 second has expired (or better: so many messages have arrived for 1 second). 
            
        // reset counter    
        counter = 0;
            
        // send saturation message for every channel, if any
        for(uint8_t i = 0; i < 6; i++)
        {
            eOerrmanDescriptor_t errdes = {0};
            if (upper_saturations[i] != 0 || lower_saturations[i] != 0)
            {
                errdes.sourcedevice         = (eOcanport1 == port) ? (eo_errman_sourcedevice_canbus1) : (eo_errman_sourcedevice_canbus2);
                errdes.sourceaddress        = EOCANPROT_FRAME_GET_SOURCE(frame);                
                errdes.code                 = eoerror_code_get(eoerror_category_HardWare, eoerror_value_HW_strain_saturation);
                errdes.par16                = i; //channel involved
                errdes.par64                = (uint64_t) (upper_saturations[i]) << 32 | (uint64_t) lower_saturations[i]; //LSW->lower_sat, MSW->upper_sat
                eo_errman_Error(eo_errman_GetHandle(), eo_errortype_error, NULL, NULL, &errdes);
                
                upper_saturations[i] = 0;
                lower_saturations[i] = 0;
            }
         }                     
    }
}

// --------------------------------------------------------------------------------------------------------------------
// - end-of-file (leave a blank line after)
// --------------------------------------------------------------------------------------------------------------------





