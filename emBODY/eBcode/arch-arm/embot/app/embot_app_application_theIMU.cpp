/*
 * Copyright (C) 2017 iCub Facility - Istituto Italiano di Tecnologia
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
// - public interface
// --------------------------------------------------------------------------------------------------------------------

#include "embot_app_application_theIMU.h"



// --------------------------------------------------------------------------------------------------------------------
// - external dependencies
// --------------------------------------------------------------------------------------------------------------------

#include "embot.h"
#include "embot_common.h"
#include "embot_binary.h"

#include <new>
#include "embot_sys_Timer.h"
#include "embot_sys_Action.h"
#include "embot_hw.h"
#include "embot_app_canprotocol.h"
#include "embot_app_canprotocol_inertial_periodic.h"

#include <cstdio>

#include "embot_app_theCANboardInfo.h"

#include "embot_app_application_theCANtracer.h"


#include "embot_common.h"

#include "embot_hw_bno055.h"
#include "embot_hw_bsp_strain2.h"


// --------------------------------------------------------------------------------------------------------------------
// - pimpl: private implementation (see scott meyers: item 22 of effective modern c++, item 31 of effective c++
// --------------------------------------------------------------------------------------------------------------------


    
struct embot::app::application::theIMU::Impl
{ 
    
    struct canLegacyConfig
    {
        embot::app::canprotocol::analog::polling::Message_ACC_GYRO_SETUP::Info  accgyroinfo;
        bool accelEnabled;
        bool gyrosEnabled;  
        canLegacyConfig() { reset(); } 
        void reset()
        {
            accgyroinfo.maskoftypes = 0;
            accgyroinfo.txperiod = 50*embot::common::time1millisec;
            accelEnabled = false;       
            gyrosEnabled = false;
        }            
    };
    
    struct canRevisitedConfig
    {
        //embot::app::canprotocol::analog::polling::Message_ACC_GYRO_SETUP::Info  accgyroinfo;
        bool accelEnabled;
        bool gyrosEnabled;  
        std::uint16_t maskofenabled;
        canRevisitedConfig() { reset(); } 
        void reset()
        {
//            accgyroinfo.maskoftypes = 0;
//            accgyroinfo.txperiod = 50*embot::common::time1millisec;
            accelEnabled = false;       
            gyrosEnabled = false;
            maskofenabled = 0;
        }            
    };
    
    
    struct imuAcquisition
    {
        embot::common::relTime duration;
        embot::common::Time timeofstart;
        bool dataisready;
        embot::hw::BNO055::Data data;
        imuAcquisition() { reset(); } 
        void reset()
        {
            duration = 0;
            timeofstart = 0;
            dataisready = false;
            data.reset();
        } 
        void onstart()
        {
            timeofstart = embot::sys::timeNow(); 
            duration = 0;            
            dataisready = false;
            data.reset();
        }
        void onstop()
        {
            dataisready = true;  
            duration = embot::sys::timeNow() - timeofstart;    
        }
    };
    
   

    Config config;
           
    bool ticking;
        
    embot::sys::Timer *ticktimer;
    embot::sys::Action action;

    imuAcquisition imuacquisition;

    bool legacymode;    // if true we work with the old protocol mode.
    canLegacyConfig canlegacyconfig;
    
   
    Impl() 
    {   
        ticking = false;  

        ticktimer = new embot::sys::Timer;           

        legacymode = true;
        canlegacyconfig.reset();
        

        imuacquisition.reset();
    }
    
   
    bool start();
    bool stop();    
    bool tick(std::vector<embot::hw::can::Frame> &replies);
    bool processdata(std::vector<embot::hw::can::Frame> &replies);
    
    bool configure(embot::app::canprotocol::analog::polling::Message_ACC_GYRO_SETUP::Info &ag);
    
    
    bool fill(embot::app::canprotocol::inertial::periodic::Message_DIGITAL_ACCELEROMETER::Info &info);
    bool fill(embot::app::canprotocol::inertial::periodic::Message_DIGITAL_GYROSCOPE::Info &info);
    
    
    // imu support
    bool acquisition_start();
    bool acquisition_retrieve();
    bool acquisition_processing();
    
    
    static void alertdataisready(void *p)
    {
        embot::app::application::theIMU::Impl *mypImpl = reinterpret_cast<embot::app::application::theIMU::Impl*>(p);
        
        if(true == mypImpl->ticking)
        {
            mypImpl->config.totask->setEvent(mypImpl->config.datareadyevent);
        }
        
        mypImpl->imuacquisition.onstop();    
    }
                      
};



bool embot::app::application::theIMU::Impl::start()
{ 
    if(true == legacymode)
    {
        ticktimer->start(canlegacyconfig.accgyroinfo.txperiod, embot::sys::Timer::Type::forever, action);
        ticking = true;    
        return true;
    }
    
    return false;
}


bool embot::app::application::theIMU::Impl::stop()
{    
    ticktimer->stop();
    ticking = false;    
    return true;
}


bool embot::app::application::theIMU::Impl::fill(embot::app::canprotocol::inertial::periodic::Message_DIGITAL_ACCELEROMETER::Info &info)
{
    bool ret = true;
    
    info.canaddress = embot::app::theCANboardInfo::getInstance().cachedCANaddress();
    info.x = imuacquisition.data.acc.x;
    info.y = imuacquisition.data.acc.y;
    info.z = imuacquisition.data.acc.z;
         
    return ret;    
}


bool embot::app::application::theIMU::Impl::fill(embot::app::canprotocol::inertial::periodic::Message_DIGITAL_GYROSCOPE::Info &info)
{
    bool ret = true;

    info.canaddress = embot::app::theCANboardInfo::getInstance().cachedCANaddress();
    info.x = imuacquisition.data.gyr.x;
    info.y = imuacquisition.data.gyr.y;
    info.z = imuacquisition.data.gyr.z;
    
    return ret;    
}




bool embot::app::application::theIMU::Impl::tick(std::vector<embot::hw::can::Frame> &replies)
{   
    if(false == ticking)
    {
        return false;
    }
    
    if(true == legacymode)
    {
        if(0 == canlegacyconfig.accgyroinfo.maskoftypes)
        {
            return false;  
        }
    }
    else //  new mode
    {
        
    }
    
    
    // start acquisition
    acquisition_start();
       
    return true;    
}


bool embot::app::application::theIMU::Impl::processdata(std::vector<embot::hw::can::Frame> &replies)
{   
    if(false == ticking)
    {
        return false;
    }
        
    // retrieve acquired imu values
    acquisition_retrieve();
    
    // processing of acquired data
    acquisition_processing();
    
    // we are ready to transmit    
    embot::hw::can::Frame frame;   
     
    if(true == legacymode) 
    {        
        if(true == canlegacyconfig.accelEnabled)
        {
            embot::app::canprotocol::inertial::periodic::Message_DIGITAL_ACCELEROMETER msg;
            embot::app::canprotocol::inertial::periodic::Message_DIGITAL_ACCELEROMETER::Info accelinfo;
            if(true == fill(accelinfo))
            {
                msg.load(accelinfo);
                msg.get(frame);
                replies.push_back(frame);
            }            
        }
        
        if(true == canlegacyconfig.gyrosEnabled)
        {
            embot::app::canprotocol::inertial::periodic::Message_DIGITAL_GYROSCOPE msg;
            embot::app::canprotocol::inertial::periodic::Message_DIGITAL_GYROSCOPE::Info gyrosinfo;
            if(true == fill(gyrosinfo))
            {
                msg.load(gyrosinfo);
                msg.get(frame);
                replies.push_back(frame);
            }            
        }
    }    
         
    return true;           
}


bool embot::app::application::theIMU::Impl::acquisition_start()
{
    imuacquisition.onstart();
    embot::common::Callback cbk(alertdataisready, this);
    embot::hw::BNO055::acquisition(embot::hw::bsp::strain2::imuBOSCH, embot::hw::BNO055::Set::FULL, imuacquisition.data, cbk); 
    return true;
}


bool embot::app::application::theIMU::Impl::acquisition_retrieve()
{

    // 1. in imuacquisition.data we have the values.    
    //std::memmove(runtimedata.data.adcvalue, runtimedata.data.dmabuffer, sizeof(runtimedata.data.adcvalue));
           
    return true;
}

bool embot::app::application::theIMU::Impl::acquisition_processing()
{
    // we dont process IMU data
    return true;    
}


// --------------------------------------------------------------------------------------------------------------------
// - the class
// --------------------------------------------------------------------------------------------------------------------



embot::app::application::theIMU::theIMU()
: pImpl(new Impl)
{       

}

         
bool embot::app::application::theIMU::initialise(Config &config)
{
    pImpl->config = config;
    
    pImpl->action.set(embot::sys::Action::EventToTask(pImpl->config.tickevent, pImpl->config.totask));
    
    embot::hw::BNO055::init(embot::hw::bsp::strain2::imuBOSCH, embot::hw::bsp::strain2::imuBOSCHconfig); 
    embot::hw::BNO055::set(embot::hw::bsp::strain2::imuBOSCH, embot::hw::BNO055::Mode::NDOF, 5*embot::common::time1millisec);
     
    return true;
}


bool embot::app::application::theIMU::configure(embot::app::canprotocol::analog::polling::Message_ACC_GYRO_SETUP::Info &ag)
{
    // if ticking: stop it
    if(true == pImpl->ticking)
    {
        stop();
    }
    
    // we are in legacy mode:
    pImpl->legacymode = true;
    
    // copy new configuration
    pImpl->canlegacyconfig.accgyroinfo = ag;
    
    // get some settings from it.    
//    static const std::uint8_t accelmask =   static_cast<std::uint8_t>(embot::app::canprotocol::analog::polling::Message_ACC_GYRO_SETUP::InertialType::analogaccelerometer) |
//                                            static_cast<std::uint8_t>(embot::app::canprotocol::analog::polling::Message_ACC_GYRO_SETUP::InertialType::internaldigitalaccelerometer) |
//                                            static_cast<std::uint8_t>(embot::app::canprotocol::analog::polling::Message_ACC_GYRO_SETUP::InertialType::externaldigitalaccelerometer) ;                                        
//    static const std::uint8_t gyrosmask =   static_cast<std::uint8_t>(embot::app::canprotocol::analog::polling::Message_ACC_GYRO_SETUP::InertialType::externaldigitalgyroscope);  
                                                   
    pImpl->canlegacyconfig.accelEnabled = 
                            embot::binary::bit::check(pImpl->canlegacyconfig.accgyroinfo.maskoftypes, static_cast<std::uint8_t>(embot::app::canprotocol::analog::polling::Message_ACC_GYRO_SETUP::InertialTypeBit::analogaccelerometer))             ||
                            embot::binary::bit::check(pImpl->canlegacyconfig.accgyroinfo.maskoftypes, static_cast<std::uint8_t>(embot::app::canprotocol::analog::polling::Message_ACC_GYRO_SETUP::InertialTypeBit::internaldigitalaccelerometer))    ||
                            embot::binary::bit::check(pImpl->canlegacyconfig.accgyroinfo.maskoftypes, static_cast<std::uint8_t>(embot::app::canprotocol::analog::polling::Message_ACC_GYRO_SETUP::InertialTypeBit::externaldigitalaccelerometer));                                               
    pImpl->canlegacyconfig.gyrosEnabled =   
                            embot::binary::bit::check(pImpl->canlegacyconfig.accgyroinfo.maskoftypes, static_cast<std::uint8_t>(embot::app::canprotocol::analog::polling::Message_ACC_GYRO_SETUP::InertialTypeBit::externaldigitalgyroscope));   
    
    // if there is something to acquire and the rate is not zero: start acquisition
            
    if((0 != pImpl->canlegacyconfig.accgyroinfo.maskoftypes) && (0 != pImpl->canlegacyconfig.accgyroinfo.txperiod))
    {
        start();
    }
  
    return true;    
}


bool embot::app::application::theIMU::start()
{    
    return pImpl->start();
}


bool embot::app::application::theIMU::stop()
{    
    return pImpl->stop();
}


bool embot::app::application::theIMU::tick(std::vector<embot::hw::can::Frame> &replies)
{   
    return pImpl->tick(replies);
}


bool embot::app::application::theIMU::processdata(std::vector<embot::hw::can::Frame> &replies)
{   
    return pImpl->processdata(replies);
}


// - end-of-file (leave a blank line after)----------------------------------------------------------------------------


