
/*
 * Copyright (C) 2023 iCub Tech - Istituto Italiano di Tecnologia
 * Author:  Marco Accame
 * email:   marco.accame@iit.it
*/


// - include guard ----------------------------------------------------------------------------------------------------

#ifndef __EMBOT_APP_BOARD_AMC2C_MBD_H_
#define __EMBOT_APP_BOARD_AMC2C_MBD_H_



#include "embot_app_bldc_theApplication.h"


namespace embot::app::board::amc2c::mbd {
    
    void Startup(embot::app::msg::ADR adr);    
    void OnTick(const std::vector<embot::app::bldc::MSG> &input, std::vector<embot::app::bldc::MSG> &output);
    
} // embot::app::board::amc2c::mbd {


#endif  // include-guard


// - end-of-file (leave a blank line after)----------------------------------------------------------------------------
