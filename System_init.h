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


#ifndef _SYSTEM_INIT_H_
#define _SYSTEM_INIT_H_

//! \file System_init.h 
//!
//! \brief  
//! 
//! \created on: Mar 20, 2015
//! \    author: LP
//!
//! (C) Copyright 2015, Oregon Tech.


// **************************************************************************
// the includes



//!
//!
//! \defgroup SYSTEM_INIT_H_
//!
//@{


#ifdef __cplusplus
extern "C" {
#endif

// **************************************************************************
// the defines

#define CPU_FREQ_MHZ		(200)
#define MAIN_ISR_FREQ_KHZ	(10)
// 1Khz -> 1000us
// 10khz ~ 100us

#define ADC_ACQUISITION_TIME	(68)

// these are calibrations from excel linear curve fitting
// y = 0.0771x + 0.5767
#define ADC_OUTPUTVOLTAGE_SCALE		(0.07718032)
#define ADC_OUTPUTVOLTAGE_OFFSET	(0.55603538)

//#define ADC_OUTPUTCURRENT_SCALE		(0.011855177)
//#define ADC_OUTPUTCURRENT_OFFSET	(-24.08506063)

#define ADC_OUTPUTCURRENT_SCALE		(-11.86554317)
#define ADC_OUTPUTCURRENT_OFFSET	(24146.76446)

#define ADC_INPUTVOLTAGE_SCALE		(0.077016977)
#define ADC_INPUTVOLTAGE_OFFSET		(0.588170892)



// **************************************************************************
// the typedefs

// **************************************************************************
// the globals

// **************************************************************************
// the function prototypes

extern void System_init(void);

#ifdef __cplusplus
}
#endif // extern "C"

//@} // ingroup
#endif // end of _SYSTEM_INIT_H_ definition
