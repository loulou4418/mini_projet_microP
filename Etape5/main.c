/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * This is a bare minimum user application template.
 *
 * For documentation of the board, go \ref group_common_boards "here" for a link
 * to the board-specific documentation.
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# Minimal main function that starts with a call to system_init()
 * -# Basic usage of on-board LED and button
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
#include <asf.h>
#include "conf_projet.h"
#include "calcul_gabarit.h"
#include "PWM.h"

uint16_t g_VPalier;

void procedure_traitement_IT(void);
uint16_t get_VPalier(void);
void set_VPalier(uint16_t VPalier);


int main (void)
{
	system_init();
	
	config_GCLK_TC6();
	config_PM();
	config_PORT();
	config_TC6();
	
	configure_TC6_IT();
	
	config_DAC();
	
	config_PWM ();

	system_interrupt_enable(SYSTEM_INTERRUPT_MODULE_TC6);


	/* Insert application code here, after the board has been initialized. */
	
	set_VPalier(5000);

	/* This skeleton code simply sets the LED to the state of the button. */
	while (1) {

		/* Is button pressed? */
		if (port_pin_get_input_level(BUTTON_0_PIN) == BUTTON_0_ACTIVE) {
			/* Yes, so turn LED on. */
			port_pin_set_output_level(LED_0_PIN, LED_0_ACTIVE);
		} else {
			/* No, so turn LED off. */
			port_pin_set_output_level(LED_0_PIN, !LED_0_ACTIVE);
		}
	}
} 

void procedure_traitement_IT(void){
	Port *ptr_Port = PORT;

	ptr_Port->Group[1].OUTTGL.reg = PORT_PB06;
}

void TC6_Handler(void){
	uint16_t Vconsigne ;
	Tc *ptr_TC;
	Dac * ptr_DAC;
	
	/* write port to check */
	procedure_traitement_IT();
	
	/* Calcul gabarit */
	Vconsigne = calcul_gabarit (get_VPalier());
	
	/* Write Dac to check */
	ptr_DAC = DAC;
	ptr_DAC -> DATA.reg = Vconsigne*DAC_RESOLUTION/V_MAX;
	
	/* Control moteur */
	write_PWM(Vconsigne);
	
	/* clear flag interrupt timer */
	ptr_TC = TC6;
	ptr_TC->COUNT16.INTFLAG.reg = TC_INTFLAG_MC0;
}

uint16_t get_VPalier(){
	return g_VPalier;
}
void set_VPalier(uint16_t VPalier){
	g_VPalier = VPalier;
}

