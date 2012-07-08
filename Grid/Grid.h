/*
 
 Grid Header File
 
 Kern is a faggot
 
 
 HAI I JUST ADDED A NEW IDIOT GAY COMMENT TO TEST FUCKING GIT
 
 
 */

#ifndef _Grid_h
#define _Grid_h

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "SPI.h"
#include "LPD8806.h"
#include "ColorList.h"
#include "FFT.h"

#define dataPin         2
#define clockPin        3
#define fftAnalogPin    0
#define fftStrobePin    6
#define fftResetPin     5


class Grid
{
private:
    int rows;       // number of rows
    int cols;       // number of columns
    int num;        // total number of LEDs
    
public:
    LPD8806* strip; //
    FFT* freqChip;
    
    Grid(int rows,int cols);
    
    int     address(int r,int c);
    void    swap(int &var1,int &var2);
    void    allOff();
    void    update();
    void    drawPixel(int r,int c,long color);
    void    drawXLine(int r,int c1,int c2,long color);
    void    drawYLine(int c,int r1,int r2,long color);
    void    drawRectangle(bool fill,int r1,int c1,int r2,int c2,long color);
    void    testEverything();
    void    splashSquares();
    void    splashSquares2();
    void    bassPulse();
    void    equalizer();
    void    pulse(int channel,int row1,int col1,int maxSize);
    void    squarePulses();
    
    //specific shapes of interest
    void    smiley1(long color);
    void    rightEyeOpen(long color);
    void    leftEyeOpen(long color); 
    void    leftWink(long color); 
    void    rightWink(long color); 
    void    oFace(long color);
    
    //function that changes smiley faces bases on frequency components
    void    faceFreq();
    
   
};




#endif
