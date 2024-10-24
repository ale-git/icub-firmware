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

// - include guard ----------------------------------------------------------------------------------------------------

#ifndef _EMBOT_APP_THECANBOARDINFO_H_
#define _EMBOT_APP_THECANBOARDINFO_H_

#include "embot_core.h"
#include "embot_prot_can.h"
#include <memory>


namespace embot { namespace app {
           
    class theCANboardInfo
    {
    public:
        static theCANboardInfo& getInstance();
                
    public:
    
        static const std::uint32_t validityKey = 0x8888dead;
        struct StoredInfo
        {   // contains the basics stored inside some embot::i2h::Storage
            std::uint32_t       key;
            std::uint8_t        canaddress;
            std::uint8_t        boardtype;
            std::uint8_t        bootloaderVmajor;
            std::uint8_t        bootloaderVminor;
            std::uint8_t        info32[32];
            std::uint8_t        applicationVmajor;
            std::uint8_t        applicationVminor;
            std::uint8_t        applicationVbuild;
            std::uint8_t        protocolVmajor;
            std::uint8_t        protocolVminor;
            
            std::uint8_t        tobefilled[3];  // to make the size of struct ... multiple of 8.
        }; 
        
        struct bootloaderInfo
        {
            embot::prot::can::Board board {embot::prot::can::Board::none};
            embot::prot::can::versionOfBOOTLOADER version {0, 0};
            std::uint8_t adr {1};
            const char * definfo32 {nullptr};
            
            bootloaderInfo() = default;
            constexpr bootloaderInfo(embot::prot::can::Board b, const embot::prot::can::versionOfBOOTLOADER &v, std::uint8_t a, const char *i) 
                        : board(b), version(v), adr(a), definfo32(i) {}             
        };
        
        
        struct applicationInfo
        {
            embot::prot::can::versionOfAPPLICATION version {0, 0, 0};
            embot::prot::can::versionOfCANPROTOCOL protocol {0, 0};

            applicationInfo() = default;
            constexpr applicationInfo(const embot::prot::can::versionOfAPPLICATION &v, const embot::prot::can::versionOfCANPROTOCOL &p) 
                        : version(v), protocol(p) {}             
        };        
        
        
        bool erase();
        
        bool synch(const bootloaderInfo &info);
        bool synch(embot::prot::can::Board type, embot::prot::can::versionOfBOOTLOADER version, std::uint8_t adr, const char *defInfo32);
        
        bool synch(const applicationInfo &info);
        bool synch(embot::prot::can::versionOfAPPLICATION application, embot::prot::can::versionOfCANPROTOCOL protocol);
        
        bool get(StoredInfo &info);
        bool set(const StoredInfo &info);
        
        std::uint8_t getCANaddress();
        bool setCANaddress(std::uint8_t adr);
        
        // the cached can address is refreshed at very call of: synch(), setCANaddress(), getCANaddress(), set().
        // it can be used by the application or by the various parsers to get access to teh can address without making a direct read from storage.        
        std::uint8_t cachedCANaddress();
        
        // todo: we could use two different pages for board and userspace. but we should share the buffer ...
        static const std::uint32_t sizeOfUserSpace = 128+256+512; 
        
        // but we can read / write particular areas of max size sizeOfUserSpace. we can use it for storing matrices or ... whatever we want, as long as we dont do mess
        bool userdatawrite(std::uint32_t address, std::uint32_t size, const void *data);
        bool userdataread(std::uint32_t address, std::uint32_t size, void *data);
        bool userdataerase();
        
    private:
        theCANboardInfo(); 
        ~theCANboardInfo(); 
  
    private:    
        struct Impl;
        std::unique_ptr<Impl> pImpl;       
    };       


}} // namespace embot { namespace app {


#endif  // include-guard


// - end-of-file (leave a blank line after)----------------------------------------------------------------------------
