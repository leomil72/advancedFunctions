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


    This sketch tests the WDT blinking the integrated LED for a while
    then resetting the MCU.


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

const byte ledPin = 13;
byte ledStatus = 1;

//set up the sketch
void setup() {
    wdt.enable(1000); //1000 ms of survival
    pinMode(ledPin, OUTPUT);
}


//main loop
void loop() {
    static byte counter = 0;
    digitalWrite(ledPin, ledStatus);
    delay(500);
    ledStatus ^= 1;
    counter++;
    if (counter > 10) { //after 10 timer, we freeze the code into an infinite loop
        for(;;); //this is a deadlock
    }
    wdt.restart(); //this ensures that the WDT will not reset the MCU
}
