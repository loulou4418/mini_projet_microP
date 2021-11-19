/*
 * conf_projet.h
 *
 * Created: 19/11/2021 09:20:53
 *  Author: e182232d
 */ 


#ifndef CONF_PROJET_H_
#define CONF_PROJET_H_

#include <asf.h>

#define GCLK_CLKCTRL_NOWRTLOCK        (0x0ul << GCLK_CLKCTRL_WRTLOCK_Pos)

#define GCLK_GENCTRL_NORUNSTDBY       (0x0ul << GCLK_GENCTRL_RUNSTDBY_Pos)
#define GCLK_GENCTRL_NODIVSEL         (0x0ul << GCLK_GENCTRL_DIVSEL_Pos)
#define GCLK_GENCTRL_NOOE             (0x0ul << GCLK_GENCTRL_OE_Pos)
#define GCLK_GENCTRL_NOOOV            (0x0ul << GCLK_GENCTRL_OOV_Pos)
#define GCLK_GENCTRL_NOIDC            (0x0ul << GCLK_GENCTRL_IDC_Pos)

#define TC_CTRLA_NORUNSTDBY           (0x0ul << TC_CTRLA_RUNSTDBY_Pos)
#define TC_CTRLA_NOENABLE             (0x0ul << TC_CTRLA_ENABLE_Pos)
#define TC_CTRLA_NOSWRST              (0x0ul << TC_CTRLA_SWRST_Pos)

#define TC_CTRLC_NOCPTEN0             (0 << TC_CTRLC_CPTEN0_Pos)
#define TC_CTRLC_NOCPTEN1             (0 << TC_CTRLC_CPTEN1_Pos)
#define TC_CTRLC_NOINVEN0             (0 << TC_CTRLC_INVEN0_Pos)
#define TC_CTRLC_NOINVEN1             (0 << TC_CTRLC_INVEN1_Pos)

#define TC_CTRLBCLR_NOONESHOT         (0x0ul << TC_CTRLBCLR_ONESHOT_Pos)

#endif /* CONF_PROJET_H_ */