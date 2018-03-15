// Identification.h

#ifndef _IDENTIFICATION_h
#define _IDENTIFICATION_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <EEPROM.h>


// Reads and writes an ID value from the EEPROM
class Identification {
public:
	uint8_t myId;

	void setId(uint8_t newId) {
		Serial.printf("Setting EEPROM id to %d\n", newId);

		uint8_t existingId = getId();

		if (existingId != newId) {
			EEPROM.write(kId, newId);
		}

		if (!hasId()) {
			EEPROM.write(kHasId, 1);
		}
	}

	bool hasId() {
		return EEPROM.read(kHasId) == 1;
	}

	uint8_t getId() {
		uint8_t id = EEPROM.read(kId);
		myId = id;
		return id;
	}

private:
	const int kHasId = 0x0;
	const int kId = 0x1;
};


#endif

