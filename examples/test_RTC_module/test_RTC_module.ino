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


	This sketch tests the RTC module printing on the serial monitor
	the current time & date of the microcontroller.


  	This code is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public
	License as published by the Free Software Foundation; either
	version 3.0 of the License, or (at your option) any later version.

    You should have received a copy of the GNU General Public License
    along with this library.  If not, see <http://www.gnu.org/licenses/>

	This code is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

	Copyleft 2013

*/

//include the library
#include "advancedFunctions.h"


//set up the sketch
void setup() {
    Serial.begin(19200);
    delay(2000); //wait a couple of seconds
    if(rtc.setTime(12, 0, 0, 24)) { //set here the time
        Serial.println(F("AN ERROR HAS OCCURED WHILE SETTING UP THE CLOCK"));
    }
    if(rtc.setDate(2013, 5, 1, 3)) { //set here the date
        Serial.println(F("AN ERROR HAS OCCURED WHILE SETTINH UP THE CALENDAR"));
    }
}


//main loop
void loop() {
    byte tempSec = rtc.getSeconds();

    printTimeAndDate(); //print the current time & date
	Serial.println(""); //empty line

    //wait 1 second
    while (tempSec == rtc.getSeconds());
}


//print the time & date
void printTimeAndDate() {
    Serial.print(rtc.getDay(), DEC);
    Serial.print(F("/"));
    Serial.print(rtc.getMonth(), DEC);
    Serial.print(F("/"));
    Serial.print(rtc.getYear(), DEC);
    Serial.print(F("  -  "));
    Serial.print(rtc.getHours(), DEC);
    Serial.print(F(":"));
    Serial.print(rtc.getMinutes(), DEC);
    Serial.print(F(":"));
    Serial.println(rtc.getSeconds(), DEC);
}
