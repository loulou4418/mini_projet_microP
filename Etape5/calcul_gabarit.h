/*
 * calcul_gabarit.h
 *
 * Created: 17/12/2021 10:20:28
 *  Author: e182232d
 */ 


#ifndef CALCUL_GABARIT_H_
#define CALCUL_GABARIT_H_

#include <stdio.h>

#define TMontee 128
#define TPalier 512
#define TDescente 128
#define TRepos 64

#define V_MAX 5000

enum state_t
{
	Repos,
	Accel,
	Vconst,
	Decel
};

uint16_t calcul_gabarit (uint16_t VPalier);

#endif /* CALCUL_GABARIT_H_ */