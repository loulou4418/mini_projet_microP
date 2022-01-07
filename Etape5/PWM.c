/*
 * PWM.c
 *
 * Created: 07/01/2022 08:28:39
 *  Author: e182232d
 */ 
#include "PWM.h"

void config_PWM (void){
	Tc *ptr_TC = TC7 ;
	
	ptr_TC -> COUNT16.CTRLA.reg = TC_CTRLA_PRESCSYNC_PRESC |
	TC_CTRLA_NORUNSTDBY |
	TC_CTRLA_PRESCALER_DIV1 |
	TC_CTRLA_WAVEGEN_MPWM |
	TC_CTRLA_MODE_COUNT16 |
	TC_CTRLA_NOENABLE |
	TC_CTRLA_NOSWRST;
	
	ptr_TC -> COUNT16.CTRLC.reg = TC_CTRLC_NOCPTEN0 |
	TC_CTRLC_NOCPTEN1 |
	TC_CTRLC_NOINVEN0 |
	TC_CTRLC_NOINVEN1;
	
	ptr_TC -> COUNT16.CTRLBCLR.reg = TC_CTRLBCLR_CMD_NONE |
	TC_CTRLBCLR_ONESHOT |
	TC_CTRLBCLR_NODIR;
	
	ptr_TC -> COUNT16.CC[0].reg = TC_CC0_Val; // 10kHz
	ptr_TC -> COUNT16.CC[1].reg = 400; // duty 50%
	
	ptr_TC -> COUNT16.CTRLA.reg |= TC_CTRLA_ENABLE;
}

void write_PWM (uint16_t duty){
	Tc *ptr_TC = TC7 ;
	
	ptr_TC -> COUNT16.CC[1].reg = (duty * TC_CC0_Val) / V_MAX;
}