//
// Non-Degree Granting Education License -- for use at non-degree
// granting, nonprofit, educational organizations only. Not for
// government, commercial, or other organizational use.
//
// File: control_foc_private.h
//
// Code generated for Simulink model 'control_foc'.
//
// Model version                  : 1.125
// Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
// C/C++ source code generated on : Wed Aug  4 00:04:39 2021
//
// Target selection: ert.tlc
// Embedded hardware selection: ARM Compatible->ARM Cortex-M
// Code generation objectives: Unspecified
// Validation result: Not run
//
#ifndef RTW_HEADER_control_foc_private_h_
#define RTW_HEADER_control_foc_private_h_
#include "rtwtypes.h"

// Macros for accessing real-time model data structure
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         (*((rtm)->errorStatus))
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    (*((rtm)->errorStatus) = (val))
#endif

#ifndef rtmGetErrorStatusPointer
#define rtmGetErrorStatusPointer(rtm)  (rtm)->errorStatus
#endif

#ifndef rtmSetErrorStatusPointer
#define rtmSetErrorStatusPointer(rtm, val) ((rtm)->errorStatus = (val))
#endif

extern const real32_T rtCP_pooled_UMvRVJ73F4lr[6];
extern const real32_T rtCP_pooled_52s2BNqONpP8[8];

#define rtCP_IaIbIc0_Gain              rtCP_pooled_UMvRVJ73F4lr  // Computed Parameter: rtCP_IaIbIc0_Gain
                                                                 //  Referenced by: '<S1>/Ia+Ib+Ic=0'

#define rtCP_DirectLookupTablenD1_table rtCP_pooled_52s2BNqONpP8 // Computed Parameter: rtCP_DirectLookupTablenD1_table
                                                                 //  Referenced by: '<S1>/Direct Lookup Table (n-D)1'

#endif                                 // RTW_HEADER_control_foc_private_h_

//
// File trailer for generated code.
//
// [EOF]
//
