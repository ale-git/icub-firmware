//
// Non-Degree Granting Education License -- for use at non-degree
// granting, nonprofit, education, and research organizations only. Not
// for commercial or industrial use.
//
// File: AMC_BLDC_types.h
//
// Code generated for Simulink model 'AMC_BLDC'.
//
// Model version                  : 7.2
// Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
// C/C++ source code generated on : Thu Dec 14 10:44:31 2023
//
// Target selection: ert.tlc
// Embedded hardware selection: ARM Compatible->ARM Cortex-M
// Code generation objectives: Unspecified
// Validation result: Not run
//
#ifndef RTW_HEADER_AMC_BLDC_types_h_
#define RTW_HEADER_AMC_BLDC_types_h_
#include "rtwtypes.h"

// Includes for objects with custom storage classes
#include "rtw_defines.h"

//
//  Registered constraints for dimension variants

#if CAN_MAX_NUM_PACKETS <= 0
# error "The preprocessor definition 'CAN_MAX_NUM_PACKETS' must be greater than '0'"
#endif

#if CAN_MAX_NUM_PACKETS >= 16
# error "The preprocessor definition 'CAN_MAX_NUM_PACKETS' must be less than '16'"
#endif

#ifndef DEFINED_TYPEDEF_FOR_JointPositions_
#define DEFINED_TYPEDEF_FOR_JointPositions_

struct JointPositions
{
  // joint positions
  real32_T position;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_MotorSensors_
#define DEFINED_TYPEDEF_FOR_MotorSensors_

struct MotorSensors
{
  real32_T Iabc[3];

  // electrical angle = angle * pole_pairs
  real32_T angle;
  real32_T temperature;
  real32_T voltage;
  real32_T current;
  uint8_T hallABC;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SensorsData_
#define DEFINED_TYPEDEF_FOR_SensorsData_

struct SensorsData
{
  // position encoders
  JointPositions jointpositions;
  MotorSensors motorsensors;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_ControlModes_
#define DEFINED_TYPEDEF_FOR_ControlModes_

typedef enum {
  ControlModes_NotConfigured = 0,      // Default value
  ControlModes_Idle,
  ControlModes_Position,
  ControlModes_PositionDirect,
  ControlModes_Current,
  ControlModes_Velocity,
  ControlModes_Voltage,
  ControlModes_Torque,
  ControlModes_HwFaultCM
} ControlModes;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Flags_
#define DEFINED_TYPEDEF_FOR_Flags_

struct Flags
{
  // control mode
  ControlModes control_mode;
  boolean_T enable_sending_msg_status;
  boolean_T fault_button;
  boolean_T enable_thermal_protection;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_MotorConfig_
#define DEFINED_TYPEDEF_FOR_MotorConfig_

struct MotorConfig
{
  // Angular offset in degrees between the stator windings and the hall sensors. 
  real32_T hall_sens_offset;
  boolean_T has_hall_sens;
  boolean_T has_quadrature_encoder;
  boolean_T has_speed_quadrature_encoder;
  boolean_T has_torque_sens;
  boolean_T use_index;
  boolean_T enable_verbosity;
  int16_T rotor_encoder_resolution;
  int16_T rotor_index_offset;
  uint8_T encoder_tolerance;
  uint8_T pole_pairs;
  real32_T Kbemf;
  real32_T Rphase;
  real32_T Imin;
  real32_T Imax;
  real32_T Vcc;
  real32_T Vmax;
  real32_T resistance;
  real32_T inductance;
  real32_T thermal_resistance;
  real32_T thermal_time_constant;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_EstimationVelocityModes_
#define DEFINED_TYPEDEF_FOR_EstimationVelocityModes_

typedef enum {
  EstimationVelocityModes_Disabled = 0,// Default value
  EstimationVelocityModes_MovingAverage,
  EstimationVelocityModes_LeastSquares
} EstimationVelocityModes;

#endif

#ifndef DEFINED_TYPEDEF_FOR_EstimationConfig_
#define DEFINED_TYPEDEF_FOR_EstimationConfig_

struct EstimationConfig
{
  EstimationVelocityModes velocity_mode;

  // Forgetting factor in [0, 1] for exponential weighting-based estimation of RMS current value 
  real32_T current_rms_lambda;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_PIDConfig_
#define DEFINED_TYPEDEF_FOR_PIDConfig_

struct PIDConfig
{
  real32_T OutMax;
  real32_T OutMin;
  real32_T P;
  real32_T I;
  real32_T D;
  real32_T N;
  real32_T I0;
  real32_T D0;
  uint8_T shift_factor;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_Thresholds_
#define DEFINED_TYPEDEF_FOR_Thresholds_

struct Thresholds
{
  // It shall be greater than hardwareJntPosMin
  real32_T jntPosMin;

  // It shall be smaller than hardwareJntPosMax
  real32_T jntPosMax;

  // Imposed by hardware constraint
  real32_T hardwareJntPosMin;

  // Imposed by hardware constraint
  real32_T hardwareJntPosMax;

  // If robotMin == rotorMax == 0, there's no check
  real32_T rotorPosMin;

  // If robotMin == rotorMax == 0, there's no check
  real32_T rotorPosMax;

  // Can be only non-negative
  real32_T jntVelMax;

  // Timeout on reception of velocity setpoint
  // Can be only non-negative
  uint32_T velocityTimeout;

  // Current that can be kept for an indefinite period of time w/o damaging the motor
  // Expressed in [A] as all the internal computations are done this way
  // Can be only non-negative
  real32_T motorNominalCurrents;

  // Current that can be applied for a short period of time
  // Expressed in [A] as all the internal computations are done this way
  // Can be only non-negative
  real32_T motorPeakCurrents;

  // Currents over this threshold can instantaneously damages the motor
  // Expressed in [A] as all the internal computations are done this way
  // Can be only non-negative
  real32_T motorOverloadCurrents;

  // Expressed in ticks
  // Max value is 32000
  // Can be only non-negative
  uint32_T motorPwmLimit;

  // The critical temperature of the motor that triggers i2t current protection. 
  real32_T motorCriticalTemperature;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_ConfigurationParameters_
#define DEFINED_TYPEDEF_FOR_ConfigurationParameters_

struct ConfigurationParameters
{
  MotorConfig motorconfig;
  EstimationConfig estimationconfig;
  PIDConfig CurLoopPID;
  PIDConfig PosLoopPID;
  PIDConfig VelLoopPID;
  PIDConfig DirLoopPID;
  Thresholds thresholds;
  real32_T environment_temperature;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_JointVelocities_
#define DEFINED_TYPEDEF_FOR_JointVelocities_

struct JointVelocities
{
  // joint velocities
  real32_T velocity;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_MotorCurrent_
#define DEFINED_TYPEDEF_FOR_MotorCurrent_

struct MotorCurrent
{
  // motor current
  real32_T current;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_MotorTemperature_
#define DEFINED_TYPEDEF_FOR_MotorTemperature_

struct MotorTemperature
{
  // motor temperature
  real32_T temperature;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_EstimatedData_
#define DEFINED_TYPEDEF_FOR_EstimatedData_

struct EstimatedData
{
  // velocity
  JointVelocities jointvelocities;

  // filtered motor current
  MotorCurrent Iq_filtered;

  // motor temperature
  MotorTemperature motor_temperature;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_MotorVoltage_
#define DEFINED_TYPEDEF_FOR_MotorVoltage_

struct MotorVoltage
{
  // motor voltage
  real32_T voltage;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_Targets_
#define DEFINED_TYPEDEF_FOR_Targets_

struct Targets
{
  JointPositions jointpositions;
  JointVelocities jointvelocities;
  MotorCurrent motorcurrent;
  MotorVoltage motorvoltage;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_ControlOuterOutputs_
#define DEFINED_TYPEDEF_FOR_ControlOuterOutputs_

struct ControlOuterOutputs
{
  boolean_T vel_en;
  boolean_T cur_en;
  boolean_T out_en;
  boolean_T pid_reset;
  MotorCurrent motorcurrent;
  real32_T current_limiter;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_FOCSlowInputs_
#define DEFINED_TYPEDEF_FOR_FOCSlowInputs_

struct FOCSlowInputs
{
  Flags flags;
  ConfigurationParameters configurationparameters;
  EstimatedData estimateddata;
  Targets targets;
  ControlOuterOutputs controlouteroutputs;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_ControlOutputs_
#define DEFINED_TYPEDEF_FOR_ControlOutputs_

struct ControlOutputs
{
  // control effort (quadrature)
  real32_T Vq;

  // control effort (3-phases)
  real32_T Vabc[3];

  // quadrature current
  MotorCurrent Iq_fbk;

  // direct current
  MotorCurrent Id_fbk;

  // RMS of Iq
  MotorCurrent Iq_rms;

  // RMS of Id
  MotorCurrent Id_rms;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_ExternalFlags_
#define DEFINED_TYPEDEF_FOR_ExternalFlags_

struct ExternalFlags
{
  // External Fault Button (1 == pressed)
  boolean_T fault_button;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_MCControlModes_
#define DEFINED_TYPEDEF_FOR_MCControlModes_

typedef enum {
  MCControlModes_Idle = 0,             // Default value
  MCControlModes_OpenLoop = 80,
  MCControlModes_SpeedVoltage = 10,
  MCControlModes_SpeedCurrent = 11,
  MCControlModes_Current = 6,
  MCControlModes_NotConfigured = 176,
  MCControlModes_HWFault = 160
} MCControlModes;

#endif

#ifndef DEFINED_TYPEDEF_FOR_BUS_MSG_CONTROL_MODE_
#define DEFINED_TYPEDEF_FOR_BUS_MSG_CONTROL_MODE_

// Fields of a CONTROL_MODE message.
struct BUS_MSG_CONTROL_MODE
{
  // Motor selector.
  boolean_T motor;

  // Control mode.
  MCControlModes mode;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_BUS_MSG_CURRENT_LIMIT_
#define DEFINED_TYPEDEF_FOR_BUS_MSG_CURRENT_LIMIT_

// Fields of a CURRENT_LIMIT message.
struct BUS_MSG_CURRENT_LIMIT
{
  // Motor selector.
  boolean_T motor;

  // Nominal current in A.
  real32_T nominal;

  // Peak current in A.
  real32_T peak;

  // Overload current in A.
  real32_T overload;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_BUS_MSG_DESIRED_TARGETS_
#define DEFINED_TYPEDEF_FOR_BUS_MSG_DESIRED_TARGETS_

// Fields of a DESIRED_TARGETS message.
struct BUS_MSG_DESIRED_TARGETS
{
  // Target current in A.
  real32_T current;

  // Target voltage in %.
  real32_T voltage;

  // Target veocity in deg/s.
  real32_T velocity;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_BUS_MSG_PID_
#define DEFINED_TYPEDEF_FOR_BUS_MSG_PID_

// Fields of a CURRENT_PID message.
struct BUS_MSG_PID
{
  // Motor selector.
  boolean_T motor;

  // Proportional gain.
  real32_T Kp;

  // Integral gain.
  real32_T Ki;

  // Derivative gain.
  real32_T Kd;

  // Shift factor.
  uint8_T Ks;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_BUS_MSG_MOTOR_CONFIG_
#define DEFINED_TYPEDEF_FOR_BUS_MSG_MOTOR_CONFIG_

struct BUS_MSG_MOTOR_CONFIG
{
  boolean_T has_hall_sens;
  boolean_T has_quadrature_encoder;
  boolean_T has_speed_quadrature_encoder;
  boolean_T has_torque_sens;
  boolean_T use_index;
  boolean_T enable_verbosity;

  // Number of polese of the motor.
  uint8_T number_poles;

  // Encoder tolerance.
  uint8_T encoder_tolerance;

  // Resolution of rotor encoder.
  int16_T rotor_encoder_resolution;

  // Offset of the rotor encoder.
  int16_T rotor_index_offset;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_BUS_MESSAGES_RX_
#define DEFINED_TYPEDEF_FOR_BUS_MESSAGES_RX_

// Aggregate of all CAN received messages.
struct BUS_MESSAGES_RX
{
  BUS_MSG_CONTROL_MODE control_mode;
  BUS_MSG_CURRENT_LIMIT current_limit;
  BUS_MSG_DESIRED_TARGETS desired_targets;
  BUS_MSG_PID pid;
  BUS_MSG_MOTOR_CONFIG motor_config;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_BUS_MESSAGES_RX_MULTIPLE_
#define DEFINED_TYPEDEF_FOR_BUS_MESSAGES_RX_MULTIPLE_

struct BUS_MESSAGES_RX_MULTIPLE
{
  BUS_MESSAGES_RX messages[CAN_MAX_NUM_PACKETS];
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_BUS_STATUS_RX_
#define DEFINED_TYPEDEF_FOR_BUS_STATUS_RX_

// Aggregate of all events specifying types of received messages.
struct BUS_STATUS_RX
{
  boolean_T control_mode;
  boolean_T current_limit;
  boolean_T desired_targets;
  boolean_T current_pid;
  boolean_T velocity_pid;
  boolean_T motor_config;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_BUS_STATUS_RX_MULTIPLE_
#define DEFINED_TYPEDEF_FOR_BUS_STATUS_RX_MULTIPLE_

struct BUS_STATUS_RX_MULTIPLE
{
  BUS_STATUS_RX status[CAN_MAX_NUM_PACKETS];
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_CANErrorTypes_
#define DEFINED_TYPEDEF_FOR_CANErrorTypes_

typedef enum {
  CANErrorTypes_No_Error = 0,          // Default value
  CANErrorTypes_Packet_Not4Us,
  CANErrorTypes_Packet_Unrecognized,
  CANErrorTypes_Packet_Malformed,
  CANErrorTypes_Packet_MultiFunctionsDetected,
  CANErrorTypes_Mode_Unrecognized
} CANErrorTypes;

#endif

#ifndef DEFINED_TYPEDEF_FOR_BUS_CAN_RX_ERRORS_
#define DEFINED_TYPEDEF_FOR_BUS_CAN_RX_ERRORS_

// Specifies the CAN error types.
struct BUS_CAN_RX_ERRORS
{
  // True if an error has been detected.
  boolean_T event;
  CANErrorTypes type;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_BUS_CAN_RX_ERRORS_MULTIPLE_
#define DEFINED_TYPEDEF_FOR_BUS_CAN_RX_ERRORS_MULTIPLE_

struct BUS_CAN_RX_ERRORS_MULTIPLE
{
  BUS_CAN_RX_ERRORS errors[CAN_MAX_NUM_PACKETS];
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_BUS_MSG_FOC_
#define DEFINED_TYPEDEF_FOR_BUS_MSG_FOC_

// Fields of a FOC message.
struct BUS_MSG_FOC
{
  // Current feedback in A.
  real32_T current;

  // Position feedback in deg.
  real32_T position;

  // Velocity feedback in deg/s.
  real32_T velocity;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_BUS_FLAGS_TX_
#define DEFINED_TYPEDEF_FOR_BUS_FLAGS_TX_

struct BUS_FLAGS_TX
{
  boolean_T dirty;
  boolean_T stuck;
  boolean_T index_broken;
  boolean_T phase_broken;
  real32_T not_calibrated;
  boolean_T ExternalFaultAsserted;
  boolean_T UnderVoltageFailure;
  boolean_T OverVoltageFailure;
  boolean_T OverCurrentFailure;
  boolean_T DHESInvalidValue;
  boolean_T AS5045CSumError;
  boolean_T DHESInvalidSequence;
  boolean_T CANInvalidProtocol;
  boolean_T CAN_BufferOverRun;
  boolean_T SetpointExpired;
  boolean_T CAN_TXIsPasv;
  boolean_T CAN_RXIsPasv;
  boolean_T CAN_IsWarnTX;
  boolean_T CAN_IsWarnRX;
  boolean_T OverHeating;
  boolean_T ADCCalFailure;
  boolean_T I2TFailure;
  boolean_T EMUROMFault;
  boolean_T EMUROMCRCFault;
  boolean_T EncoderFault;
  boolean_T FirmwareSPITimingError;
  boolean_T AS5045CalcError;
  boolean_T FirmwarePWMFatalError;
  boolean_T CAN_TXWasPasv;
  boolean_T CAN_RXWasPasv;
  boolean_T CAN_RTRFlagActive;
  boolean_T CAN_WasWarn;
  boolean_T CAN_DLCError;
  boolean_T SiliconRevisionFault;
  boolean_T PositionLimitUpper;
  boolean_T PositionLimitLower;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_BUS_MSG_STATUS_
#define DEFINED_TYPEDEF_FOR_BUS_MSG_STATUS_

struct BUS_MSG_STATUS
{
  MCControlModes control_mode;

  // control effort (quadrature)
  real32_T pwm_fbk;
  BUS_FLAGS_TX flags;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_BUS_MESSAGES_TX_
#define DEFINED_TYPEDEF_FOR_BUS_MESSAGES_TX_

// Aggregate of all CAN transmitted messages.
struct BUS_MESSAGES_TX
{
  BUS_MSG_FOC foc;
  BUS_MSG_STATUS status;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_BUS_STATUS_TX_
#define DEFINED_TYPEDEF_FOR_BUS_STATUS_TX_

// Aggregate of all events specifying types of transmitted messages.
struct BUS_STATUS_TX
{
  boolean_T foc;
  boolean_T status;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_BUS_CAN_PACKET_
#define DEFINED_TYPEDEF_FOR_BUS_CAN_PACKET_

// Fields of a transmitted CAN packet.
struct BUS_CAN_PACKET
{
  // ID of the CAN packet.
  uint16_T ID;

  // PAYLOAD of the CAN packet.
  uint8_T PAYLOAD[8];
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_BUS_CAN_
#define DEFINED_TYPEDEF_FOR_BUS_CAN_

struct BUS_CAN
{
  // If true, the packet is available to be processed.
  boolean_T available;
  uint8_T length;
  BUS_CAN_PACKET packet;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_BUS_CAN_MULTIPLE_
#define DEFINED_TYPEDEF_FOR_BUS_CAN_MULTIPLE_

struct BUS_CAN_MULTIPLE
{
  BUS_CAN packets[CAN_MAX_NUM_PACKETS];
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_CANClassTypes_
#define DEFINED_TYPEDEF_FOR_CANClassTypes_

typedef enum {
  CANClassTypes_Motor_Control_Command = 0,// Default value
  CANClassTypes_Motor_Control_Streaming = 1,
  CANClassTypes_Analog_Sensors_Command = 2,
  CANClassTypes_Skin_Sensor_Streaming = 4,
  CANClassTypes_Inertial_Sensor_Streaming = 5,
  CANClassTypes_Future_Use = 6,
  CANClassTypes_Management_Bootloader = 7
} CANClassTypes;

#endif

// Forward declaration for rtModel
typedef struct tag_RTM_AMC_BLDC_T RT_MODEL_AMC_BLDC_T;

#endif                                 // RTW_HEADER_AMC_BLDC_types_h_

//
// File trailer for generated code.
//
// [EOF]
//
