/*
	advancedFunctions.h - A collection of utilities for Arduino DUE to
	use the advanced functions of the integrated peripherals of
	the Atmel SAM3X8E microcontroller.

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


#ifndef advancedFunctions_H
#define advancedFunctions_H


//library version
#define AVANCEDFUNCTION_VERSION 050

//check MCU compatibility - dueRTC only works on Arduino DUE/SAM3X8E
#if !defined(__SAM3X8E__)
#error Sorry, this library ONLY works with Arduino DUE and/or SAM3X8E
#endif

#include "Arduino.h"
//incude sub files
#include "myTrng.h"
#include "myRtc.h"
#include "myWdt.h"

#endif
