// radio.h

#ifndef _RADIO_h
#define _RADIO_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <SPI.h>
#include <RH_RF95.h>
#include <RadioHead.h>

enum PayloadMessageType {
	EMPTY,
	PULSE_NOW,
};

typedef struct {
	uint8_t nodeId; // who's sending
	//uint8_t leaderId; // who we think is leader
	uint16_t frameCount;
	//PayloadMessageType messageType;
	//unsigned long uptime;
} Payload;

class Radio {
public:

	RH_RF95 radio;

	// Stores the latest packet
	Payload latestReceived;
	//uint8_t len;

	void initialize();
	//bool recv(Payload& buf, uint8_t* len);
	bool tryReceive();
	//void send(char * data);
	//void send(uint8_t * data);

	void send(Payload* data);
	void sendFrameCount(uint8_t myId, uint16_t fc);

};

#endif
