/*
Goal here is to reach a smooth sinusoidal led pulse
without blocking the main (read: only) thread.

We should be able to do this by repeatedly calling led_update()
which will move towards target brightness in increments
*/

#include "lights.h"

uint8_t minTargetBrightness = MIN_BRIGHTNESS;
uint8_t maxTargetBrightness = MAX_BRIGHTNESS;
uint8_t ledDelta = LED_DELTA;

uint8_t currentBrightness = 0;
bool increasing = true;

unsigned long lastCalledMillis = 0;
unsigned int rate = BRIGHTNESS_CHANGE_RATE;

void led_update() {

	// if the function is called more than once every 100 millis
	// we do nothing
	unsigned long m = millis();
	if (m < lastCalledMillis + rate) {
		return;
	}
	else {
		lastCalledMillis = m;
	}

	if (increasing && currentBrightness <= maxTargetBrightness - ledDelta) {
		currentBrightness += ledDelta;
	}
	else if (!increasing && currentBrightness >= minTargetBrightness + ledDelta) {
		currentBrightness -= ledDelta;
	}
	else {
		increasing = !increasing;
	}

	set_led_brightness(currentBrightness);
}


void set_led_brightness(uint8_t val) {
	analogWrite(PWM_PIN, val);
}

void yielding_led_update(unsigned long frameCount) {
	float offset = frameCount / 2048.0;
	int value = 127.5 + 127.5 * sin(offset * 2.0 * PI);
	set_led_brightness(value);
	yield();
}

//void yielding_always_sin_led_update() {
//	long time = sync_clock;
//	int val = 128 * sin(time * 2.0 * PI);
//	if (val < 0) {
//		set_led_brightness(0);
//	}
//	else {
//		set_led_brightness(val);
//	}
//	yield();
//}