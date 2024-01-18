//
// Non-Degree Granting Education License -- for use at non-degree
// granting, nonprofit, education, and research organizations only. Not
// for commercial or industrial use.
//
// File: can_encoder.h
//
// Code generated for Simulink model 'can_encoder'.
//
// Model version                  : 6.3
// Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
// C/C++ source code generated on : Mon Jan 15 14:41:18 2024
//
// Target selection: ert.tlc
// Embedded hardware selection: ARM Compatible->ARM Cortex-M
// Code generation objectives: Unspecified
// Validation result: Not run
//
#ifndef RTW_HEADER_can_encoder_h_
#define RTW_HEADER_can_encoder_h_
#include "rtwtypes.h"
#include "can_encoder_types.h"

//
//  Exported Global Parameters
//
//  Note: Exported global parameters are tunable parameters with an exported
//  global storage class designation.  Code generation will declare the memory for
//  these parameters and exports their symbols.
//

extern real32_T CAN_ANGLE_DEG2ICUB;    // Variable: CAN_ANGLE_DEG2ICUB
                                          //  Referenced by:
                                          //    '<S2>/Gain1'
                                          //    '<S2>/Gain3'
                                          //  2^16/360

extern uint8_T CAN_ID_AMC;             // Variable: CAN_ID_AMC
                                          //  Referenced by:
                                          //    '<S2>/Constant'
                                          //    '<S4>/Constant'
                                          //  4 bits defining the ID of the AMC_BLDC board.

extern void can_encoder(const BUS_MESSAGES_TX *rtu_messages_tx, const
  BUS_STATUS_TX *rtu_status_tx, const ConfigurationParameters
  *rtu_ConfigurationParameters, BUS_CAN_MULTIPLE *rty_pck_tx);

// Model reference registration function
extern void can_encoder_initialize(const char_T **rt_errorStatus);

//-
//  The generated code includes comments that allow you to trace directly
//  back to the appropriate location in the model.  The basic format
//  is <system>/block_name, where system is the system number (uniquely
//  assigned by Simulink) and block_name is the name of the block.
//
//  Use the MATLAB hilite_system command to trace the generated code back
//  to the model.  For example,
//
//  hilite_system('<S3>')    - opens system 3
//  hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
//
//  Here is the system hierarchy for this model
//
//  '<Root>' : 'can_encoder'
//  '<S1>'   : 'can_encoder/CAN_Encoder'
//  '<S2>'   : 'can_encoder/CAN_Encoder/FOC'
//  '<S3>'   : 'can_encoder/CAN_Encoder/NotUsed'
//  '<S4>'   : 'can_encoder/CAN_Encoder/STATUS'
//  '<S5>'   : 'can_encoder/CAN_Encoder/FOC/format_can_id'
//  '<S6>'   : 'can_encoder/CAN_Encoder/FOC/format_foc_pck'
//  '<S7>'   : 'can_encoder/CAN_Encoder/FOC/format_can_id/format_can_id'
//  '<S8>'   : 'can_encoder/CAN_Encoder/STATUS/format_can_id'
//  '<S9>'   : 'can_encoder/CAN_Encoder/STATUS/format_status_pck'
//  '<S10>'  : 'can_encoder/CAN_Encoder/STATUS/format_can_id/format_can_id'

#endif                                 // RTW_HEADER_can_encoder_h_

//
// File trailer for generated code.
//
// [EOF]
//
