 /**********************************************************************
 *
 *    Filename:       UserParms.h
 *
 *    Tools used:     MPLAB IDE -> 8.30
 *                    C30 -> 3.12
 *
 *  In this file are grouped all the parameters that the user is likely 
 *  to change when a new motor, encoder or load are connected.
 *  Other parameters are related to HW configuration and control loops
 *  are not likely to be changed by the average user.
 *
 **********************************************************************/

#ifndef __USERPARMS_H__
#define __USERPARMS_H__

#define UDEF_SPEED_MAX  32767
#define HALL_ERROR_MAX_CNT 1000

//
// ADC Scaling for current reading. 
//
// Scaling constants: Determined by hardware design. 
// +-5 Amps sensor on PhaseA and PhaseC(B), current reading inverted in sign, 
// zero current on halfscale of Allegro ACS714 (2.5V)
// 
// ACS714-05 has a sensitivity 185mV/A, out of linearity range of 5A a 5V output is 
//  near 5[V]/0.185[V/A]=+-13.5[A]!!
//
// ADC voltage divider: 6.3K series 100K//15K = 6.3K series 13.043K -> scale factor = 0.657318
//  then when out = 5V vadc = 5*0.657318 = 3.286V
//
// full scale positive current reading is around 13.5[A], 1/13.5=0.074074
//  -> 32768==13.5A
// e.g the value for 1A reading is 32768:13.5A=x:1A
//
// For the ACS714-10 the sensitivity is 100mV/A

//
// DC-Link parameters
// 
// Undervoltage and Overvoltage values in 100mV units.
// The undervoltage protection will trigger if the VDCLink drops below this value. 
#define UNDERVOLTAGE_THRESHOLD 100
// The overvoltage detection will trigger if the VDCLink rise above this value. 
#define OVERVOLTAGE_THRESHOLD  600

// Deadtime in seconds (range 1.6 us to 25 ns)
// DHES accept a greater zero cross distortion in order to keep lower temperature
//#define DEADTIMESEC	  0.00000100
  #define DEADTIMESEC     0.00000025 // 250 ns 

// this forces the 2foc interrupt to delay PWM registers update when it is 
// about to do it very close to the PWM hardware register buffering.
// The number represent the estimated clock cycles taken by SVgen to
// update those registers. The call to SVgen is thus delayed if the
// algo foresee that the HW will shadows register during SVGen (in the
// next PWMSAFETIME clock cycles)
#define PWMSAFETIME 50 // svgen takes 34 cycles. be conservative

//
// CAN communication parameters
//
// Data rate of outgoing messages in 0.1 millisecond units
#define CAN_OUTPUT_DATARATE (float)2.0

//this macro let you to work with 2foc without fault
//#define NO_FAULT
//the ems send desired current in periodic message (the ems can send only one message for all 4 2FOC)
//NOTE: if you use this mode, you must be sure that 2FOC can addres belong to [1, 4].
#define DESIRED_CURR_IN_PER_MSG_BY_EMS          

// Oscillator Parameters
#define PLLIN          10000000  // External Crystal or Clock Frequency (Hz)
#define DESIREDMIPS	   40000000  // Enter desired MIPS
#define PWMFREQUENCY      20000  // Hz

#define BOARD_CAN_ADDR_DEFAULT 0xE

#endif
