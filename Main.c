/*
 * Main.c
 *
 *  Created on: Mar 20, 2015
 *      Author: Jack
 */


// **************************************************************************
// the includes

// system includes
#include <math.h>
#include "main.h"
#include "system_init.h"
#include "ot_pwm.h"
#include "InterruptServiceRoutines.h"
// **************************************************************************
// the defines



// **************************************************************************
// the globals
//extern float_t gOutputVoltageCounts;
extern uint16_t gAdcBuf_OutputVoltage[ADC_BUF_LEN];
//uint_least16_t gCounter_updateGlobals = 0;

//bool Flag_Latch_softwareUpdate = true;

//CTRL_Handle ctrlHandle;


//USER_Params gUserParams;

//HAL_PwmData_t gPwmData = {_IQ(0.0), _IQ(0.0), _IQ(0.0)};
//
//HAL_AdcData_t gAdcData;
//
//_iq gMaxCurrentSlope = _IQ(0.0);


// Declare your function prototypes here
//---------------------------------------------------------------

//void Calculate_optimal_freq();
//void Calculate_optimal_freq3();
void Calculate_optimal_freqV2();
void Calculate_optimal_freq_directCMPA();
// General System variables - useful for debug
void Calculate_optimal_pointV100();
void Calculate_optimal_pointV80();
void Calculate_optimal_pointV120();
void Calculate_optimal_point();
void  Calculate_optimal_pointV155();
void Calculate_optimal_points();

float_t gPulseWidth1_ns, gPulseWidth2_ns, gPeriod_ns;
float_t minDuty;
float_t maxDuty;

uint32_t Vout, VoutFilt;
uint32_t SumAdcBuf, SumAdcFiltBuf;

float_t gReferenceVoltage=38;
uint16_t gReferenceVoltageCounts;

bool_t RunPWM = 0;
bool_t gEnablePID = 0;


uint16_t SwitchingFrequencyKHz = 500;
float duty = 0.25;
float duty_increment = 0.01;
uint32_t RED_ns = 289;
//uint32_t RED_ps = 280000;
uint32_t FED_ns = 260;
//uint32_t FED_ps = 280000;

uint32_t gA1 = 1152369;
uint32_t gB1 = 1542507;
float_t  gOptimalFreq;

float_t gActualDuty;

uint16_t delay = 868;

float_t gLoadDuty=0.2;

bool_t gEnableSetFreq = 0;

float_t gTon;
uint32_t gCompareA, gPeriod;
uint32_t gCompareAManual = 2133531, gPeriodManual = 169;


float_t gRealDuty;
uint16_t grealFreqKhz;
uint32_t gRealRED_ns, gRealFED_ns;
float_t gFEDns_cal, gFEDns_cal_offset=0;


PWM_Ctrl_Obj gPWMCh123;
PWM_Ctrl_Handle gPWMCh123Handle;

static inline void PWM_set_period_compare_edgeDelay_ch123(PWM_Ctrl_Handle handle, const uint16_t periodCounts, const uint32_t compareCounts,
		const uint16_t risingEdgeDelayNs, const uint16_t fallingEdgeDelayNs)
{
	PWM_Ctrl_Obj *obj = (PWM_Ctrl_Obj *)handle;

	uint16_t redNs = risingEdgeDelayNs;
	uint16_t fedNs = fallingEdgeDelayNs;
	uint16_t minPWHighFetNs = obj->minPulseWidthHighsideFetNs;
	uint16_t minPWLowFetNs = obj->minPulseWidthLowsideFetNs;
	//uint16_t minPeriodNs = obj->minPeriodNs;

	uint16_t period_ns = (periodCounts+1) * 10;

	float_t duty = (float_t)(compareCounts)/(((uint32_t)(periodCounts+1))<<16);

	// 1. Make sure rising edge delay and falling edge delay not too big

	while((redNs + fedNs + minPWHighFetNs + minPWLowFetNs) > obj->maxPeriodNs){
		if(redNs > 80){
			redNs -= 5;
		}

		if(fedNs > 80){
			fedNs -= 5;
		}
	}

	if(redNs < obj->minRisingEdgeDelayNs){
		redNs = obj->minRisingEdgeDelayNs;
	}
	if(fedNs < obj->minFallingEdgeDelayNs){
		fedNs = obj->minFallingEdgeDelayNs;
	}

	// 2. Make sure period is not too small
	uint16_t minPeriodNs = redNs + fedNs + minPWHighFetNs + minPWLowFetNs;
	if(minPeriodNs < obj->minPeriodNs){
		minPeriodNs = obj->minPeriodNs;
	}
	uint16_t maxPeriodNs = obj->maxPeriodNs;

	if(period_ns < minPeriodNs){
		period_ns = minPeriodNs;
	}
	if(period_ns > maxPeriodNs){
		period_ns = maxPeriodNs;
	}

	// 3. Make sure duty is not too small or too large

	float_t minDuty = (float_t)(minPWHighFetNs + redNs)/period_ns;
	float_t maxDuty = 1- (float_t)(minPWLowFetNs +fedNs)/period_ns;

	if(duty>maxDuty){
		duty = maxDuty;
	}
	if(duty<minDuty){
		duty = minDuty;
	}

	// 4. Calculate value for registers
	obj->risingEdgeDelayNs = redNs;
	obj->fallingEdgeDelayNs = fedNs;

	obj->periodNs = period_ns;
	obj->periodCounts = period_ns/10 - 1; // 100Mhz => 10ns ~ 1 count
	//obj->minPeriodNs = minPeriodNs;

	obj->duty = duty;
	obj->compareCounts = (uint32_t)( duty * ((uint32_t)(obj->periodCounts + 1) << 16) ); // 32bits high resolution compare
	obj->minDuty = minDuty;
	obj->maxDuty = maxDuty;


	// 5. Write into registers
	EALLOW;
	PWM_set_rising_edge_delay_ch123_ns(obj->risingEdgeDelayNs);
	PWM_set_falling_edge_delay_ch123_ns(obj->fallingEdgeDelayNs);

	ePWM[PWM_Channel_1]->TBPRD = obj->periodCounts;
	ePWM[PWM_Channel_2]->TBPRD = obj->periodCounts;
	ePWM[PWM_Channel_3]->TBPRD = obj->periodCounts;
	ePWM[PWM_Channel_1]->CMPA.all = obj->compareCounts;
	ePWM[PWM_Channel_2]->CMPA.all = obj->compareCounts;
	ePWM[PWM_Channel_3]->CMPA.all = obj->compareCounts;
	EDIS;
}

void local_init()
{
//	gPWMCh123.actualCompareCounts = 0;
//	gPWMCh123.actualFallingEdgeDelayNs = 0;
//	gPWMCh123.actualPeriodCounts = 0;
//	gPWMCh123.actualRisingEdgeDelayNs = 0;

	gPWMCh123.compareCounts = 100 << 8;
	gPWMCh123.fallingEdgeDelayNs = 58;
	gPWMCh123.risingEdgeDelayNs = 58;
	gPWMCh123.periodCounts = 200;

	gPWMCh123.minPulseWidthHighsideFetNs = PWM_MIN_PULSE_WIDTH_HIGHSIDE_NS;
	gPWMCh123.minPulseWidthLowsideFetNs = PWM_MIN_PULSE_WIDTH_LOWSIDE_NS;
	gPWMCh123.minPeriodNs = 500; // 500ns ~2MHZ
	gPWMCh123.maxPeriodNs = 11368; // ~ 11us or 88Khz

	gPWMCh123.minRisingEdgeDelayNs = 68;
	gPWMCh123.minFallingEdgeDelayNs = 88;

	gPWMCh123Handle = (PWM_Ctrl_Handle)(&gPWMCh123);
}
void main(void)
 {

	System_init();
	//PWM_set_duty_ch123(duty);
	//GPIO_setHigh(LED1); // turn on motors

	local_init();

	while(1)
	{
		gOutputVoltageCounts = get_sum(gAdcaBufCounts, ADC_BUF_LEN) / ADC_BUF_LEN;
		gOutputCurrentCounts = get_sum(gAdcdBufCounts, ADC_BUF_LEN) / ADC_BUF_LEN;
		gInputVoltageCounts = get_sum(gAdccBufCounts, ADC_BUF_LEN) / ADC_BUF_LEN;

		gOutputVoltage = ADC_OUTPUTVOLTAGE_SCALE * gOutputVoltageCounts + ADC_OUTPUTVOLTAGE_OFFSET;
		gOutputCurrent = ADC_OUTPUTCURRENT_SCALE * gOutputCurrentCounts + ADC_OUTPUTCURRENT_OFFSET;
		gInputVoltage = ADC_INPUTVOLTAGE_SCALE * gInputVoltageCounts + ADC_INPUTVOLTAGE_OFFSET;

		//Calculate_optimal_freqV2();
		//Calculate_optimal_freq_directCMPA();
		if(gReferenceVoltage >145){
			Calculate_optimal_pointV155();
		}else if(gReferenceVoltage > 90){
			Calculate_optimal_pointV100();
		}else {
			Calculate_optimal_pointV80();
		}

//		Calculate_optimal_points();

		if(!gEnableSetFreq){
			//PWM_set_duty_frequencyKhz_deadbandNs_ch123(&duty, &SwitchingFrequencyKHz, &RED_ns, &FED_ns);
			PWM_set_period_compare_edgeDelay_ch123(gPWMCh123Handle, gPeriodManual, gCompareAManual, RED_ns, FED_ns);
		}else{
//			EPwm1Regs.TBPRD = gPeriod;
//			EPwm1Regs.CMPA.all = gCompareA;

			//PWM_set_period_compare_edgeDelay_ch123(gPWMCh123Handle, gPeriod, gCompareA, RED_ns, FED_ns);
			PWM_set_period_compare_edgeDelay_ch123(gPWMCh123Handle, gPeriod, gCompareA, RED_ns, gFEDns_cal);

		}

		//DELAY_US(500*delay);

		PWM_update_scale_factor_optimizer();

		PWM_set_duty(PWM_Channel_6, gLoadDuty);

		gPeriod_ns = (uint32_t)1000*1000/SwitchingFrequencyKHz; // period in ns
		gPulseWidth1_ns = duty*gPeriod_ns - RED_ns;
		gPulseWidth2_ns = (1-duty)*gPeriod_ns - FED_ns;

//		minDuty = (float_t)(PWM_MIN_PULSE_WIDTH_NS + RED_ps/1000)/gPeriod_ns;
//		maxDuty = 1- (float_t)(PWM_MIN_PULSE_WIDTH_NS +FED_ps/1000)/gPeriod_ns;

		//gOutputVoltageCounts = get_average(gAdcBuf_OutputVoltage, ADC_BUF_LEN);
		//TestLED();
	}


}

float_t gTonOffset = 0;
float_t gTonAddedScale = 0;
float_t gDbredOffset=0, gDbfedOffset=0;


float_t gCtrl_Ton_scale = -CTRL_TON_SCALE;
float_t gCtrl_Ton_offset = CTRL_TON_OFFSET;



float_t gPeriodOffset = 0;
float_t gCompareOffsetNs = 0;

float_t gTonScaleOffset = 0;

float_t gMaxIloadForFED = 1600;


void Calculate_optimal_freq_directCMPA()
{
	float_t Iload = gOutputCurrent;
	float_t CmpA_ns;

	CmpA_ns = (47.94232811 + gTonScaleOffset) * Iload / (gInputVoltage - gOutputVoltage) + 397.0559289 + gTonOffset ;
	//gCompareA = (uint32_t)256 * 25.6 * (gTon + gPWMCh123.risingEdgeDelayNs + gCompareOffsetNs);


	if(Iload > gMaxIloadForFED) {
		gFEDns_cal = 88;
	}else if(Iload > 0) {

		//gFEDns_cal = -0.00000006 * Iload * Iload * Iload + 0.0003 * Iload * Iload - 0.371 * Iload + 268;
		gFEDns_cal = 0.0001 * Iload * Iload -0.2685 * Iload + 258  + gFEDns_cal_offset;
	}else{

	}

	//gFEDns_cal = 0.0002 * Iload * Iload -0.3669 * Iload + 279.8 + gFEDns_cal_offset;
	//gFEDns_cal = -0.1729 * Iload  + 252.85 + gFEDns_cal_offset;


	//gPeriod = 0.094901377 *  gInputVoltage * (gTon + (gPWMCh123.risingEdgeDelayNs + gPWMCh123.fallingEdgeDelayNs)/2) / gReferenceVoltage + 10.2525457 + gPeriodOffset;
	gPeriod = 0.096894246 *  gInputVoltage * (CmpA_ns - gPWMCh123.risingEdgeDelayNs/2 + gPWMCh123.fallingEdgeDelayNs/2 ) / gReferenceVoltage + 3.717242036 + gPeriodOffset;

	gCompareA = (uint32_t)256 * 25.6 * CmpA_ns;

}

void Calculate_optimal_pointV80()
{
	float_t Iload = gOutputCurrent;
	float_t CmpA_ns;

	float_t tmp1 = Iload * 46.18125259 + 55402.8125;

	CmpA_ns = tmp1 / (gInputVoltage - gOutputVoltage) + + gTonOffset;

	//CmpA_ns = (48.53461071 + gTonScaleOffset) * tmp1 + 445 + gTonOffset ;
	//CmpA_ns = (46.07503472 + gTonScaleOffset) * tmp1 + 470.5237237 + gTonOffset ;

	if(Iload >2000){
		CmpA_ns += -0.0258 * Iload + 50;
	}else if(Iload>345){
		CmpA_ns +=12;
	}else if(Iload>0){
		CmpA_ns += 0.1855 * Iload - 52;
	}


//	CmpA_ns = 0.055608217 * tmp1 * tmp1 * tmp1
//			-2.26601401 * tmp1 * tmp1
//			+ 70.76744521 * tmp1
//			+ 513.1172458
//			 + gTonOffset ;


	if(Iload > gMaxIloadForFED) {
		gFEDns_cal = 88;
	}else if(Iload > 0) {
		gFEDns_cal = -3.56761E-07 * Iload * Iload * Iload
				+ 0.000820632 * Iload * Iload
				-0.648968734 * Iload
				+ 298.1742134
				+ gFEDns_cal_offset;
	}else{

	}

	//gPeriod = 0.099803304 *  gInputVoltage * (CmpA_ns - gPWMCh123.risingEdgeDelayNs/2 + gPWMCh123.fallingEdgeDelayNs/2 ) / gReferenceVoltage - 1.67209181 + gPeriodOffset;
	gPeriod = 0.098238221 *  gInputVoltage * (CmpA_ns - gPWMCh123.risingEdgeDelayNs/2 + gPWMCh123.fallingEdgeDelayNs/2 ) / gReferenceVoltage - 0.040395399 + gPeriodOffset;

	gCompareA = (uint32_t)256 * 25.6 * CmpA_ns;
}


void Calculate_optimal_pointV100()
{
	float_t Iload = gOutputCurrent;
	float_t CmpA_ns;


	float_t tmp1 = 45.31863744 * Iload + 56147.19338;

	CmpA_ns = tmp1/(gInputVoltage - gOutputVoltage) + gTonOffset;

//	float_t tmp1 = Iload / (gInputVoltage - gOutputVoltage);
//
//	CmpA_ns = (45.25080331 + gTonScaleOffset) * tmp1 + 582.1038287 + gTonOffset ;


//	CmpA_ns = 0.055608217 * tmp1 * tmp1 * tmp1
//			-2.26601401 * tmp1 * tmp1
//			+ 70.76744521 * tmp1
//			+ 513.1172458
//			 + gTonOffset ;


	if(Iload > gMaxIloadForFED) {
		gFEDns_cal = 88;
	}else if(Iload > 0) {
		gFEDns_cal = -1.29555E-07 * Iload * Iload * Iload
				+ 0.00041374 * Iload * Iload
				-0.455601768 * Iload
				+ 282.0711943
				+ gFEDns_cal_offset;
	}else{

	}

	gPeriod = 0.097902748 *  gInputVoltage * (CmpA_ns - gPWMCh123.risingEdgeDelayNs/2 + gPWMCh123.fallingEdgeDelayNs/2 ) / gReferenceVoltage -1.246662741 + gPeriodOffset;

	gCompareA = (uint32_t)256 * 25.6 * CmpA_ns;
}

void Calculate_optimal_pointV155()
{
	float_t Iload = gOutputCurrent;
	float_t CmpA_ns;

	float_t tmp1 = 42.55554223 * Iload + 59848.95918;

	CmpA_ns = tmp1 / (gInputVoltage - gOutputVoltage) + gTonOffset;

//	if(Iload >1000){
//		CmpA_ns += -0.026 * Iload + 45;
//	}else if(Iload>0){
//		CmpA_ns +=0.0556 * Iload - 32;
//	}

//	CmpA_ns = 0.055608217 * tmp1 * tmp1 * tmp1
//			-2.26601401 * tmp1 * tmp1
//			+ 70.76744521 * tmp1
//			+ 513.1172458
//			 + gTonOffset ;


	if(Iload > gMaxIloadForFED) {
		gFEDns_cal = 88;
	}else if(Iload > 0) {
		gFEDns_cal = -2.27393E-08 * Iload * Iload * Iload
				+ 0.000112364 * Iload * Iload
				-0.197204548 * Iload
				+ 213.8789664
				+ gFEDns_cal_offset;
	}else{

	}

	gPeriod = 0.099108986 *  gInputVoltage * (CmpA_ns - gPWMCh123.risingEdgeDelayNs/2 + gPWMCh123.fallingEdgeDelayNs/2 ) / gReferenceVoltage - 4.727105909 + gPeriodOffset;

	gCompareA = (uint32_t)256 * 25.6 * CmpA_ns;
}

void Calculate_optimal_points()
{
	float_t Iload = gOutputCurrent;
	float_t CmpA_ns;

	float_t tmp1 = Iload / (gInputVoltage - gOutputVoltage);

	float_t scaleCMP, offsetCMP;

	float_t refVout = gReferenceVoltage;
	scaleCMP = -0.050554647 * refVout + 51.05972862;

	offsetCMP = 0.001513479	* refVout * refVout * refVout
			-0.359474018 * refVout * refVout
			+32.21327167 * refVout
			-571.1445148;



	CmpA_ns = (scaleCMP) * tmp1 + offsetCMP + gTonOffset ;

//	if(Iload >1000){
//		CmpA_ns += -0.026 * Iload + 45;
//	}else if(Iload>0){
//		CmpA_ns +=0.0556 * Iload - 32;
//	}

//	CmpA_ns = 0.055608217 * tmp1 * tmp1 * tmp1
//			-2.26601401 * tmp1 * tmp1
//			+ 70.76744521 * tmp1
//			+ 513.1172458
//			 + gTonOffset ;


	if(Iload > gMaxIloadForFED) {
		gFEDns_cal = 88;
	}else if(Iload > 0) {
		gFEDns_cal = -1.09794E-07 * Iload * Iload * Iload
				+0.00038225 * Iload * Iload
				-0.448273202 * Iload
				+280.9003597
				+ gFEDns_cal_offset;
	}else{

	}

	gPeriod = 0.09799973 *  gInputVoltage * (CmpA_ns - gPWMCh123.risingEdgeDelayNs/2 + gPWMCh123.fallingEdgeDelayNs/2 ) / gReferenceVoltage + 0.194050106 + gPeriodOffset;

	gCompareA = (uint32_t)256 * 25.6 * CmpA_ns;
}
