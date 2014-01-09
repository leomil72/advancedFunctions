/*
 * This file is part of advancedFunctions library, a collection of functions
 * written for Arduino DUE and/or Atmel SAM3X8E microcontroller
 *
 *
 * myTrng returns random numbers
 *
 * See the README file for more info
 *
 */

#include "myTrng.h"

myTrng::myTrng(void) {
}

//return a 32-bits random number
uint32_t myTrng::getLong(void) {
	static bool _Trng_enabled = false;

	//check if the TRNG has already been initialized
    if (!_Trng_enabled) {
        pmc_enable_periph_clk(ID_TRNG);
        TRNG->TRNG_IDR = 0xFFFFFFFF;
        TRNG->TRNG_CR = TRNG_CR_KEY(0x524e47) | TRNG_CR_ENABLE;
        _Trng_enabled = true;
    }

    while (!(TRNG->TRNG_ISR & TRNG_ISR_DATRDY));
    return TRNG->TRNG_ODATA;
}



//return a 16-bits random number
uint16_t myTrng::getInt(void) {
	return uint16_t(myTrng::getLong());
}


//return an 8-bits random number
uint8_t myTrng::getByte(void) {
	return uint8_t(myTrng::getLong());
}


//instantiate a new object
myTrng trng;
