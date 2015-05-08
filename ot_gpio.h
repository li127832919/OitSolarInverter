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


#ifndef _OT_GPIO_H_
#define _OT_GPIO_H_

//! \file ot_gpio.h 
//!
//! \brief  
//! 
//! \created on: Mar 20, 2015
//! \    author: LP
//!
//! (C) Copyright 2015, Oregon Tech.


// **************************************************************************
// the includes
#include "F28x_Project.h"     // Device Headerfile and Examples Include File

//!
//!
//! \defgroup OT_GPIO_H_
//!
//@{


#ifdef __cplusplus
extern "C" {
#endif

// **************************************************************************
// the defines

#define LED1	13
#define LED2	14
//#define LED1	GPIO_Number_13


// **************************************************************************
// the typedefs

// **************************************************************************
// the globals

// **************************************************************************
// the function prototypes

static inline void GPIO_toggle(uint16_t gpioNumber)
{
	EALLOW;
	if(gpioNumber < 32){
		GpioDataRegs.GPATOGGLE.all = (uint32_t)1 << gpioNumber;
	} else if(gpioNumber <64) {
		GpioDataRegs.GPBTOGGLE.all =(uint32_t)1 << (gpioNumber - 32);
	} else {
		GpioDataRegs.GPCTOGGLE.all =(uint32_t)1 << (gpioNumber - 64);
	}
	EDIS;
}



static inline void GPIO_setHigh(uint16_t gpioNumber)
{

	EALLOW;

	if(gpioNumber < 32){
		GpioDataRegs.GPASET.all = (uint32_t)1 << gpioNumber;
	} else if(gpioNumber <64) {
		GpioDataRegs.GPBSET.all =(uint32_t)1 << (gpioNumber - 32);
	} else {
		GpioDataRegs.GPCSET.all =(uint32_t)1 << (gpioNumber - 64);
	}

	EDIS;

	return;
} // end of GPIO_setHigh() function


static inline void GPIO_setLow(uint16_t gpioNumber)
{
	EALLOW;

	if(gpioNumber < 32){
		GpioDataRegs.GPACLEAR.all = (uint32_t)1 << gpioNumber;
	} else if(gpioNumber <64) {
		GpioDataRegs.GPBCLEAR.all =(uint32_t)1 << (gpioNumber - 32);
	} else {
		GpioDataRegs.GPCCLEAR.all =(uint32_t)1 << (gpioNumber - 64);
	}

	EDIS;
	return;
} // end of GPIO_setLow() function


#ifdef __cplusplus
}
#endif // extern "C"

//@} // ingroup
#endif // end of _OT_GPIO_H_ definition
