/*
 * This file is part of advancedFunctions library, a collection of functions
 * written for Arduino DUE and/or Atmel SAM3X8E microcontroller
 *
 *
 * myWdt lets to use the WatchDog Timer
 *
 * See the README file for more info
 *
 */

#include "myWdt.h"

uint8_t _wdtSet = 0;

//class constructor: it disables the WDT by default
myWdt::myWdt(void) {
}

//enable WDT
uint8_t myWdt::enable(uint32_t _tempInterval) {
	if (_wdtSet) { //error! WDT_MR register can only be set once
		return 1;
	}

	if ((_tempInterval < 1UL) || (_tempInterval > 16383UL)) { //max allowed value is 16 seconds
		_tempInterval = 16UL; //default value
	}

	_tempInterval = _tempInterval >> 2; // interval is divided by 4
    //we write the interval twice because the WDT MR register has 2 different values, WDD and WDV:
    //WDV contains the internal while WDD containes the delta to let the user to restart the WDT timer
    //without generating errors. In case of errors, the WDT triggers a reset. Using the same values
    //we disable this feature.
	WDT->WDT_MR = WDT_MR_WDV(_tempInterval) | WDT_MR_WDD(_tempInterval) | WDT_MR_WDRSTEN;
	_wdtSet = 1;
	return 0;
}



//restart the WDT counter so that it doesn't reset the MCU
void myWdt::restart() {
    WDT->WDT_CR = 0xA5000001;
}


//disable the WDT
uint8_t myWdt::disable() {
	if (_wdtSet) { //error! WDT_MR register can only be set once
		return 1;
	}
    WDT->WDT_MR = WDT_MR_WDDIS;
    _wdtSet = 1;
    return 0;
}

//instantiate a new object
myWdt wdt;


