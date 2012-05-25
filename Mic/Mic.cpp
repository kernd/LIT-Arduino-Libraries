#include <Mic.h>

Mic::Mic(int analogPin, double averageTime)
	:	analogPin(analogPin),
	 	averageTime(averageTime),
	 	counter(0),
	 	data(0),
	 	sum(0),
	 	gain(1),
	 	sensitivity(256),
	 	startTime(0),
	 	optFlag(false)
{
	mapping[0] = 51;
	mapping[1] = 102;
	mapping[2] = 153;
	mapping[3] = 204;
	mapping[4] = 255;
	mapping[5] = 306;
	mapping[6] = 357;
	mapping[7] = 408;
	mapping[8] = 459;
	mapping[9] = 512;
}

double Mic::sample(void)
{	
	if(optFlag == false)
	{
		optFlag = true;
		startTime = millis();
		optimizeSensitivity();
		
	}
	
	if(millis() - startTime > averageTime * 1000)
	{
		optFlag = false;
	}
	data = (analogRead(analogPin) - 512); //* (256/sensitivity);
	data = abs(data);
	sum+=data;
	counter = counter+1;
	return data*.5/sensitivity;

}

double Mic::getAverage(void)
{
    double average;
	average = sum/counter;
	Serial.println(average);
	
	sum = 0;
	counter = 0;
	return average;
}

double Mic::changeSensitivity(int sensNum)
{
	if(sensNum <= 10 && sensNum >= 1) 
		sensitivity = sensNum;
	
	return sensNum;
}

int Mic::optimizeSensitivity()
{
	double average = getAverage();
	for(int i = 0; i < 10; i++)
	{
		if(average <= mapping[i])
		{
			sensitivity = mapping[i];
			Serial.println(sensitivity);
			break;
		}
	}
	
	return sensitivity;
}

int Mic::getCounter(void)
{
	return counter;
}

void Mic::changeGain(double gainIn)
{
	
}

	 