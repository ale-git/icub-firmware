//
// Non-Degree Granting Education License -- for use at non-degree
// granting, nonprofit, educational organizations only. Not for
// government, commercial, or other organizational use.
//
// File: control_foc_private.h
//
// Code generated for Simulink model 'control_foc'.
//
// Model version                  : 1.120
// Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
// C/C++ source code generated on : Fri Jul 30 09:48:35 2021
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

extern const real32_T rtCP_pooled_SkIFpbqzrhXd[8];

#define rtCP_DirectLookupTablenD1_table rtCP_pooled_SkIFpbqzrhXd // Computed Parameter: rtCP_DirectLookupTablenD1_table
                                                                 //  Referenced by: '<S1>/Direct Lookup Table (n-D)1'

#endif                                 // RTW_HEADER_control_foc_private_h_

//
// File trailer for generated code.
//
// [EOF]
//
