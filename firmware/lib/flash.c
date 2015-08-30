/*! \file flash.c
  \author Andreas Droescher
  \brief Flash access on msp430.
*/

#include "command.h"
#include "platform.h"

void eraseflash(uint8_t* address) {
	WDTCTL = WDTPW + WDTHOLD;		// Stop watchdog timer
	while (FCTL3 & BUSY)			// Wait till busy flag is 0
		asm("nop");
	
	FCTL2 = FWKEY+FSSEL1+0x30;		// ACLK / 48 = 333kHZ 
	FCTL3 = FWKEY;					// Clear LOCK
	FCTL1 = FWKEY+ERASE;			// Enable segment erase
	*address = 0;					// Dummy write, erase Segment
	while (FCTL3 & BUSY)			// Wait till busy flag is 0
		asm("nop");
	FCTL3 = FWKEY+LOCK;				// Done, set LOCK
}

void writeflash(uint8_t* address, uint8_t value) {
	WDTCTL = WDTPW + WDTHOLD;		// Stop watchdog timer
	while (FCTL3 & BUSY)			// Wait till busy flag is 0
		asm("nop");

	FCTL2 = FWKEY+FSSEL1+0x30;		// ACLK / 48 = 333kHZ 
	FCTL3 = FWKEY;					// Clear LOCK
	FCTL1 = FWKEY+WRT;				// Enable write
	*(address) = value;				// Copy data
	while (FCTL3 & BUSY)			// Wait till busy flag is 0
		asm("nop");
	FCTL1 = FWKEY;					// Clear WRT
	FCTL3 = FWKEY+LOCK;				// Set LOCK
}

uint8_t readflash(uint8_t* address) {
	return *(address);
}

//! Handles a monitor command.
void flash_handle_fn( uint8_t const app,
					uint8_t const verb,
					uint32_t const len)
{
		switch(verb) {
			case 0x21:
				eraseflash(cmddataword[0]);
				txdata(app,0,0);
				break;
			case 0x22:
				writeflash(cmddataword[0], cmddata[2]);
				txdata(app,0,0);
				break;
			case 0x23:
				cmddata[0] = readflash(cmddataword[0]);
				txdata(app,0,1);
				break;
		}
}
