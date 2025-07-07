//
// Non-Degree Granting Education License -- for use at non-degree
// granting, nonprofit, education, and research organizations only. Not
// for commercial or industrial use.
//
// File: codegen_Jacobian.h
//
// Code generated for Simulink model 'codegen_Jacobian'.
//
// Model version                  : 1.37
// Simulink Coder version         : 25.1 (R2025a) 21-Nov-2024
// C/C++ source code generated on : Mon Jul  7 16:46:56 2025
//
// Target selection: ert.tlc
// Embedded hardware selection: ARM Compatible->ARM Cortex-M
// Code generation objectives:
//    1. Execution efficiency
//    2. RAM efficiency
// Validation result: Not run
//
#ifndef codegen_Jacobian_h_
#define codegen_Jacobian_h_
#include <cmath>
#include "rtwtypes.h"
#ifndef DEFINED_TYPEDEF_FOR_Data_angularPosition_
#define DEFINED_TYPEDEF_FOR_Data_angularPosition_

struct Data_angularPosition
{
  real32_T angularPosition;
};

#endif

// Class declaration for model codegen_Jacobian
class codegen_Jacobian final
{
  // public data and function members
 public:
  // External inputs (root inport signals with default storage)
  struct ExtU {
    Data_angularPosition Pitch;        // '<Root>/Pitch'
    Data_angularPosition Roll;         // '<Root>/Roll'
  };

  // External outputs (root outports fed by signals with default storage)
  struct ExtY {
    real32_T J00;                      // '<Root>/J00'
    real32_T J01;                      // '<Root>/J01'
    real32_T J10;                      // '<Root>/J10'
    real32_T J11;                      // '<Root>/J11'
  };

  // Real-time Model Data Structure
  struct RT_MODEL {
    const char_T * volatile errorStatus;
    const char_T* getErrorStatus() const;
    void setErrorStatus(const char_T* const volatile aErrorStatus);
  };

  // Copy Constructor
  codegen_Jacobian(codegen_Jacobian const&) = delete;

  // Assignment Operator
  codegen_Jacobian& operator= (codegen_Jacobian const&) & = delete;

  // Move Constructor
  codegen_Jacobian(codegen_Jacobian &&) = delete;

  // Move Assignment Operator
  codegen_Jacobian& operator= (codegen_Jacobian &&) = delete;

  // Real-Time Model get method
  codegen_Jacobian::RT_MODEL * getRTM();

  // External inputs
  ExtU rtU;

  // External outputs
  ExtY rtY;

  // model initialize function
  static void initialize();

  // model step function
  void step();

  // Constructor
  codegen_Jacobian();

  // Destructor
  ~codegen_Jacobian();

  // private data and function members
 private:
  // Real-Time Model
  RT_MODEL rtM;
};

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
//  '<Root>' : 'codegen_Jacobian'
//  '<S1>'   : 'codegen_Jacobian/Jacobian (end-effector to prismatic joints)'

#endif                                 // codegen_Jacobian_h_

//
// File trailer for generated code.
//
// [EOF]
//
