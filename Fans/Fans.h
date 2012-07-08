/*
 
 Fans Header File
 
 Created specifically for Christina for Bisco
 Jul 4 2012
 
 */

#ifndef _Fans_h
#define _Fans_h

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "LPD8806.h"
#include "SPI.h"

#define thumb   1
#define index   2
#define middle  3
#define ring    4
#define pinky   5

#define back    0
#define palm    1

#define dataPin 2
#define clockPin 3

/*
 ARRAYS
 - Need to consider if this is the right amt of LEDs.
 - First column is thumb, last column is pinky.
 - Top row is fingertip, bottom closer to hand.
 
 front: height - 1:knuckles,    6:fingertips
        finger - 1:thumb        5:pinky
 */

class Fans
{
private:
    int num;
    
    
    
    int color;

    
public:
    LPD8806 *strip;
    
    Fans(int num);
    
    void pixel(int side, int finger, int height);
    void finger(int side, int finger);
    void row(int side, int height);
    void side(int side);
    void all();
    
    
    
    
};


int top[6][5] =         { 
    {5,11,17,23,29},            // fingertips
    {4,10,16,22,28},            // 
    {3,9,15,21,27},             // thumb --> pinky
    {2,8,14,20,26},             // 
    {1,7,13,19,25},             // 
    {0,6,12,18,24}     };       // knuckles


int bottom[4][5] =      { 
    {46,42,38,34,30},           // fingertips
    {47,43,39,35,31},           // thumb --> pinky
    {48,44,40,36,32},           //
    {49,45,41,37,33}    };      // knuckles


//LPD8806 strip = LPD8806(num,dataPin,clockPin);


/*
 FUNCTIONS - TO MAKE
 
 Fundamentals
 - light pixel
 - light finger
 - light row
 - light side
 - light all
 
 Functionality
 - change color
 - 

 Sequences
 - sparkle
 - pulse
 - streaks
 - side to side
 - 
 
 */









#endif
