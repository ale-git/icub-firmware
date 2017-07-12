/****************************************************
*  STRAIN2 board - iCub Facility - 2017             *
*  PGA308 configuration                             *
*                                                   *
*  Written by Andrea Mura                           *
*  <andrea.mura@iit.it>                             *
****************************************************/

#include "stm32l4xx_hal.h"

#ifndef PGA308_H
#define PGA308_H

#define LOW   0
#define HIGH  1

#define ZDAC  0x00
#define GDAC  0x01
#define CFG0  0x02
#define CFG1  0x03
#define CFG2  0x04
#define CHKS  0x05
#define SFTC  0x07

#define ONEW_WR			0x00
#define ONEW_RD			0x01
#define	ONEW_ACK		0
#define	ONEW_NACK		1

#define	W_STRAIN1_HIGH    HAL_GPIO_WritePin(W_STRAIN1_GPIO_Port, W_STRAIN1_Pin, GPIO_PIN_SET);
#define	W_STRAIN2_HIGH    HAL_GPIO_WritePin(W_STRAIN2_GPIO_Port, W_STRAIN2_Pin, GPIO_PIN_SET);
#define	W_STRAIN3_HIGH    HAL_GPIO_WritePin(W_STRAIN3_GPIO_Port, W_STRAIN3_Pin, GPIO_PIN_SET);
#define	W_STRAIN4_HIGH    HAL_GPIO_WritePin(W_STRAIN4_GPIO_Port, W_STRAIN4_Pin, GPIO_PIN_SET);
#define	W_STRAIN5_HIGH    HAL_GPIO_WritePin(W_STRAIN5_GPIO_Port, W_STRAIN5_Pin, GPIO_PIN_SET);
#define	W_STRAIN6_HIGH    HAL_GPIO_WritePin(W_STRAIN6_GPIO_Port, W_STRAIN6_Pin, GPIO_PIN_SET);

#define	W_STRAIN1_LOW     HAL_GPIO_WritePin(W_STRAIN1_GPIO_Port, W_STRAIN1_Pin, GPIO_PIN_RESET);
#define	W_STRAIN2_LOW     HAL_GPIO_WritePin(W_STRAIN2_GPIO_Port, W_STRAIN2_Pin, GPIO_PIN_RESET);
#define	W_STRAIN3_LOW     HAL_GPIO_WritePin(W_STRAIN3_GPIO_Port, W_STRAIN3_Pin, GPIO_PIN_RESET);
#define	W_STRAIN4_LOW     HAL_GPIO_WritePin(W_STRAIN4_GPIO_Port, W_STRAIN4_Pin, GPIO_PIN_RESET);
#define	W_STRAIN5_LOW     HAL_GPIO_WritePin(W_STRAIN5_GPIO_Port, W_STRAIN5_Pin, GPIO_PIN_RESET);
#define	W_STRAIN6_LOW     HAL_GPIO_WritePin(W_STRAIN6_GPIO_Port, W_STRAIN6_Pin, GPIO_PIN_RESET);

#define W_STRAIN1_input		LL_GPIO_SetPinMode(W_STRAIN1_GPIO_Port, W_STRAIN1_Pin, LL_GPIO_MODE_INPUT);			LL_GPIO_SetPinOutputType(W_STRAIN1_GPIO_Port, W_STRAIN1_Pin, LL_GPIO_PULL_NO);
#define W_STRAIN2_input		LL_GPIO_SetPinMode(W_STRAIN2_GPIO_Port, W_STRAIN2_Pin, LL_GPIO_MODE_INPUT);			LL_GPIO_SetPinOutputType(W_STRAIN2_GPIO_Port, W_STRAIN2_Pin, LL_GPIO_PULL_NO);
#define W_STRAIN3_input		LL_GPIO_SetPinMode(W_STRAIN3_GPIO_Port, W_STRAIN3_Pin, LL_GPIO_MODE_INPUT);			LL_GPIO_SetPinOutputType(W_STRAIN3_GPIO_Port, W_STRAIN3_Pin, LL_GPIO_PULL_NO);
#define W_STRAIN4_input		LL_GPIO_SetPinMode(W_STRAIN4_GPIO_Port, W_STRAIN4_Pin, LL_GPIO_MODE_INPUT);			LL_GPIO_SetPinOutputType(W_STRAIN4_GPIO_Port, W_STRAIN4_Pin, LL_GPIO_PULL_NO);
#define W_STRAIN5_input		LL_GPIO_SetPinMode(W_STRAIN5_GPIO_Port, W_STRAIN5_Pin, LL_GPIO_MODE_INPUT);			LL_GPIO_SetPinOutputType(W_STRAIN5_GPIO_Port, W_STRAIN5_Pin, LL_GPIO_PULL_NO);
#define W_STRAIN6_input		LL_GPIO_SetPinMode(W_STRAIN6_GPIO_Port, W_STRAIN6_Pin, LL_GPIO_MODE_INPUT);			LL_GPIO_SetPinOutputType(W_STRAIN6_GPIO_Port, W_STRAIN6_Pin, LL_GPIO_PULL_NO);

#define W_STRAIN1_output	LL_GPIO_SetPinMode(W_STRAIN1_GPIO_Port, W_STRAIN1_Pin, LL_GPIO_MODE_OUTPUT);		LL_GPIO_SetPinOutputType(W_STRAIN1_GPIO_Port, W_STRAIN1_Pin, LL_GPIO_OUTPUT_OPENDRAIN);
#define W_STRAIN2_output	LL_GPIO_SetPinMode(W_STRAIN2_GPIO_Port, W_STRAIN2_Pin, LL_GPIO_MODE_OUTPUT);		LL_GPIO_SetPinOutputType(W_STRAIN2_GPIO_Port, W_STRAIN2_Pin, LL_GPIO_OUTPUT_OPENDRAIN);
#define W_STRAIN3_output	LL_GPIO_SetPinMode(W_STRAIN3_GPIO_Port, W_STRAIN3_Pin, LL_GPIO_MODE_OUTPUT);		LL_GPIO_SetPinOutputType(W_STRAIN3_GPIO_Port, W_STRAIN3_Pin, LL_GPIO_OUTPUT_OPENDRAIN);
#define W_STRAIN4_output	LL_GPIO_SetPinMode(W_STRAIN4_GPIO_Port, W_STRAIN4_Pin, LL_GPIO_MODE_OUTPUT);		LL_GPIO_SetPinOutputType(W_STRAIN4_GPIO_Port, W_STRAIN4_Pin, LL_GPIO_OUTPUT_OPENDRAIN);
#define W_STRAIN5_output	LL_GPIO_SetPinMode(W_STRAIN5_GPIO_Port, W_STRAIN5_Pin, LL_GPIO_MODE_OUTPUT);		LL_GPIO_SetPinOutputType(W_STRAIN5_GPIO_Port, W_STRAIN5_Pin, LL_GPIO_OUTPUT_OPENDRAIN);
#define W_STRAIN6_output	LL_GPIO_SetPinMode(W_STRAIN6_GPIO_Port, W_STRAIN6_Pin, LL_GPIO_MODE_OUTPUT);		LL_GPIO_SetPinOutputType(W_STRAIN6_GPIO_Port, W_STRAIN6_Pin, LL_GPIO_OUTPUT_OPENDRAIN);

#define PGA308_DimBufferTX 4
extern uint8_t PGA308_BufferTx[PGA308_DimBufferTX];

void PGA308_init(void);
void PGA308_OneWireWrite(uint8_t CHANNEL, uint8_t REGISTER, uint16_t VALUE);
void PGA308_OneWireRead(uint8_t CHANNEL, uint8_t REGISTER);
void PGA308_OneWire(uint16_t GPIO, uint8_t IO);
void PGA308_BitValue(uint8_t channel, uint8_t value);

#define nr_adc_sample (uint16_t) 400 // number of samples for the average measure
extern uint16_t adc_values[6];           // contains all ADC channels conversion
extern uint16_t adc_sample;

typedef struct 
{
  uint32_t STRAIN1;
  uint32_t STRAIN2;
  uint32_t STRAIN3;
  uint32_t STRAIN4;
  uint32_t STRAIN5;
	uint32_t STRAIN6;
}adc_measure_t;
extern adc_measure_t adc_measure;
extern adc_measure_t mean;

typedef struct 
{
  uint32_t STRAIN1[nr_adc_sample];
  uint32_t STRAIN2[nr_adc_sample];
  uint32_t STRAIN3[nr_adc_sample];
  uint32_t STRAIN4[nr_adc_sample];
  uint32_t STRAIN5[nr_adc_sample];
	uint32_t STRAIN6[nr_adc_sample];
}fifo;
extern fifo adc_samples;

#endif
