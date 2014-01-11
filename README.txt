****************************************
 A D V A N C E D      F U N C T I O N S
****************************************

This library is a collection of advanced functions (which gives the name
of this software) written to use the integrated peripherals of the
Atmel SAM3X8E microcontroller of the Arduino DUE board that are not
supported by the Arduino IDE.

Written by Leonardo Miliani <www DOT leonardomiliani DOT com>

The latest version of this library can be found at:
http://www.leonardomiliani.com/
or at:
https://github.com/leomil72

****************************************
VERSION HISTORY

v. 0.1.0:  first release - only RTC module is present
v. 0.2.0:  added TRNG module
v. 0.3.0:  added WDT module
v. 0.3.1:  now the WDT module works correctly
v. 0.4.0:  added some timing functions, i.e. functions to work with timestamps
v. 0.5.0:  fixed serial speed bugs in the example sketches. Now the library
           can use the external 32 kHz crystal, if present

****************************************
INSTALL THE LIBRARY

Unpack the archive, then check the folder where the Arduino IDE 1.5.x saves
your sketches. To do that, run the Arduino IDE then click on File/Preferences
and look the path of the current folder sketchs. Inside that folder, create
(if you already don't have it) a folder called "libraries", then copy
inside it the folder you had extracted before.

To use the new functions, simply add this line at the top of a sketch:
#include "advancedFunctions.h"

Now you're ready to use the peripherals that are not supported by specific
function of the Arduino IDE.

****************************************
FUNCTIONS

Currently the library supports the following peripherals and functions:

RTC - Real Time Clock
The SAM3X8E has an integrated real time clock (RTC) that is clocked by
a 32,768 Hz clock (derived by the system clock). It keeps time & date and
has alarm functionalities too (using interrupts).

TRNG - True Random Number Generator
The SAM3X8E integrates a robust true random number generator that has passed
the American NIST Special Publication 800-22 and Diehard Random Tests Suites.
It can provide a lot of entropy at a very high rate (32 bits every 84 clock
cycles).

WDT - WatchDog Timer
The WatchDog Timer is a timer that can reset the microcontroller if the code
becomes trapped in a deadlock. The user can choose the interval in milliseconds
between 1 and 16000.

****************************************
SUPPORTED MICROCONTROLLERS

The library only supports the Arduino DUE board and its microcontroller,
the Atmel SAM3X8E.

****************************************
LICENCE AND WARRANTIES

This library is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the Free
Software Foundation; either version 3.0 of the License, or (at your option)
any later version.

You should have received a copy of the GNU General Public License along
with this library.  If not, see <http://www.gnu.org/licenses/>

This library is distributed in the hope that it will be useful,	but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE. No liability for its usage.

This document is released under the terms of the Creatice Commons Share-Alike,
Attribution, Not Commercial 3.0.

Copyleft 2013

****************************************
DOCUMENT REVISION

6th revision - 2013/09/24
