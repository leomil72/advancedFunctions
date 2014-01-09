/*
    This file is part of advancedFunctions library, a collection of functions
    written for Arduino DUE and/or Atmel SAM3X8E microcontroller

	myWdt lets to use the Watchdog Timer

	For more infos, please read the README.txt file.

	Written by Leonardo Miliani <www DOT leonardomiliani DOT com>

    The latest version of this library can be found at:
    http://www.leonardomiliani.com/
    or at:
    https://github.com/leomil72

  	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public
	License as published by the Free Software Foundation; either
	version 3.0 of the License, or (at your option) any later version.

    You should have received a copy of the GNU General Public License
    along with this library.  If not, see <http://www.gnu.org/licenses/>

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

	Copyleft 2013

*/

#ifndef myWDT_H
#define myWDT_H

#include "advancedFunctions.h"

//library version
#define myWDT_VERSION 010

//class to get random numbers from the internal TRNG
class myWdt {
	public:
		//public methods
		myWdt(void);
		uint8_t enable(uint32_t _tempWdtInterval = 16);
        uint8_t disable(void);
        void restart(void);
	private:
		//private methods
};

extern myWdt wdt;

#endif
