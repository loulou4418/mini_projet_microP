/*
 * config_projet.c
 *
 * Created: 19/11/2021 09:23:12
 *  Author: e182232d
 */ 
#include "conf_projet.h"

void confiig_GCLK_TC6(void)
{
	Gclk *ptr_GCLK = GCLK;
	
	ptr_GCLK->CLKCTRL.reg = GCLK_CLKCTRL_NOWRTLOCK |
							GCLK_CLKCTRL_CLKEN |
							GCLK_CLKCTRL_GEN_GCLK0 |
							GCLK_CLKCTRL_ID_TC6_TC7 ;
	ptr_GCLK->GENCTRL.reg = GCLK_GENCTRL_NORUNSTDBY |
							GCLK_GENCTRL_NODIVSEL |
							GCLK_GENCTRL_NOOE |
							GCLK_GENCTRL_NOOOV |
							GCLK_GENCTRL_NOIDC |
							GCLK_GENCTRL_GENEN |
							GCLK_GENCTRL_SRC_OSC8M |
							GCLK_GENCTRL_ID(0);
}

void config_PM_TC6(void){
	Pm *ptr_PM = PM;
	
	ptr_PM -> CPUSEL.reg = PM_CPUSEL_CPUDIV_DIV1;
	ptr_PM -> APBCSEL.reg = PM_APBCSEL_APBCDIV_DIV1;
	ptr_PM -> APBCMASK.reg = PM_APBCMASK_TC6;
}

void config_PORT(void){
	Port *ptr_port = PORT ;
	
	ptr_port -> Group[1].DIRSET.reg = PORT_PB02 ;
	ptr_port -> Group[1].PMUX[].reg = PORT_PMUX_PMUXE_E;
	ptr_port -> Group[1].PINCFG[].reg = PORT_PINCFG_DRVLEAK |
	//A FINIR
}

void config_TC6(void){
	Tc *ptr_TC = TC6 ;
	
	ptr_TC -> COUNT16.CTRLA.reg = TC_CTRLA_PRESCSYNC_PRESC |
								  TC_CTRLA_NORUNSTDBY |
								  TC_CTRLA_PRESCALER_DIV1 |
								  TC_CTRLA_WAVEGEN_MFRQ |
								  TC_CTRLA_MODE_COUNT16 |
								  TC_CTRLA_NOENABLE |
								  TC_CTRLA_NOSWRST;
	ptr_TC -> COUNT16.CTRLC.reg = TC_CTRLC_NOCPTEN0 |
								  TC_CTRLC_NOCPTEN1 |
								  TC_CTRLC_NOINVEN0 |
								  TC_CTRLC_NOINVEN1;
	ptr_TC -> COUNT16.CTRLBCLR.reg = TC_CTRLBCLR_CMD_NONE |
									 TC_CTRLBCLR_NOONESHOT |
									 TC_CTRLBCLR_DIR;
	ptr_TC -> COUNT16.CC[0].reg = DEMIE_PERIODE_1kHz; //0X1387 (4999)_10
	
	ptr_TC -> COUNT16.CTRLA.reg |= TC_CTRLA_ENABLE;								 
								  
}