// StatusLed.h

#ifndef _STATUSLED_h
#define _STATUSLED_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "pins.h"

class StatusLed {
public:
	bool state = 0;
	uint8_t counter = 0;
	void toggle();

};

#endif

