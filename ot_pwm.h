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


#ifndef _OT_PWM_H_
#define _OT_PWM_H_

//! \file ot_pwm.h 
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
#include "SFO_V8.h"
#include "TI/types.h"
//#include "../TI/pwm.h"

//!
//!
//! \defgroup OT_PWM_H_
//!
//@{


#ifdef __cplusplus
extern "C" {
#endif

// **************************************************************************
// the defines

//#define PWM_MAX_DUTYCYCLE		0.95
//#define PWM_MIN_DUTYCYCLE		0.05
//#define PWM_MIN_PULSE_WIDTH_NS		(38)
#define PWM_MIN_PULSE_WIDTH_HIGHSIDE_NS	(38)
#define PWM_MIN_PULSE_WIDTH_LOWSIDE_NS	(28)
//TODO: different pulse width for high & low side


// **************************************************************************
// the typedefs

//! \brief Enumeration to define PWM channel
//!
typedef enum
{
	PWM_Channel_All=0,
	PWM_Channel_1,
	PWM_Channel_2,
	PWM_Channel_3,
	PWM_Channel_4,
	PWM_Channel_5,
	PWM_Channel_6,
	PWM_Channel_7,
	PWM_Channel_8,
	PWM_Channel_Max = PWM_Channel_8
} PWM_Channel_e;

//! \brief Defines the PWM controller object
//!
typedef struct _PWM_Ctrl_Obj_
{
	uint16_t periodCounts;
	uint16_t periodNs;
	uint32_t compareCounts;
	uint16_t risingEdgeDelayNs;
	uint16_t fallingEdgeDelayNs;

	float_t duty;
//	uint16_t actualPeriodCounts;
//	uint32_t actualCompareCounts;
//	uint32_t actualRisingEdgeDelayNs;
//	uint32_t actualFallingEdgeDelayNs;

	uint16_t minPulseWidthHighsideFetNs;
	uint16_t minPulseWidthLowsideFetNs;

	uint16_t minPeriodNs;
	uint16_t maxPeriodNs;
	float_t minDuty;
	float_t maxDuty;

	uint16_t minRisingEdgeDelayNs;
	uint16_t minFallingEdgeDelayNs;


} PWM_Ctrl_Obj;

//! \brief Defines the PWM control handle
//!
typedef struct _PWM_Ctrl_Obj_ *PWM_Ctrl_Handle;

// **************************************************************************
// the globals

extern uint16_t gMinPulseWidthHighSide_ns;
extern uint16_t gMinPulseWidthLowSide_ns;

//====================================================================
// The following declarations are required in order to use the SFO
// library functions:
//
extern int MEP_ScaleFactor; // Global variable used by teh SFO library
// Result can be used for all HRPWM channels
// This variable is also copied to HRMSTEP
// register by SFO() function.

// Array of pointers to EPwm register structures:
// *ePWM[0] is defined as dummy value not used in the example
extern volatile struct EPWM_REGS *ePWM[PWM_CH];
//====================================================================

// **************************************************************************
// the function prototypes

// functions for scale factor optimizer
extern void PWM_init_scale_factor_optimizer();
extern void PWM_update_scale_factor_optimizer();
extern void PWM_scale_factor_optimizer_error(void); // it will hang if error


////! \brief     Gets the value of the Counter Compare A hardware
////! \param[in] pwmHandle  The pulse width modulation (PWM) object handle
////! \return    The CMPA value
//static inline uint32_t PWM_get_CmpA(volatile struct EPWM_REGS *pwm)
//{
//    return *pwm->CMPA.all;
//} // end of PWM_get_CmpA() function
//
//
////! \brief     Writes the pulse width modulation (PWM) data value to the Counter Compare A hardware
////! \param[in] pwmHandle  The pulse width modulation (PWM) object handle
////! \param[in] pwmData    The PWM data value
//static inline void PWM_set_CmpA(volatile struct EPWM_REGS *pwm, const uint32_t val)
//{
//    *pwm->CMPA.all = val;
//} // end of PWM_setCmpA() function



// ****************** duty cycle ************************************
static inline void PWM_set_duty(PWM_Channel_e chnl, const float fDutyFine)
{
	// TODO: add assertion to make sure 0<fDutyFine<1
	volatile struct EPWM_REGS *pwm = ePWM[chnl];

	pwm->CMPA.all = (Uint32)(fDutyFine * (((Uint32)(pwm->TBPRD)) << 16 ));
}

static inline void PWM_set_duty_ch123(const float fDutyFine)
{
	// make sure duty within range
//	if( (fDutyFine < PWM_MIN_DUTYCYCLE) || (fDutyFine > PWM_MAX_DUTYCYCLE))	{
//		return;
//	}

	PWM_set_duty(PWM_Channel_1, fDutyFine);
	PWM_set_duty(PWM_Channel_2, fDutyFine);
	PWM_set_duty(PWM_Channel_3, fDutyFine);
}

static inline void PWM_set_duty_min_pulse_width_ch123(float_t *duty, const uint16_t SwitchingFrequencyKhz, const  uint32_t RED_ns, const  uint32_t FED_ns)
{
	uint16_t period_ns = (uint32_t)1000*1000/SwitchingFrequencyKhz; // period in ns

	float_t minDuty = (float_t)(gMinPulseWidthHighSide_ns + RED_ns)/period_ns;
	float_t maxDuty = 1- (float_t)(gMinPulseWidthLowSide_ns +FED_ns)/period_ns;

	float_t tmpDuty;

	if(*duty < minDuty) {
		*duty = minDuty;
	}
	if(*duty > maxDuty) {
		*duty = maxDuty;
	}
	tmpDuty = *duty;

	PWM_set_duty(PWM_Channel_1, tmpDuty);
	PWM_set_duty(PWM_Channel_2, tmpDuty);
	PWM_set_duty(PWM_Channel_3, tmpDuty);
}

// ****************** switching frequency  **************************

static inline void PWM_set_period_counts(PWM_Channel_e chnl, const uint16_t periodCounts){
	EALLOW;
	(*ePWM[chnl]).TBPRD = periodCounts;
	EDIS;
}

static inline void PWM_set_frequency_KHz(PWM_Channel_e chnl, const uint16_t frequencyKHz)
{
	uint16_t periodCounts = (uint16_t)((uint32_t)100 * 1000 / frequencyKHz - 1);

	PWM_set_period_counts(chnl, periodCounts);
}

static inline void PWM_set_frequency_ch123_KHz(const uint16_t frequencyKHz)
{
	uint16_t periodCounts = (uint16_t)((uint32_t)100 * 1000 / frequencyKHz - 1);

	PWM_set_period_counts(PWM_Channel_1, periodCounts);
	PWM_set_period_counts(PWM_Channel_2, periodCounts);
	PWM_set_period_counts(PWM_Channel_3, periodCounts);
}

// ******************** dead-band  ****************************
// ******* (rising edge delay, falling edge delay) ************

static inline void PWM_set_rising_edge_delay_ch123_ns(const uint16_t ns)
{
	uint32_t tmp = ((uint32_t)ns <<7) / 5; // 5ns per coarse step

	uint32_t tmp1 = tmp >> 7;
	uint32_t tmp2 = (tmp - (tmp1 << 7) );

	(*ePWM[PWM_Channel_1]).DBRED = tmp1;
	EPwm1Regs.DBRED = tmp1;
	EPwm1Regs.DBREDHR.bit.DBREDHR = tmp2;

	EPwm2Regs.DBRED = tmp1;
	EPwm2Regs.DBREDHR.bit.DBREDHR = tmp2;

	EPwm3Regs.DBRED = tmp1;
	EPwm3Regs.DBREDHR.bit.DBREDHR = tmp2;
}

static inline void PWM_set_rising_edge_delay_ch123_ps(const uint32_t ps)
{
	uint32_t tmp = (ps <<7) / 5000; // 5000ps per coarse step


	uint32_t tmp1 = tmp >> 7;
	uint32_t tmp2 = (tmp - (tmp1 << 7) );
	if(tmp2 > 127){
		tmp2 = 127;
	}

	EPwm1Regs.DBRED = tmp1;
	EPwm1Regs.DBREDHR.bit.DBREDHR = tmp2;

	EPwm2Regs.DBRED = tmp1;
	EPwm2Regs.DBREDHR.bit.DBREDHR = tmp2;

	EPwm3Regs.DBRED = tmp1;
	EPwm3Regs.DBREDHR.bit.DBREDHR = tmp2;
}

static inline void PWM_set_falling_edge_delay_ch123_ns(const uint16_t ns)
{
	uint32_t tmp = ((uint32_t)ns <<7) / 5; // 5ns per coarse step

	uint32_t tmp1 = tmp >> 7;
	uint32_t tmp2 = (tmp - (tmp1 << 7) );

	EPwm1Regs.DBFED = tmp1;
	EPwm1Regs.DBFEDHR.bit.DBFEDHR = tmp2;

	EPwm2Regs.DBFED = tmp1;
	EPwm2Regs.DBFEDHR.bit.DBFEDHR = tmp2;

	EPwm3Regs.DBFED = tmp1;
	EPwm3Regs.DBFEDHR.bit.DBFEDHR = tmp2;
}
static inline void PWM_set_falling_edge_delay_ch123_ps(const uint32_t ps)
{
	uint32_t tmp = (ps <<7) / 5000; // 5000ps per coarse step

	uint32_t tmp1 = tmp >> 7;
	uint32_t tmp2 = (tmp - (tmp1 << 7) );
	if(tmp2 > 127){
		tmp2 = 127;
	}

	EPwm1Regs.DBFED = tmp1;
	EPwm1Regs.DBFEDHR.bit.DBFEDHR = tmp2;

	EPwm2Regs.DBFED = tmp1;
	EPwm2Regs.DBFEDHR.bit.DBFEDHR = tmp2;

	EPwm3Regs.DBFED = tmp1;
	EPwm3Regs.DBFEDHR.bit.DBFEDHR = tmp2;
}



// TODO: check to make sure FED+RED < period
extern float_t gRealDuty;
extern uint16_t grealFreqKhz;
extern uint32_t gRealRED_ns, gRealFED_ns;

static inline void PWM_set_duty_frequencyKhz_deadbandNs_ch123(float_t *duty, uint16_t *freqKhz, uint32_t *RED_ns, uint32_t *FED_ns)
{
	uint16_t fKhz = *freqKhz;
	uint16_t period_ns = (uint32_t)1000*1000/(fKhz); // period in ns

	gRealRED_ns = *RED_ns;
	gRealFED_ns = *FED_ns;
	gRealDuty = *duty;
	grealFreqKhz = *freqKhz;

	// make sure Rising edge delay & falling edge delay not too large
	while((gRealRED_ns + gRealFED_ns + gMinPulseWidthHighSide_ns + gMinPulseWidthLowSide_ns) > period_ns){

		if(gRealRED_ns > 80){
			gRealRED_ns -= 5;
		}
		if(gRealFED_ns > 80){
			gRealFED_ns -= 5;
		}
	}

	uint32_t redNs = gRealRED_ns;
	uint32_t fedNs = gRealFED_ns;

	uint16_t minPeriod_ns = redNs + fedNs + gMinPulseWidthHighSide_ns + gMinPulseWidthLowSide_ns;

	// make sure frequency not too large
	if(period_ns < minPeriod_ns){
		period_ns = minPeriod_ns;
		grealFreqKhz = (uint32_t)1000*1000/period_ns;
	}


	float_t minDuty = (float_t)(gMinPulseWidthHighSide_ns + redNs)/period_ns;
	float_t maxDuty = 1- (float_t)(gMinPulseWidthLowSide_ns +fedNs)/period_ns;

	// make sure duty is within range
	if(gRealDuty < minDuty) {
		gRealDuty = minDuty;
	}
	if(gRealDuty > maxDuty) {
		gRealDuty = maxDuty;
	}


	float_t tmpDuty = gRealDuty;
	uint32_t tmp = (uint32_t)(period_ns*25.6); //
	uint32_t tmp1 = (tmp >> 8);
	uint32_t tmp2 = (tmp - (tmp1<<8));

	uint16_t periodCounts = tmp1 - 1;  // 100Mhz ~ 10ns
	uint16_t periodCountsHR = tmp2<<8;

	//uint16_t periodCounts = (uint16_t)((uint32_t)100 * 1000 / frequencyKHz - 1);
	EALLOW;

	PWM_set_rising_edge_delay_ch123_ns(redNs);
	PWM_set_falling_edge_delay_ch123_ns(fedNs);
	ePWM[PWM_Channel_1]->TBPRD = periodCounts;
	ePWM[PWM_Channel_2]->TBPRD = periodCounts;
	ePWM[PWM_Channel_3]->TBPRD = periodCounts;
	ePWM[PWM_Channel_1]->TBPRDHR = periodCountsHR;
	ePWM[PWM_Channel_2]->TBPRDHR = periodCountsHR;
	ePWM[PWM_Channel_3]->TBPRDHR = periodCountsHR;
	ePWM[PWM_Channel_1]->CMPA.all = (Uint32)(tmpDuty * (((Uint32)(ePWM[PWM_Channel_1]->TBPRD)) << 16 ));
	ePWM[PWM_Channel_2]->CMPA.all = (Uint32)(tmpDuty * (((Uint32)(ePWM[PWM_Channel_2]->TBPRD)) << 16 ));
	ePWM[PWM_Channel_3]->CMPA.all = (Uint32)(tmpDuty * (((Uint32)(ePWM[PWM_Channel_3]->TBPRD)) << 16 ));

	EDIS;
}



//static inline void PWM_set_period_compare_edgeDelay_ch123(PWM_Ctrl_Handle handle)
//{
//	PWM_Ctrl_Obj *obj = (PWM_Ctrl_Obj *)handle;
//
//
//
//
//}



static inline void PWM_set_frequency_ch123_HR(const uint16_t frequencyKHz)
{
	uint32_t tmp = ((uint32_t)100 * 1000 * 256 / frequencyKHz);
	uint32_t tmp1 = tmp >> 8;
	uint32_t tmp2 = (tmp - (tmp1<<8));

	EPwm1Regs.TBPRD   = tmp1 - 1;
	EPwm1Regs.TBPRDHR = tmp2;

	EPwm2Regs.TBPRD   = tmp1 - 1;
	EPwm2Regs.TBPRDHR = tmp2;

	EPwm3Regs.TBPRD   = tmp1-1;
	EPwm3Regs.TBPRDHR = tmp2;

}



#ifdef __cplusplus
}
#endif // extern "C"

//@} // ingroup
#endif // end of _OT_PWM_H_ definition
