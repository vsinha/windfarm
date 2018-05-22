// 
// 
// 

#include "StatusLed.h"

void StatusLed::toggle() {
	counter = (counter + 1) % 100; 

	if (counter == 0) {
		digitalWrite(BUILTIN_LED_PIN, state);
		state = !state;
	}
}
