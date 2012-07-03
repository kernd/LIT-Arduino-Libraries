#ifndef __Sector_h__
#define __Sector_h__

#include <LPD8806.h>

// Arduino versioning.
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"	// for digitalRead, digitalWrite, etc
#else
#include "WProgram.h"
#endif

class Sector {
private:
	int numLEDS; //number of LEDs in the sector
	int *map; //pointer to mapping array
	
	
public:
	Sector(int numLEDs, int mapIn[]); //constructor
	~Sector(); //destructor
	void on(int r, int g, int b); //turns all LEDs in sector to specified color
	void off(); //turns all LEDs in sector off
	void pulse(int r, int g, int b, int onTime, int offTime); //blinks sector a specified color at specified rate
	void fade(int r, int g, int b, int onTime, int offTime); //same as pulse but brightness fades in and out
	
};

#endif /* __Sector.h__ */