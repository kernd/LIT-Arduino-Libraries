// LEDArray Library
// LEDArray.cpp
//
// This library is defined for the 56-LED array
// 
/* NOTES
 
 Stuff to pass to functions:
 
 Type       Name                    Means...                Possible values
 int    :   colorArray[]        :   color input         :   color[],redP,etc.
 int    :   row                 :   row                 :   1-7
 int    :   col                 :   column              :   1-8
 char   :   x                   :   variable for case   :   depends on fn
 int    :   ctr                 :   counter             :   depends on fn
 int    :   colorList[]         :   list of pointers to colors
 
 
 - should we build in a time-delay to these functions instead of in loop?
 - do I need to keep including spectrum[] in function declarations?
 
 
 */



#include "SPI.h"        // LPD8806 stuff
#include "LPD8806.h"
#include "LEDArray.h"


int num         = 56;   // number of LEDs in array
int dataPin     = 2;    // for LED strip
int clockPin    = 3;    // for LED strip
LPD8806 strip = LPD8806(num,dataPin,clockPin);


int ledArray[7][8] = {  
    { 7, 6, 5, 4, 3, 2, 1, 0},
    { 8, 9,10,11,12,13,14,15},
    {23,22,21,20,19,18,17,16},
    {24,25,26,27,28,29,30,31},
    {39,38,37,36,35,34,33,32},
    {40,41,42,43,44,45,46,47},
    {55,54,53,52,51,50,49,48}   };

int numRows = 7;
int numCols = 8;

int brightness = 20;    // for brightness of LEDs

bool io=0;

bool ioArray[7];

// pre-defined colors
int red[]       = {brightness,0,0};
int yellow[]    = {brightness,brightness,0};
int green[]     = {0,brightness,0};
int cyan[]      = {0,brightness,brightness};
int blue[]      = {0,0,brightness};
int magenta[]   = {brightness,0,brightness};
int white[]     = {brightness,brightness,brightness};
int black[]     = {0,0,0};

// pointers to these colors
int *redP       = red;
int *yellowP    = yellow;
int *greenP     = green;
int *cyanP      = cyan;
int *blueP      = blue;
int *magentaP   = magenta;
int *whiteP     = white;
int *blackP     = black;

// array of pointers to colors
int *colors[] = {redP,yellowP,greenP,cyanP,blueP,magentaP,whiteP};

int rectParameters[7][4];

int splashArray[7][5];

int counter = 0;


/*
 ########################################################################
 FUNCTIONS
 ########################################################################
 */

// _______________________________________________________________
// COLOR CYCLE
// takes in color array and cycles through r,g,b values
// _______________________________________________________________
void colorcycle(int color[])
{
    int r = color[0];
    int g = color[1];
    int b = color[2];
    
    if(b == 0)
    {
        if(g<127)
        {
            r--;
            g++;
        }
    }
    
    if(r == 0)
    {
        if(b < 127)
        {
            g--;
            b++;
        }
    }
    
    if (g == 0)
    {
        if(r < 127)
        {
            b--;
            r++;
        }
    }
    
    color[0] = r;
    color[1] = g;
    color[2] = b;
}
// _______________________________________________________________
// LIGHT CELL
// lights a cell at intersection of row and col
// _______________________________________________________________
void lightCell(int row, int col, int color[])
{
    strip.setPixelColor(ledArray[row-1][col-1],color[0],color[1],color[2]);
}
// _______________________________________________________________
// LIGHT LINE
// lights up cells along a certain line from add1 to add2
// line = row or column #  |  x is 'r' or 'c'
// _______________________________________________________________
void lightLine(char x,int line,int add1,int add2,int color[])
{
    switch(x)
    {
        case 'r':                        // light up along a row
            for (int n=add1;n<=add2;n++)
            {
                lightCell(line,n,color);
            }
            break;
        case 'c':                        // light up along a column
            for (int n=add1;n<=add2;n++)
            {
                lightCell(n,line,color);
            }
            break;
    }
}
// _______________________________________________________________
// LIGHT ROW
// lights up an entire row
// _______________________________________________________________
void lightRow(int row, int color[])
{
    lightLine('r',row,1,8,color);
}
// _______________________________________________________________
// LIGHT COLUMN
// lights up an entire column
// _______________________________________________________________
void lightColumn(int col, int color[])
{
    lightLine('c',col,1,7,color);
}
// _______________________________________________________________
// LIGHT RECTANGLE
// lights up a rectangle from (row1,col1) to (row2,col2)
// 'f' = filled, 'o' = outline
// _______________________________________________________________
void lightRectangle(char x,int row1,int col1,int row2, int col2,int color[])
{
    switch (x)
    {
        case 'f':   // for a filled rectangle
            for (int n=row1;n<=row2;n++)
            {
                lightLine('r',n,col1,col2,color);
            }
            break;
        case 'o':   // for the outline of a rectangle
            lightLine('r',row1,col1,col2,color);
            lightLine('c',col1,row1,row2,color);
            lightLine('r',row2,col1,col2,color);
            lightLine('c',col2,row1,row2,color);
            break;
    }
}
// _______________________________________________________________
// HI
// lights up 'Hi!'
// _______________________________________________________________
void hi(int color[])
{
    lightColumn(1,color);
    lightColumn(4,color);           // H
    lightLine('r',4,1,4,color);
    
    lightLine('c',6,4,7,color);     // i
    lightCell(2,6,color);
    
    lightCell(7,8,color);           // !
    lightLine('c',8,1,5,color);
    
    strip.show();
}
// _______________________________________________________________
// START UP SEQUENCE
// flashes color-changing rectangles from outside in a few times.
// _______________________________________________________________
void startUpSequence(int time)
{
    for (int c=0; c<4;c++)          // light up full rectangles first
    {                               // and moves inwards
        lightRectangle('f',c+1,c+1,7-c,8-c,colors[c]);
        strip.show();
        delay(time);
    }
    
    for (int c=0;c<4;c++)           // light up outlines and cycles through
    {                               // different colors for nice effect
        for (int d=0;d<4;d++)
        {
            int a = c+d;            // allows cycling for each iter
            if (a>3) a = a-4;       // of for loop
            
            lightRectangle('o',d,d,7-d,8-d,colors[a]);
            strip.show();
            delay(time);
        }
    }
}
// _______________________________________________________________
// OFF
// sets all LEDs to off
// _______________________________________________________________
void off()
{
    for (int n=0;n<=numRows;n++)
    {
        lightRow(n,black);
    }
}
// _______________________________________________________________
// EQUALIZER
// takes in the spectrum and outputs an equalizer.
// 'r' - rainbow (pass 0 to color array)
// 'c' - specific color
// 's' - switches color once a beat is detected
// _______________________________________________________________
void equalizer(char x,int color[],int spectrum[])
{
    switch (x)
    {
        case 'r': // rainbow equalizer (pass 0 to color)
            lightLine('r',1,1,spectrum[0]/120,red);
            lightLine('r',2,1,spectrum[1]/120,yellow);
            lightLine('r',3,1,spectrum[2]/120,green);
            lightLine('r',4,1,spectrum[3]/120,cyan);
            lightLine('r',5,1,spectrum[4]/120,blue);
            lightLine('r',6,1,spectrum[5]/120,magenta);
            lightLine('r',7,1,spectrum[6]/120,white);
            break;
            
        case 'c': // specific color equalizer
            for(int n=0;n<7;n++)
            {
                lightLine('r',n+1,1,spectrum[n]/120,color);
            }
            break;
            
        case 's': // switch color on beat
            detectBeat(spectrum,0,3);
            changeColor(colors[counter],color);
            for(int n=0;n<7;n++)
            {
                lightLine('r',n+1,1,spectrum[n]/120,color);
            }
            break;
            
            //return counter;
    }
}
// _______________________________________________________________
// CHANGE COLOR
// takes in color array and changes it to value dictated by *ptr
// _______________________________________________________________
void changeColor(int *ptr, int colorArray[])
{
    // changes the color array based on the input *ptr
    for (int n=0;n<3;n++)
    {
        colorArray[n] = *(ptr + n);
    }
}
// _______________________________________________________________
// DETECT BEAT
// tests if a certain channel within the fft spectrum 
// passes a cutoff value and, if so, increases a counter by 1
// _______________________________________________________________
void detectBeat(int spectrum[],int channel,int cutoff)
{
    if (spectrum[channel]/120 > cutoff)
    {
        if (io)
        {
            counter++;                      // brings counter back to 0
            if (counter>6) counter = counter-7;     // if its too high (8)
            io=0;
        }
    }
    else io=1;
}
// _______________________________________________________________
// LIGHT PULSE RECTANGLE
// built for Pulse Rectangle function (see below).
// provides a case statement to determine how many outlined
// rectangles to light up.
// _______________________________________________________________
void lightPulseRectangle(int x)
{
    switch (x)
    {
        case 1:
            lightRectangle('o',4,4,4,5,white);
            break;
        case 2:
            lightRectangle('o',3,3,5,6,red);
            break;
        case 3:
            lightRectangle('o',2,2,6,7,blue);
            break;
        case 4:
            lightRectangle('o',1,1,7,8,green);
            break;
    }
}
// _______________________________________________________________
// PULSE RECTANGLE
// tests a certain channel in the spectrum for intensity 
// and lights up a corresponding number of outlined rectangles.
// _______________________________________________________________
void pulseRectangle(int spectrum[],int channel)
{
    if (spectrum[channel]/120 > 5) lightPulseRectangle(4);
    if (spectrum[channel]/120 > 3) lightPulseRectangle(3);
    if (spectrum[channel]/120 > 2) lightPulseRectangle(2);
    if (spectrum[channel]/120 > 0) lightPulseRectangle(1);
}
// _______________________________________________________________
// AMERICAN FLAG
// displays the american flag. stars part flashes with time delay
// _______________________________________________________________
void americanFlag(int time)
{
    delay(time);
    
    lightLine('r',1,4,8,red);       // red stripes
    lightLine('r',3,4,8,red);
    lightLine('r',5,1,8,red);
    lightLine('r',7,1,8,red);
    
    lightLine('r',2,4,8,white);     // white stripes
    lightLine('r',4,4,8,white);
    lightLine('r',6,1,8,white);
    
    if (io)
    {
        lightRectangle('f',1,1,4,4,blue);
        lightCell(1,1,white);
        lightCell(1,3,white);
        lightCell(2,2,white);
        lightCell(2,4,white);
        lightCell(3,1,white);
        lightCell(3,3,white);
        lightCell(4,2,white);
        lightCell(4,4,white);
        
        strip.show();
        io=0;
    }
    else
    {
        lightRectangle('f',1,1,4,4,white);
        lightCell(1,1,blue);
        lightCell(1,3,blue);
        lightCell(2,2,blue);
        lightCell(2,4,blue);
        lightCell(3,1,blue);
        lightCell(3,3,blue);
        lightCell(4,2,blue);
        lightCell(4,4,blue);
        
        strip.show();
        io=1;
    }
}
// _______________________________________________________________
// RANDOM RECTANGLES
// displays randomly-sized and randomly-colored rectangles which 
// respond to the beat and will display 5 rectangles at a time
// _______________________________________________________________
void randomRectangles(int spectrum[])
{
    int temp = counter;                     // allows for counter to be tested after
    // beat detect function  runs
    detectBeat(spectrum,1,3);
    
    if (temp != counter)                    // if beat detected, set another random rectangle
    {
        rectParameters[counter][0] = rand()%8+1;    // starting row address
        rectParameters[counter][1] = rand()%7+1;    // starting col address
        rectParameters[counter][2] = rand()%(8-rectParameters[counter][0])+1; // end row address
        rectParameters[counter][3] = rand()%(7-rectParameters[counter][1])+1; // end col address
        
        off();
        
        for (int n=0;n<7;n++)
        {
            int sRow = rectParameters[n][0];
            int sCol = rectParameters[n][1];
            int eRow = rectParameters[n][2];
            int eCol = rectParameters[n][3];
            
            lightRectangle('f',sRow,sCol,eRow,eCol,colors[n]); // light up 7 rectangles
        }
    }
    strip.show();
    
}
// _______________________________________________________________
// SPLASH SQUARES
// displays growing squares of different colors depending 
// on beats occurring on various frequency bands
// _______________________________________________________________
void splashSquares(int spectrum[])
{
    
    
    for (int n=0;n<7;n++)           // finds out which frequencies have beats
    {
        bool start = 0;
        int temp = counter;
        detectBeat(spectrum,n,4);
        if (temp !=counter)
        {
            ioArray[n] = 1;         // if beat is detected, then set random pixel
            splashArray[n][0] = 1;  // only one square per frequency band at any given time
            splashArray[n][1] = rand()%7+1; // set initial values for random cell
            splashArray[n][2] = rand()%8+1;
            splashArray[n][3] = splashArray[n][1];
            splashArray[n][4] = splashArray[n][2];
            start = 1;  // indicate the first iteration of cell
        }
        
        /*
        if (ioArray[n] == 1)
        {
            Serial.print(n);
            Serial.print(" ");
            Serial.print(start);
            Serial.print(" ");
            Serial.print(io);
            Serial.println();
        }
        */
        if (start != 1 && ioArray[n] == 1)      // grow square if its not the first iter
        {
            Serial.print(n);
            Serial.println();
            if (splashArray[n][0] < 9)  splashArray[n][0]++;
            if (splashArray[n][1] > 1)  splashArray[n][1]--;
            if (splashArray[n][2] > 1)  splashArray[n][2]--;
            if (splashArray[n][3] < 7)  splashArray[n][3]++;
            if (splashArray[n][4] < 8)  splashArray[n][4]++;
            start = 0;
        }
        
        if (splashArray[n][0] > 8)              // if square is max size, turn off
        {
            for (int m=0;m<5;m++)
            {
                splashArray[n][m] = 0;
                ioArray[n] = 0;
            }
        }
        
        if (ioArray[n] != 0)
        {
            int sRow = splashArray[n][1];
            int sCol = splashArray[n][2];
            int eRow = splashArray[n][3];
            int eCol = splashArray[n][4];
            
            lightRectangle('f',sRow,sCol,eRow,eCol,colors[n]);  // display square
        }
        
    }
}















