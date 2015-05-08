/* --COPYRIGHT--,BSD
 * Copyright (c) 2015, Oregon Tech
 * Some rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Oregon Tech nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --/COPYRIGHT-- */

#include "F28x_Project.h"
#include "ot_gpio.h"
#include "ot_pwm.h"
#include "system_init.h"
#include "InterruptServiceRoutines.h"
#include "TI/pid.h"
#include "main.h"

//! \file InterruptServiceRoutines.c 
//!
//! \brief  
//! 
//! \created on: Mar 22, 2015
//! \    author: LP
//!
//! (C) Copyright 2015, Oregon Tech.

// General System variables - useful for debug

uint16_t gLEDcnt=0;

uint16_t gAdcaBufCounts[ADC_BUF_LEN];  // output voltage
uint16_t gAdccBufCounts[ADC_BUF_LEN];  // input voltage
uint16_t gAdcdBufCounts[ADC_BUF_LEN];  // output current
uint16_t gOutputVoltageCounts, gOutputCurrentCounts, gInputVoltageCounts;
float_t gOutputVoltage, gOutputCurrent, gInputVoltage;


PID_Obj		gPIDOutputVoltage;
PID_Handle	gPIDOutputVoltageHandle;

void read_adc_data(void);
uint16_t get_average(uint16_t *ptr, uint16_t numberOfSample);
uint32_t get_sum(uint16_t *ptr, uint16_t numberOfSample);
void control_output_voltage(void);


//__interrupt void cpu_timer0_isr(void)
//{
//   CpuTimer0.InterruptCount++;
//
//   // Acknowledge this interrupt to receive more interrupts from group 1
//   PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
//}

__interrupt void cpu_timer1_isr(void)
{
   CpuTimer1.InterruptCount++;
   // The CPU acknowledges the interrupt.
   //GPIO_toggle(LED1);
}

__interrupt void cpu_timer2_isr(void)
{

//   if(CpuTimer2.InterruptCount == 99999){
//	   CpuTimer2.InterruptCount = 0;
//	   GPIO_toggle(LED2);
//   }else{
//	   CpuTimer2.InterruptCount++;
//   }
	GPIO_setHigh(LED1);

	read_adc_data();
	//control_output_voltage();


	if(gLEDcnt++ > (uint_least32_t)MAIN_ISR_FREQ_KHZ*1000/LED_BLINK_FREQ_HZ)
	{
		GPIO_toggle(LED2);
		gLEDcnt=0;
	}


	GPIO_setLow(LED1);
   // The CPU acknowledges the interrupt.
}

void read_adc_data(void)
{
	static uint16_t buf_cnt = 0;

	if(buf_cnt++ == ADC_BUF_LEN){
		buf_cnt=0;
	}

	gAdcaBufCounts[buf_cnt] = get_average((uint16_t *)&AdcaResultRegs.ADCRESULT0, ADC_NUMBER_OF_SAMPLES_PER_INT);
	gAdccBufCounts[buf_cnt] = get_average((uint16_t *)&AdccResultRegs.ADCRESULT0, ADC_NUMBER_OF_SAMPLES_PER_INT);
	gAdcdBufCounts[buf_cnt] = get_average((uint16_t *)&AdcdResultRegs.ADCRESULT0, ADC_NUMBER_OF_SAMPLES_PER_INT);


//	gOutputVoltageCounts = get_sum(gAdcaBufCounts, ADC_BUF_LEN) / ADC_BUF_LEN;
//	gOutputCurrentCounts = get_sum(gAdcdBufCounts, ADC_BUF_LEN) / ADC_BUF_LEN;
//
//	gOutputVoltage = ADC_OUTPUTVOLTAGE_SCALE * gOutputVoltageCounts + ADC_OUTPUTVOLTAGE_OFFSET;
//	gOutputCurrent = ADC_OUTPUTCURRENT_SCALE * gOutputCurrentCounts + ADC_OUTPUTCURRENT_OFFSET;
}

//uint16_t MATH_abs_of(uint16_t val)
//{
//	uint16_t tmp = val;
//	if(val < 0){
//		tmp = -val;
//	}
//
//	return tmp;
//}

void control_output_voltage(void)
{


	//gReferenceVoltageCounts = 12.9455888 * gReferenceVoltage - 6.926683;

	if(gEnablePID){
		//float_t outputVoltage = (float)gOutputVoltage/ADC_OUTPUTVOLTAGE_SCALE_CNT_PER_VOLT;
		if(MATH_abs(gOutputVoltage - gReferenceVoltage) > PID_BANDGAP_VOLS){
			float_t pid_out;
			PID_run_parallel(gPIDOutputVoltageHandle, gReferenceVoltage, gOutputVoltage, 0, &pid_out);
			duty = pid_out/MAX_INPUT_VOLTAGE;
		}

	}

}

uint16_t get_average(uint16_t *ptr, uint16_t numberOfSample)
{
	uint16_t i;
	uint32_t sum = 0;

	for(i=0; i< numberOfSample; i++){
		sum+= *ptr++;
	}

	return (uint16_t)(sum/numberOfSample);
}

uint32_t get_sum(uint16_t *ptr, uint16_t numberOfSample)
{
	uint16_t i;
	uint32_t sum = 0;

	for(i=0; i< numberOfSample; i++){
		sum+= *ptr++;
	}
	return sum;
}

/// Over current protection

__interrupt void adcd_ppb_isr(void)
{
	EALLOW;
	EPwm1Regs.TZFRC.bit.OST = 1; //force PWM off
	EPwm2Regs.TZFRC.bit.OST = 1;
	EPwm3Regs.TZFRC.bit.OST = 1;
	EDIS;
	//warning, you are outside of PPB limits
	if(AdcdRegs.ADCEVTSTAT.bit.PPB1TRIPHI)
	{
		//voltage exceeded high limit
		asm("   ESTOP0");

		//clear the trip flag and continue
		AdcdRegs.ADCEVTCLR.bit.PPB1TRIPHI = 1;
	}
	if(AdcdRegs.ADCEVTSTAT.bit.PPB1TRIPLO)
	{
		//voltage exceeded low limit
		asm("   ESTOP0");

		//clear the trip flag and continue
		AdcdRegs.ADCEVTCLR.bit.PPB1TRIPLO = 1;
	}

	PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;
}

__interrupt void adcb_ppb_isr(void)
{
	EALLOW;
	EPwm1Regs.TZFRC.bit.OST = 1; //force PWM off
	EPwm2Regs.TZFRC.bit.OST = 1;
	EPwm3Regs.TZFRC.bit.OST = 1;
	EDIS;
	//warning, you are outside of PPB limits
	if(AdcbRegs.ADCEVTSTAT.bit.PPB1TRIPHI)
	{
		//voltage exceeded high limit
		asm("   ESTOP0");

		//clear the trip flag and continue
		AdcbRegs.ADCEVTCLR.bit.PPB1TRIPHI = 1;
	}
	if(AdcbRegs.ADCEVTSTAT.bit.PPB1TRIPLO)
	{
		//voltage exceeded low limit
		asm("   ESTOP0");

		//clear the trip flag and continue
		AdcbRegs.ADCEVTCLR.bit.PPB1TRIPLO = 1;
	}

	PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;
}
