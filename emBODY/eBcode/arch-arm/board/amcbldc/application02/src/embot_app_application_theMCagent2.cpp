
/*
 * Copyright (C) 2021 iCub Tech - Istituto Italiano di Tecnologia
 * Author:  Marco Accame
 * email:   marco.accame@iit.it
*/


// --------------------------------------------------------------------------------------------------------------------
// - public interface
// --------------------------------------------------------------------------------------------------------------------

#include "embot_app_application_theMCagent2.h"



// --------------------------------------------------------------------------------------------------------------------
// - external dependencies
// --------------------------------------------------------------------------------------------------------------------

#include "embot_hw_motor.h"
#include "control_outer.h"
#include "control_foc.h"
#include "FOCInnerLoop.h"

#include "embot_app_theCANboardInfo.h"

#include "encoder.h"
#include "pwm.h"

// --------------------------------------------------------------------------------------------------------------------
// - pimpl: private implementation (see scott meyers: item 22 of effective modern c++, item 31 of effective c++
// --------------------------------------------------------------------------------------------------------------------

struct embot::app::application::theMCagent2::Impl
{   
    Config config {};
        
    bool initted {false};
        
    //embot::hw::motor::Position encoder {0};
    //embot::hw::motor::Position hallcounter {0};
    
    embot::prot::can::motor::polling::ControlMode cm {embot::prot::can::motor::polling::ControlMode::Idle};    
    bool applychanges {false};
    
    control_outerModelClass control_outer;
    
    //struct rtu_control_outer_T
    //{
        ControlModes rtu_Flags_control_mode; 
        boolean_T rtu_Flags_PID_reset;
        real32_T rtu_Config_velocitylimits_limit[2];
        real32_T rtu_Config_motorconfig_reductio;
        boolean_T rtu_Config_motorconfig_has_spee;
        real32_T rtu_Config_PosLoopPID_P;
        real32_T rtu_Config_PosLoopPID_I;
        real32_T rtu_Config_PosLoopPID_D;
        real32_T rtu_Config_PosLoopPID_N;
        real32_T rtu_Config_VelLoopPID_P;
        real32_T rtu_Config_VelLoopPID_I; 
        real32_T rtu_Config_VelLoopPID_D; 
        real32_T rtu_Config_VelLoopPID_N;
        real32_T rtu_Config_DirLoopPID_P;
        real32_T rtu_Config_DirLoopPID_I; 
        real32_T rtu_Config_DirLoopPID_D;
        real32_T rtu_Config_DirLoopPID_N; 
        real32_T rtu_Sensors_jointpositions_posi;
        real32_T rtu_Sensors_motorsensors_omega;
        real32_T rtu_Targets_jointpositions_posi;
        real32_T rtu_Targets_jointvelocities_vel; 
    //};
    
    //rtu_control_outer_T rtu_control_outer;
    
    //struct rty_control_outer_T
    //{
        boolean_T rty_OuterOutputs_vel_en;
        boolean_T rty_OuterOutputs_cur_en;
        boolean_T rty_OuterOutputs_out_en;
        real32_T rty_OuterOutputs_motorcurrent_c;
    //};
    
    //rty_control_outer_T rty_control_outer;
    
    static control_focModelClass control_foc;
    
    struct rtu_control_foc_T
    {
        boolean_T rtu_Flags_PID_reset = false;
        
        real32_T rtu_Config_motorconfig_Kp =    2.f;
        real32_T rtu_Config_motorconfig_Ki =  500.f;
        
        real32_T rtu_Config_motorconfig_Kbemf  = 0.f;
        real32_T rtu_Config_motorconfig_Rphase = 0.f;
        
        real32_T rtu_Config_motorconfig_Vmax =  9.f;
        real32_T rtu_Config_motorconfig_Vcc  = 24.f;
        
        real32_T rtu_Sensors_motorsensors_Iabc[3] = {0,0,0};
        real32_T rtu_Sensors_motorsensors_angl_k = 0;
        real32_T rtu_Sensors_motorsensors_omeg_k = 0;
        uint8_T rtu_Sensors_motorsensors_hall_e  = 0;
        
        real32_T rtu_Targets_motorcurrent_curr_c = 0;
        real32_T rtu_Targets_motorvoltage_volt_e = 0;
        real32_T rtu_OuterOutputs_motorcurrent_d = 0;
        
        boolean_T rtu_OuterOutputs_vel_en = 0;
        boolean_T rtu_OuterOutputs_cur_en = 0;
        boolean_T rtu_OuterOutputs_out_en = 0;
    };
    
    rtu_control_foc_T rtu_control_foc;
    
    struct rty_control_foc_T
    {
        uint16_T rty_Vabc_PWM_ticks[3];
        real32_T rty_Iq_fbk_current;
    };
    
    rty_control_foc_T rty_control_foc;
    
    static embot::prot::can::motor::periodic::Message_FOC::Info info; 
    
    
    Impl() = default;
    
    static void inner_foc_callback(int16_T Iuvw[3], void* rtu, void* rty)
    {
        rtu_control_foc_T* u = (rtu_control_foc_T*)rtu;
        rty_control_foc_T* y = (rty_control_foc_T*)rty;
                
        embot::hw::motor::gethallstatus(embot::hw::MOTOR::one, u->rtu_Sensors_motorsensors_hall_e);
        
        embot::hw::motor::Position electricalAngle;
        embot::hw::motor::getencoder(embot::hw::MOTOR::one, electricalAngle);
        
        static uint16_t electricalAngleOld = electricalAngle;
        int16_t delta = electricalAngle - electricalAngleOld;
        electricalAngleOld = electricalAngle;
        
        static real32_T speed = 0;
        
        speed = 0.9f*speed + 0.1f*(real32_T(delta));
        
        //speed = real32_T(delta);
        
        u->rtu_Sensors_motorsensors_angl_k = real32_T(electricalAngle)*0.0054931640625f;
        
        u->rtu_Sensors_motorsensors_Iabc[0] = 0.001f*Iuvw[0];
        u->rtu_Sensors_motorsensors_Iabc[1] = 0.001f*Iuvw[1];
        u->rtu_Sensors_motorsensors_Iabc[2] = 0.001f*Iuvw[2];
                
        control_foc.control_foc_ISR(
            &(u->rtu_Flags_PID_reset), 
            &(u->rtu_Config_motorconfig_Kp), 
            &(u->rtu_Config_motorconfig_Ki), 
            &(u->rtu_Config_motorconfig_Kbemf), 
            &(u->rtu_Config_motorconfig_Rphase), 
            &(u->rtu_Config_motorconfig_Vmax), 
            &(u->rtu_Config_motorconfig_Vcc), 
            u->rtu_Sensors_motorsensors_Iabc,
            &(u->rtu_Sensors_motorsensors_angl_k),        
            &(u->rtu_Sensors_motorsensors_omeg_k), 
            &(u->rtu_Sensors_motorsensors_hall_e), 
            &(u->rtu_Targets_motorcurrent_curr_c), 
            &(u->rtu_Targets_motorvoltage_volt_e), 
            &(u->rtu_OuterOutputs_vel_en), 
            &(u->rtu_OuterOutputs_cur_en), 
            &(u->rtu_OuterOutputs_out_en), 
            &(u->rtu_OuterOutputs_motorcurrent_d), 
            y->rty_Vabc_PWM_ticks,
            &(y->rty_Iq_fbk_current)
        );
                
            real32_T Va = y->rty_Vabc_PWM_ticks[0];
            real32_T Vb = y->rty_Vabc_PWM_ticks[1];
            real32_T Vc = y->rty_Vabc_PWM_ticks[2];
                    
            real32_T Vavg = 0.333f*(Va+Vb+Vc);
            
            Va -= Vavg;
            Vb -= Vavg;
            Vc -= Vavg;
                    
            info.canaddress = embot::app::theCANboardInfo::getInstance().cachedCANaddress();   
            info.current = int16_t(1000.0f*y->rty_Iq_fbk_current);
            info.velocity = int16_t(10.0f*speed); 
            info.position = (int32_t(Va)<<20) | (int32_t(Vb)<<10) | int16_t(Vc);  
                
        embot::hw::motor::setpwmUVW(embot::hw::MOTOR::one, y->rty_Vabc_PWM_ticks[0], y->rty_Vabc_PWM_ticks[1], y->rty_Vabc_PWM_ticks[2]);
        
        static int noflood = 0;
        if (++noflood > 28000)
        {
            noflood = 0;
            static char msg[128];
            
            sprintf(msg, "FOC hall = %d elang = %f\n  Iq* = %f Iq = %f\n  speed = %f\n", 
                u->rtu_Sensors_motorsensors_hall_e, u->rtu_Sensors_motorsensors_angl_k,
                u->rtu_Targets_motorcurrent_curr_c, y->rty_Iq_fbk_current, 
                10.0f*speed);      
            
            
            embot::core::print(msg);              
        }
    }
    
    bool initialise()
    {
        if(true == initted)
        {
            return true;
        }    
        // init motor
        embot::hw::motor::init(embot::hw::MOTOR::one, {});
        
        embot::hw::motor::setADCcallback(embot::hw::MOTOR::one, inner_foc_callback, &rtu_control_foc, &rty_control_foc);
            
        // call MBD.init
        control_outer.initialize();
        control_foc.initialize();
            
        initted = true;
        return true;   
    }

    bool tick(std::vector<embot::prot::can::Frame> &outframes)
    {
        if(true == applychanges)
        {
            // in case we change control mode to idle, i impose pwm = 0;
            // in case i change the pwm ... well, we manage that in HERE
            if(embot::prot::can::motor::polling::ControlMode::Idle == cm)
            {
                rty_OuterOutputs_out_en = false;
                rty_OuterOutputs_vel_en = false;
                rty_OuterOutputs_cur_en = false;
                
                embot::hw::motor::motorDisable(embot::hw::MOTOR::one);
            }
                        
            if(embot::prot::can::motor::polling::ControlMode::Current == cm)
            {
                rty_OuterOutputs_out_en = true;
                rty_OuterOutputs_vel_en = false;
                rty_OuterOutputs_cur_en = true;
                
                embot::hw::motor::motorEnable(embot::hw::MOTOR::one);
            }
            
            if(embot::prot::can::motor::polling::ControlMode::OpenLoop == cm)
            {
                rty_OuterOutputs_out_en = true;
                rty_OuterOutputs_vel_en = false;
                rty_OuterOutputs_cur_en = false;
                
                embot::hw::motor::motorEnable(embot::hw::MOTOR::one);
            }
            
            applychanges = false;      
        }
        
        /*
        control_outer.step(
            &rtu_Flags_control_mode, 
            &rtu_Flags_PID_reset, 
            rtu_Config_velocitylimits_limit,
            &rtu_Config_motorconfig_reductio,
            &rtu_Config_motorconfig_has_spee,
            &rtu_Config_PosLoopPID_P, 
            &rtu_Config_PosLoopPID_I,
            &rtu_Config_PosLoopPID_D, 
            &rtu_Config_PosLoopPID_N, 
            &rtu_Config_VelLoopPID_P,
            &rtu_Config_VelLoopPID_I, 
            &rtu_Config_VelLoopPID_D, 
            &rtu_Config_VelLoopPID_N,
            &rtu_Config_DirLoopPID_P, 
            &rtu_Config_DirLoopPID_I, 
            &rtu_Config_DirLoopPID_D,
            &rtu_Config_DirLoopPID_N, 
            &rtu_Sensors_jointpositions_posi, 
            &rtu_Sensors_motorsensors_omega, 
            &rtu_Targets_jointpositions_posi, 
            &rtu_Targets_jointvelocities_vel, 
            &rty_OuterOutputs_vel_en,
            &rty_OuterOutputs_cur_en, 
            &rty_OuterOutputs_out_en, 
            &rty_OuterOutputs_motorcurrent_c
        );
        */
        
        rtu_control_foc.rtu_OuterOutputs_motorcurrent_d = rty_OuterOutputs_motorcurrent_c;
        
        rtu_control_foc.rtu_OuterOutputs_vel_en = rty_OuterOutputs_vel_en;
        rtu_control_foc.rtu_OuterOutputs_cur_en = rty_OuterOutputs_cur_en;
        rtu_control_foc.rtu_OuterOutputs_out_en = rty_OuterOutputs_out_en;
        
        if(embot::prot::can::motor::polling::ControlMode::Idle != cm)
        {
            // add status of motor...
            
            //embot::hw::motor::getencoder(embot::hw::MOTOR::one, encoder);
            //embot::hw::motor::gethallcounter(embot::hw::MOTOR::one, hallcounter);
            
            
            // do whatever the MBD needs 
            // call MBD.tick
 
            embot::prot::can::Frame frame {};   
                            
            embot::prot::can::motor::periodic::Message_FOC msg;
            
            info.canaddress = embot::app::theCANboardInfo::getInstance().cachedCANaddress();                 
            
            msg.load(info);
            msg.get(frame);
            outframes.push_back(frame);              
        }
        
        return true;
    }    
};

control_focModelClass embot::app::application::theMCagent2::Impl::control_foc;
embot::prot::can::motor::periodic::Message_FOC::Info embot::app::application::theMCagent2::Impl::info;

// --------------------------------------------------------------------------------------------------------------------
// - the class
// --------------------------------------------------------------------------------------------------------------------


embot::app::application::theMCagent2& embot::app::application::theMCagent2::getInstance()
{
    static theMCagent2* p = new theMCagent2();
    return *p;
}

embot::app::application::theMCagent2::theMCagent2()
{
    pImpl = std::make_unique<Impl>();
}  

    
embot::app::application::theMCagent2::~theMCagent2() { }
        
bool embot::app::application::theMCagent2::initialise(const Config &config)
{
    pImpl->control_outer.initialize();
    pImpl->control_foc.initialize();
    
    pImpl->config = config;   
    return pImpl->initialise();
}

bool embot::app::application::theMCagent2::tick(std::vector<embot::prot::can::Frame> &outframes)
{
    return pImpl->tick(outframes);
}


// interface to CANagentMC

bool embot::app::application::theMCagent2::get(const embot::prot::can::motor::periodic::Message_EMSTO2FOC_DESIRED_CURRENT::Info &info)
{
    embot::core::print("received EMSTO2FOC_DESIRED_CURRENT[]: " + std::to_string(info.current[0]) + ", " + std::to_string(info.current[1]) + ", " + std::to_string(info.current[2]));
 
    pImpl->rtu_control_foc.rtu_Targets_motorcurrent_curr_c = pImpl->rtu_control_foc.rtu_Targets_motorvoltage_volt_e = 0.001f*((real32_T)info.current[0]);
    
    pImpl->applychanges = true;
    
    return true;    
}


bool embot::app::application::theMCagent2::get(const embot::prot::can::motor::polling::Message_SET_CONTROL_MODE::Info &info)
{   
    embot::core::print("received SET_CONTROL_MODE[]: " + embot::prot::can::motor::polling::tostring(info.controlmode) + " for motindex " + embot::prot::can::motor::polling::tostring(info.motorindex));

    pImpl->cm = info.controlmode;
    pImpl->applychanges = true;
    
    return true;    
}

bool embot::app::application::theMCagent2::get(const embot::prot::can::motor::polling::Message_GET_CONTROL_MODE::Info &info, embot::prot::can::motor::polling::Message_GET_CONTROL_MODE::ReplyInfo &replyinfo)
{    
    embot::core::print("received GET_CONTROL_MODE[]: for motindex " + embot::prot::can::motor::polling::tostring(info.motorindex));
    replyinfo.motorindex = info.motorindex;
    replyinfo.controlmode =  pImpl->cm;
    return true;    
}



// - end-of-file (leave a blank line after)----------------------------------------------------------------------------


