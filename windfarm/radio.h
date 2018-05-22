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
    LEADER,
    SYNC
};

typedef struct {
	uint8_t nodeId; // who's sending
	uint8_t leaderId; // who we think is leader
	uint16_t frameCount;
	PayloadMessageType messageType;
	//unsigned long uptime;
} Payload;

class Radio {
public:

	RH_RF95 radio;

	// Stores the latest packet
	Payload latestReceived;

	void initialize();
	bool tryReceive();

	void send(Payload* data);
	void sendFrameCount(uint8_t myId, uint8_t leaderId, uint16_t fc);
    void sendLeader(uint8_t myId, uint8_t leaderId);
};

#endif
