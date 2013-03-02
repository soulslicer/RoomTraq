/*
 * DistanceDriver.h
 *
 * Created: 2/23/2013 3:03:24 PM
 *  Author: Raaj
 */ 


#ifndef DISTANCEDRIVER_H_
#define DISTANCEDRIVER_H_

/************************************************************************
 * DistanceDriver
 
 1. Pings the URM37 sensors and gets distance in cm
 2. Makes sense of the incoming data to update total room count
 ************************************************************************/

//Include Paths
#include <SoftwareSerial.h>
#include <Streaming.h>
#include <avr/pgmspace.h>
#include "URMSerial.h"

// The measurement we're taking
#define DISTANCE 1
#define TEMPERATURE 2
#define ERROR 3
#define NOTREADY 4
#define TIMEOUT 5

#define URM1 0
#define URM2 1

class DistanceDriver{
	
	public:
	DistanceDriver(byte pinReceiveURM1, byte pinSendURM1,byte pinReceiveURM2, byte pinSendURM2);
	void pingCount();
	void setBaseValue(int value);
	int entryCount;
	
	private:
	URMSerial urm1;
	URMSerial urm2;
	int baseValue;
	void getCount(bool sensor);
};

#endif /* DISTANCEDRIVER_H_ */