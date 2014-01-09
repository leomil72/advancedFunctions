/*
    This file is part of advancedFunctions library, a collection of functions
    written for Arduino DUE and/or Atmel SAM3X8E microcontroller

	myTrng returns random numbers

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


#ifndef myTRNG_H
#define myTRNG_H

#include "advancedFunctions.h"

//library version
#define myRTC_VERSION 010

//class to get random numbers from the internal TRNG
class myTrng {
	public:
		//public methods
		myTrng(void);
		uint8_t getByte(void);
		uint16_t getInt(void);
		uint32_t getLong(void);
	private:
		//private methods
};

extern myTrng trng;

#endif
