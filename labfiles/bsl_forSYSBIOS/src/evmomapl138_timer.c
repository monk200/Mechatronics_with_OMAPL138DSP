//-----------------------------------------------------------------------------
// \file    evmomapl138_timer.c
// \brief   implementation of a timer driver for OMAP-L138.
//
//-----------------------------------------------------------------------------

#include "evmomapl138.h"
#include "evmomapl138_timer.h"

//-----------------------------------------------------------------------------
// Private Defines and Macros
//-----------------------------------------------------------------------------
// Changed by Dan Block for different clock source for Timer 2 and 3
// Uses PLL0_CLK2
//#define TIMER_DIV       (12)
//#define TICKS_PER_US    (2)
#define TIMER_DIV       (15)
#define TICKS_PER_US    (10)


//-----------------------------------------------------------------------------
// Public Function Definitions
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// \brief   initialize the microsecond timer.
//
// \param   none.
//
// \return  uint32_t
//    ERR_NO_ERROR - everything is ok...us timer ready to use.
//    ERR_INIT_FAIL - something happened during initialization.
//-----------------------------------------------------------------------------
uint32_t USTIMER_init(void)
{

    // For SYS/BIOS it sets up TMR2 itself  so I commented out Dan Block 09/20/17


    // configure timer 2 for free run.
	// 32-bit unchained mode, timer3:4 /12 prescaler.

	// enable muxed pins as gpio outputs and disable all related interrupts.
	// would need to also setup the pinmux register to select the gpio
	// function of these pins in order to use as gpio.
//   TMR2->GPINT_GPEN = GPENO12 | GPENI12;
//   TMR2->GPDATA_GPDIR = GPDIRO12 | GPDIRI12;

   // stop and reset timer
   // Dan Block added these extra two TGCR sets to zero.  Sometimes the set to zero was not occuring in all register elements
//   TMR2->TGCR = 0x00000000;
//   TMR2->TGCR = 0x00000000;
//   TMR2->TGCR = 0x00000000;
//   TMR2->TCR = 0x00000000;

   // disable interrupts and set emulation to free run.
//   TMR2->INTCTLSTAT = 0;
//   SETBIT(TMR2->EMUMGT, SOFT | FREE);

   // config timer2 in 32-bit unchained mode.
   // remove timer2 - 3:4 from reset.
//   SETBIT(TMR2->TGCR, PRESCALER(TIMER_DIV - 1) | TIMMODE_32BIT_UNCHAINED | TIM34RS );

   // init timer2 - 1:2 period....use full range of counter.
//   TMR2->TIM34 = 0x00000000;
//   TMR2->PRD34 = 0xFFFFFFFF;

   // start timer2 - 3:4.
//   SETBIT(TMR2->TCR, ENAMODE34_CONT);

   // configure timer 3 for start/stop.
	// 32-bit unchained mode, timer3:4 /12 prescaler.

	// enable muxed pins as gpio outputs and disable all related interrupts.
	// would need to also setup the pinmux register to select the gpio
	// function of these pins in order to use as gpio.
   TMR3->GPINT_GPEN = GPENO12 | GPENI12;
   TMR3->GPDATA_GPDIR = GPDIRO12 | GPDIRI12;

   // stop and reset timer.
   // Dan Block added these extra two TGCR sets to zero.  Sometimes the set to zero was not occuring in all register elements
   TMR3->TGCR = 0x00000000;
   TMR3->TGCR = 0x00000000;
   TMR3->TGCR = 0x00000000;
   TMR3->TCR = 0x00000000;

   // disable interrupts and set emulation to free run.
   TMR3->INTCTLSTAT = 0;
   SETBIT(TMR3->EMUMGT, SOFT | FREE);

   // config timer3 in 32-bit unchained mode.
   SETBIT(TMR3->TGCR, PRESCALER(TIMER_DIV - 1) | TIMMODE_32BIT_UNCHAINED);

   // init timer3 - 3:4 period....0 until someone calls delay().
   TMR3->TIM34 = 0x00000000;
   TMR3->PRD34 = 0x00000000;
   
   return (ERR_NO_ERROR);
}

//-----------------------------------------------------------------------------
// \brief   halts execution for "in_delay" number of microseconds.
//
// \param   uint32_t in_delay - the number of us to delay.
//
// \return  none.
//-----------------------------------------------------------------------------
void USTIMER_delay(uint32_t in_delay)
{
   // stop the timer, clear int stat, and clear timer value.
   CLRBIT(TMR3->TGCR, TIM34RS);
   TMR3->TCR = 0x00000000;
   SETBIT(TMR3->INTCTLSTAT, PRDINTSTAT34);
   TMR3->TIM34 = 0x00000000;

   // setup compare time.
   // NOTE: not checking for possible rollover here...do not pass in a
   // value > 0x7FFFFFFF....would result in a much shorter delay than expected.
   TMR3->PRD34 = TICKS_PER_US * in_delay;
   
   // start timer3 - 3:4 to run once up to the period.
   SETBIT(TMR3->TCR, ENAMODE34_ONETIME);
   SETBIT(TMR3->TGCR, TIM34RS);
   
   // wait for the signal that we have hit our period.
   while (!CHKBIT(TMR3->INTCTLSTAT, PRDINTSTAT34))
   {
      asm(" nop");
   }
//   uint32_t i;
//   for (i = 0; i < in_delay * 1; i++) {}
}

//-----------------------------------------------------------------------------
// \brief   resets the timer to 0.
//
// \param   none.
//
// \return  none.
//-----------------------------------------------------------------------------
void USTIMER_reset(void)
{
   CLRBIT(TMR2->TGCR, TIM34RS);
   TMR2->TIM34 = 0x00000000;
   SETBIT(TMR2->TGCR, TIM34RS);
}

//-----------------------------------------------------------------------------
// \brief   returns the current timer value, in microseconds.
//
// \param   none.
//
// \return  uint32_t - timer value, in us.
//-----------------------------------------------------------------------------
uint32_t USTIMER_get(void)
{
   return (TMR2->TIM34 / TICKS_PER_US);
}

//-----------------------------------------------------------------------------
// \brief   sets the timer value, in microseconds.
//
// \param   uint32_t in_time - value to set the timer, in us.
//
// \return  none.
//-----------------------------------------------------------------------------
void USTIMER_set(uint32_t in_time)
{
   TMR2->TIM34 = TICKS_PER_US * in_time;
}
