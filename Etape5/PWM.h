/*
 * PWM.h
 *
 * Created: 07/01/2022 08:29:01
 *  Author: e182232d
 */ 


#ifndef PWM_H_
#define PWM_H_

#include <asf.h>
#include "calcul_gabarit.h"

#define TC_CTRLA_NORUNSTDBY           (0x0ul << TC_CTRLA_RUNSTDBY_Pos)
#define TC_CTRLA_NOENABLE             (0x0ul << TC_CTRLA_ENABLE_Pos)
#define TC_CTRLA_NOSWRST              (0x0ul << TC_CTRLA_SWRST_Pos)

#define TC_CTRLC_NOCPTEN0             (0 << TC_CTRLC_CPTEN0_Pos)
#define TC_CTRLC_NOCPTEN1             (0 << TC_CTRLC_CPTEN1_Pos)
#define TC_CTRLC_NOINVEN0             (0 << TC_CTRLC_INVEN0_Pos)
#define TC_CTRLC_NOINVEN1             (0 << TC_CTRLC_INVEN1_Pos)

#define TC_CTRLBCLR_NOONESHOT         (0x0ul << TC_CTRLBCLR_ONESHOT_Pos)
#define TC_CTRLBCLR_NODIR				(0x0ul << TC_CTRLBCLR_DIR_Pos)


#define TC_CC0_Val (800-1)
#define PWM_MAX_DUTY 100

void config_PWM (void);
void write_PWM (uint16_t duty);




#endif /* PWM_H_ */