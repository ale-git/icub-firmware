//
// Non-Degree Granting Education License -- for use at non-degree
// granting, nonprofit, education, and research organizations only. Not
// for commercial or industrial use.
//
// File: codegen_Jacobian.cpp
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
#include "codegen_Jacobian.h"
#include <cmath>
#include "rtwtypes.h"

// Model step function
void codegen_Jacobian::step()
{
  real32_T JacobianMatrix_2x2_tmp;
  real32_T JacobianMatrix_2x2_tmp_0;
  real32_T JacobianMatrix_2x2_tmp_1;
  real32_T JacobianMatrix_2x2_tmp_2;
  real32_T a;
  real32_T a_tmp;
  real32_T a_tmp_0;
  real32_T a_tmp_tmp;
  real32_T b_a;
  real32_T b_a_tmp;
  real32_T b_a_tmp_0;
  real32_T c_a;
  real32_T c_a_tmp;
  real32_T c_a_tmp_0;
  real32_T c_pitch;
  real32_T c_roll;
  real32_T s_pitch;
  real32_T s_roll;

  // MATLAB Function: '<Root>/Jacobian (end-effector to prismatic joints)' incorporates:
  //   Inport: '<Root>/End Effector References In'

  c_roll = std::cos(rtU.EndEffectorReferencesIn.Roll.position.angularPosition);
  s_roll = std::sin(rtU.EndEffectorReferencesIn.Roll.position.angularPosition);
  c_pitch = std::cos(rtU.EndEffectorReferencesIn.Pitch.position.angularPosition);
  s_pitch = std::sin(rtU.EndEffectorReferencesIn.Pitch.position.angularPosition);
  a_tmp_tmp = 99.0F * s_pitch;
  a_tmp = 10.0F * c_pitch * c_roll + a_tmp_tmp;
  a_tmp_0 = 50.0F * c_pitch * s_roll;
  a = (a_tmp + a_tmp_0) - 443.0F;
  b_a_tmp = 198.0F * c_pitch - 20.0F * c_roll * s_pitch;
  b_a_tmp_0 = 100.0F * s_pitch * s_roll;
  b_a = (b_a_tmp - b_a_tmp_0) + 141.0F;
  c_a_tmp = 50.0F * c_roll;
  c_a_tmp_0 = 10.0F * s_roll;
  c_a = (c_a_tmp_0 - c_a_tmp) + 43.0F;
  a_tmp = (a_tmp - a_tmp_0) - 443.0F;
  b_a_tmp = (b_a_tmp + b_a_tmp_0) + 141.0F;
  c_a_tmp = (c_a_tmp + c_a_tmp_0) - 43.0F;
  a = std::sqrt((a * a * 4.0F + b_a * b_a) + c_a * c_a * 4.0F);
  a_tmp = std::sqrt((a_tmp * a_tmp * 4.0F + b_a_tmp * b_a_tmp) + c_a_tmp *
                    c_a_tmp * 4.0F);
  b_a_tmp_0 = 5.0F * c_roll;
  b_a = b_a_tmp_0 - s_roll;
  c_a = c_roll / 100.0F;
  c_a_tmp = s_roll / 20.0F;
  c_a_tmp_0 = c_roll / 20.0F;
  b_a_tmp = s_roll / 100.0F;
  a_tmp_tmp = c_pitch * c_roll / 100.0F + a_tmp_tmp / 1000.0F;
  a_tmp_0 = c_pitch * s_roll / 20.0F;
  JacobianMatrix_2x2_tmp = 99.0F * c_pitch / 1000.0F - c_roll * s_pitch / 100.0F;
  JacobianMatrix_2x2_tmp_0 = s_pitch * s_roll / 20.0F;

  // Outport generated from: '<Root>/JacobianMatrix_2x2' incorporates:
  //   MATLAB Function: '<Root>/Jacobian (end-effector to prismatic joints)'

  rtY.JacobianMatrix_2x2[0] = ((((a_tmp_tmp + a_tmp_0) - 0.443F) * (b_a *
    c_pitch) / 50.0F + (c_a + c_a_tmp) * 2.0F * ((b_a_tmp - c_a_tmp_0) + 0.043F))
    - ((JacobianMatrix_2x2_tmp - JacobianMatrix_2x2_tmp_0) + 0.0705F) * (b_a *
    s_pitch) / 50.0F) * 1000.0F / a;

  // MATLAB Function: '<Root>/Jacobian (end-effector to prismatic joints)'
  b_a = 141.0F * c_pitch;
  JacobianMatrix_2x2_tmp_1 = (43857.0F * c_pitch / 500000.0F + 13959.0F *
    s_pitch / 1.0E+6F) + b_a * c_roll / 100000.0F;
  b_a = b_a * s_roll / 20000.0F;
  c_roll = 443.0F * c_roll * s_pitch / 50000.0F;
  JacobianMatrix_2x2_tmp_2 = 443.0F * s_pitch * s_roll / 10000.0F;

  // Outport generated from: '<Root>/JacobianMatrix_2x2' incorporates:
  //   MATLAB Function: '<Root>/Jacobian (end-effector to prismatic joints)'

  rtY.JacobianMatrix_2x2[2] = -((((JacobianMatrix_2x2_tmp_1 + b_a) - c_roll) -
    JacobianMatrix_2x2_tmp_2) * 1000.0F) / a;

  // MATLAB Function: '<Root>/Jacobian (end-effector to prismatic joints)'
  s_roll += b_a_tmp_0;

  // Outport generated from: '<Root>/JacobianMatrix_2x2' incorporates:
  //   MATLAB Function: '<Root>/Jacobian (end-effector to prismatic joints)'

  rtY.JacobianMatrix_2x2[1] = (((c_a - c_a_tmp) * 2.0F * ((c_a_tmp_0 + b_a_tmp)
    - 0.043F) - ((a_tmp_tmp - a_tmp_0) - 0.443F) * (s_roll * c_pitch) / 50.0F) +
    ((JacobianMatrix_2x2_tmp + JacobianMatrix_2x2_tmp_0) + 0.0705F) * (s_roll *
    s_pitch) / 50.0F) * 1000.0F / a_tmp;
  rtY.JacobianMatrix_2x2[3] = -((((JacobianMatrix_2x2_tmp_1 - b_a) - c_roll) +
    JacobianMatrix_2x2_tmp_2) * 1000.0F) / a_tmp;
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
