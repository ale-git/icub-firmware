//
// Non-Degree Granting Education License -- for use at non-degree
// granting, nonprofit, educational organizations only. Not for
// government, commercial, or other organizational use.
//
// File: Position_Controller.h
//
// Code generated for Simulink model 'Position_Controller'.
//
// Model version                  : 2.0
// Simulink Coder version         : 9.4 (R2020b) 29-Jul-2020
// C/C++ source code generated on : Wed Nov 11 09:08:01 2020
//
// Target selection: ert.tlc
// Embedded hardware selection: ARM Compatible->ARM Cortex-M
// Code generation objectives:
//    1. Execution efficiency
//    2. RAM efficiency
// Validation result: Not run
//
#ifndef RTW_HEADER_Position_Controller_h_
#define RTW_HEADER_Position_Controller_h_
#include <stddef.h>
#include "rtwtypes.h"
#include <cfloat>
#include <cmath>
#include <cstring>
#include "rtwtypes.h"

// Model Code Variants

// Macros for accessing real-time model data structure
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

// Custom Type definition for MATLAB Function: '<S1>/motors2quat'
#ifndef struct_tag_v7m7NEstuUdktFlQqRQnjB
#define struct_tag_v7m7NEstuUdktFlQqRQnjB

struct tag_v7m7NEstuUdktFlQqRQnjB
{
  real_T a;
  real_T b;
  real_T c;
  real_T d;
};

#endif                                 //struct_tag_v7m7NEstuUdktFlQqRQnjB

#ifndef typedef_quaternion
#define typedef_quaternion

typedef tag_v7m7NEstuUdktFlQqRQnjB quaternion;

#endif                                 //typedef_quaternion

extern "C" {
  static real_T rtGetNaN(void);
  static real32_T rtGetNaNF(void);
}                                      // extern "C"
  extern "C"
{
  extern real_T rtInf;
  extern real_T rtMinusInf;
  extern real_T rtNaN;
  extern real32_T rtInfF;
  extern real32_T rtMinusInfF;
  extern real32_T rtNaNF;
  static void rt_InitInfAndNaN(size_t realSize);
  static boolean_T rtIsInf(real_T value);
  static boolean_T rtIsInfF(real32_T value);
  static boolean_T rtIsNaN(real_T value);
  static boolean_T rtIsNaNF(real32_T value);
  typedef struct {
    struct {
      uint32_T wordH;
      uint32_T wordL;
    } words;
  } BigEndianIEEEDouble;

  typedef struct {
    struct {
      uint32_T wordL;
      uint32_T wordH;
    } words;
  } LittleEndianIEEEDouble;

  typedef struct {
    union {
      real32_T wordLreal;
      uint32_T wordLuint;
    } wordL;
  } IEEESingle;
}                                      // extern "C"

extern "C" {
  static real_T rtGetInf(void);
  static real32_T rtGetInfF(void);
  static real_T rtGetMinusInf(void);
  static real32_T rtGetMinusInfF(void);
}                                      // extern "C"
  // Class declaration for model Position_Controller
  class Position_ControllerModelClass
{
  // public data and function members
 public:
  // Block signals and states (default storage) for system '<Root>'
  typedef struct {
    quaternion T;                      // '<S1>/motors2quat'
    real_T Filter_DSTATE[3];           // '<S35>/Filter'
    real_T Integrator_DSTATE[3];       // '<S40>/Integrator'
    real_T singularity_reg;            // '<S1>/motors2quat'
  } DW;

  // Constant parameters (default storage)
  typedef struct {
    // Pooled Parameter (Expression: Q)
    //  Referenced by:
    //    '<S1>/motors2quat'
    //    '<S1>/ypr2motors'

    real_T pooled4[9];
  } ConstP;

  // External inputs (root inport signals with default storage)
  typedef struct {
    real_T ypr[3];                     // '<Root>/ypr+'
    real_T theta[3];                   // '<Root>/theta'
  } ExtU;

  // External outputs (root outports fed by signals with default storage)
  typedef struct {
    real_T Tau[3];                     // '<Root>/Tau+'
    real_T ypr_meas[3];                // '<Root>/ypr_meas'
    real_T Singularity;                // '<Root>/Singularity'
    real_T InRange;                    // '<Root>/InRange'
    real_T Cycles;                     // '<Root>/Cycles'
  } ExtY;

  // Real-time Model Data Structure
  struct RT_MODEL {
    const char_T * volatile errorStatus;
  };

  // External inputs
  ExtU rtU;

  // External outputs
  ExtY rtY;

  // model initialize function
  void initialize();

  // model step function
  void step();

  // Constructor
  Position_ControllerModelClass();

  // Destructor
  ~Position_ControllerModelClass();

  // Real-Time Model get method
  Position_ControllerModelClass::RT_MODEL * getRTM();

  // private data and function members
 private:
  // Block signals and states
  DW rtDW;

  // Real-Time Model
  RT_MODEL rtM;

  // private member function(s) for subsystem '<Root>'
  real_T maximum(const real_T x[3]);
  real_T minimum(const real_T x[3]);
  void sind(real_T x[3]);
  real_T det(const real_T x[9]);
  void mldivide(const real_T A[9], const real_T B_0[3], real_T Y[3]);
}

;

// Constant parameters (default storage)
extern const Position_ControllerModelClass::ConstP rtConstP;

//-
//  The generated code includes comments that allow you to trace directly
//  back to the appropriate location in the model.  The basic format
//  is <system>/block_name, where system is the system number (uniquely
//  assigned by Simulink) and block_name is the name of the block.
//
//  Note that this particular code originates from a subsystem build,
//  and has its own system numbers different from the parent model.
//  Refer to the system hierarchy for this subsystem below, and use the
//  MATLAB hilite_system command to trace the generated code back
//  to the parent model.  For example,
//
//  hilite_system('ok_wrist_simple_motors_3/Position_Controller')    - opens subsystem ok_wrist_simple_motors_3/Position_Controller
//  hilite_system('ok_wrist_simple_motors_3/Position_Controller/Kp') - opens and selects block Kp
//
//  Here is the system hierarchy for this model
//
//  '<Root>' : 'ok_wrist_simple_motors_3'
//  '<S1>'   : 'ok_wrist_simple_motors_3/Position_Controller'
//  '<S2>'   : 'ok_wrist_simple_motors_3/Position_Controller/PID Controller'
//  '<S3>'   : 'ok_wrist_simple_motors_3/Position_Controller/Quaternions to Rotation Angles1'
//  '<S4>'   : 'ok_wrist_simple_motors_3/Position_Controller/motors2quat'
//  '<S5>'   : 'ok_wrist_simple_motors_3/Position_Controller/wrapTo180'
//  '<S6>'   : 'ok_wrist_simple_motors_3/Position_Controller/ypr2motors'
//  '<S7>'   : 'ok_wrist_simple_motors_3/Position_Controller/PID Controller/Anti-windup'
//  '<S8>'   : 'ok_wrist_simple_motors_3/Position_Controller/PID Controller/D Gain'
//  '<S9>'   : 'ok_wrist_simple_motors_3/Position_Controller/PID Controller/Filter'
//  '<S10>'  : 'ok_wrist_simple_motors_3/Position_Controller/PID Controller/Filter ICs'
//  '<S11>'  : 'ok_wrist_simple_motors_3/Position_Controller/PID Controller/I Gain'
//  '<S12>'  : 'ok_wrist_simple_motors_3/Position_Controller/PID Controller/Ideal P Gain'
//  '<S13>'  : 'ok_wrist_simple_motors_3/Position_Controller/PID Controller/Ideal P Gain Fdbk'
//  '<S14>'  : 'ok_wrist_simple_motors_3/Position_Controller/PID Controller/Integrator'
//  '<S15>'  : 'ok_wrist_simple_motors_3/Position_Controller/PID Controller/Integrator ICs'
//  '<S16>'  : 'ok_wrist_simple_motors_3/Position_Controller/PID Controller/N Copy'
//  '<S17>'  : 'ok_wrist_simple_motors_3/Position_Controller/PID Controller/N Gain'
//  '<S18>'  : 'ok_wrist_simple_motors_3/Position_Controller/PID Controller/P Copy'
//  '<S19>'  : 'ok_wrist_simple_motors_3/Position_Controller/PID Controller/Parallel P Gain'
//  '<S20>'  : 'ok_wrist_simple_motors_3/Position_Controller/PID Controller/Reset Signal'
//  '<S21>'  : 'ok_wrist_simple_motors_3/Position_Controller/PID Controller/Saturation'
//  '<S22>'  : 'ok_wrist_simple_motors_3/Position_Controller/PID Controller/Saturation Fdbk'
//  '<S23>'  : 'ok_wrist_simple_motors_3/Position_Controller/PID Controller/Sum'
//  '<S24>'  : 'ok_wrist_simple_motors_3/Position_Controller/PID Controller/Sum Fdbk'
//  '<S25>'  : 'ok_wrist_simple_motors_3/Position_Controller/PID Controller/Tracking Mode'
//  '<S26>'  : 'ok_wrist_simple_motors_3/Position_Controller/PID Controller/Tracking Mode Sum'
//  '<S27>'  : 'ok_wrist_simple_motors_3/Position_Controller/PID Controller/Tsamp - Integral'
//  '<S28>'  : 'ok_wrist_simple_motors_3/Position_Controller/PID Controller/Tsamp - Ngain'
//  '<S29>'  : 'ok_wrist_simple_motors_3/Position_Controller/PID Controller/postSat Signal'
//  '<S30>'  : 'ok_wrist_simple_motors_3/Position_Controller/PID Controller/preSat Signal'
//  '<S31>'  : 'ok_wrist_simple_motors_3/Position_Controller/PID Controller/Anti-windup/Disc. Clamping Ideal'
//  '<S32>'  : 'ok_wrist_simple_motors_3/Position_Controller/PID Controller/Anti-windup/Disc. Clamping Ideal/Dead Zone'
//  '<S33>'  : 'ok_wrist_simple_motors_3/Position_Controller/PID Controller/Anti-windup/Disc. Clamping Ideal/Dead Zone/Enabled'
//  '<S34>'  : 'ok_wrist_simple_motors_3/Position_Controller/PID Controller/D Gain/Internal Parameters'
//  '<S35>'  : 'ok_wrist_simple_motors_3/Position_Controller/PID Controller/Filter/Disc. Forward Euler Filter'
//  '<S36>'  : 'ok_wrist_simple_motors_3/Position_Controller/PID Controller/Filter ICs/Internal IC - Filter'
//  '<S37>'  : 'ok_wrist_simple_motors_3/Position_Controller/PID Controller/I Gain/Internal Parameters'
//  '<S38>'  : 'ok_wrist_simple_motors_3/Position_Controller/PID Controller/Ideal P Gain/Internal Parameters'
//  '<S39>'  : 'ok_wrist_simple_motors_3/Position_Controller/PID Controller/Ideal P Gain Fdbk/Disabled'
//  '<S40>'  : 'ok_wrist_simple_motors_3/Position_Controller/PID Controller/Integrator/Discrete'
//  '<S41>'  : 'ok_wrist_simple_motors_3/Position_Controller/PID Controller/Integrator ICs/Internal IC'
//  '<S42>'  : 'ok_wrist_simple_motors_3/Position_Controller/PID Controller/N Copy/Disabled'
//  '<S43>'  : 'ok_wrist_simple_motors_3/Position_Controller/PID Controller/N Gain/Internal Parameters'
//  '<S44>'  : 'ok_wrist_simple_motors_3/Position_Controller/PID Controller/P Copy/Internal Parameters Ideal'
//  '<S45>'  : 'ok_wrist_simple_motors_3/Position_Controller/PID Controller/Parallel P Gain/Passthrough'
//  '<S46>'  : 'ok_wrist_simple_motors_3/Position_Controller/PID Controller/Reset Signal/Disabled'
//  '<S47>'  : 'ok_wrist_simple_motors_3/Position_Controller/PID Controller/Saturation/Enabled'
//  '<S48>'  : 'ok_wrist_simple_motors_3/Position_Controller/PID Controller/Saturation Fdbk/Disabled'
//  '<S49>'  : 'ok_wrist_simple_motors_3/Position_Controller/PID Controller/Sum/Sum_PID'
//  '<S50>'  : 'ok_wrist_simple_motors_3/Position_Controller/PID Controller/Sum Fdbk/Disabled'
//  '<S51>'  : 'ok_wrist_simple_motors_3/Position_Controller/PID Controller/Tracking Mode/Disabled'
//  '<S52>'  : 'ok_wrist_simple_motors_3/Position_Controller/PID Controller/Tracking Mode Sum/Passthrough'
//  '<S53>'  : 'ok_wrist_simple_motors_3/Position_Controller/PID Controller/Tsamp - Integral/Passthrough'
//  '<S54>'  : 'ok_wrist_simple_motors_3/Position_Controller/PID Controller/Tsamp - Ngain/Passthrough'
//  '<S55>'  : 'ok_wrist_simple_motors_3/Position_Controller/PID Controller/postSat Signal/Forward_Path'
//  '<S56>'  : 'ok_wrist_simple_motors_3/Position_Controller/PID Controller/preSat Signal/Forward_Path'
//  '<S57>'  : 'ok_wrist_simple_motors_3/Position_Controller/Quaternions to Rotation Angles1/Angle Calculation'
//  '<S58>'  : 'ok_wrist_simple_motors_3/Position_Controller/Quaternions to Rotation Angles1/Quaternion Normalize'
//  '<S59>'  : 'ok_wrist_simple_motors_3/Position_Controller/Quaternions to Rotation Angles1/Angle Calculation/Protect asincos input'
//  '<S60>'  : 'ok_wrist_simple_motors_3/Position_Controller/Quaternions to Rotation Angles1/Angle Calculation/Protect asincos input/If Action Subsystem'
//  '<S61>'  : 'ok_wrist_simple_motors_3/Position_Controller/Quaternions to Rotation Angles1/Angle Calculation/Protect asincos input/If Action Subsystem1'
//  '<S62>'  : 'ok_wrist_simple_motors_3/Position_Controller/Quaternions to Rotation Angles1/Angle Calculation/Protect asincos input/If Action Subsystem2'
//  '<S63>'  : 'ok_wrist_simple_motors_3/Position_Controller/Quaternions to Rotation Angles1/Quaternion Normalize/Quaternion Modulus'
//  '<S64>'  : 'ok_wrist_simple_motors_3/Position_Controller/Quaternions to Rotation Angles1/Quaternion Normalize/Quaternion Modulus/Quaternion Norm'

#endif                                 // RTW_HEADER_Position_Controller_h_

//
// File trailer for generated code.
//
// [EOF]
//
