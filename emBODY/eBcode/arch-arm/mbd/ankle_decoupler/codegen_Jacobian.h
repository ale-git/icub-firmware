//
// Non-Degree Granting Education License -- for use at non-degree
// granting, nonprofit, education, and research organizations only. Not
// for commercial or industrial use.
//
// File: codegen_Jacobian.h
//
// Code generated for Simulink model 'codegen_Jacobian'.
//
// Model version                  : 1.10
// Simulink Coder version         : 25.1 (R2025a) 21-Nov-2024
// C/C++ source code generated on : Mon Jun 30 15:45:57 2025
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
#ifndef DEFINED_TYPEDEF_FOR_Data_linearVelocity_
#define DEFINED_TYPEDEF_FOR_Data_linearVelocity_

struct Data_linearVelocity
{
  real32_T velocity;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_Data_linearPosition_
#define DEFINED_TYPEDEF_FOR_Data_linearPosition_

struct Data_linearPosition
{
  real32_T position;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_Data_linearAcceleration_
#define DEFINED_TYPEDEF_FOR_Data_linearAcceleration_

struct Data_linearAcceleration
{
  real_T acceleration;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_Data_force_
#define DEFINED_TYPEDEF_FOR_Data_force_

struct Data_force
{
  real_T force;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_Data_dutyCycle_
#define DEFINED_TYPEDEF_FOR_Data_dutyCycle_

struct Data_dutyCycle
{
  real_T dutyCycle;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_Data_current_
#define DEFINED_TYPEDEF_FOR_Data_current_

struct Data_current
{
  real_T current;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_Data_linearReferences_
#define DEFINED_TYPEDEF_FOR_Data_linearReferences_

struct Data_linearReferences
{
  Data_linearVelocity velocity;
  Data_linearPosition position;
  Data_linearAcceleration acceleration;
  Data_force force;
  Data_dutyCycle dutyCycle;
  Data_current current;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_Data_angularPosition_
#define DEFINED_TYPEDEF_FOR_Data_angularPosition_

struct Data_angularPosition
{
  real32_T angularPosition;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_Data_angularVelocity_
#define DEFINED_TYPEDEF_FOR_Data_angularVelocity_

struct Data_angularVelocity
{
  real32_T angularVelocity;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_Data_angularAcceleration_
#define DEFINED_TYPEDEF_FOR_Data_angularAcceleration_

struct Data_angularAcceleration
{
  real_T angularAcceleration;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_Data_torque_
#define DEFINED_TYPEDEF_FOR_Data_torque_

struct Data_torque
{
  real_T torque;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_Data_rotationalReferences_
#define DEFINED_TYPEDEF_FOR_Data_rotationalReferences_

struct Data_rotationalReferences
{
  Data_angularPosition position;
  Data_angularVelocity velocity;
  Data_angularAcceleration acceleration;
  Data_torque torque;
  Data_dutyCycle dutyCycle;
  Data_current current;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_Data_References_
#define DEFINED_TYPEDEF_FOR_Data_References_

struct Data_References
{
  Data_linearReferences Actuator1;
  Data_linearReferences Actuator2;
  Data_rotationalReferences Motor2;
  Data_rotationalReferences Motor1;
  Data_rotationalReferences Roll;
  Data_rotationalReferences Pitch;
};

#endif

// Class declaration for model codegen_Jacobian
class codegen_Jacobian final
{
  // public data and function members
 public:
  // External inputs (root inport signals with default storage)
  struct ExtU {
    Data_References EndEffectorReferencesIn;// '<Root>/End Effector References In' 
  };

  // External outputs (root outports fed by signals with default storage)
  struct ExtY {
    real32_T JacobianMatrix_2x2[4];    // '<Root>/JacobianMatrix_2x2'
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
