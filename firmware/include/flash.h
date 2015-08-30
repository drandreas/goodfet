/*! \file flash.h
  \author Andreas Droescher
  \brief Flash access on msp430.
*/

#ifndef FLASH_H
#define FLASH_H

void erase(uint8_t* address);

void write(uint8_t* address, uint8_t value);

uint8_t read(uint8_t* address);

#endif // FLASH_H