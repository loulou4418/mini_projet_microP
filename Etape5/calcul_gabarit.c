/*
 * calcul_gabarit.c
 *
 * Created: 17/12/2021 10:19:05
 *  Author: e182232d
 */
#include "calcul_gabarit.h"

uint16_t calcul_gabarit (uint16_t VPalier){
	
	static uint16_t Temps = 0;
	static enum state_t state = Repos;
	static uint16_t Vconsigne = 0;
	
	switch (state)
	{
		case Repos :
		Vconsigne = 0;
		Temps ++;
		if(Temps >= 64){
			state = Accel;
			Temps = 0;
		}
		break;
		
		case Accel :
		if(Temps>=TMontee){
			state = Vconst;
			Temps = 0;
			Vconsigne = VPalier;
		}
		else{
			Temps ++;
			Vconsigne = (VPalier * Temps) / TMontee;
		}
		break;
		
		case Vconst :
		if (Temps>=TPalier){
			state = Decel;
			Temps = 0;
		}
		else{
			Temps ++;
		}
		break;
		
		case Decel:
		if(Temps >= TDescente){
			state = Repos;
			Temps = 0;
			Vconsigne = 0;
		}
		else{
			Temps ++;
			Vconsigne = (VPalier * (TDescente - Temps)) / TDescente;
		}
		break;
	}
	
	return Vconsigne;
}