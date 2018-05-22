// lights.h

#ifndef _LIGHTS_h
#define _LIGHTS_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include <FastLED.h>

#include "sync_protocol.h"
#include "pins.h"

#define MAX_BRIGHTNESS 255
#define MIN_BRIGHTNESS 0
#define LED_DELTA 5
#define BRIGHTNESS_CHANGE_RATE 50

#define NUM_LEDS 56
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB

namespace lights {
	void setup();
	void set_led_brightness(uint8_t val);
	void update_addressable_leds(int numLeds, uint8_t val);
	void yielding_led_update(unsigned long frameCount);
}

/*
Blink cycle:
fade 10 seconds
fade in for 5 seconds (sinusoidally?)
fade out for 5 seconds
if this is sinusoidal we want the freq of the sine wave to be 20 sec
wait 10 seconds

total cycle time: 20 seconds

one way to do this
sin wave height of LED brightness (128), period = desired freq
calculate sin() constantly and set brighness to zero
if the sin value comes out negative
*/

#endif
