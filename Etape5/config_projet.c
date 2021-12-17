/*
 * config_projet.c
 *
 * Created: 19/11/2021 09:23:12
 *  Author: e182232d
 */ 
#include "conf_projet.h"

void config_GCLK_TC6(void)
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
							
	/* DAC */						
	ptr_GCLK->CLKCTRL.reg = GCLK_CLKCTRL_NOWRTLOCK |
							GCLK_CLKCTRL_CLKEN |
							GCLK_CLKCTRL_GEN_GCLK1 |
							GCLK_CLKCTRL_ID_DAC ;
		
	ptr_GCLK->GENCTRL.reg = GCLK_GENCTRL_NORUNSTDBY |
							GCLK_GENCTRL_NODIVSEL |
							GCLK_GENCTRL_OE |
							GCLK_GENCTRL_NOOOV |
							GCLK_GENCTRL_NOIDC |
							GCLK_GENCTRL_GENEN |
							GCLK_GENCTRL_SRC_OSC8M |
							GCLK_GENCTRL_ID(0x1);
							
	ptr_GCLK->GENDIV.reg =	GCLK_GENDIV_ID(0x1)		|
							GCLK_GENDIV_DIV(25);
}

void config_PM(void){
	Pm *ptr_PM = PM;
	
	ptr_PM -> CPUSEL.reg = PM_CPUSEL_CPUDIV_DIV1;
	ptr_PM -> APBCSEL.reg = PM_APBCSEL_APBCDIV_DIV1;
	ptr_PM -> APBCMASK.reg |= PM_APBCMASK_TC6 | PM_APBCMASK_TC7 | PM_APBCMASK_DAC;
}

void config_PORT(void){
	Port *ptr_port = PORT ;
	
	ptr_port -> Group[1].DIRSET.reg = PORT_PB02 | PORT_PB06 ; //  PORT_PB06 6/2 ????
	ptr_port -> Group[1].PMUX[2/2].reg = PORT_PMUX_PMUXE_E;
	ptr_port -> Group[1].PINCFG[2].reg = PORT_PINCFG_DRVSTR_NO |
										  PORT_PINCFG_PULLEN_NO |
										  PORT_PINCFG_INEN_NO |
										  PORT_PINCFG_PMUXEN;
	/* PWM */									  
	ptr_port -> Group[1].DIRSET.reg =  PORT_PB01;
	ptr_port -> Group[1].PMUX[1/2].reg = PORT_PMUX_PMUXO_E;
	ptr_port -> Group[1].PINCFG[1].reg = PORT_PINCFG_DRVSTR_NO |
											PORT_PINCFG_PULLEN_NO |
											PORT_PINCFG_INEN_NO |
											PORT_PINCFG_PMUXEN;
	
	
	
	/* DAC */								  
	ptr_port -> Group[0].DIRSET.reg = PORT_PA02;
	ptr_port -> Group[0].PMUX[2/2].reg = PORT_PMUX_PMUXE_B;
	ptr_port -> Group[0].PINCFG[2].reg = PORT_PINCFG_DRVSTR_NO |
										 PORT_PINCFG_PULLEN_NO |
										 PORT_PINCFG_INEN_NO |
										 PORT_PINCFG_PMUXEN;
										 
	/* CLK DAC OUT */
	ptr_port -> Group[1].DIRSET.reg = PORT_PB15;
	ptr_port -> Group[1].PMUX[15/2].reg = PORT_PMUX_PMUXO_H;
	ptr_port -> Group[1].PINCFG[15].reg = PORT_PINCFG_DRVSTR_NO |
										 PORT_PINCFG_PULLEN_NO |
										 PORT_PINCFG_INEN_NO |
										 PORT_PINCFG_PMUXEN;
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
									 TC_CTRLBCLR_ONESHOT |
									 TC_CTRLBCLR_DIR;
	ptr_TC -> COUNT16.CC[0].reg = 7999; //0X1387 (4999)_10
	
	ptr_TC -> COUNT16.CTRLA.reg |= TC_CTRLA_ENABLE;								 
								  
}


void configure_TC6_IT(void){
	Tc *ptr_TC = TC6;

	ptr_TC->COUNT16.INTENSET.reg = TC_INTFLAG_MC0;

}

void config_DAC(void){

	Dac *ptr_DAC = DAC ;
	
	ptr_DAC ->CTRLA.reg = DAC_CTRLA_RUNSTDBY |
					  DAC_CTRLA_ENABLE |
					  DAC_CTRLA_SWRST_NO ;
	//while (ptr_DAC->STATUS.reg != 0);
	ptr_DAC ->CTRLB.reg = DAC_CTRLB_REFSEL_AVCC |
					  DAC_CTRLB_BDWP_NO |
					  DAC_CTRLB_VPD_NO |
					  DAC_CTRLB_LEFTADJ_NO |
					  DAC_CTRLB_IOEN_NO |
					  DAC_CTRLB_EOEN ;
	//while (ptr_DAC->STATUS.reg != 0);
	ptr_DAC ->DATA.reg = 0;
	
}

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
											
		ptr_TC -> COUNT16.CC[0].reg = 800; // 10kHz
		ptr_TC -> COUNT16.CC[1].reg = 400; // duty 50%
		
		ptr_TC -> COUNT16.CTRLA.reg |= TC_CTRLA_ENABLE;
}
