//
// Non-Degree Granting Education License -- for use at non-degree
// granting, nonprofit, educational organizations only. Not for
// government, commercial, or other organizational use.
//
// File: Position_Controller.cpp
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
#include "Position_Controller.h"
#define NumBitsPerChar                 8U

extern real_T rt_atan2d_snf(real_T u0, real_T u1);
extern real_T rt_remd_snf(real_T u0, real_T u1);

//===========*
//  Constants *
// ===========
#define RT_PI                          3.14159265358979323846
#define RT_PIF                         3.1415927F
#define RT_LN_10                       2.30258509299404568402
#define RT_LN_10F                      2.3025851F
#define RT_LOG10E                      0.43429448190325182765
#define RT_LOG10EF                     0.43429449F
#define RT_E                           2.7182818284590452354
#define RT_EF                          2.7182817F

//
//  UNUSED_PARAMETER(x)
//    Used to specify that a function parameter (argument) is required but not
//    accessed by the function body.

#ifndef UNUSED_PARAMETER
#if defined(__LCC__)
#define UNUSED_PARAMETER(x)                                      // do nothing
#else

//
//  This is the semi-ANSI standard way of indicating that an
//  unused function parameter is required.

#define UNUSED_PARAMETER(x)            (void) (x)
#endif
#endif

extern "C" {
  real_T rtInf;
  real_T rtMinusInf;
  real_T rtNaN;
  real32_T rtInfF;
  real32_T rtMinusInfF;
  real32_T rtNaNF;
}
  extern "C"
{
  //
  // Initialize rtNaN needed by the generated code.
  // NaN is initialized as non-signaling. Assumes IEEE.
  //
  static real_T rtGetNaN(void)
  {
    size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
    real_T nan = 0.0;
    if (bitsPerReal == 32U) {
      nan = rtGetNaNF();
    } else {
      union {
        LittleEndianIEEEDouble bitVal;
        real_T fltVal;
      } tmpVal;

      tmpVal.bitVal.words.wordH = 0xFFF80000U;
      tmpVal.bitVal.words.wordL = 0x00000000U;
      nan = tmpVal.fltVal;
    }

    return nan;
  }

  //
  // Initialize rtNaNF needed by the generated code.
  // NaN is initialized as non-signaling. Assumes IEEE.
  //
  static real32_T rtGetNaNF(void)
  {
    IEEESingle nanF = { { 0 } };

    nanF.wordL.wordLuint = 0xFFC00000U;
    return nanF.wordL.wordLreal;
  }
}

extern "C" {
  //
  // Initialize the rtInf, rtMinusInf, and rtNaN needed by the
  // generated code. NaN is initialized as non-signaling. Assumes IEEE.
  //
  static void rt_InitInfAndNaN(size_t realSize)
  {
    (void) (realSize);
    rtNaN = rtGetNaN();
    rtNaNF = rtGetNaNF();
    rtInf = rtGetInf();
    rtInfF = rtGetInfF();
    rtMinusInf = rtGetMinusInf();
    rtMinusInfF = rtGetMinusInfF();
  }

  // Test if value is infinite
  static boolean_T rtIsInf(real_T value)
  {
    return (boolean_T)((value==rtInf || value==rtMinusInf) ? 1U : 0U);
  }

  // Test if single-precision value is infinite
  static boolean_T rtIsInfF(real32_T value)
  {
    return (boolean_T)(((value)==rtInfF || (value)==rtMinusInfF) ? 1U : 0U);
  }

  // Test if value is not a number
  static boolean_T rtIsNaN(real_T value)
  {
    boolean_T result = (boolean_T) 0;
    size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
    if (bitsPerReal == 32U) {
      result = rtIsNaNF((real32_T)value);
    } else {
      union {
        LittleEndianIEEEDouble bitVal;
        real_T fltVal;
      } tmpVal;

      tmpVal.fltVal = value;
      result = (boolean_T)((tmpVal.bitVal.words.wordH & 0x7FF00000) ==
                           0x7FF00000 &&
                           ( (tmpVal.bitVal.words.wordH & 0x000FFFFF) != 0 ||
                            (tmpVal.bitVal.words.wordL != 0) ));
    }

    return result;
  }

  // Test if single-precision value is not a number
  static boolean_T rtIsNaNF(real32_T value)
  {
    IEEESingle tmp;
    tmp.wordL.wordLreal = value;
    return (boolean_T)( (tmp.wordL.wordLuint & 0x7F800000) == 0x7F800000 &&
                       (tmp.wordL.wordLuint & 0x007FFFFF) != 0 );
  }
}
  extern "C"
{
  //
  // Initialize rtInf needed by the generated code.
  // Inf is initialized as non-signaling. Assumes IEEE.
  //
  static real_T rtGetInf(void)
  {
    size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
    real_T inf = 0.0;
    if (bitsPerReal == 32U) {
      inf = rtGetInfF();
    } else {
      union {
        LittleEndianIEEEDouble bitVal;
        real_T fltVal;
      } tmpVal;

      tmpVal.bitVal.words.wordH = 0x7FF00000U;
      tmpVal.bitVal.words.wordL = 0x00000000U;
      inf = tmpVal.fltVal;
    }

    return inf;
  }

  //
  // Initialize rtInfF needed by the generated code.
  // Inf is initialized as non-signaling. Assumes IEEE.
  //
  static real32_T rtGetInfF(void)
  {
    IEEESingle infF;
    infF.wordL.wordLuint = 0x7F800000U;
    return infF.wordL.wordLreal;
  }

  //
  // Initialize rtMinusInf needed by the generated code.
  // Inf is initialized as non-signaling. Assumes IEEE.
  //
  static real_T rtGetMinusInf(void)
  {
    size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
    real_T minf = 0.0;
    if (bitsPerReal == 32U) {
      minf = rtGetMinusInfF();
    } else {
      union {
        LittleEndianIEEEDouble bitVal;
        real_T fltVal;
      } tmpVal;

      tmpVal.bitVal.words.wordH = 0xFFF00000U;
      tmpVal.bitVal.words.wordL = 0x00000000U;
      minf = tmpVal.fltVal;
    }

    return minf;
  }

  //
  // Initialize rtMinusInfF needed by the generated code.
  // Inf is initialized as non-signaling. Assumes IEEE.
  //
  static real32_T rtGetMinusInfF(void)
  {
    IEEESingle minfF;
    minfF.wordL.wordLuint = 0xFF800000U;
    return minfF.wordL.wordLreal;
  }
}

// Function for MATLAB Function: '<S1>/motors2quat'
real_T Position_ControllerModelClass::maximum(const real_T x[3])
{
  real_T ex;
  int32_T idx;
  int32_T k;
  boolean_T exitg1;
  if (!rtIsNaN(x[0])) {
    idx = 1;
  } else {
    idx = 0;
    k = 2;
    exitg1 = false;
    while ((!exitg1) && (k < 4)) {
      if (!rtIsNaN(x[k - 1])) {
        idx = k;
        exitg1 = true;
      } else {
        k++;
      }
    }
  }

  if (idx == 0) {
    ex = x[0];
  } else {
    ex = x[idx - 1];
    while (idx + 1 <= 3) {
      if (ex < x[idx]) {
        ex = x[idx];
      }

      idx++;
    }
  }

  return ex;
}

// Function for MATLAB Function: '<S1>/motors2quat'
real_T Position_ControllerModelClass::minimum(const real_T x[3])
{
  real_T ex;
  int32_T idx;
  int32_T k;
  boolean_T exitg1;
  if (!rtIsNaN(x[0])) {
    idx = 1;
  } else {
    idx = 0;
    k = 2;
    exitg1 = false;
    while ((!exitg1) && (k < 4)) {
      if (!rtIsNaN(x[k - 1])) {
        idx = k;
        exitg1 = true;
      } else {
        k++;
      }
    }
  }

  if (idx == 0) {
    ex = x[0];
  } else {
    ex = x[idx - 1];
    while (idx + 1 <= 3) {
      if (ex > x[idx]) {
        ex = x[idx];
      }

      idx++;
    }
  }

  return ex;
}

real_T rt_atan2d_snf(real_T u0, real_T u1)
{
  real_T y;
  int32_T u0_0;
  int32_T u1_0;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = (rtNaN);
  } else if (rtIsInf(u0) && rtIsInf(u1)) {
    if (u0 > 0.0) {
      u0_0 = 1;
    } else {
      u0_0 = -1;
    }

    if (u1 > 0.0) {
      u1_0 = 1;
    } else {
      u1_0 = -1;
    }

    y = std::atan2(static_cast<real_T>(u0_0), static_cast<real_T>(u1_0));
  } else if (u1 == 0.0) {
    if (u0 > 0.0) {
      y = RT_PI / 2.0;
    } else if (u0 < 0.0) {
      y = -(RT_PI / 2.0);
    } else {
      y = 0.0;
    }
  } else {
    y = std::atan2(u0, u1);
  }

  return y;
}

real_T rt_remd_snf(real_T u0, real_T u1)
{
  real_T u1_0;
  real_T y;
  if (rtIsNaN(u0) || rtIsNaN(u1) || rtIsInf(u0)) {
    y = (rtNaN);
  } else if (rtIsInf(u1)) {
    y = u0;
  } else {
    if (u1 < 0.0) {
      u1_0 = std::ceil(u1);
    } else {
      u1_0 = std::floor(u1);
    }

    if ((u1 != 0.0) && (u1 != u1_0)) {
      u1_0 = std::abs(u0 / u1);
      if (!(std::abs(u1_0 - std::floor(u1_0 + 0.5)) > DBL_EPSILON * u1_0)) {
        y = 0.0 * u0;
      } else {
        y = std::fmod(u0, u1);
      }
    } else {
      y = std::fmod(u0, u1);
    }
  }

  return y;
}

// Function for MATLAB Function: '<S1>/motors2quat'
void Position_ControllerModelClass::sind(real_T x[3])
{
  real_T absx;
  real_T c_x;
  int8_T n;
  if (rtIsInf(x[0]) || rtIsNaN(x[0])) {
    c_x = (rtNaN);
  } else {
    c_x = rt_remd_snf(x[0], 360.0);
    absx = std::abs(c_x);
    if (absx > 180.0) {
      if (c_x > 0.0) {
        c_x -= 360.0;
      } else {
        c_x += 360.0;
      }

      absx = std::abs(c_x);
    }

    if (absx <= 45.0) {
      c_x *= 0.017453292519943295;
      n = 0;
    } else if (absx <= 135.0) {
      if (c_x > 0.0) {
        c_x = (c_x - 90.0) * 0.017453292519943295;
        n = 1;
      } else {
        c_x = (c_x + 90.0) * 0.017453292519943295;
        n = -1;
      }
    } else if (c_x > 0.0) {
      c_x = (c_x - 180.0) * 0.017453292519943295;
      n = 2;
    } else {
      c_x = (c_x + 180.0) * 0.017453292519943295;
      n = -2;
    }

    switch (n) {
     case 0:
      c_x = std::sin(c_x);
      break;

     case 1:
      c_x = std::cos(c_x);
      break;

     case -1:
      c_x = -std::cos(c_x);
      break;

     default:
      c_x = -std::sin(c_x);
      break;
    }
  }

  x[0] = c_x;
  if (rtIsInf(x[1]) || rtIsNaN(x[1])) {
    c_x = (rtNaN);
  } else {
    c_x = rt_remd_snf(x[1], 360.0);
    absx = std::abs(c_x);
    if (absx > 180.0) {
      if (c_x > 0.0) {
        c_x -= 360.0;
      } else {
        c_x += 360.0;
      }

      absx = std::abs(c_x);
    }

    if (absx <= 45.0) {
      c_x *= 0.017453292519943295;
      n = 0;
    } else if (absx <= 135.0) {
      if (c_x > 0.0) {
        c_x = (c_x - 90.0) * 0.017453292519943295;
        n = 1;
      } else {
        c_x = (c_x + 90.0) * 0.017453292519943295;
        n = -1;
      }
    } else if (c_x > 0.0) {
      c_x = (c_x - 180.0) * 0.017453292519943295;
      n = 2;
    } else {
      c_x = (c_x + 180.0) * 0.017453292519943295;
      n = -2;
    }

    switch (n) {
     case 0:
      c_x = std::sin(c_x);
      break;

     case 1:
      c_x = std::cos(c_x);
      break;

     case -1:
      c_x = -std::cos(c_x);
      break;

     default:
      c_x = -std::sin(c_x);
      break;
    }
  }

  x[1] = c_x;
  if (rtIsInf(x[2]) || rtIsNaN(x[2])) {
    c_x = (rtNaN);
  } else {
    c_x = rt_remd_snf(x[2], 360.0);
    absx = std::abs(c_x);
    if (absx > 180.0) {
      if (c_x > 0.0) {
        c_x -= 360.0;
      } else {
        c_x += 360.0;
      }

      absx = std::abs(c_x);
    }

    if (absx <= 45.0) {
      c_x *= 0.017453292519943295;
      n = 0;
    } else if (absx <= 135.0) {
      if (c_x > 0.0) {
        c_x = (c_x - 90.0) * 0.017453292519943295;
        n = 1;
      } else {
        c_x = (c_x + 90.0) * 0.017453292519943295;
        n = -1;
      }
    } else if (c_x > 0.0) {
      c_x = (c_x - 180.0) * 0.017453292519943295;
      n = 2;
    } else {
      c_x = (c_x + 180.0) * 0.017453292519943295;
      n = -2;
    }

    switch (n) {
     case 0:
      c_x = std::sin(c_x);
      break;

     case 1:
      c_x = std::cos(c_x);
      break;

     case -1:
      c_x = -std::cos(c_x);
      break;

     default:
      c_x = -std::sin(c_x);
      break;
    }
  }

  x[2] = c_x;
}

// Function for MATLAB Function: '<S1>/motors2quat'
real_T Position_ControllerModelClass::det(const real_T x[9])
{
  real_T A[9];
  real_T b_y;
  real_T smax;
  real_T y;
  int32_T c;
  int32_T c_ix;
  int32_T c_k;
  int32_T d;
  int32_T ijA;
  int32_T ix;
  int32_T iy;
  int32_T j;
  int8_T ipiv[3];
  boolean_T isodd;
  std::memcpy(&A[0], &x[0], 9U * sizeof(real_T));
  ipiv[0] = 1;
  ipiv[1] = 2;
  for (j = 0; j < 2; j++) {
    c = j << 2;
    iy = 0;
    ix = c;
    smax = std::abs(A[c]);
    for (c_k = 2; c_k <= 3 - j; c_k++) {
      ix++;
      b_y = std::abs(A[ix]);
      if (b_y > smax) {
        iy = c_k - 1;
        smax = b_y;
      }
    }

    if (A[c + iy] != 0.0) {
      if (iy != 0) {
        iy += j;
        ipiv[j] = static_cast<int8_T>(iy + 1);
        smax = A[j];
        A[j] = A[iy];
        A[iy] = smax;
        smax = A[j + 3];
        A[j + 3] = A[iy + 3];
        A[iy + 3] = smax;
        smax = A[j + 6];
        A[j + 6] = A[iy + 6];
        A[iy + 6] = smax;
      }

      iy = (c - j) + 3;
      for (ix = c + 1; ix < iy; ix++) {
        A[ix] /= A[c];
      }
    }

    iy = c;
    ix = c + 3;
    for (c_k = 0; c_k <= 1 - j; c_k++) {
      if (A[ix] != 0.0) {
        smax = -A[ix];
        c_ix = c + 1;
        d = (iy - j) + 6;
        for (ijA = iy + 4; ijA < d; ijA++) {
          A[ijA] += A[c_ix] * smax;
          c_ix++;
        }
      }

      ix += 3;
      iy += 3;
    }
  }

  isodd = (ipiv[0] > 1);
  y = A[0] * A[4] * A[8];
  if (ipiv[1] > 2) {
    isodd = !isodd;
  }

  if (isodd) {
    y = -y;
  }

  return y;
}

// Function for MATLAB Function: '<S1>/motors2quat'
void Position_ControllerModelClass::mldivide(const real_T A[9], const real_T
  B_0[3], real_T Y[3])
{
  real_T b_A[9];
  real_T maxval;
  real_T y;
  int32_T r1;
  int32_T r2;
  int32_T r3;
  int32_T rtemp;
  std::memcpy(&b_A[0], &A[0], 9U * sizeof(real_T));
  r1 = 0;
  r2 = 1;
  r3 = 2;
  maxval = std::abs(A[0]);
  y = std::abs(A[1]);
  if (y > maxval) {
    maxval = y;
    r1 = 1;
    r2 = 0;
  }

  if (std::abs(A[2]) > maxval) {
    r1 = 2;
    r2 = 1;
    r3 = 0;
  }

  b_A[r2] = A[r2] / A[r1];
  b_A[r3] /= b_A[r1];
  b_A[r2 + 3] -= b_A[r1 + 3] * b_A[r2];
  b_A[r3 + 3] -= b_A[r1 + 3] * b_A[r3];
  b_A[r2 + 6] -= b_A[r1 + 6] * b_A[r2];
  b_A[r3 + 6] -= b_A[r1 + 6] * b_A[r3];
  if (std::abs(b_A[r3 + 3]) > std::abs(b_A[r2 + 3])) {
    rtemp = r2;
    r2 = r3;
    r3 = rtemp;
  }

  b_A[r3 + 3] /= b_A[r2 + 3];
  b_A[r3 + 6] -= b_A[r3 + 3] * b_A[r2 + 6];
  Y[1] = B_0[r2] - B_0[r1] * b_A[r2];
  Y[2] = (B_0[r3] - B_0[r1] * b_A[r3]) - b_A[r3 + 3] * Y[1];
  Y[2] /= b_A[r3 + 6];
  Y[0] = B_0[r1] - b_A[r1 + 6] * Y[2];
  Y[1] -= b_A[r2 + 6] * Y[2];
  Y[1] /= b_A[r2 + 3];
  Y[0] -= b_A[r1 + 3] * Y[1];
  Y[0] /= b_A[r1];
}

// Model step function
void Position_ControllerModelClass::step()
{
  real_T oa[12];
  real_T up[12];
  real_T b[9];
  real_T q[9];
  real_T theta_diff_0[9];
  real_T b_ob[3];
  real_T ob[3];
  real_T theta_diff[3];
  real_T absx;
  real_T b_oc_idx_0;
  real_T b_oc_idx_1;
  real_T b_oc_idx_2;
  real_T od;
  real_T od_idx_1;
  real_T od_idx_2;
  real_T p_idx_5;
  real_T rtb_Product1;
  real_T rtb_Product2;
  real_T rtb_Product3;
  real_T theta;
  int32_T cycles;
  int32_T d_k;
  int32_T exitg1;
  int32_T idx;
  int32_T q_tmp;
  int8_T rtb_DataTypeConv1_idx_0;
  boolean_T exitg2;
  boolean_T guard1 = false;
  boolean_T rtb_NotEqual_idx_0;

  // Outputs for Atomic SubSystem: '<Root>/Position_Controller'
  // MATLAB Function: '<S1>/motors2quat' incorporates:
  //   Inport: '<Root>/theta'

  // :  if isempty(T)
  // :  if isempty(singularity_reg)
  // :  theta_diff = theta_meas - [145; -90; 40];
  // :  for k=1:3
  // :  if max(abs(theta_diff)) < 5.0
  theta_diff[0] = rtU.theta[0] - 145.0;

  // :  while theta_diff(k) > 180.0
  while (theta_diff[0] > 180.0) {
    // :  theta_diff(k) = theta_diff(k) - 360.0
    theta_diff[0] -= 360.0;
  }

  // :  while theta_diff(k) < -180.0
  while (theta_diff[0] < -180.0) {
    // :  theta_diff(k) = theta_diff(k) + 360.0
    theta_diff[0] += 360.0;
  }

  b_ob[0] = std::abs(theta_diff[0]);
  theta_diff[1] = rtU.theta[1] - -90.0;

  // :  while theta_diff(k) > 180.0
  while (theta_diff[1] > 180.0) {
    // :  theta_diff(k) = theta_diff(k) - 360.0
    theta_diff[1] -= 360.0;
  }

  // :  while theta_diff(k) < -180.0
  while (theta_diff[1] < -180.0) {
    // :  theta_diff(k) = theta_diff(k) + 360.0
    theta_diff[1] += 360.0;
  }

  b_ob[1] = std::abs(theta_diff[1]);
  theta_diff[2] = rtU.theta[2] - 40.0;

  // :  while theta_diff(k) > 180.0
  while (theta_diff[2] > 180.0) {
    // :  theta_diff(k) = theta_diff(k) - 360.0
    theta_diff[2] -= 360.0;
  }

  // :  while theta_diff(k) < -180.0
  while (theta_diff[2] < -180.0) {
    // :  theta_diff(k) = theta_diff(k) + 360.0
    theta_diff[2] += 360.0;
  }

  b_ob[2] = std::abs(theta_diff[2]);
  if (maximum(b_ob) < 5.0) {
    // :  singularity_reg = 0;
    rtDW.singularity_reg = 0.0;
  }

  // :  if singularity_reg
  if (rtDW.singularity_reg != 0.0) {
    // :  attitude = compact(T);
    p_idx_5 = rtDW.T.a;
    theta = rtDW.T.b;
    b_oc_idx_1 = rtDW.T.c;
    b_oc_idx_0 = rtDW.T.d;

    // Outport: '<Root>/Singularity'
    // :  singularity = singularity_reg;
    rtY.Singularity = rtDW.singularity_reg;

    // :  cycles = 0;
    cycles = 0;
  } else {
    // :  for cycles=1:200
    cycles = 1;
    idx = 0;
    guard1 = false;
    do {
      exitg1 = 0;
      if (idx < 200) {
        cycles = idx + 1;

        // :  q = rotatepoint(T,Q);
        theta = std::sqrt(((rtDW.T.a * rtDW.T.a + rtDW.T.b * rtDW.T.b) +
                           rtDW.T.c * rtDW.T.c) + rtDW.T.d * rtDW.T.d);
        rtb_Product3 = rtDW.T.a / theta;
        absx = rtDW.T.b / theta;
        rtb_Product1 = rtDW.T.c / theta;
        rtb_Product2 = rtDW.T.d / theta;
        up[0] = 0.0;
        up[1] = 0.0;
        up[2] = 0.0;
        std::memcpy(&up[3], &rtConstP.pooled4[0], 9U * sizeof(real_T));
        p_idx_5 = ((rtb_Product3 * up[0] - absx * up[3]) - rtb_Product1 * up[6])
          - rtb_Product2 * up[9];
        od_idx_1 = ((rtb_Product3 * up[3] + absx * up[0]) + rtb_Product1 * up[9])
          - rtb_Product2 * up[6];
        od_idx_2 = ((rtb_Product3 * up[6] - absx * up[9]) + rtb_Product1 * up[0])
          + rtb_Product2 * up[3];
        od = ((rtb_Product3 * up[9] + absx * up[6]) - rtb_Product1 * up[3]) +
          rtb_Product2 * up[0];
        oa[0] = ((p_idx_5 * rtb_Product3 - od_idx_1 * -absx) - od_idx_2 *
                 -rtb_Product1) - od * -rtb_Product2;
        b_ob[0] = ((p_idx_5 * -absx + od_idx_1 * rtb_Product3) + od_idx_2 *
                   -rtb_Product2) - od * -rtb_Product1;
        b_oc_idx_0 = ((p_idx_5 * -rtb_Product1 - od_idx_1 * -rtb_Product2) +
                      od_idx_2 * rtb_Product3) + od * -absx;
        theta_diff[0] = ((p_idx_5 * -rtb_Product2 + od_idx_1 * -rtb_Product1) -
                         od_idx_2 * -absx) + od * rtb_Product3;
        p_idx_5 = ((rtb_Product3 * up[1] - absx * up[4]) - rtb_Product1 * up[7])
          - rtb_Product2 * up[10];
        od_idx_1 = ((rtb_Product3 * up[4] + absx * up[1]) + rtb_Product1 * up[10])
          - rtb_Product2 * up[7];
        od_idx_2 = ((rtb_Product3 * up[7] - absx * up[10]) + rtb_Product1 * up[1])
          + rtb_Product2 * up[4];
        od = ((rtb_Product3 * up[10] + absx * up[7]) - rtb_Product1 * up[4]) +
          rtb_Product2 * up[1];
        oa[1] = ((p_idx_5 * rtb_Product3 - od_idx_1 * -absx) - od_idx_2 *
                 -rtb_Product1) - od * -rtb_Product2;
        b_ob[1] = ((p_idx_5 * -absx + od_idx_1 * rtb_Product3) + od_idx_2 *
                   -rtb_Product2) - od * -rtb_Product1;
        b_oc_idx_1 = ((p_idx_5 * -rtb_Product1 - od_idx_1 * -rtb_Product2) +
                      od_idx_2 * rtb_Product3) + od * -absx;
        theta_diff[1] = ((p_idx_5 * -rtb_Product2 + od_idx_1 * -rtb_Product1) -
                         od_idx_2 * -absx) + od * rtb_Product3;
        p_idx_5 = ((rtb_Product3 * up[2] - absx * up[5]) - rtb_Product1 * up[8])
          - rtb_Product2 * up[11];
        od_idx_1 = ((rtb_Product3 * up[5] + absx * up[2]) + rtb_Product1 * up[11])
          - rtb_Product2 * up[8];
        od_idx_2 = ((rtb_Product3 * up[8] - absx * up[11]) + rtb_Product1 * up[2])
          + rtb_Product2 * up[5];
        od = ((rtb_Product3 * up[11] + absx * up[8]) - rtb_Product1 * up[5]) +
          rtb_Product2 * up[2];
        oa[2] = ((p_idx_5 * rtb_Product3 - od_idx_1 * -absx) - od_idx_2 *
                 -rtb_Product1) - od * -rtb_Product2;
        b_ob[2] = ((p_idx_5 * -absx + od_idx_1 * rtb_Product3) + od_idx_2 *
                   -rtb_Product2) - od * -rtb_Product1;
        b_oc_idx_2 = ((p_idx_5 * -rtb_Product1 - od_idx_1 * -rtb_Product2) +
                      od_idx_2 * rtb_Product3) + od * -absx;
        p_idx_5 = ((p_idx_5 * -rtb_Product2 + od_idx_1 * -rtb_Product1) -
                   od_idx_2 * -absx) + od * rtb_Product3;
        up[3] = b_ob[0];
        up[9] = theta_diff[0];
        oa[3] = b_ob[0];
        oa[6] = b_oc_idx_0;
        oa[9] = theta_diff[0];
        up[4] = b_ob[1];
        up[10] = theta_diff[1];
        oa[4] = b_ob[1];
        oa[7] = b_oc_idx_1;
        oa[10] = theta_diff[1];
        rtb_Product3 = b_ob[2];
        oa[5] = b_ob[2];
        oa[8] = b_oc_idx_2;
        oa[11] = p_idx_5;

        // :  m = [sqrt(q(1,1)^2+q(1,2)^2) sqrt(q(2,1)^2+q(2,2)^2) sqrt(q(3,1)^2+q(3,2)^2)]; 
        b_oc_idx_0 *= b_oc_idx_0;
        theta_diff[0] = std::sqrt(b_ob[0] * b_ob[0] + b_oc_idx_0);
        b_oc_idx_1 *= b_oc_idx_1;
        theta_diff[1] = std::sqrt(b_ob[1] * b_ob[1] + b_oc_idx_1);
        theta_diff[2] = std::sqrt(b_ob[2] * b_ob[2] + b_oc_idx_2 * b_oc_idx_2);

        // :  if min(abs(m)) == 0
        for (d_k = 0; d_k < 3; d_k++) {
          q_tmp = (d_k + 1) * 3;
          q[3 * d_k] = oa[q_tmp];
          q[3 * d_k + 1] = oa[q_tmp + 1];
          q[3 * d_k + 2] = oa[q_tmp + 2];
          b_ob[d_k] = std::abs(theta_diff[d_k]);
        }

        if (minimum(b_ob) == 0.0) {
          // :  cycles = -1;
          cycles = -1;
          guard1 = true;
          exitg1 = 1;
        } else {
          // :  arg = [(PQ(1)-Pz(1)*q(1,3))/m(1); (PQ(2)-Pz(2)*q(2,3))/m(2); (PQ(3)-Pz(3)*q(3,3))/m(3)]; 
          ob[0] = (0.5 - -0.57735026918962573 * up[9]) / std::sqrt(up[3] * up[3]
            + b_oc_idx_0);
          ob[1] = (0.087155742747658166 - -0.57735026918962573 * up[10]) / std::
            sqrt(up[4] * up[4] + b_oc_idx_1);
          ob[2] = (-0.49999999999999994 - -0.57735026918962573 * p_idx_5) / std::
            sqrt(rtb_Product3 * rtb_Product3 + b_oc_idx_2 * b_oc_idx_2);

          // :  if max(abs(arg)) > 1.0
          b_ob[0] = std::abs(ob[0]);
          b_ob[1] = std::abs(ob[1]);
          b_ob[2] = std::abs(ob[2]);
          if (maximum(b_ob) > 1.0) {
            // :  cycles = -2;
            cycles = -2;
            guard1 = true;
            exitg1 = 1;
          } else {
            // :  theta = atan2d(q(:,2),q(:,1))+[90; 90; 90;]-asind(arg);
            // :  theta_err = theta_meas-theta;
            // :  for k=1:3
            // :  if max(abs(theta_err)) < 0.01
            ob[0] = 57.295779513082323 * std::asin(ob[0]);
            theta_diff[0] = (57.295779513082323 * rt_atan2d_snf(q[3], q[0]) +
                             90.0) - ob[0];

            // :  while theta_err(k) > 180.0
            for (rtb_Product1 = rtU.theta[0] - theta_diff[0]; rtb_Product1 >
                 180.0; rtb_Product1 -= 360.0) {
              // :  theta_err(k) = theta_err(k) - 360.0
            }

            // :  while theta_err(k) < -180.0
            while (rtb_Product1 < -180.0) {
              // :  theta_err(k) = theta_err(k) + 360.0
              rtb_Product1 += 360.0;
            }

            b_ob[0] = std::abs(rtb_Product1);
            theta_diff[1] = 57.295779513082323 * rt_atan2d_snf(q[4], q[1]);
            ob[1] = 57.295779513082323 * std::asin(ob[1]);
            theta_diff[1] = (theta_diff[1] + 90.0) - ob[1];

            // :  while theta_err(k) > 180.0
            for (od_idx_1 = rtU.theta[1] - theta_diff[1]; od_idx_1 > 180.0;
                 od_idx_1 -= 360.0) {
              // :  theta_err(k) = theta_err(k) - 360.0
            }

            // :  while theta_err(k) < -180.0
            while (od_idx_1 < -180.0) {
              // :  theta_err(k) = theta_err(k) + 360.0
              od_idx_1 += 360.0;
            }

            b_ob[1] = std::abs(od_idx_1);
            theta_diff[2] = 57.295779513082323 * rt_atan2d_snf(q[5], q[2]);
            ob[2] = 57.295779513082323 * std::asin(ob[2]);
            theta_diff[2] = (theta_diff[2] + 90.0) - ob[2];

            // :  while theta_err(k) > 180.0
            for (od_idx_2 = rtU.theta[2] - theta_diff[2]; od_idx_2 > 180.0;
                 od_idx_2 -= 360.0) {
              // :  theta_err(k) = theta_err(k) - 360.0
            }

            // :  while theta_err(k) < -180.0
            while (od_idx_2 < -180.0) {
              // :  theta_err(k) = theta_err(k) + 360.0
              od_idx_2 += 360.0;
            }

            b_ob[2] = std::abs(od_idx_2);
            if (maximum(b_ob) < 0.01) {
              // :  T = normalize(T);
              rtDW.T.a /= theta;
              rtDW.T.b /= theta;
              rtDW.T.c /= theta;
              rtDW.T.d /= theta;

              // :  attitude = compact(T);
              p_idx_5 = rtDW.T.a;
              theta = rtDW.T.b;
              b_oc_idx_1 = rtDW.T.c;
              b_oc_idx_0 = rtDW.T.d;

              // :  singularity = singularity_reg;
              rtY.Singularity = rtDW.singularity_reg;
              exitg1 = 1;
            } else {
              // :  p = [cosd(theta) sind(theta) Pz];
              if (rtIsInf(theta_diff[0]) || rtIsNaN(theta_diff[0])) {
                b_oc_idx_2 = (rtNaN);
              } else {
                rtb_Product3 = rt_remd_snf(theta_diff[0], 360.0);
                absx = std::abs(rtb_Product3);
                if (absx > 180.0) {
                  if (rtb_Product3 > 0.0) {
                    rtb_Product3 -= 360.0;
                  } else {
                    rtb_Product3 += 360.0;
                  }

                  absx = std::abs(rtb_Product3);
                }

                if (absx <= 45.0) {
                  rtb_Product3 *= 0.017453292519943295;
                  rtb_DataTypeConv1_idx_0 = 0;
                } else if (absx <= 135.0) {
                  if (rtb_Product3 > 0.0) {
                    rtb_Product3 = (rtb_Product3 - 90.0) * 0.017453292519943295;
                    rtb_DataTypeConv1_idx_0 = 1;
                  } else {
                    rtb_Product3 = (rtb_Product3 + 90.0) * 0.017453292519943295;
                    rtb_DataTypeConv1_idx_0 = -1;
                  }
                } else if (rtb_Product3 > 0.0) {
                  rtb_Product3 = (rtb_Product3 - 180.0) * 0.017453292519943295;
                  rtb_DataTypeConv1_idx_0 = 2;
                } else {
                  rtb_Product3 = (rtb_Product3 + 180.0) * 0.017453292519943295;
                  rtb_DataTypeConv1_idx_0 = -2;
                }

                switch (rtb_DataTypeConv1_idx_0) {
                 case 0:
                  b_oc_idx_2 = std::cos(rtb_Product3);
                  break;

                 case 1:
                  b_oc_idx_2 = -std::sin(rtb_Product3);
                  break;

                 case -1:
                  b_oc_idx_2 = std::sin(rtb_Product3);
                  break;

                 default:
                  b_oc_idx_2 = -std::cos(rtb_Product3);
                  break;
                }
              }

              if (rtIsInf(theta_diff[1]) || rtIsNaN(theta_diff[1])) {
                theta = (rtNaN);
              } else {
                rtb_Product3 = rt_remd_snf(theta_diff[1], 360.0);
                absx = std::abs(rtb_Product3);
                if (absx > 180.0) {
                  if (rtb_Product3 > 0.0) {
                    rtb_Product3 -= 360.0;
                  } else {
                    rtb_Product3 += 360.0;
                  }

                  absx = std::abs(rtb_Product3);
                }

                if (absx <= 45.0) {
                  rtb_Product3 *= 0.017453292519943295;
                  rtb_DataTypeConv1_idx_0 = 0;
                } else if (absx <= 135.0) {
                  if (rtb_Product3 > 0.0) {
                    rtb_Product3 = (rtb_Product3 - 90.0) * 0.017453292519943295;
                    rtb_DataTypeConv1_idx_0 = 1;
                  } else {
                    rtb_Product3 = (rtb_Product3 + 90.0) * 0.017453292519943295;
                    rtb_DataTypeConv1_idx_0 = -1;
                  }
                } else if (rtb_Product3 > 0.0) {
                  rtb_Product3 = (rtb_Product3 - 180.0) * 0.017453292519943295;
                  rtb_DataTypeConv1_idx_0 = 2;
                } else {
                  rtb_Product3 = (rtb_Product3 + 180.0) * 0.017453292519943295;
                  rtb_DataTypeConv1_idx_0 = -2;
                }

                switch (rtb_DataTypeConv1_idx_0) {
                 case 0:
                  theta = std::cos(rtb_Product3);
                  break;

                 case 1:
                  theta = -std::sin(rtb_Product3);
                  break;

                 case -1:
                  theta = std::sin(rtb_Product3);
                  break;

                 default:
                  theta = -std::cos(rtb_Product3);
                  break;
                }
              }

              if (rtIsInf(theta_diff[2]) || rtIsNaN(theta_diff[2])) {
                rtb_Product3 = (rtNaN);
              } else {
                rtb_Product3 = rt_remd_snf(theta_diff[2], 360.0);
                absx = std::abs(rtb_Product3);
                if (absx > 180.0) {
                  if (rtb_Product3 > 0.0) {
                    rtb_Product3 -= 360.0;
                  } else {
                    rtb_Product3 += 360.0;
                  }

                  absx = std::abs(rtb_Product3);
                }

                if (absx <= 45.0) {
                  rtb_Product3 *= 0.017453292519943295;
                  rtb_DataTypeConv1_idx_0 = 0;
                } else if (absx <= 135.0) {
                  if (rtb_Product3 > 0.0) {
                    rtb_Product3 = (rtb_Product3 - 90.0) * 0.017453292519943295;
                    rtb_DataTypeConv1_idx_0 = 1;
                  } else {
                    rtb_Product3 = (rtb_Product3 + 90.0) * 0.017453292519943295;
                    rtb_DataTypeConv1_idx_0 = -1;
                  }
                } else if (rtb_Product3 > 0.0) {
                  rtb_Product3 = (rtb_Product3 - 180.0) * 0.017453292519943295;
                  rtb_DataTypeConv1_idx_0 = 2;
                } else {
                  rtb_Product3 = (rtb_Product3 + 180.0) * 0.017453292519943295;
                  rtb_DataTypeConv1_idx_0 = -2;
                }

                switch (rtb_DataTypeConv1_idx_0) {
                 case 0:
                  rtb_Product3 = std::cos(rtb_Product3);
                  break;

                 case 1:
                  rtb_Product3 = -std::sin(rtb_Product3);
                  break;

                 case -1:
                  rtb_Product3 = std::sin(rtb_Product3);
                  break;

                 default:
                  rtb_Product3 = -std::cos(rtb_Product3);
                  break;
                }
              }

              sind(theta_diff);
              b_oc_idx_0 = theta_diff[0];
              b_oc_idx_1 = theta_diff[1];
              p_idx_5 = theta_diff[2];

              // :  q1xp1 = cross(q(1,:),p(1,:));
              theta_diff[2] = q[0] * b_oc_idx_0 - q[3] * b_oc_idx_2;

              // :  q2xp2 = cross(q(2,:),p(2,:));
              ob[2] = q[1] * b_oc_idx_1 - q[4] * theta;

              // :  q3xp3 = cross(q(3,:),p(3,:));
              absx = q[2] * p_idx_5 - q[5] * rtb_Product3;

              // :  if min(abs([q1xp1(3) q2xp2(3) q3xp3(3)])) == 0.0
              b_ob[0] = std::abs(theta_diff[2]);
              b_ob[1] = std::abs(ob[2]);
              b_ob[2] = std::abs(absx);
              if (minimum(b_ob) == 0.0) {
                // :  cycles = -3;
                cycles = -3;
                guard1 = true;
                exitg1 = 1;
              } else {
                // :  if det([q1xp1/q1xp1(3); q2xp2/q2xp2(3); q3xp3/q3xp3(3)]) == 0.0 
                b_oc_idx_0 = (q[3] * -0.57735026918962573 - q[6] * b_oc_idx_0) /
                  theta_diff[2];
                theta_diff_0[0] = b_oc_idx_0;
                b_oc_idx_1 = (q[4] * -0.57735026918962573 - q[7] * b_oc_idx_1) /
                  ob[2];
                theta_diff_0[1] = b_oc_idx_1;
                p_idx_5 = (q[5] * -0.57735026918962573 - q[8] * p_idx_5) / absx;
                theta_diff_0[2] = p_idx_5;
                b_oc_idx_2 = (q[6] * b_oc_idx_2 - q[0] * -0.57735026918962573) /
                  theta_diff[2];
                theta_diff_0[3] = b_oc_idx_2;
                theta = (q[7] * theta - q[1] * -0.57735026918962573) / ob[2];
                theta_diff_0[4] = theta;
                rtb_Product3 = (q[8] * rtb_Product3 - q[2] *
                                -0.57735026918962573) / absx;
                theta_diff_0[5] = rtb_Product3;
                od = theta_diff[2] / theta_diff[2];
                theta_diff_0[6] = od;
                rtb_Product2 = ob[2] / ob[2];
                theta_diff_0[7] = rtb_Product2;
                absx /= absx;
                theta_diff_0[8] = absx;
                if (det(theta_diff_0) == 0.0) {
                  // :  cycles = -4;
                  cycles = -4;
                  guard1 = true;
                  exitg1 = 1;
                } else {
                  // :  T = quaternion(([q1xp1/q1xp1(3); q2xp2/q2xp2(3); q3xp3/q3xp3(3)]\(0.02*theta_err))','rotvec')*T; 
                  theta_diff_0[0] = b_oc_idx_0;
                  theta_diff_0[1] = b_oc_idx_1;
                  theta_diff_0[2] = p_idx_5;
                  theta_diff[0] = 0.02 * rtb_Product1;
                  theta_diff_0[3] = b_oc_idx_2;
                  theta_diff_0[4] = theta;
                  theta_diff_0[5] = rtb_Product3;
                  theta_diff[1] = 0.02 * od_idx_1;
                  theta_diff_0[6] = od;
                  theta_diff_0[7] = rtb_Product2;
                  theta_diff_0[8] = absx;
                  theta_diff[2] = 0.02 * od_idx_2;
                  mldivide(theta_diff_0, theta_diff, ob);
                  rtb_Product3 = 1.0;
                  absx = 0.0;
                  rtb_Product1 = 0.0;
                  rtb_Product2 = 0.0;
                  theta = std::sqrt((ob[0] * ob[0] + ob[1] * ob[1]) + ob[2] *
                                    ob[2]);
                  b_oc_idx_0 = std::sin(theta / 2.0);
                  if (theta != 0.0) {
                    ob[0] = ob[0] / theta * b_oc_idx_0;
                    ob[1] = ob[1] / theta * b_oc_idx_0;
                    rtb_Product3 = std::cos(theta / 2.0);
                    absx = ob[0];
                    rtb_Product1 = ob[1];
                    rtb_Product2 = ob[2] / theta * b_oc_idx_0;
                  }

                  theta = ((rtb_Product3 * rtDW.T.a - absx * rtDW.T.b) -
                           rtb_Product1 * rtDW.T.c) - rtb_Product2 * rtDW.T.d;
                  b_oc_idx_0 = ((rtb_Product3 * rtDW.T.b + absx * rtDW.T.a) +
                                rtb_Product1 * rtDW.T.d) - rtb_Product2 *
                    rtDW.T.c;
                  b_oc_idx_1 = ((rtb_Product3 * rtDW.T.c - absx * rtDW.T.d) +
                                rtb_Product1 * rtDW.T.a) + rtb_Product2 *
                    rtDW.T.b;
                  rtDW.T.d = ((rtb_Product3 * rtDW.T.d + absx * rtDW.T.c) -
                              rtb_Product1 * rtDW.T.b) + rtb_Product2 * rtDW.T.a;
                  rtDW.T.a = theta;
                  rtDW.T.b = b_oc_idx_0;
                  rtDW.T.c = b_oc_idx_1;
                  idx++;
                  guard1 = false;
                }
              }
            }
          }
        }
      } else {
        guard1 = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);

    if (guard1) {
      // :  T = quaternion(1,0,0,0);
      rtDW.T.a = 1.0;
      rtDW.T.b = 0.0;
      rtDW.T.c = 0.0;
      rtDW.T.d = 0.0;

      // :  attitude = compact(T);
      p_idx_5 = rtDW.T.a;
      theta = rtDW.T.b;
      b_oc_idx_1 = rtDW.T.c;
      b_oc_idx_0 = rtDW.T.d;

      // :  singularity_reg = 1;
      rtDW.singularity_reg = 1.0;

      // :  singularity = singularity_reg;
      rtY.Singularity = rtDW.singularity_reg;
    }
  }

  // Sqrt: '<S63>/sqrt' incorporates:
  //   Product: '<S64>/Product'
  //   Product: '<S64>/Product1'
  //   Product: '<S64>/Product2'
  //   Product: '<S64>/Product3'
  //   Sum: '<S64>/Sum'

  rtb_Product3 = std::sqrt(((p_idx_5 * p_idx_5 + theta * theta) + b_oc_idx_1 *
    b_oc_idx_1) + b_oc_idx_0 * b_oc_idx_0);

  // Product: '<S58>/Product'
  absx = p_idx_5 / rtb_Product3;

  // Product: '<S58>/Product1'
  rtb_Product1 = theta / rtb_Product3;

  // Product: '<S58>/Product2'
  rtb_Product2 = b_oc_idx_1 / rtb_Product3;

  // Product: '<S58>/Product3'
  rtb_Product3 = b_oc_idx_0 / rtb_Product3;

  // Fcn: '<S3>/fcn2' incorporates:
  //   Fcn: '<S3>/fcn5'

  b_oc_idx_0 = absx * absx;
  b_oc_idx_1 = rtb_Product1 * rtb_Product1;
  p_idx_5 = rtb_Product2 * rtb_Product2;
  b_oc_idx_2 = rtb_Product3 * rtb_Product3;

  // Trigonometry: '<S57>/Trigonometric Function1' incorporates:
  //   Fcn: '<S3>/fcn1'
  //   Fcn: '<S3>/fcn2'

  theta_diff[0] = rt_atan2d_snf((rtb_Product1 * rtb_Product2 + absx *
    rtb_Product3) * 2.0, ((b_oc_idx_0 + b_oc_idx_1) - p_idx_5) - b_oc_idx_2);

  // Fcn: '<S3>/fcn3'
  theta = (rtb_Product1 * rtb_Product3 - absx * rtb_Product2) * -2.0;

  // If: '<S59>/If' incorporates:
  //   Constant: '<S60>/Constant'
  //   Constant: '<S61>/Constant'
  //   Inport: '<S62>/In'

  if (theta > 1.0) {
    // Outputs for IfAction SubSystem: '<S59>/If Action Subsystem' incorporates:
    //   ActionPort: '<S60>/Action Port'

    od = 1.0;

    // End of Outputs for SubSystem: '<S59>/If Action Subsystem'
  } else if (theta < -1.0) {
    // Outputs for IfAction SubSystem: '<S59>/If Action Subsystem1' incorporates:
    //   ActionPort: '<S61>/Action Port'

    od = 1.0;

    // End of Outputs for SubSystem: '<S59>/If Action Subsystem1'
  } else {
    // Outputs for IfAction SubSystem: '<S59>/If Action Subsystem2' incorporates:
    //   ActionPort: '<S62>/Action Port'

    od = theta;

    // End of Outputs for SubSystem: '<S59>/If Action Subsystem2'
  }

  // End of If: '<S59>/If'

  // Fcn: '<S3>/fcn4'
  theta = (rtb_Product2 * rtb_Product3 + absx * rtb_Product1) * 2.0;

  // MATLAB Function: '<S1>/ypr2motors' incorporates:
  //   Inport: '<Root>/ypr+'

  // :  theta = [0;0;0];
  // :  q = Q*eul2rotm(deg2rad(ypr'))';
  b_ob[0] = 0.0;
  od_idx_1 = 0.017453292519943295 * rtU.ypr[0];
  rtb_Product3 = std::cos(od_idx_1);
  ob[0] = std::sin(od_idx_1);
  b_ob[1] = 0.0;
  od_idx_1 = 0.017453292519943295 * rtU.ypr[1];
  absx = std::cos(od_idx_1);
  ob[1] = std::sin(od_idx_1);
  b_ob[2] = 0.0;
  od_idx_1 = 0.017453292519943295 * rtU.ypr[2];
  od_idx_2 = std::cos(od_idx_1);
  od_idx_1 = std::sin(od_idx_1);
  b[0] = absx * rtb_Product3;
  rtb_Product1 = od_idx_1 * ob[1];
  b[3] = rtb_Product1 * rtb_Product3 - od_idx_2 * ob[0];
  rtb_Product2 = od_idx_2 * ob[1];
  b[6] = rtb_Product2 * rtb_Product3 + od_idx_1 * ob[0];
  b[1] = absx * ob[0];
  b[4] = rtb_Product1 * ob[0] + od_idx_2 * rtb_Product3;
  b[7] = rtb_Product2 * ob[0] - od_idx_1 * rtb_Product3;
  b[2] = -ob[1];
  b[5] = od_idx_1 * absx;
  b[8] = od_idx_2 * absx;
  for (idx = 0; idx < 3; idx++) {
    for (d_k = 0; d_k < 3; d_k++) {
      q_tmp = idx + 3 * d_k;
      q[q_tmp] = 0.0;
      q[q_tmp] += rtConstP.pooled4[idx] * b[d_k];
      q[q_tmp] += rtConstP.pooled4[idx + 3] * b[d_k + 3];
      q[q_tmp] += rtConstP.pooled4[idx + 6] * b[d_k + 6];
    }
  }

  // :  m = [sqrt(q(1,1)^2+q(1,2)^2) sqrt(q(2,1)^2+q(2,2)^2) sqrt(q(3,1)^2+q(3,2)^2)]; 
  rtb_Product1 = std::sqrt(q[0] * q[0] + q[3] * q[3]);
  od_idx_1 = std::sqrt(q[1] * q[1] + q[4] * q[4]);
  absx = std::sqrt(q[2] * q[2] + q[5] * q[5]);

  // :  if min(abs(m)) == 0
  ob[0] = std::abs(rtb_Product1);
  ob[1] = std::abs(od_idx_1);
  ob[2] = std::abs(absx);
  if (!rtIsNaN(ob[0])) {
    idx = 1;
  } else {
    idx = 0;
    d_k = 2;
    exitg2 = false;
    while ((!exitg2) && (d_k < 4)) {
      if (!rtIsNaN(ob[d_k - 1])) {
        idx = d_k;
        exitg2 = true;
      } else {
        d_k++;
      }
    }
  }

  if (idx == 0) {
    rtb_Product3 = ob[0];
  } else {
    rtb_Product3 = ob[idx - 1];
    while (idx + 1 <= 3) {
      if (rtb_Product3 > ob[idx]) {
        rtb_Product3 = ob[idx];
      }

      idx++;
    }
  }

  if (rtb_Product3 == 0.0) {
    // Outport: '<Root>/InRange'
    // :  in_range = -1;
    rtY.InRange = -1.0;
  } else {
    // :  arg = [(PQ(1)-Pz(1)*q(1,3))/m(1); (PQ(2)-Pz(2)*q(2,3))/m(2); (PQ(3)-Pz(3)*q(3,3))/m(3)]; 
    rtb_Product1 = (0.5 - -0.57735026918962573 * q[6]) / rtb_Product1;
    od_idx_1 = (0.087155742747658166 - -0.57735026918962573 * q[7]) / od_idx_1;
    od_idx_2 = (-0.49999999999999994 - -0.57735026918962573 * q[8]) / absx;

    // :  if max(abs(arg)) > 1
    ob[0] = std::abs(rtb_Product1);
    ob[1] = std::abs(od_idx_1);
    ob[2] = std::abs(od_idx_2);
    if (!rtIsNaN(ob[0])) {
      idx = 1;
    } else {
      idx = 0;
      d_k = 2;
      exitg2 = false;
      while ((!exitg2) && (d_k < 4)) {
        if (!rtIsNaN(ob[d_k - 1])) {
          idx = d_k;
          exitg2 = true;
        } else {
          d_k++;
        }
      }
    }

    if (idx == 0) {
      rtb_Product3 = ob[0];
    } else {
      rtb_Product3 = ob[idx - 1];
      while (idx + 1 <= 3) {
        if (rtb_Product3 < ob[idx]) {
          rtb_Product3 = ob[idx];
        }

        idx++;
      }
    }

    if (rtb_Product3 > 1.0) {
      // Outport: '<Root>/InRange'
      // :  in_range = -2;
      rtY.InRange = -2.0;
    } else {
      // :  theta = atan2d(q(:,2),q(:,1))+[90; 90; 90;]-asind(arg);
      b_ob[0] = (57.295779513082323 * rt_atan2d_snf(q[3], q[0]) + 90.0) -
        57.295779513082323 * std::asin(rtb_Product1);
      b_ob[1] = (57.295779513082323 * rt_atan2d_snf(q[4], q[1]) + 90.0) -
        57.295779513082323 * std::asin(od_idx_1);
      b_ob[2] = (57.295779513082323 * rt_atan2d_snf(q[5], q[2]) + 90.0) -
        57.295779513082323 * std::asin(od_idx_2);

      // Outport: '<Root>/InRange'
      // :  in_range = 1;
      rtY.InRange = 1.0;
    }
  }

  // End of MATLAB Function: '<S1>/ypr2motors'

  // MATLAB Function: '<S1>/wrapTo180' incorporates:
  //   Inport: '<Root>/theta'
  //   Sum: '<S1>/Sum'

  // :  y = u;
  // :  for k=1:3
  b_ob[0] -= rtU.theta[0];

  // :  while y(k) > 180.0
  while (b_ob[0] > 180.0) {
    // :  y(k) = y(k) - 360.0
    b_ob[0] -= 360.0;
  }

  // :  while y(k) < -180.0
  while (b_ob[0] < -180.0) {
    // :  y(k) = y(k) + 360.0
    b_ob[0] += 360.0;
  }

  // Gain: '<S43>/Filter Coefficient' incorporates:
  //   DiscreteIntegrator: '<S35>/Filter'
  //   Gain: '<S34>/Derivative Gain'
  //   Sum: '<S35>/SumD'

  ob[0] = (0.0125 * b_ob[0] - rtDW.Filter_DSTATE[0]) * 100.0;

  // Gain: '<S38>/Proportional Gain' incorporates:
  //   DiscreteIntegrator: '<S40>/Integrator'
  //   Sum: '<S49>/Sum'

  rtb_Product3 = ((b_ob[0] + rtDW.Integrator_DSTATE[0]) + ob[0]) * 0.005;

  // DeadZone: '<S33>/DeadZone'
  if (rtb_Product3 > 0.0102) {
    rtb_Product1 = rtb_Product3 - 0.0102;
  } else if (rtb_Product3 >= -0.0102) {
    rtb_Product1 = 0.0;
  } else {
    rtb_Product1 = rtb_Product3 - -0.0102;
  }

  // RelationalOperator: '<S31>/NotEqual' incorporates:
  //   Gain: '<S31>/ZeroGain'

  rtb_NotEqual_idx_0 = (0.0 * rtb_Product3 != rtb_Product1);

  // Signum: '<S31>/SignPreSat'
  if (rtb_Product1 < 0.0) {
    rtb_Product1 = -1.0;
  } else if (rtb_Product1 > 0.0) {
    rtb_Product1 = 1.0;
  } else if (rtb_Product1 == 0.0) {
    rtb_Product1 = 0.0;
  } else {
    rtb_Product1 = (rtNaN);
  }

  // DataTypeConversion: '<S31>/DataTypeConv1'
  rtb_DataTypeConv1_idx_0 = static_cast<int8_T>(rtb_Product1);

  // Gain: '<S37>/Integral Gain'
  rtb_Product1 = 0.5 * b_ob[0];

  // Update for DiscreteIntegrator: '<S35>/Filter'
  rtDW.Filter_DSTATE[0] += 0.001 * ob[0];

  // Signum: '<S31>/SignPreIntegrator'
  if (rtb_Product1 < 0.0) {
    absx = -1.0;
  } else if (rtb_Product1 > 0.0) {
    absx = 1.0;
  } else if (rtb_Product1 == 0.0) {
    absx = 0.0;
  } else {
    absx = (rtNaN);
  }

  // Switch: '<S31>/Switch' incorporates:
  //   Constant: '<S31>/Constant1'
  //   DataTypeConversion: '<S31>/DataTypeConv2'
  //   Logic: '<S31>/AND3'
  //   RelationalOperator: '<S31>/Equal1'

  if (rtb_NotEqual_idx_0 && (rtb_DataTypeConv1_idx_0 == static_cast<int8_T>(absx)))
  {
    rtb_Product1 = 0.0;
  }

  // Update for DiscreteIntegrator: '<S40>/Integrator'
  rtDW.Integrator_DSTATE[0] += 0.001 * rtb_Product1;

  // Saturate: '<S47>/Saturation'
  if (rtb_Product3 > 0.0102) {
    // Outport: '<Root>/Tau+'
    rtY.Tau[0] = 0.0102;
  } else if (rtb_Product3 < -0.0102) {
    // Outport: '<Root>/Tau+'
    rtY.Tau[0] = -0.0102;
  } else {
    // Outport: '<Root>/Tau+'
    rtY.Tau[0] = rtb_Product3;
  }

  // Outport: '<Root>/ypr_meas' incorporates:
  //   Gain: '<S1>/Gain3'

  rtY.ypr_meas[0] = 57.295779513082323 * theta_diff[0];

  // MATLAB Function: '<S1>/wrapTo180' incorporates:
  //   Inport: '<Root>/theta'
  //   Sum: '<S1>/Sum'

  b_ob[1] -= rtU.theta[1];

  // :  while y(k) > 180.0
  while (b_ob[1] > 180.0) {
    // :  y(k) = y(k) - 360.0
    b_ob[1] -= 360.0;
  }

  // :  while y(k) < -180.0
  while (b_ob[1] < -180.0) {
    // :  y(k) = y(k) + 360.0
    b_ob[1] += 360.0;
  }

  // Gain: '<S43>/Filter Coefficient' incorporates:
  //   DiscreteIntegrator: '<S35>/Filter'
  //   Gain: '<S34>/Derivative Gain'
  //   Sum: '<S35>/SumD'

  ob[1] = (0.0125 * b_ob[1] - rtDW.Filter_DSTATE[1]) * 100.0;

  // Gain: '<S38>/Proportional Gain' incorporates:
  //   DiscreteIntegrator: '<S40>/Integrator'
  //   Sum: '<S49>/Sum'

  absx = ((b_ob[1] + rtDW.Integrator_DSTATE[1]) + ob[1]) * 0.005;

  // DeadZone: '<S33>/DeadZone'
  if (absx > 0.0102) {
    od_idx_1 = absx - 0.0102;
  } else if (absx >= -0.0102) {
    od_idx_1 = 0.0;
  } else {
    od_idx_1 = absx - -0.0102;
  }

  // RelationalOperator: '<S31>/NotEqual' incorporates:
  //   Gain: '<S31>/ZeroGain'

  rtb_NotEqual_idx_0 = (0.0 * absx != od_idx_1);

  // Signum: '<S31>/SignPreSat'
  if (od_idx_1 < 0.0) {
    od_idx_1 = -1.0;
  } else if (od_idx_1 > 0.0) {
    od_idx_1 = 1.0;
  } else if (od_idx_1 == 0.0) {
    od_idx_1 = 0.0;
  } else {
    od_idx_1 = (rtNaN);
  }

  // DataTypeConversion: '<S31>/DataTypeConv1'
  rtb_DataTypeConv1_idx_0 = static_cast<int8_T>(od_idx_1);

  // Gain: '<S37>/Integral Gain'
  od_idx_1 = 0.5 * b_ob[1];

  // Update for DiscreteIntegrator: '<S35>/Filter'
  rtDW.Filter_DSTATE[1] += 0.001 * ob[1];

  // Signum: '<S31>/SignPreIntegrator'
  if (od_idx_1 < 0.0) {
    rtb_Product3 = -1.0;
  } else if (od_idx_1 > 0.0) {
    rtb_Product3 = 1.0;
  } else if (od_idx_1 == 0.0) {
    rtb_Product3 = 0.0;
  } else {
    rtb_Product3 = (rtNaN);
  }

  // Switch: '<S31>/Switch' incorporates:
  //   Constant: '<S31>/Constant1'
  //   DataTypeConversion: '<S31>/DataTypeConv2'
  //   Logic: '<S31>/AND3'
  //   RelationalOperator: '<S31>/Equal1'

  if (rtb_NotEqual_idx_0 && (rtb_DataTypeConv1_idx_0 == static_cast<int8_T>
       (rtb_Product3))) {
    od_idx_1 = 0.0;
  }

  // Update for DiscreteIntegrator: '<S40>/Integrator'
  rtDW.Integrator_DSTATE[1] += 0.001 * od_idx_1;

  // Saturate: '<S47>/Saturation'
  if (absx > 0.0102) {
    // Outport: '<Root>/Tau+'
    rtY.Tau[1] = 0.0102;
  } else if (absx < -0.0102) {
    // Outport: '<Root>/Tau+'
    rtY.Tau[1] = -0.0102;
  } else {
    // Outport: '<Root>/Tau+'
    rtY.Tau[1] = absx;
  }

  // Outport: '<Root>/ypr_meas' incorporates:
  //   Gain: '<S1>/Gain3'
  //   Trigonometry: '<S57>/trigFcn'

  rtY.ypr_meas[1] = 57.295779513082323 * std::asin(od);

  // MATLAB Function: '<S1>/wrapTo180' incorporates:
  //   Inport: '<Root>/theta'
  //   Sum: '<S1>/Sum'

  b_ob[2] -= rtU.theta[2];

  // :  while y(k) > 180.0
  while (b_ob[2] > 180.0) {
    // :  y(k) = y(k) - 360.0
    b_ob[2] -= 360.0;
  }

  // :  while y(k) < -180.0
  while (b_ob[2] < -180.0) {
    // :  y(k) = y(k) + 360.0
    b_ob[2] += 360.0;
  }

  // Gain: '<S43>/Filter Coefficient' incorporates:
  //   DiscreteIntegrator: '<S35>/Filter'
  //   Gain: '<S34>/Derivative Gain'
  //   Sum: '<S35>/SumD'

  ob[2] = (0.0125 * b_ob[2] - rtDW.Filter_DSTATE[2]) * 100.0;

  // Gain: '<S38>/Proportional Gain' incorporates:
  //   DiscreteIntegrator: '<S40>/Integrator'
  //   Sum: '<S49>/Sum'

  absx = ((b_ob[2] + rtDW.Integrator_DSTATE[2]) + ob[2]) * 0.005;

  // DeadZone: '<S33>/DeadZone'
  if (absx > 0.0102) {
    od_idx_2 = absx - 0.0102;
  } else if (absx >= -0.0102) {
    od_idx_2 = 0.0;
  } else {
    od_idx_2 = absx - -0.0102;
  }

  // RelationalOperator: '<S31>/NotEqual' incorporates:
  //   Gain: '<S31>/ZeroGain'

  rtb_NotEqual_idx_0 = (0.0 * absx != od_idx_2);

  // Signum: '<S31>/SignPreSat'
  if (od_idx_2 < 0.0) {
    od_idx_2 = -1.0;
  } else if (od_idx_2 > 0.0) {
    od_idx_2 = 1.0;
  } else if (od_idx_2 == 0.0) {
    od_idx_2 = 0.0;
  } else {
    od_idx_2 = (rtNaN);
  }

  // DataTypeConversion: '<S31>/DataTypeConv1'
  rtb_DataTypeConv1_idx_0 = static_cast<int8_T>(od_idx_2);

  // Gain: '<S37>/Integral Gain'
  od_idx_2 = 0.5 * b_ob[2];

  // Update for DiscreteIntegrator: '<S35>/Filter'
  rtDW.Filter_DSTATE[2] += 0.001 * ob[2];

  // Signum: '<S31>/SignPreIntegrator'
  if (od_idx_2 < 0.0) {
    rtb_Product3 = -1.0;
  } else if (od_idx_2 > 0.0) {
    rtb_Product3 = 1.0;
  } else if (od_idx_2 == 0.0) {
    rtb_Product3 = 0.0;
  } else {
    rtb_Product3 = (rtNaN);
  }

  // Switch: '<S31>/Switch' incorporates:
  //   Constant: '<S31>/Constant1'
  //   DataTypeConversion: '<S31>/DataTypeConv2'
  //   Logic: '<S31>/AND3'
  //   RelationalOperator: '<S31>/Equal1'

  if (rtb_NotEqual_idx_0 && (rtb_DataTypeConv1_idx_0 == static_cast<int8_T>
       (rtb_Product3))) {
    od_idx_2 = 0.0;
  }

  // Update for DiscreteIntegrator: '<S40>/Integrator'
  rtDW.Integrator_DSTATE[2] += 0.001 * od_idx_2;

  // Saturate: '<S47>/Saturation'
  if (absx > 0.0102) {
    // Outport: '<Root>/Tau+'
    rtY.Tau[2] = 0.0102;
  } else if (absx < -0.0102) {
    // Outport: '<Root>/Tau+'
    rtY.Tau[2] = -0.0102;
  } else {
    // Outport: '<Root>/Tau+'
    rtY.Tau[2] = absx;
  }

  // Outport: '<Root>/ypr_meas' incorporates:
  //   Fcn: '<S3>/fcn5'
  //   Gain: '<S1>/Gain3'
  //   Trigonometry: '<S57>/Trigonometric Function3'

  rtY.ypr_meas[2] = 57.295779513082323 * rt_atan2d_snf(theta, ((b_oc_idx_0 -
    b_oc_idx_1) - p_idx_5) + b_oc_idx_2);

  // Outport: '<Root>/Cycles' incorporates:
  //   MATLAB Function: '<S1>/motors2quat'

  rtY.Cycles = cycles;

  // End of Outputs for SubSystem: '<Root>/Position_Controller'
}

// Model initialize function
void Position_ControllerModelClass::initialize()
{
  // Registration code

  // initialize non-finites
  rt_InitInfAndNaN(sizeof(real_T));

  // SystemInitialize for Atomic SubSystem: '<Root>/Position_Controller'
  // SystemInitialize for MATLAB Function: '<S1>/motors2quat'
  // :  T = quaternion(1,0,0,0);
  rtDW.T.a = 1.0;
  rtDW.T.b = 0.0;
  rtDW.T.c = 0.0;
  rtDW.T.d = 0.0;

  // End of SystemInitialize for SubSystem: '<Root>/Position_Controller'
  // :  singularity_reg = 0;
}

// Constructor
Position_ControllerModelClass::Position_ControllerModelClass() :
  rtU(),
  rtY(),
  rtDW(),
  rtM()
{
  // Currently there is no constructor body generated.
}

// Destructor
Position_ControllerModelClass::~Position_ControllerModelClass()
{
  // Currently there is no destructor body generated.
}

// Real-Time Model get method
Position_ControllerModelClass::RT_MODEL * Position_ControllerModelClass::getRTM()
{
  return (&rtM);
}

//
// File trailer for generated code.
//
// [EOF]
//
