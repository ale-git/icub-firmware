//
// Non-Degree Granting Education License -- for use at non-degree
// granting, nonprofit, education, and research organizations only. Not
// for commercial or industrial use.
//
// File: TorqueModel.cpp
//
// Code generated for Simulink model 'TorqueModel'.
//
// Model version                  : 3.5
// Simulink Coder version         : 9.8 (R2022b) 13-May-2022
// C/C++ source code generated on : Thu Oct  6 12:32:42 2022
//
// Target selection: ert.tlc
// Embedded hardware selection: ARM Compatible->ARM Cortex-M
// Code generation objectives:
//    1. Execution efficiency
//    2. RAM efficiency
// Validation result: Not run
//
#include "TorqueModel.h"
#include <cmath>
#include "rtwtypes.h"
#include "TorqueModel_capi.h"

// Model step function
void TorqueModel::step()
{
  real_T rtb_Abs1;
  real_T rtb_Subtract;

  // Outputs for Atomic SubSystem: '<Root>/TorqueModel'
  // Sum: '<S1>/Subtract' incorporates:
  //   Gain: '<S1>/Gain'
  //   Inport: '<Root>/JointPos'
  //   Inport: '<Root>/MotorPos'

  rtb_Subtract = 0.00625 * rtU.MotorPos + rtU.JointPos;

  // Backlash: '<S1>/Backlash'
  if (rtb_Subtract < rtDW.PrevY - 5.9921124526782858E-6) {
    // Backlash: '<S1>/Backlash'
    rtb_Subtract += 5.9921124526782858E-6;
  } else if (rtb_Subtract <= rtDW.PrevY + 5.9921124526782858E-6) {
    // Backlash: '<S1>/Backlash'
    rtb_Subtract = rtDW.PrevY;
  } else {
    // Backlash: '<S1>/Backlash'
    rtb_Subtract -= 5.9921124526782858E-6;
  }

  // End of Backlash: '<S1>/Backlash'

  // Abs: '<S1>/Abs1'
  rtb_Abs1 = std::abs(rtb_Subtract);

  // Switch: '<S1>/Switch' incorporates:
  //   Bias: '<S1>/Add Constant'
  //   Bias: '<S1>/Add Constant1'
  //   Bias: '<S1>/Add Constant2'
  //   Gain: '<S1>/Gain1'
  //   Switch: '<S1>/Switch1'

  if (rtb_Abs1 - 0.0011575000000000001 > 0.0) {
    rtb_Abs1 = (rtb_Abs1 - 0.0011575000000000001) * 29000.0 + 25.0;
  } else if (rtb_Abs1 - 0.0004375 > 0.0) {
    // Switch: '<S1>/Switch1' incorporates:
    //   Bias: '<S1>/Add Constant2'
    //   Bias: '<S1>/Add Constant3'
    //   Gain: '<S1>/Gain2'

    rtb_Abs1 = (rtb_Abs1 - 0.0004375) * 25000.0 + 7.0;
  } else {
    // Switch: '<S1>/Switch1' incorporates:
    //   Gain: '<S1>/Gain3'

    rtb_Abs1 *= 16000.0;
  }

  // End of Switch: '<S1>/Switch'

  // Update for Backlash: '<S1>/Backlash'
  rtDW.PrevY = rtb_Subtract;

  // Signum: '<S1>/Sign'
  if (rtb_Subtract < 0.0) {
    rtb_Subtract = -1.0;
  } else {
    rtb_Subtract = (rtb_Subtract > 0.0);
  }

  // Outport: '<Root>/Torque meas' incorporates:
  //   Product: '<S1>/Product'
  //   Signum: '<S1>/Sign'

  rtY.Torquemeas = rtb_Subtract * rtb_Abs1;

  // End of Outputs for SubSystem: '<Root>/TorqueModel'
}

// Model initialize function
void TorqueModel::initialize()
{
  // Registration code

  // Initialize DataMapInfo substructure containing ModelMap for C API
  TorqueModel_InitializeDataMapInfo((&rtM));
}

// Constructor
TorqueModel::TorqueModel() :
  rtU(),
  rtY(),
  rtDW(),
  rtM()
{
  // Currently there is no constructor body generated.
}

// Destructor
TorqueModel::~TorqueModel()
{
  // Currently there is no destructor body generated.
}

// Real-Time Model get method
TorqueModel::RT_MODEL * TorqueModel::getRTM()
{
  return (&rtM);
}

//
// File trailer for generated code.
//
// [EOF]
//
