/*
 
 Fans C++ File
 
 Created specifically for Christina for Bisco
 Jul 4 2012
 
 Generally, we need to think this through a bit better. 
 
 */

#include <iostream>
#include "Fans.h"

// Constructor
Fans :: Fans(int num)
:num(num)
{
    strip = new LPD8806(num,dataPin,clockPin);
}

void Fans :: address(int side, int finger, int height) // NEED TO COMPLETE THIS
{
    switch (side)
    {
        case 0:
            // going up
            // going down
            break;
        case 1:
            // going up
            // going down
            break;
    }
}


void Fans :: pixel(int side, int finger, int height)
{
    switch (side)
    {
        case 0:
            strip->setPixelColor(top[6-height][finger-1],color);
            break;
        case 1:
            strip->setPixelColor(bottom[4-height][finger-1],color);
            break;
    }
}

void Fans :: finger(int side, int finger)
{
    switch (side)
    {
        case 0:
            for (int n=0;n<6;n++)
            {
                strip->setPixelColor(top[n][finger],color);
            }
            break;
        case 1:
            for (int n=0;n<4;n++)
            {
                strip->setPixelColor(bottom[n][finger],color);
            }
            break;
    }
}

void Fans :: row(int side, int height)
{
    switch (side)
    {
        case 0:
            for (int n=0;n<5;n++)
            {
                strip->setPixelColor(top[6-height][n],color);
            }
            break;
        case 1:
            for (int n=0;n<5;n++)
            {
                strip->setPixelColor(bottom[4-height][n],color);
            }
            break;
    }
}

void Fans :: side(int side)
{
    switch (side)
    {
        case 0:
            for (int n=0;n<6;n++)
            {
                for (int m=0;m<5;m++)
                {
                    strip->setPixelColor(top[n][m],color);
                }
            }
            break;
        case 1:
            for (int n=0;n<4;n++)
            {
                for (int m=0;m<5;m++)
                {
                    strip->setPixelColor(bottom[n][m],color);
                }
            }
            break;
    }
}

void Fans :: all()
{
    for (int n=0;n<50;n++)
    {
        strip->setPixelColor(n,color);
    }
}



















