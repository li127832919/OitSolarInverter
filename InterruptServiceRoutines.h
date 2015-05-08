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


#ifndef _INTERRUPTSERVICEROUTINES_H_
#define _INTERRUPTSERVICEROUTINES_H_

//! \file InterruptServiceRoutines.h 
//!
//! \brief  
//! 
//! \created on: Mar 22, 2015
//! \    author: LP
//!
//! (C) Copyright 2015, Oregon Tech.


// **************************************************************************
// the includes
#include "TI/pid.h"

//!
//!
//! \defgroup INTERRUPTSERVICEROUTINES_H_
//!
//@{


#ifdef __cplusplus
extern "C" {
#endif

// **************************************************************************
// the defines

#define LED_BLINK_FREQ_HZ   		(5)
#define ADC_BUF_LEN			(38)

#define ADC_NUMBER_OF_SAMPLES_PER_INT	(16)

#define PID_BANDGAP_VOLS		(0.5)
#define MAX_INPUT_VOLTAGE		(200)

// **************************************************************************
// the typedefs

// **************************************************************************
// the globals
extern 	PID_Obj		gPIDOutputVoltage;
extern  PID_Handle	gPIDOutputVoltageHandle;

extern float_t gOutputVoltage, gOutputCurrent, gInputVoltage;
extern uint16_t gOutputVoltageCounts, gOutputCurrentCounts, gInputVoltageCounts;

extern uint16_t gAdcaBufCounts[ADC_BUF_LEN];
extern uint16_t gAdccBufCounts[ADC_BUF_LEN];
extern uint16_t gAdcdBufCounts[ADC_BUF_LEN];

// **************************************************************************
// the function prototypes

//extern __interrupt void cpu_timer0_isr(void);
//extern __interrupt void cpu_timer1_isr(void);
extern __interrupt void cpu_timer2_isr(void);
//extern __interrupt void main_isr(void);
extern __interrupt void adcd_ppb_isr(void);
extern __interrupt void adcb_ppb_isr(void);

extern uint16_t get_average(uint16_t *ptr, uint16_t numberOfSample);

extern uint32_t get_sum(uint16_t *ptr, uint16_t numberOfSample);

#ifdef __cplusplus
}
#endif // extern "C"

//@} // ingroup
#endif // end of _INTERRUPTSERVICEROUTINES_H_ definition
