/*
 * Copyright (C) 2011 Department of Robotics Brain and Cognitive Sciences - Istituto Italiano di Tecnologia
 * Author:  Valentina Gaggero
 * email:   valentina.gaggero@iit.it
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
#include "stdio.h"
#include "OPCprotocolManager_Cfg.h" 
#include "OPCprotocolManager.h"


// --------------------------------------------------------------------------------------------------------------------
// - declaration of extern public interface
// --------------------------------------------------------------------------------------------------------------------



// --------------------------------------------------------------------------------------------------------------------
// - declaration of extern hidden interface 
// --------------------------------------------------------------------------------------------------------------------


// --------------------------------------------------------------------------------------------------------------------
// - #define with internal scope
// --------------------------------------------------------------------------------------------------------------------
// empty-section


// --------------------------------------------------------------------------------------------------------------------
// - definition (and initialisation) of extern variables, but better using _get(), _set() 
// --------------------------------------------------------------------------------------------------------------------

static opcprotman_var_map_t s_myarray[] = 
{
    {
        .var        = eom_ipnet_hid_DEBUG_id,
        .size       = sizeof(EOMtheIPnetDEBUG_t),
        .ptr        = NULL,
        .onrec      = NULL
    },
    {
        .var        = eom_emsrunner_hid_DEBUG_id,
        .size       = sizeof(EOMtheEMSrunnerDEBUG_t),
        .ptr        = NULL,
        .onrec      = NULL
    },
    {
        .var        = eom_emstransceiver_hid_DEBUG_id,
        .size       = sizeof(EOMtheEMStransceiverDEBUG_t),
        .ptr        = NULL,
        .onrec      = NULL
    },
    {
        .var        = eo_emsController_hid_DEBUG_id,
        .size       = sizeof(EOemsControllerDEBUG_t),
        .ptr        = NULL,
        .onrec      = NULL
    },    
    {
        .var        = eo_canFaultLogDEBUG_id,
        .size       = sizeof(EOcanFaultLogDEBUG_t),
        .ptr        = NULL,
        .onrec      = NULL
    },

     {
        .var        = eo_EncoderErrorDEBUG_id,
        .size       = sizeof(EOencoderErrorDEBUG_t),
        .ptr        = NULL,
        .onrec      = NULL
    } 
    
};

opcprotman_cfg_t opcprotmanCFGv0x1234 =
{
    .databaseversion        = 0x1234,
    .numberofvariables      = opcProt_numofvar_max,
    .arrayofvariablemap     = s_myarray
};

// --------------------------------------------------------------------------------------------------------------------
// - typedef with internal scope
// --------------------------------------------------------------------------------------------------------------------
// empty-section


// --------------------------------------------------------------------------------------------------------------------
// - declaration of static functions
// --------------------------------------------------------------------------------------------------------------------
// empty-section


// --------------------------------------------------------------------------------------------------------------------
// - definition (and initialisation) of static variables
// --------------------------------------------------------------------------------------------------------------------
// empty-section


// --------------------------------------------------------------------------------------------------------------------
// - definition of extern public functions
// --------------------------------------------------------------------------------------------------------------------

extern opcprotman_cfg_t* OPCprotocolManager_Cfg_getconfig(void)
{
    return(&opcprotmanCFGv0x1234);
}


// --------------------------------------------------------------------------------------------------------------------
// - definition of extern hidden functions 
// --------------------------------------------------------------------------------------------------------------------
// empty-section


// --------------------------------------------------------------------------------------------------------------------
// - definition of static functions 
// --------------------------------------------------------------------------------------------------------------------
// empty-section


// --------------------------------------------------------------------------------------------------------------------
// - end-of-file (leave a blank line after)
// --------------------------------------------------------------------------------------------------------------------




