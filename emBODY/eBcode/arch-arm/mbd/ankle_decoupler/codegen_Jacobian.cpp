//
// Non-Degree Granting Education License -- for use at non-degree
// granting, nonprofit, education, and research organizations only. Not
// for commercial or industrial use.
//
// File: codegen_Jacobian.cpp
//
// Code generated for Simulink model 'codegen_Jacobian'.
//
// Model version                  : 1.21
// Simulink Coder version         : 25.1 (R2025a) 21-Nov-2024
// C/C++ source code generated on : Thu Jul  3 17:01:58 2025
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
  real32_T J_tmp;
  real32_T J_tmp_0;
  real32_T J_tmp_1;
  real32_T J_tmp_2;
  real32_T a_tmp;
  real32_T a_tmp_tmp;
  real32_T b_a;
  real32_T b_a_tmp;
  real32_T b_a_tmp_0;
  real32_T b_a_tmp_1;
  real32_T b_a_tmp_2;
  real32_T c_a_tmp;
  real32_T c_a_tmp_0;
  real32_T c_a_tmp_1;
  real32_T c_a_tmp_tmp;
  real32_T c_pitch;
  real32_T c_roll;
  real32_T s_pitch;
  real32_T s_roll;

  // MATLAB Function: '<Root>/Jacobian (end-effector to prismatic joints)' incorporates:
  //   Inport: '<Root>/Pitch'
  //   Inport: '<Root>/Roll'

  c_roll = std::cos(rtU.Roll.angularPosition);
  s_roll = std::sin(rtU.Roll.angularPosition);
  c_pitch = std::cos(rtU.Pitch.angularPosition);
  s_pitch = std::sin(rtU.Pitch.angularPosition);
  a_tmp_tmp = 99.0F * c_pitch;
  a_tmp = a_tmp_tmp - 10.0F * s_pitch;
  b_a_tmp = 10.0F * c_pitch;
  b_a_tmp_0 = 50.0F * s_roll;
  b_a_tmp_1 = b_a_tmp * c_roll;
  b_a_tmp_2 = 99.0F * c_roll * s_pitch;
  b_a = ((b_a_tmp_1 + b_a_tmp_0) + b_a_tmp_2) - 443.0F;
  c_a_tmp_tmp = 99.0F * s_pitch;
  c_a_tmp = c_a_tmp_tmp * s_roll;
  c_a_tmp_0 = 50.0F * c_roll;
  c_a_tmp_1 = b_a_tmp * s_roll;
  b_a_tmp = ((c_a_tmp - c_a_tmp_0) + c_a_tmp_1) + 43.0F;
  b_a_tmp_0 = ((b_a_tmp_0 - b_a_tmp_1) - b_a_tmp_2) + 443.0F;
  c_a_tmp_0 = ((c_a_tmp + c_a_tmp_0) + c_a_tmp_1) - 43.0F;
  b_a_tmp_1 = (a_tmp + 68.0F) * (a_tmp + 68.0F);
  b_a = std::sqrt((b_a * b_a + b_a_tmp_1) + b_a_tmp * b_a_tmp);
  b_a_tmp = std::sqrt((b_a_tmp_0 * b_a_tmp_0 + b_a_tmp_1) + c_a_tmp_0 *
                      c_a_tmp_0);
  c_a_tmp_0 = s_roll / 20.0F;
  b_a_tmp_0 = c_pitch * c_roll / 100.0F;
  b_a_tmp_2 /= 1000.0F;
  b_a_tmp_1 = a_tmp * c_roll;
  a_tmp_tmp = (c_a_tmp_tmp / 1000.0F + c_pitch / 100.0F) * 2.0F * ((a_tmp_tmp /
    1000.0F - s_pitch / 100.0F) + 0.068F);
  c_a_tmp /= 1000.0F;
  c_a_tmp_tmp = c_roll / 20.0F;
  c_a_tmp_1 = c_pitch * s_roll / 100.0F;
  a_tmp *= s_roll;

  // Outport: '<Root>/J' incorporates:
  //   MATLAB Function: '<Root>/Jacobian (end-effector to prismatic joints)'

  rtY.J[0] = (((((b_a_tmp_0 + c_a_tmp_0) + b_a_tmp_2) - 0.443F) * b_a_tmp_1 /
               500.0F - a_tmp_tmp) + (((c_a_tmp - c_a_tmp_tmp) + c_a_tmp_1) +
    0.043F) * a_tmp / 500.0F) * 500.0F / b_a;

  // MATLAB Function: '<Root>/Jacobian (end-effector to prismatic joints)'
  J_tmp = 443.0F * c_roll / 10000.0F;
  J_tmp_0 = 43.0F * s_roll / 10000.0F;
  J_tmp_1 = 43857.0F * s_pitch * s_roll / 500000.0F;
  J_tmp_2 = 43.0F * c_pitch * c_roll / 50000.0F;
  s_roll = 443.0F * c_pitch * s_roll / 50000.0F;
  c_roll = 4257.0F * c_roll * s_pitch / 500000.0F;

  // Outport: '<Root>/J' incorporates:
  //   MATLAB Function: '<Root>/Jacobian (end-effector to prismatic joints)'

  rtY.J[2] = (((((J_tmp_0 - J_tmp) + J_tmp_1) + J_tmp_2) + s_roll) + c_roll) *
    500.0F / b_a;
  rtY.J[1] = -((((((c_a_tmp_0 - b_a_tmp_0) - b_a_tmp_2) + 0.443F) * b_a_tmp_1 /
                 500.0F + a_tmp_tmp) - (((c_a_tmp + c_a_tmp_tmp) + c_a_tmp_1) -
    0.043F) * a_tmp / 500.0F) * 500.0F) / b_a_tmp;
  rtY.J[3] = (((((J_tmp + J_tmp_0) + J_tmp_1) - J_tmp_2) + s_roll) - c_roll) *
    500.0F / b_a_tmp;
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
