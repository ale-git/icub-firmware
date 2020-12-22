
/*
 * Copyright (C) 2020 iCub Tech - Istituto Italiano di Tecnologia
 * Author:  Marco Accame
 * email:   marco.accame@iit.it
*/


// --------------------------------------------------------------------------------------------------------------------
// - public interface
// --------------------------------------------------------------------------------------------------------------------

#include "tCTRL.h"

// --------------------------------------------------------------------------------------------------------------------
// - external dependencies
// --------------------------------------------------------------------------------------------------------------------

#include "embot_os_Thread.h"
#include "embot_os_Timer.h"
#include "embot_os_rtos.h"

#include <array>

#include "embot_app_PZdriver.h"

#if defined(USE_PZMdriver) 
#include "piezo.h"
#include "tables.h"
#endif

// --------------------------------------------------------------------------------------------------------------------
// - pimpl: private implementation (see scott meyers: item 22 of effective modern c++, item 31 of effective c++
// --------------------------------------------------------------------------------------------------------------------


     
struct embot::app::ctrl::tCTRL::Impl
{  
    Config _config {};  

    static constexpr embot::os::Event evtTick = embot::core::binary::mask::pos2mask<embot::os::Event>(0);        

    embot::os::EventThread * evt {nullptr};
    embot::os::Timer *tmr {nullptr};
    
    bool _active {true};
    
    // one lut
    embot::app::myPZlut *_pzlut {nullptr};
    // three drivers, one per motor
    std::array<embot::app::PZdriver*, embot::core::tointegral(embot::hw::PZM::maxnumberof)> _pzdrivers {nullptr};
    // three setpoints, one per motor
    std::array<embot::app::PZdriver::setpoint_t, embot::core::tointegral(embot::hw::PZM::maxnumberof)> _setpoints {0};

    
    Impl() 
    {
        // ....
    }
    
    ~Impl()
    {
        // ...
    }
    
    bool start(const Config &config)
    {
        _config = config;
        // ...
        
         embot::os::EventThread::Config configEV { 
            6*1024, 
            embot::os::Priority::high47, 
            ctrl_startup,
            this,
            50*embot::core::time1millisec,
            ctrl_onevent,
            "tCTRL"
        };
        
            
        // create the main thread 
        evt = new embot::os::EventThread;          
        // and start it
        evt->start(configEV);        
        
        // and activate the timer.
        tmr = new embot::os::Timer;   
        embot::os::Action act(embot::os::EventToThread(evtTick, evt));
        embot::os::Timer::Config cfg{_config.period, act, embot::os::Timer::Mode::forever, 0};
        tmr->start(cfg);       
        
        return true;
    } 
    
    static void ctrl_startup(embot::os::Thread *t, void *param)
    {
        embot::app::ctrl::tCTRL::Impl *impl = reinterpret_cast<embot::app::ctrl::tCTRL::Impl*>(param);
        
        impl->_pzlut = new embot::app::myPZlut;
        
        for(int i=0; i<impl->_pzdrivers.size(); i++)
        {
            embot::hw::PZM pzm = static_cast<embot::hw::PZM>(i);
            impl->_pzdrivers[i] = new embot::app::PZdriver;
            impl->_pzdrivers[i]->init({pzm, impl->_pzlut});
            impl->_pzdrivers[i]->start();
        }

#if defined(USE_PZMdriver)        
        piezoMotorCfg_t pzm = { delta_8192, 8192 };
        piezoInit( &pzm, &pzm, &pzm);
#endif  
    }
    
    static void ctrl_onevent(embot::os::Thread *t, embot::os::EventMask eventmask, void *param)
    {  
        if(0 == eventmask)
        {   // timeout ...         
            return;
        }
        
        embot::app::ctrl::tCTRL::Impl *impl = reinterpret_cast<embot::app::ctrl::tCTRL::Impl*>(param);

        if(true == embot::core::binary::mask::check(eventmask, evtTick)) 
        {      
            embot::core::TimeFormatter tf(embot::core::now());        
            embot::core::print("tCTRL::onevent() -> evtTick received @ time = " + tf.to_string());  

            if(true == impl->_active)
            {
                impl->get_data();
                
                impl->run_matlab();
                
                impl->apply_results();
            }
        }
        
        // other possible events ...
        
    }
    
    
    void get_data() 
    {
        
        // read shared memory pool with sensors data, with data coming from CAN, ... 
        // in general whatever is required to run the control
        
        // assign data to the control class generated by matlab    
    }
            
    void run_matlab()
    {
        // just tick the control
        
        
        // get the values for the PZ drivers
        

        static uint32_t value {0};       
        _setpoints[0] = value;
        _setpoints[1] = value+1;
        _setpoints[2] = value+2;        
        value += 16;    
    }
            
    void apply_results()
    {
        // give the values to the PZ drivers
        
        for(int i=0; i<_pzdrivers.size(); i++)
        {
            _pzdrivers[i]->set(_setpoints[i]);
        }

    }
        
};




// --------------------------------------------------------------------------------------------------------------------
// - all the rest
// --------------------------------------------------------------------------------------------------------------------

    

embot::app::ctrl::tCTRL::tCTRL()
: pImpl(new Impl())
{ 

}


embot::app::ctrl::tCTRL::~tCTRL()
{   
    delete pImpl;
}

bool embot::app::ctrl::tCTRL::start(const Config &config)
{
    return pImpl->start(config);
}





// - end-of-file (leave a blank line after)----------------------------------------------------------------------------




