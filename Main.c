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

//! \file main.c 
//!
//! \brief  
//! 
//! \created on: May 12, 2015
//! \    author: LP
//!
//! (C) Copyright 2015, Oregon Tech.

// **************************************************************************
// the includes

#include "F28x_Project.h"     // Device Headerfile and Examples Include File
#include "system-init.h"
#include "ti-sfo-v8.h"
#include "user.h"
#include "oit-gpio.h"
#include "ctrl.h"
#include "oit-math.h"

// **************************************************************************
// the defines

// **************************************************************************
// the typedefs

// **************************************************************************
// the globals

CTRL_Obj ctrl;
CTRL_Handle ctrlHandle;

//==========temporary vars for debug only

uint32_t gMainPWM_Compare = 0;
uint16_t gMainPWM_Period = 667;
uint16_t gMainPWM_PeriodLong = 667;
uint16_t gMainPWM_PeriodShort = 80;
uint16_t gMainPWM_Phase2Shift = 0;
uint16_t gMainPWM_Phase3Shift = 0;
uint16_t gMainPWM_RED     = 3;
uint16_t gMainPWM_REDHR   = 128;
uint16_t gMainPWM_FED     = 3;
uint16_t gMainPWM_FEDHR   = 128;


float_t gScaleLow	= 0.1;
float_t gScaleHi	= 0.9;

// **************************************************************************
// the local function prototypes





// **************************************************************************
// the functions

void main()
{
	System_init();

	ctrlHandle = CTRL_init(&ctrl, sizeof(ctrl));

	CTRL_setDefaultParams(ctrlHandle);

	while(1)
	{

		{
			CTRL_SinCycleState_e current_state, next_state;

			current_state = CTRL_getCurrentSinCycleState(ctrlHandle);
			next_state    = CTRL_getNextSinCycleState(ctrlHandle);


		}


		PWM_update_scale_factor_optimizer();
	}

}


__interrupt void cpu_timer2_isr(void)
{



	GPIO_setHigh(GPIO_LED_WHITE);

//========= do the job according to state and next state

	CTRL_SinCycleState_e next_state    = CTRL_getNextSinCycleState(ctrlHandle);
	CTRL_SinCycleState_e current_state = CTRL_getCurrentSinCycleState(ctrlHandle);

	if(current_state != next_state)
//	if(CTRL_getCurrentSinCycleState(ctrlHandle) != next_state)
	{

		CTRL_doChangeSinCycleState(ctrlHandle, next_state);
//			GPIO_toggle(GPIO_LED_BLUE);
		current_state = next_state;
	}



 	if(current_state == CTRL_SinCycleState_Positive){
 		gMainPWM_Period = gMainPWM_PeriodLong;
 		gMainPWM_Compare =  gScaleLow *((uint32_t)gMainPWM_Period << 16);

 	}else {
 		gMainPWM_Period = gMainPWM_PeriodShort;
 		gMainPWM_Compare =  gScaleHi *((uint32_t)gMainPWM_Period << 16);
 	}
 	gMainPWM_Phase2Shift = MATH_ONE_OVER_THREE * gMainPWM_Period;
 	gMainPWM_Phase3Shift = MATH_TWO_OVER_THREE * gMainPWM_Period;


	EPwm1Regs.CMPA.all= gMainPWM_Compare;
	EPwm1Regs.TBPRD   = gMainPWM_Period;
	EPwm2Regs.TBPHS.bit.TBPHS = gMainPWM_Phase2Shift;
	EPwm3Regs.TBPHS.bit.TBPHS = gMainPWM_Phase3Shift;

	EPwm1Regs.DBRED = gMainPWM_RED;
	EPwm1Regs.DBREDHR.bit.DBREDHR = gMainPWM_REDHR;
	EPwm2Regs.DBRED = gMainPWM_RED;
	EPwm2Regs.DBREDHR.bit.DBREDHR = gMainPWM_REDHR;
	EPwm3Regs.DBRED = gMainPWM_RED;
	EPwm3Regs.DBREDHR.bit.DBREDHR = gMainPWM_REDHR;

	EPwm1Regs.DBFED = gMainPWM_FED;
	EPwm1Regs.DBFEDHR.bit.DBFEDHR = gMainPWM_FEDHR;
	EPwm2Regs.DBFED = gMainPWM_FED;
	EPwm2Regs.DBFEDHR.bit.DBFEDHR = gMainPWM_FEDHR;
	EPwm3Regs.DBFED = gMainPWM_FED;
	EPwm3Regs.DBFEDHR.bit.DBFEDHR = gMainPWM_FEDHR;





//================ managing state changes

	static uint16_t line_freq_cnt = 0;
	if(line_freq_cnt++ == 166){
		line_freq_cnt = 0;
		//EPwm1Regs.TBCTL.bit.SWFSYNC = 1;                // Synchronize high resolution phase to start HR period
	}

	switch (line_freq_cnt) {
	case 0: //begin of positive cycle
		CTRL_setNextSinCycleState(ctrlHandle, CTRL_SinCycleState_Positive);

		break;
	case 83: //begin of negative cycle
		CTRL_setNextSinCycleState(ctrlHandle, CTRL_SinCycleState_Negative);

		break;
	default:
		break;
	}


	GPIO_setLow(GPIO_LED_WHITE);

   // The CPU acknowledges the interrupt.
}


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


