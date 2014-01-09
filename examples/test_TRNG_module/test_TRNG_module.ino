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


	This sketch tests the TRNG module printing on the serial monitor
	some random numbers.


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
}


//main loop
void loop() {
    byte tempSec = rtc.getSeconds();

    printRndNumbers(); //print some random numbers
	Serial.println(""); //empty line

    //wait 1 second
    delay(1000);
}


//print some random numbers
void printRndNumbers() {
    Serial.print(F("Random byte: "));
    Serial.println(trng.getByte(), DEC);
    Serial.print(F("Random integer: "));
    Serial.println(trng.getInt(), DEC);
    Serial.print(F("Random long: "));
    Serial.println(trng.getLong(), DEC);
}

