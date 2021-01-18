
/*
 * Copyright (C) 2020 iCub Tech - Istituto Italiano di Tecnologia
 * Author:  Marco Accame
 * email:   marco.accame@iit.it
*/

// - include guard ----------------------------------------------------------------------------------------------------

#ifndef _EMBOT_HW_ADS122C04_BSP_H_
#define _EMBOT_HW_ADS122C04_BSP_H_


#include "embot_core.h"
#include "embot_hw_types.h"
#include "embot_hw_bsp.h"


namespace embot { namespace hw { namespace ads122c04 {
                                  
    struct PROP
    {   
        embot::hw::i2c::Descriptor i2cdes {embot::hw::I2C::none, 0};        
    };
    
    struct BSP : public embot::hw::bsp::SUPP
    {
        constexpr static std::uint8_t maxnumberof = embot::core::tointegral(embot::hw::ADS122C04::maxnumberof);
        constexpr BSP(std::uint32_t msk, std::array<const PROP*, maxnumberof> pro) : SUPP(msk), properties(pro) {} 
        constexpr BSP() : SUPP(0), properties({0}) {}
            
        std::array<const PROP*, maxnumberof> properties;    
        constexpr const PROP * getPROP(embot::hw::ADS122C04 h) const { return supported(h) ? properties[embot::core::tointegral(h)] : nullptr; }
        void init(embot::hw::ADS122C04 h) const;
    };
    
    const BSP& getBSP();
    
}}} // namespace embot { namespace hw { namespace ads122c04 { 



#endif  // include-guard


// - end-of-file (leave a blank line after)----------------------------------------------------------------------------


