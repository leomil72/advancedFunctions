/*
    This file is part of advancedFunctions library, a collection of functions
    written for Arduino DUE and/or Atmel SAM3X8E microcontroller

	myRtc is a library that let you manage the internal Real-Time
    Clock of the Arduino DUE boards.

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


#ifndef myRTC_H
#define myRTC_H

#include "advancedFunctions.h"


//library version
#define myRTC_VERSION 040


//dueRTC class
class myRTC {
	public:
		//public methods
		myRTC();
        uint8_t getHours(void);
        uint8_t getMinutes(void);
        uint8_t getSeconds(void);
        unsigned int getYear(void);
        uint8_t getMonth(void);
        uint8_t getDay(void);
        uint8_t setTime(uint8_t _tempHours = 0, uint8_t _tempMinutes = 0, uint8_t _tempSeconds = 0, uint8_t _tempFormat = 24);
        uint8_t setDate(unsigned int _tempYear = 2013, uint8_t _tempMonth = 1, uint8_t _tempDay = 1, uint8_t _tempWeekDay = 1);
        uint32_t getTimestamp(uint16_t epoch = 1970);
        uint8_t setClockWithTimestamp(uint32_t timestamp, uint16_t epoch = 1970);
        bool isLeapYear(uint16_t);
        uint8_t weekDay(uint32_t timestamp);
	private:
        //private methods
        uint8_t dec2bcd(uint8_t value);
        uint8_t bcd2dec(uint8_t value);
};

extern myRTC rtc;

#endif
