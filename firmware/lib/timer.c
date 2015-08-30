/*! \file timer.h
  \author Andreas Droescher
  \brief Timer functions
*/

#include "platform.h"
#include "command.h"

#ifndef _GNU_ASSEMBLER_
#include <msp430.h>
#endif

// Timer A1 interrupt service routine
volatile u16 tickcount;
void __attribute__((interrupt(TIMERA1_VECTOR))) tick() {
	if(TACTL & TAIFG) {
		TACTL &= ~TAIFG;
		if(++tickcount >= 50*30) {
			led_toggle();
			tickcount = 0;			
		}
	}
}

void startSampling() {
	__dint();
	tickcount = 0;
    TACTL  = 0;      //clear all
	TACCR0 = 0x96B0; //devisor
    TACTL |=TACLR;   //reset timer
    TACTL |=
        TASSEL_2     //smclk source
      + ID0 + ID1    //device by 8
	  + MC_1         //Count to TACCR0
	  + TAIE;        //enable timer interupt
	__eint();
}

void stopSampling() {
	TACTL  = 0;      //clear all
}