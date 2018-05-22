/*
Goal here is to reach a smooth sinusoidal led pulse
without blocking the main (read: only) thread.

We should be able to do this by repeatedly calling led_update()
which will move towards target brightness in increments
*/

#include "lights.h"

namespace lights {

	uint8_t minTargetBrightness = MIN_BRIGHTNESS;
	uint8_t maxTargetBrightness = MAX_BRIGHTNESS;
	uint8_t ledDelta = LED_DELTA;

	uint8_t currentBrightness = 0;
	bool increasing = true;

	unsigned long lastCalledMillis = 0;
	unsigned int rate = BRIGHTNESS_CHANGE_RATE;

	CRGB leds[NUM_LEDS];

	void setup() {
		FastLED.addLeds<LED_TYPE, EXTERNAL_ADDRESSABLE_LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
	}

	void set_led_brightness(uint8_t val) {
		analogWrite(EXTERNAL_SINGLE_LED_PIN, val);
	}

	int counter = 0;

	void update_addressable_leds(int numLeds, uint8_t val) {

		counter = (counter + 1) % numLeds;
		
		for (int i = 0; i < numLeds; i++) {
			leds[i] = CRGB::OrangeRed;
		}

		FastLED.setBrightness(val);
		FastLED.show();
	}


	void yielding_led_update(unsigned long frameCount) {
		float offset = frameCount / 4096.0;
		int value = 127.5 + 127.5 * sin(offset * 2.0 * PI);
		set_led_brightness(value);

		update_addressable_leds(NUM_LEDS, value);

		yield();
	}
}