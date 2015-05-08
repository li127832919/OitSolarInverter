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


#ifndef _MAIN_H_
#define _MAIN_H_

//! \file Main.h 
//!
//! \brief  
//! 
//! \created on: Mar 20, 2015
//! \    author: LP
//!
//! (C) Copyright 2015, Oregon Tech.


// **************************************************************************
// the includes


// modules

// drivers

// platforms

#include "F28x_Project.h"     // Device Headerfile and Examples Include File
#include "SFO_V8.h"
#include "ot_gpio.h"
#include "TI/types.h"

//!
//!
//! \defgroup MAIN_H_
//!
//@{


#ifdef __cplusplus
extern "C" {
#endif

// **************************************************************************
// the defines

#define CTRL_TON_SCALE			(35.9209622)
#define CTRL_TON_OFFSET			(9.061814856)

#define CTRL_TON_SCALE2			(4927.54573)
#define CTRL_TON_OFFSET2		(9.061814856)


#define CTRL_PERIOD_SCALE		(0.961071979)
#define CTRL_PERIOD_OFFSET		(7.083119)




// **************************************************************************
// the typedefs

// **************************************************************************
// the globals

extern float duty;
extern float_t gReferenceVoltage;
extern uint16_t gReferenceVoltageCounts;
extern bool_t gEnablePID;

extern float_t gReferenceLoadCurrent;
extern bool_t gEnableLoadPID;
extern float_t gLoadDuty;


extern float_t gTon;
// **************************************************************************
// the function prototypes



#ifdef __cplusplus
}
#endif // extern "C"

//@} // ingroup
#endif // end of _MAIN_H_ definition
