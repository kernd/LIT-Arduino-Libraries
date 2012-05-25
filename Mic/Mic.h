#ifndef __Mic_h__
#define __Mic_h__

// Arduino versioning.
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"	// for digitalRead, digitalWrite, etc
#else
#include "WProgram.h"
#endif

class Mic {
private:
	int analogPin;
	double counter; // Keeps track of number of samples
	double data; // ADC voltage value seen on analog pin
	double sum; // Keeps track of sum of all samples
	double gain; //this is the gain set by the rheostat
	double averageTime;
	int sensitivity; //The sensitivity to the mic's output
	int mapping[10];
	unsigned long startTime;
	bool optFlag;
	
public:
	Mic(int analogPin, double averageTime);
	double changeSensitivity(int sensNum);
	double sample(void);
	double getAverage(void);
	int getCounter(void);
	void changeGain(double gainIn);
	int optimizeSensitivity(void);
	
};

#endif /* __Mic_h__ */