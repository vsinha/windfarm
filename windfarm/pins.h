// pins.h

#ifndef _PINS_h
#define _PINS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define BUILTIN_LED_PIN 9
#define EXTERNAL_SINGLE_LED_PIN 5
#define EXTERNAL_ADDRESSABLE_LED_PIN 6

#endif

