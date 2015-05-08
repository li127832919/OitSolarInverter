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


#ifndef _OT_ADC_H_
#define _OT_ADC_H_

//! \file ot_adc.h 
//!
//! \brief  
//! 
//! \created on: Mar 23, 2015
//! \    author: LP
//!
//! (C) Copyright 2015, Oregon Tech.


// **************************************************************************
// the includes



//!
//!
//! \defgroup OT_ADC_H_
//!
//@{


#ifdef __cplusplus
extern "C" {
#endif

// **************************************************************************
// the defines


//! \brief Defines the ADC delay for part of the ADC initialization
//!
#define ADC_DELAY_usec                 10000L

//! \brief Defines the number of ADC bits
//!
#define ADC_numBits                     12

//! \brief Defines the bias value corresponding to a voltage bias of 1.65V on the input data (3.3V input, 12 bit ADC)
//!
#define ADC_dataBias                   (1 << (ADC_numBits - 1))


//! \brief Defines the location of the INTPULSEPOS bits in the ADCTL1 register
//!
#define ADC_ADCCTL1_INTPULSEPOS_BITS       (1 << 2)

//! \brief Defines the location of the ADCPWDNZ bits in the ADCTL1 register
//!
#define ADC_ADCCTL1_ADCPWDN_BITS           (1 << 7)

//! \brief Defines the location of the ADCBSYCHAN bits in the ADCTL1 register
//!
//#define ADC_ADCCTL1_ADCBSYCHAN_BITS        (31 << 8)

//! \brief Defines the location of the ADCBSY bits in the ADCTL1 register
//!
#define ADC_ADCCTL1_ADCBSY_BITS            (1 << 13)


// **************************************************************************
// the typedefs


//! \brief Enumeration to define the ADC clock prescaler
//!
typedef enum
{
  ADC_ClockPrescaler_1=0,                     //!< Denotes Main Clock Prescaling of 0
  ADC_ClockPrescaler_2=2,
  ADC_ClockPrescaler_2_5=3,
  ADC_ClockPrescaler_3=4,
  ADC_ClockPrescaler_3_5=5,
  ADC_ClockPrescaler_4=6,
  ADC_ClockPrescaler_4_5=7,
  ADC_ClockPrescaler_5,
  ADC_ClockPrescaler_5_5,
  ADC_ClockPrescaler_6
} ADC_ClockPrescaler_e;

////! \brief Enumeration to define the analog-to-digital converter (ADC) interrupt pulse generation mode
////!
//typedef enum
//{
//  ADC_IntPulsePosition_early=0,     //!< Denotes that interrupt pulse generation occurs when the ADC begins conversion
//  ADC_IntPulsePosition_late=1       //!< Denotes that interrupt pulse generation occurs 1 cycle prior to the ADC result latching
//} ADC_IntPulseGenMode_e;


//! \brief Enumeration to define the start of conversion (SOC) trigger source
//!
typedef enum
{
  ADC_SocTrigSrc_Sw=(0 << 11),               //!< Denotes a software trigger source for the SOC flag
  ADC_SocTrigSrc_CpuTimer_0=(1 << 11),       //!< Denotes a CPUTIMER0 trigger source for the SOC flag
  ADC_SocTrigSrc_CpuTimer_1=(2 << 11),       //!< Denotes a CPUTIMER1 trigger source for the SOC flag
  ADC_SocTrigSrc_CpuTimer_2=(3 << 11),       //!< Denotes a CPUTIMER2 trigger source for the SOC flag
  ADC_SocTrigSrc_XINT2_XINT2SOC=(4 << 11),   //!< Denotes a XINT2, XINT2SOC trigger source for the SOC flag
  ADC_SocTrigSrc_EPWM1_ADCSOCA=(5 << 11),    //!< Denotes a EPWM1, ADCSOCA trigger source for the SOC flag
  ADC_SocTrigSrc_EPWM1_ADCSOCB=(6 << 11),    //!< Denotes a EPWM1, ADCSOCB trigger source for the SOC flag
  ADC_SocTrigSrc_EPWM2_ADCSOCA=(7 << 11),    //!< Denotes a EPWM2, ADCSOCA trigger source for the SOC flag
  ADC_SocTrigSrc_EPWM2_ADCSOCB=(8 << 11),    //!< Denotes a EPWM2, ADCSOCB trigger source for the SOC flag
  ADC_SocTrigSrc_EPWM3_ADCSOCA=(9 << 11),    //!< Denotes a EPWM3, ADCSOCA trigger source for the SOC flag
  ADC_SocTrigSrc_EPWM3_ADCSOCB=(10 << 11),   //!< Denotes a EPWM3, ADCSOCB trigger source for the SOC flag
  ADC_SocTrigSrc_EPWM4_ADCSOCA=(11 << 11),   //!< Denotes a EPWM4, ADCSOCA trigger source for the SOC flag
  ADC_SocTrigSrc_EPWM4_ADCSOCB=(12 << 11),   //!< Denotes a EPWM4, ADCSOCB trigger source for the SOC flag
  ADC_SocTrigSrc_EPWM5_ADCSOCA=(13 << 11),   //!< Denotes a EPWM5, ADCSOCA trigger source for the SOC flag
  ADC_SocTrigSrc_EPWM5_ADCSOCB=(14 << 11),   //!< Denotes a EPWM5, ADCSOCB trigger source for the SOC flag
  ADC_SocTrigSrc_EPWM6_ADCSOCA=(15 << 11),   //!< Denotes a EPWM6, ADCSOCA trigger source for the SOC flag
  ADC_SocTrigSrc_EPWM6_ADCSOCB=(16 << 11),   //!< Denotes a EPWM7, ADCSOCB trigger source for the SOC flag
  ADC_SocTrigSrc_EPWM7_ADCSOCA=(17 << 11),   //!< Denotes a EPWM7, ADCSOCA trigger source for the SOC flag
  ADC_SocTrigSrc_EPWM7_ADCSOCB=(18 << 11),   //!< Denotes a EPWM7, ADCSOCB trigger source for the SOC flag
  ADC_SocTrigSrc_EPWM8_ADCSOCA=(19 << 11),   //!< Denotes a EPWM8, ADCSOCA trigger source for the SOC flag
  ADC_SocTrigSrc_EPWM8_ADCSOCB=(20 << 11)    //!< Denotes a EPWM8, ADCSOCB trigger source for the SOC flag
} ADC_SocTrigSrc_e;

// **************************************************************************
// the globals

// **************************************************************************
// the function prototypes



#ifdef __cplusplus
}
#endif // extern "C"

//@} // ingroup
#endif // end of _OT_ADC_H_ definition
