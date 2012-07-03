// LEDArray Library
// LEDArray.h
//
// This library is defined for the 56-LED array
// 
// 

#ifndef __LEDArray_h_
#define __LEDArray_h_

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "LPD8806.h"

extern int num;//         = 56;
extern int dataPin;//     = 2;
extern int clockPin;//    = 3;
extern LPD8806 strip;//   = LPD8806(num,dataPin,clockPin);

extern int smallArray[7][8];

extern int largeArray[18][18];

extern volatile int freqArray[7][10];
extern volatile int freqCounter;
extern volatile int freqAvgs[7];

extern bool a;  // for setting lg array

extern int numRows;// = 7;
extern int numCols;// = 8;

extern int brightness;

// pre-defined colors
extern int red[3];//       = {127,0,0};
extern int yellow[3];//    = {127,127,0};
extern int green[3];//     = {0,127,0};
extern int cyan[3];//      = {0,127,127};
extern int blue[3];//      = {0,0,127};
extern int magenta[3];//   = {127,0,127};
extern int white[3];//     = {127,127,127};

extern int *redP; //       = red;
extern int *yellowP; //    = yellow;
extern int *greenP; //     = green;
extern int *cyanP; //      = cyan;
extern int *blueP; //      = blue;
extern int *magentaP; //   = magenta;
extern int *whiteP; //     = white;
extern int *blackP; //     = black;

extern int *colors[];

extern int rectParameters[7][4];

extern int counter;

extern bool io;

extern bool ioArray[7];

void setLargeArray(bool a);
void setSmallArray(bool a);
void colorcycle(int color[]);
void lightCell(int row, int col, int color[]);
void lightLine(char x,int row,int col1,int col2,int color[]);
void lightRow(int row,int color[]);
void lightColumn(int col,int color[]);
void lightRectangle(char x,int row1,int col1,int row2,int col2,int color[]);
void hi(int color[]);
void startUpSequence(int time);
void off();
void equalizer(char x,int color[],volatile int spectrum[]);
void changeColor(int *ptr, int colorArray[]);
void pulseRectangle(int spectrum[],int channel);
void detectBeat(volatile int spectrum[],int channel,int cutoff);
void americanFlag(int time);
void randomRectangles(int spectrum[]);
void splashSquares(int spectrum[],int rows, int cols);

#endif