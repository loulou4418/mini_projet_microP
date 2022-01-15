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

void procedure_traitement_IT(void);
uint16_t calcul_gabarit ();

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

	//Faire l'interruption
	system_interrupt_enable(SYSTEM_INTERRUPT_MODULE_TC6);


	/* Insert application code here, after the board has been initialized. */

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
	Tc *ptr_TC = TC6;
	Dac * ptr_DAC;

	procedure_traitement_IT();
	
	ptr_DAC = DAC;
	ptr_DAC -> DATA.reg = calcul_gabarit ();

	ptr_TC->COUNT16.INTFLAG.reg = TC_INTFLAG_MC0;
}

uint16_t calcul_gabarit (){
		typedef enum state_t
		{
			WAIT,
			RISE,
			CTE,
			FALL
		} state_t;

		static state_t state = WAIT;
		static uint16_t time = 0;
		static uint16_t DACValue = 0;

		switch (state)
		{
			case WAIT:
			time++;
			if (time >= 64)
			{
				state = RISE;
				time = 0;
			}
			break;

			case RISE:
			time ++;
			if (DACValue < (1024 - 8)){
				DACValue += 8;
			}
			if (time >= 128)
			{
				state = CTE;
				DACValue = 1023;
				time = 0;
			}
			break;

			case CTE:
			time++;
			if (time >= 512)
			{
				state = FALL;
				time = 0;
			}
			break;

			case FALL:
			time++;
			if(DACValue > (0 + 8)){
				DACValue -= 8;
			}
			/* time : 1023/8 = 128 */
			if (time >= 128)
			{
				state = WAIT;
				DACValue = 0;
				time = 0;
			}
			break;

			/* Etat defaut = erreur raz variables */
			default:
			state = WAIT;
			time = 0;
			DACValue = 0;
			break;
		}
	return DACValue;
}