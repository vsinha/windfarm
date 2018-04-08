#ifdef OTA_PROGRAMMER

#include <Arduino.h>
#include "Identification.h"
#include "StatusLed.h"
#include "pins.h"
#include "radio.h"

#define SERIAL_BAUD 115200

StatusLed statusLed;
Identification id;
Radio radio;

void setup() {
    Serial.begin(SERIAL_BAUD);
    while (!Serial); // Wait for serial port to be available

    pinMode(BUILTIN_LED_PIN, OUTPUT);
    pinMode(PWM_PIN, OUTPUT);

    // set the id in EEPROM
    id.setId(6);

    // load up the ID we have stored
    id.getId();
    Serial.printf("Our ID is %d\n", id.myId);
}

byte ReadFromSerial() {
    byte incomingByte = 0;
    if (Serial.available() > 0) {
        incomingByte = Serial.read();
        Serial.print("RECV: ");
        Serial.println(incomingByte, HEX);
    }
}

void loop() {
    ReadFromSerial();
}

#endif