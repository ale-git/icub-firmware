//
// Non-Degree Granting Education License -- for use at non-degree
// granting, nonprofit, education, and research organizations only. Not
// for commercial or industrial use.
//
// File: codegen_Jacobian.cpp
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
#include "codegen_Jacobian.h"
#include <cmath>
#include "rtwtypes.h"

// Model step function
void codegen_Jacobian::step()
{
  real32_T J01_tmp;
  real32_T J01_tmp_0;
  real32_T J01_tmp_1;
  real32_T J01_tmp_2;
  real32_T J01_tmp_3;
  real32_T J01_tmp_4;
  real32_T J01_tmp_5;
  real32_T J01_tmp_tmp;
  real32_T a;
  real32_T a_tmp;
  real32_T a_tmp_0;
  real32_T a_tmp_1;
  real32_T a_tmp_2;
  real32_T b_a;
  real32_T b_a_tmp;
  real32_T b_a_tmp_0;
  real32_T b_a_tmp_1;
  real32_T b_a_tmp_2;
  real32_T b_a_tmp_tmp;
  real32_T c_a;
  real32_T c_a_tmp;
  real32_T c_a_tmp_0;
  real32_T c_a_tmp_1;

  // MATLAB Function: '<Root>/Jacobian (end-effector to prismatic joints)' incorporates:
  //   Inport: '<Root>/Pitch'
  //   Inport: '<Root>/Roll'

  a_tmp = std::cos(rtU.Roll.angularPosition);
  a_tmp_0 = std::sin(rtU.Roll.angularPosition);
  a_tmp_1 = 50.0F * a_tmp;
  a_tmp_2 = 10.0F * a_tmp_0;
  a = (a_tmp_2 - a_tmp_1) + 43.0F;
  b_a_tmp = std::cos(rtU.Pitch.angularPosition);
  b_a_tmp_0 = std::sin(rtU.Pitch.angularPosition);
  b_a_tmp_tmp = 99.0F * b_a_tmp_0;
  b_a_tmp_1 = 10.0F * b_a_tmp * a_tmp + b_a_tmp_tmp;
  b_a_tmp_2 = 50.0F * b_a_tmp * a_tmp_0;
  b_a = (b_a_tmp_1 + b_a_tmp_2) - 443.0F;
  c_a_tmp = 50.0F * b_a_tmp_0 * a_tmp_0;
  c_a_tmp_0 = 99.0F * b_a_tmp;
  c_a_tmp_1 = 10.0F * a_tmp * b_a_tmp_0;
  c_a = ((c_a_tmp_0 - c_a_tmp) - c_a_tmp_1) + 68.0F;
  a_tmp_1 = (a_tmp_1 + a_tmp_2) - 43.0F;
  b_a_tmp_1 = (b_a_tmp_1 - b_a_tmp_2) - 443.0F;
  c_a_tmp = ((c_a_tmp + c_a_tmp_0) - c_a_tmp_1) + 68.0F;
  a = std::sqrt((a * a + b_a * b_a) + c_a * c_a);
  b_a = 17.0F * b_a_tmp;
  c_a = 43857.0F * b_a_tmp / 500000.0F + 1683.0F * b_a_tmp_0 / 125000.0F;
  c_a_tmp_1 = 443.0F * b_a_tmp_0 * a_tmp_0 / 10000.0F;
  b_a_tmp_2 = b_a * a_tmp / 12500.0F;
  b_a = b_a * a_tmp_0 / 2500.0F;
  a_tmp_2 = 443.0F * a_tmp * b_a_tmp_0 / 50000.0F;

  // Outport: '<Root>/J00' incorporates:
  //   MATLAB Function: '<Root>/Jacobian (end-effector to prismatic joints)'

  rtY.J00 = -(((((c_a - c_a_tmp_1) + b_a_tmp_2) + b_a) - a_tmp_2) * 500.0F) / a;

  // MATLAB Function: '<Root>/Jacobian (end-effector to prismatic joints)'
  J01_tmp_tmp = 5.0F * a_tmp;
  J01_tmp = J01_tmp_tmp - a_tmp_0;
  c_a_tmp_0 /= 1000.0F;
  J01_tmp_0 = b_a_tmp_0 * a_tmp_0 / 20.0F;
  J01_tmp_1 = a_tmp * b_a_tmp_0 / 100.0F;
  J01_tmp_2 = a_tmp / 100.0F;
  J01_tmp_3 = a_tmp_0 / 20.0F;
  J01_tmp_4 = a_tmp / 20.0F;
  J01_tmp_5 = a_tmp_0 / 100.0F;
  a_tmp = b_a_tmp * a_tmp / 100.0F + b_a_tmp_tmp / 1000.0F;
  b_a_tmp_tmp = b_a_tmp * a_tmp_0 / 20.0F;

  // Outport: '<Root>/J01' incorporates:
  //   MATLAB Function: '<Root>/Jacobian (end-effector to prismatic joints)'

  rtY.J01 = ((((a_tmp + b_a_tmp_tmp) - 0.443F) * (J01_tmp * b_a_tmp) / 50.0F +
              (J01_tmp_2 + J01_tmp_3) * 2.0F * ((J01_tmp_5 - J01_tmp_4) + 0.043F))
             - (((c_a_tmp_0 - J01_tmp_0) - J01_tmp_1) + 0.068F) * (J01_tmp *
              b_a_tmp_0) / 50.0F) * 500.0F / a;

  // MATLAB Function: '<Root>/Jacobian (end-effector to prismatic joints)'
  a_tmp_1 = std::sqrt((a_tmp_1 * a_tmp_1 + b_a_tmp_1 * b_a_tmp_1) + c_a_tmp *
                      c_a_tmp);

  // Outport: '<Root>/J10' incorporates:
  //   MATLAB Function: '<Root>/Jacobian (end-effector to prismatic joints)'

  rtY.J10 = -(((((c_a + c_a_tmp_1) + b_a_tmp_2) - b_a) - a_tmp_2) * 500.0F) /
    a_tmp_1;

  // MATLAB Function: '<Root>/Jacobian (end-effector to prismatic joints)'
  a_tmp_0 += J01_tmp_tmp;

  // Outport: '<Root>/J11' incorporates:
  //   MATLAB Function: '<Root>/Jacobian (end-effector to prismatic joints)'

  rtY.J11 = (((((c_a_tmp_0 + J01_tmp_0) - J01_tmp_1) + 0.068F) * (a_tmp_0 *
    b_a_tmp_0) / 50.0F + (J01_tmp_2 - J01_tmp_3) * 2.0F * ((J01_tmp_4 +
    J01_tmp_5) - 0.043F)) - ((a_tmp - b_a_tmp_tmp) - 0.443F) * (a_tmp_0 *
              b_a_tmp) / 50.0F) * 500.0F / a_tmp_1;
}

// Model initialize function
void codegen_Jacobian::initialize()
{
  // (no initialization code required)
}

const char_T* codegen_Jacobian::RT_MODEL::getErrorStatus() const
{
  return (errorStatus);
}

void codegen_Jacobian::RT_MODEL::setErrorStatus(const char_T* const volatile
  aErrorStatus)
{
  (errorStatus = aErrorStatus);
}

// Constructor
codegen_Jacobian::codegen_Jacobian() :
  rtU(),
  rtY(),
  rtM()
{
  // Currently there is no constructor body generated.
}

// Destructor
// Currently there is no destructor body generated.
codegen_Jacobian::~codegen_Jacobian() = default;

// Real-Time Model get method
codegen_Jacobian::RT_MODEL * codegen_Jacobian::getRTM()
{
  return (&rtM);
}

//
// File trailer for generated code.
//
// [EOF]
//
