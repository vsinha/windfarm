/*
 Name:		windfarm.ino
 Created:	3/3/2018 9:52:14 AM
 Author:	viraj
*/

#ifndef OTA_PROGRAMMER

#include "Identification.h"
#include "StatusLed.h"
#include "sync_protocol.h"
#include "pins.h"
#include "lights.h"
#include "radio.h"
#include <Arduino.h>

#define SERIAL_BAUD 115200

StatusLed statusLed;
Identification id;
Radio radio;

void setup() {
	Serial.begin(SERIAL_BAUD);
	while (!Serial); // Wait for serial port to be available

	radio.initialize();

	pinMode(BUILTIN_LED_PIN, OUTPUT);
	pinMode(PWM_PIN, OUTPUT);

	// set the id in EEPROM
	id.setId(6);

	// load up the ID we have stored
	id.getId();
	Serial.printf("Our ID is %d\n", id.myId);
}

// 1,000 microseconds in a millisecond and 1,000,000 microseconds in a second
const unsigned long frameLength = 10000; 
unsigned long startTime;
unsigned long elapsed;

uint16_t frameCount = 0; // this will roll over

// Synchronizes frameCount from master to slaves
void transmitOrReceiveSyncPacket() {
    if (id.myId == 1) {
        // we are the broadcaster!
        if (frameCount % 256 == 0) {
            radio.sendFrameCount(id.myId, frameCount);
        }
    }
    else {
        if (radio.tryReceive()) {
            int correctionFactor = 3; // this is a guess
            frameCount = radio.latestReceived.frameCount + correctionFactor;
        }
    }
}

void loop() {
	startTime = micros();
	frameCount += 1;
	statusLed.toggle();

	yielding_led_update(frameCount);

    transmitOrReceiveSyncPacket();

	elapsed = micros() - startTime;
	if (elapsed < frameLength) {
		delayMicroseconds(frameLength - elapsed);
	}
	else { // remainder >= frameLength
		// this means we're running out of time in each frame
		Serial.printf("oot! %ld\n", elapsed);
	}
}

#endif // !OTA_PROGRAMMER
