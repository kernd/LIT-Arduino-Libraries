#include <Sector.h>

//constructor
Sector::Sector(int numLEDS, int mapIn[])
	:	numLEDS(numLEDS)
{
	//dynamically allocate array for mapping
	map = (int *) malloc (numLEDS * sizeof(int));
	//assign mapping
	for(int i = 1; i < numLEDS; i++)
	{
		map[i] = mapIn[i];
	}
}

//destructor
Sector::~Sector()
{
	free(map);
}

//turns all LEDs in sector to specified color
void Sector::on(int r, int g, int b) 
{
	extern LPD8806 strip;
	for(int i = 0; i < numLEDS; i++)
	{
		strip.setPixelColor(map[i], r, g, b);
	}
	strip.show();

}

//turns all LEDs in sector off
void Sector::off() 
{
	extern LPD8806 strip;
	for(int n = 0; n < numLEDS; n++)
	{
		strip.setPixelColor(map[n], 0);
	}
	strip.show();
}

//blinks sector a specified color at specified rate
void Sector::pulse(int r, int g, int b, int onTime, int offTime)
{
	
}

//same as pulse but brightness fades in and out
void Sector::fade(int r, int g, int b, int onTime, int offTime)
{
	
}



	 