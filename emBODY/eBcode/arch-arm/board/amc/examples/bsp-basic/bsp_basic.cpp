
/*
 * Copyright (C) 2021 iCub Tech - Istituto Italiano di Tecnologia
 * Author:  Marco Accame
 * email:   marco.accame@iit.it
*/


#include "bsp_basic.h"

#include "stdint.h"
#include "stm32hal.h"


int bsp_basic_itm_puts(const char* str) 
{    
    if(nullptr == str)
    {
        return(0);
    }

    std::uint32_t ch;
    int num = 0;
    while('\0' != (ch = *str))
    {
        ITM_SendChar(ch);
        str++;
        num++;
    }
     
    ITM_SendChar('\n');
    return(++num);    
}

// the led section. we use 

#if defined(STM32HAL_BOARD_AMC)
    
    // led1 orange is on PH13,
    static GPIO_TypeDef * GPIOLED = GPIOH;
    static const uint16_t PinLED = GPIO_PIN_13;
    static void clockEnableLED() {  __HAL_RCC_GPIOH_CLK_ENABLE(); }
#endif

void bsp_basic_led_init()
{
    
#if defined(STM32HAL_BOARD_AMC ) 
    // start clock
    clockEnableLED();
    
    // configure led
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = PinLED;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOLED, &GPIO_InitStruct);
    
    // switch it on
    HAL_GPIO_WritePin(GPIOLED, PinLED, GPIO_PIN_SET); 
    
    // switch it off
    HAL_GPIO_WritePin(GPIOLED, PinLED, GPIO_PIN_RESET); 
#endif    
}

void bsp_basic_led_toggle()
{
#if defined(STM32HAL_BOARD_AMC)
    HAL_GPIO_TogglePin(GPIOLED, PinLED);  
#endif    
}
 
// this macro is seen through stm32hal.h
//#if defined(STM32HAL_removeWEAK_ETH)
//// others, required because they have been removed from stm32hal.h7.stm32h745disco.lib
//void HAL_ETH_RxCpltCallback(ETH_HandleTypeDef *heth) {}
//void HAL_ETH_PMTCallback(ETH_HandleTypeDef *heth) {}
//void HAL_ETH_TxCpltCallback(ETH_HandleTypeDef *heth) {}
//#endif

// - end-of-file (leave a blank line after)----------------------------------------------------------------------------



