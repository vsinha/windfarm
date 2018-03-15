// 
// 
// 

#include "radio.h"


void Radio::initialize() {
	if (radio.init()) {
		Serial.printf("Radio init succeeded\n");
	}
	else {
		Serial.printf("Radio init failed\n"); 
	}

	// Defaults after init are 434.0MHz, 13dBm, Bw = 125 kHz, Cr = 4/5, Sf = 128chips/symbol, CRC on
	radio.setFrequency(915);

	//len = sizeof(Payload);

	//Serial.printf("payload len: %d\n", len);
}

//bool Radio::recv(char* buf, uint8_t* len) {
//	return radio.recv((uint8_t*)buf, len);
//}

// if the radio is available fill the buffer with whatever message we've got
// return status indicates whether we took any action
bool Radio::tryReceive() {
	radio.waitPacketSent();
	
	uint8_t len = sizeof(Payload);
	if (radio.available()) {
		if (radio.recv((uint8_t*)&latestReceived, &len)) {
			Serial.printf("recv id=%d, fc=%u\n", latestReceived.nodeId, latestReceived.frameCount);
			return true;
		}
	}

	return false;
}

void Radio::sendFrameCount(uint8_t myId, uint16_t fc) {
	Payload p;
	p.nodeId = myId;
	p.frameCount = fc;
	send(&p);
}

void Radio::send(Payload* p) {
	uint8_t len = sizeof(Payload);
	Serial.printf("send myId=%d, fc=%u\n", p->nodeId, p->frameCount);
	radio.send((uint8_t*)p, len);
}

//void Radio::send(char* data) {
//	radio.send((uint8_t*)data, sizeof(data));
//}

//void Radio::send(Payload* data) {
//	send((uint8_t*)data);
//}
//
//void Radio::send(uint8_t* data) {
//	radio.send(data, sizeof(data));
//}