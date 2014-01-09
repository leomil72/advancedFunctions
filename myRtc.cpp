/*
 * This file is part of advancedFunctions library, a collection of functions
 * written for Arduino DUE and/or Atmel SAM3X8E microcontroller
 *
 *
 * myRtc manages the interal RTC
 *
 * See the README file for more info
 *
 */

//include required files
#include "myRtc.h"

//comment the following line if you want to use the internal low freq. RC oscillator
#define USE_EXTERNAL_CRYSTAL

//global settings - modify them to change the dueRTC characteristics
uint8_t _initialized;
uint8_t daysPerMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

//class constructor
myRTC::myRTC(void) {
	_initialized = 1;
#ifdef USE_EXTERNAL_CRYSTAL
	//activate the 32 kHz external clock to source the Slow Clock Generator
	SUPC->SUPC_CR = ((((uint32_t)(0xA5)) << 24) | (SUPC_CR_XTALSEL));
	while ((SUPC->SUPC_SR & SUPC_SR_OSCSEL) != SUPC_SR_OSCSEL); //wait until the switch has been done
#endif
}


//get hours
uint8_t myRTC::getHours() {
	uint8_t _tempByte = ((RTC->RTC_TIMR & 0x003F0000) >> 16);
	return bcd2dec(_tempByte);
}


//get minutes
uint8_t myRTC::getMinutes() {
	uint8_t _tempByte = ((RTC->RTC_TIMR & 0x00007F00) >> 8);
	return bcd2dec(_tempByte);
}


//get seconds
uint8_t myRTC::getSeconds() {
	uint8_t _tempByte = RTC->RTC_TIMR & 0x0000007F;
	return bcd2dec(_tempByte);
}


//get year
unsigned int myRTC::getYear() {
	uint8_t _tempByte = (RTC->RTC_CALR & 0x0000007F);
	uint8_t _tempByte2 = ((RTC->RTC_CALR & 0x00007F00) >> 8);
	return ((bcd2dec(_tempByte) * 100) + (bcd2dec(_tempByte2)));
}


//get month
uint8_t myRTC::getMonth() {
	uint8_t _tempByte = ((RTC->RTC_CALR & 0x001F0000) >> 16);
	return bcd2dec(_tempByte);
}


//get day
uint8_t myRTC::getDay() {
	uint8_t _tempByte = ((RTC->RTC_CALR & 0x3F000000) >> 24);
	return bcd2dec(_tempByte);
}


//set internal time
uint8_t myRTC::setTime(uint8_t _tempHours, uint8_t _tempMinutes, uint8_t _tempSeconds, uint8_t _tempFormat) {

	unsigned long _tempTime = 0;

	//check for correct values
	if (_tempHours > 23) {
		_tempHours = 0;
	}
	if (_tempMinutes > 59) {
		_tempMinutes = 0;
	}
	if (_tempSeconds > 59) {
		_tempSeconds = 0;
	}
	if ((_tempFormat != 12) && (_tempFormat != 24)) {
		_tempFormat = 24;
	}

	//convert values into BCD
	_tempTime = (uint32_t)(dec2bcd(_tempHours) << 16);
	_tempTime |= (uint32_t)(dec2bcd(_tempMinutes) << 8);
	_tempTime |= (uint32_t)(dec2bcd(_tempSeconds));


	//stop the RTC
	RTC->RTC_CR |= RTC_CR_UPDTIM;
	//wait for Acknowledge
	while ((RTC->RTC_SR & RTC_SR_ACKUPD) != (RTC_SR_ACKUPD));
	//clear Acknowledge bit
	RTC->RTC_SCCR |= RTC_SCCR_ACKCLR;
	//set new time
	RTC->RTC_TIMR = _tempTime;
	if (_tempFormat == 24) {
		RTC->RTC_MR &= ~RTC_MR_HRMOD;
	} else {
		RTC->RTC_MR |= RTC_MR_HRMOD;
	}
	//restart RTC
	RTC->RTC_CR &= ~RTC_CR_UPDTIM;
	//reset SEC bit
	RTC->RTC_SCCR |= RTC_SCCR_SECCLR;
	//wait for 1 second
	while((RTC->RTC_SR & RTC_SR_SEC) != (RTC_SR_SEC));
	return (uint8_t)(RTC->RTC_VER & RTC_VER_NVTIM);
}



//set internal date
uint8_t myRTC::setDate(unsigned int _tempYear, uint8_t _tempMonth, uint8_t _tempDay, uint8_t _tempWeekDay) {

	unsigned long _tempDate = 0;

	//check for correct values
	if ((_tempYear < 1900) || (_tempYear > 2099)) {
		_tempYear = 2000;
	}
	if ((_tempMonth < 1) || (_tempMonth > 12)) {
		_tempMonth = 1;
	}
	if ((_tempDay < 1) || (_tempDay > 31)) {
		_tempDay = 1;
	}
	if ((_tempWeekDay < 1) || (_tempWeekDay > 7)) {
		_tempWeekDay = 1;
	}

	//convert values into BCD
	_tempDate = (uint32_t)(dec2bcd(_tempYear / 100)); //century
	_tempDate |= ((uint32_t)dec2bcd(_tempYear % 100)) << 8; //year
	_tempDate |= ((uint32_t)dec2bcd(_tempMonth)) << 16; //month
	_tempDate |= ((uint32_t)dec2bcd(_tempWeekDay)) << 21; //day of week
	_tempDate |= ((uint32_t)dec2bcd(_tempDay)) << 24; //day

	//stop the RTC
	RTC->RTC_CR |= RTC_CR_UPDCAL;
	//wait for Acknowledge
	while ((RTC->RTC_SR & RTC_SR_ACKUPD) != (RTC_SR_ACKUPD));
	//clear Acknowledge bit
	RTC->RTC_SCCR |= RTC_SCCR_ACKCLR;
	//set new date
	RTC->RTC_CALR = _tempDate;
	//restart RTC
	RTC->RTC_CR &= ~RTC_CR_UPDCAL;
	//reset SEC bit
	RTC->RTC_SCCR |= RTC_SCCR_SECCLR;
	//wait for 1 second
	while((RTC->RTC_SR & RTC_SR_SEC) != (RTC_SR_SEC));
	return (uint8_t)(RTC->RTC_VER & RTC_VER_NVCAL);
}

//convert from decimal to BCD notation
uint8_t myRTC::dec2bcd(uint8_t val) {
	return (((val / 10) * 16) + (val % 10));
}


//convert from BCD to a decimal value
uint8_t myRTC::bcd2dec(uint8_t val) {
	return (((val / 16) * 10) + (val % 16));
}


//returns a timestamp giving the number of seconds since a particular year (default=1970)
uint32_t myRTC::getTimestamp(uint16_t epoch){
	uint32_t time=0;

	//check the epoch
	if (epoch == 0) {
		epoch = 1970;
	} else if (epoch < 1900) {
		epoch = 1900;
	} else if (epoch > 1970) {
		epoch = 1970;
	} else if ((epoch != 1900) && (epoch != 1970)) {
		epoch = 1970;
	}

	//One revolution of the Earth is not 365 days but accurately 365.2422 days.
	//It is leap year that adjusts this decimal fraction. But...
	time += (getYear() - epoch) * 365.2422;
	for (uint8_t i = 0; i < getMonth() - 1; i++){
		time += daysPerMonth[i]; //find day from month
	}
	time = (time + getDay()) * 24UL; //find hours from day
	time = (time + getHours()) * 60UL; //find minutes from hours
	time = (time + getMinutes()) * 60UL; //find seconds from minute
	time += getSeconds(); // add seconds
	if (time > 951847199UL) { time += 86400UL; } //year 2000 is a special leap year, so 1 day must be added if date is greater than 29/02/2000
	return (time - 86400UL); //because years start at day 0.0, not day 1.
}

// set the internal clock using a timestamp using the epoch passed as argument
uint8_t myRTC::setClockWithTimestamp(uint32_t timestamp, uint16_t epoch) {
	uint32_t dayT;

	if (timestamp > 951847199UL) { timestamp -= 86400UL; } //year 2000 is a special leap year, so 1 day must be added if date is greater than 29/02/2000
	timestamp += 86400UL; //days in the calendar start from Jan., 1 not from Jan., 0
	dayT = timestamp / (60UL * 60UL * 24UL);
	float remaining = timestamp - dayT * (60UL * 60UL * 24UL);
	uint16_t yearT = (dayT / 365.2422);
	float dayRemaining = dayT - yearT * 365.2422;

	if (epoch == 0) {
		epoch = 1970;
	} else if (epoch < 1900) {
		epoch = 1900;
	} else if (epoch > 1970) {
		epoch = 1970;
	} else if ((epoch != 1900) && (epoch != 1970)) {
		epoch = 1970;
	}

	yearT += epoch;
	if (dayRemaining >= 365.2422) {
		return 1;//my math is wrong!
    }
	if (yearT < epoch) {
		return 2;//year not supported!
    }
	uint8_t monthT = 0;
	while (dayRemaining > daysPerMonth[monthT]){
		dayRemaining -= daysPerMonth[monthT];
		if (monthT == 1 && isLeapYear(yearT)) {
			dayRemaining--;
		}
		monthT++;
	}

	monthT++;//because month 0 doesn't exist
	if (monthT > 12) {
		return 3;//my math is wrong!
    }
	if (dayRemaining >= (60UL*60UL*24UL)) {
		return 4;//my math is wrong!
    }
	dayT = dayRemaining;
	if (dayRemaining - dayT > 0){ //add partial day!
		dayT++;
	}
	uint8_t hoursT = remaining / (60UL * 60UL);
	remaining = remaining - hoursT * (60UL * 60UL);
	if (remaining >= (60UL * 60UL)) {
		return 5;//my math is wrong!
    }
	uint8_t minutesT = remaining / 60UL;
	remaining = remaining - minutesT * 60UL;
	if (remaining >= 60) {
		return 6;//my math is wrong!
    }
	setTime(hoursT, minutesT, remaining, 24);
	setDate(yearT, monthT, dayT, weekDay(timestamp));
	return 0;
}


//return the day of the week giving a timestamp
uint8_t myRTC::weekDay(uint32_t timestamp) {
  return ((timestamp / 86400UL) + 4 ) % 7;
}


//check if the current year is a leap year
bool myRTC::isLeapYear(uint16_t yearT) {
	if (yearT == 0) { yearT = getYear(); }
	if (((yearT % 4) == 0) && ((yearT % 100) != 0) || ((yearT % 400) == 0)) {
		return true;
	} else {
		return false;
	}
}


//instantiate a new object
myRTC rtc;
