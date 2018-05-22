/*
 Name:		windfarm.ino
 Created:	3/3/2018 9:52:14 AM
 Author:	viraj
*/

#include <Arduino.h>
#include "Identification.h"
#include "StatusLed.h"
#include "pins.h"

#include "sync_protocol.h"
#include "lights.h"
#include "radio.h"

#define SERIAL_BAUD 115200

StatusLed statusLed;
Identification id;
Radio radio;

void setup() {
	Serial.begin(SERIAL_BAUD);
	while (!Serial); // Wait for serial port to be available

	radio.initialize();

    randomSeed(analogRead(0));

	pinMode(BUILTIN_LED_PIN, OUTPUT);
	pinMode(EXTERNAL_ADDRESSABLE_LED_PIN, OUTPUT);
	pinMode(EXTERNAL_SINGLE_LED_PIN, OUTPUT);

	lights::setup();

	// set the id in EEPROM
	//id.setId(3);

	// load up the ID we have stored
	id.getId();
	Serial.printf("Our ID is %d\n", id.myId);
}

// 1,000 microseconds in a millisecond and 1,000,000 microseconds in a second
const unsigned long frameLength = 30000; 
unsigned long startTime;
unsigned long elapsed;

uint16_t frameCount = 0; // this will roll over

int numTicksSinceLastMaster = 0;
int ticksSinceLastMasterLimit = 1000;
int myLeader;

void handleLeaderPacket() {
    numTicksSinceLastMaster = 0;

    int newLeader = radio.latestReceived.leaderId;

    if (id.myId == myLeader && newLeader != id.myId) {
        if (random(0, 100) < 50) {
            Serial.printf("%d: adopting new leader %d (replacing ourself)\n", newLeader);
            myLeader = newLeader;
        }
        else {
            // fuck 'em we're still leader
        }
    }
    else {
        Serial.printf("%d: adopting new leader %d\n", newLeader);
        myLeader = newLeader;
    }
}

void handleSyncPacket() {
    int correctionFactor = 3; // this is a guess
    frameCount = radio.latestReceived.frameCount + correctionFactor;
}

void receivePacket() {
    if (radio.tryReceive()) {
        handleLeaderPacket();
        handleSyncPacket();
    }
}

long prevTime = 0;
long currTime = 0;

void loop() {
    prevTime = currTime;
    currTime = millis();
	frameCount += currTime - prevTime;
	
    statusLed.toggle();

	lights::yielding_led_update(frameCount);

    receivePacket();

    if (numTicksSinceLastMaster > ticksSinceLastMasterLimit) {
        Serial.printf("%d: Electing ourself leader\n", id.myId);

        // we haven't heard from anyone, so declare ourselves master
        // and tell everyone
        myLeader = id.myId;
        radio.sendLeader(id.myId, myLeader);

        numTicksSinceLastMaster = 0;
    }

    // TODO: this is `void doLeaderBehavior();`
    if (myLeader == id.myId) { // we're leader
        if (frameCount % 512 == 0) {
            Serial.printf("%d: We're leader, broadcasting\n", id.myId);
            radio.sendFrameCount(id.myId, id.myId, frameCount);
        }
    }
    else {
        //Serial.printf("%d: We're not leader\n", id.myId);
        numTicksSinceLastMaster += 1;
    }

	// delay
	//elapsed = micros() - startTime;
	//if (elapsed < frameLength) {
	//	delayMicroseconds(frameLength - elapsed);
	//}
	//else { // remainder >= frameLength
	//	// this means we're running out of time in each frame
	//	Serial.printf("oot! %ld\n", elapsed);
	//}
}
