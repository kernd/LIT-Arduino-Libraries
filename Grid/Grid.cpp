#include <iostream>

#include "Grid.h"

// get rid of this shit if it doesn't work? or figure out a function which can
// initialize it all instead?

int smiley1xmap[] = {3,4,5,14,15,16,3,4,5,6,13,14,15,16,4,5,6,7,12,13,14,15,5,6,7,8,11,12,13,14,6,7,8,9,10,11,12,13,7,8,9,10,11,12};
int smiley1ymap[] = {11,11,11,11,11,11,12,12,12,12,12,12,12,12,13,13,13,13,13,13,13,13,14,14,14,14,14,14,14,14,15,15,15,15,15,15,15,15,16,16,16,16,16,16};

int leftEyeOpenXmap[] = {5,4,5,6,3,4,5,6,7,4,5,6,5};
int leftEyeOpenYmap[] = {2,3,3,3,4,4,4,4,4,5,5,5,6};

int rightEyeOpenXmap[] = {14,13,14,15,12,13,14,15,16,13,14,15,14};
int rightEyeOpenYmap[] = {2,3,3,3,4,4,4,4,4,5,5,5,6};

int leftWinkXmap[] = {7,3,4,5,6,7};
int leftWinkYmap[] = {3,4,4,4,4,4};

int rightWinkXmap[] = {12,12,13,14,15,16};
int rightWinkYmap[] = {3,4,4,4,4,4};

int oFaceXmap[] = {4, 15,7,8,9,10,11,12,6,7,8,9,10,11,12,13,5,6,7,8,11,12,13,14,4,5,6,7,12,13,14,15,3,4,5,6,13,14,15,16,3,4,5,14,15,16,3,4,5,14,15,16,3,4,5,6,13,14,15,16,4,5,6,7,12,13,14,15,5,6,7,8,11,12,13,14,6,7,8,9,10,11,12,13,7,8,9,10,11,12};
int oFaceYmap[] = {2,2,5,5,5,5,5,5,6,6,6,6,6,6,6,6,7,7,7,7,7,7,7,7,8,8,8,8,8,8,8,8,9,9,9,9,9,9,9,9,10,10,10,10,10,10,11,11,11,11,11,11,12,12,12,12,12,12,12,12,13,13,13,13,13,13,13,13,14,14,14,14,14,14,14,14,15,15,15,15,15,15,15,15,16,16,16,16,16,16};

// constructor
Grid :: Grid(int rows, int cols)
:rows(rows),
cols(cols),
num(rows*cols)

{
    strip       = new ;
    freqChip    = new FFT(fftAnalogPin,fftStrobePin,fftResetPin);
}

int Grid :: address(int r,int c)
{
    if ((rows+r) % 2 == 0)  return (rows-r)*cols + c - 1;   // going right
    else                    return (rows-r)*cols + cols-c;  // going left
}

void Grid :: swap(int &var1,int &var2)
{
    if (var1>var2)
    {
        int temp = var1;
        var1=var2;
        var2=temp;
    }
}

void Grid :: update()
{
    strip->show();
}

void Grid :: allOff()
{
    for (int n=1;n<=rows;n++)
    {
        drawXLine(n,1,cols,black);
    }
}

void Grid :: drawPixel(int r,int c,long color)
{
    strip->setPixelColor(address(r,c),color);
}

void Grid :: drawXLine(int r,int c1,int c2,long color)
{
    swap(c1,c2);
    
    for (int n=c1;n<=c2;n++)
    {
        drawPixel(r,n,color);
    }
}

void Grid :: drawYLine(int c,int r1,int r2,long color)
{
    swap(r1,r2);
    
    for (int n=r1;n<=r2;n++)
    {
        drawPixel(n,c,color);
    }
}

void Grid :: drawRectangle(bool fill,int r1,int c1,int r2,int c2,long color)
{
    swap(r1,r2);
    swap(c1,c2);
    
    switch (fill)
    {
        case 0: // outline
            drawXLine(r1,c1,c2,color);
            drawXLine(r2,c1,c2,color);
            drawYLine(c1,r1,r2,color);
            drawYLine(c2,r1,r2,color);
            break;
            
        case 1: // filled
            for (int n=r1;n<=r2;n++)
            {
                drawXLine(n,c1,c2,color);
            }
            break;
    }
}

void Grid :: testEverything()
{
    delay(2000);
    drawPixel(2,4,red);
    drawPixel(17,1,blue);
    drawPixel(14,13,green);
    update();
    delay(2000);
    drawXLine(12,3,16,magenta);
    drawXLine(13,16,3,cyan);
    update();
    delay(2000);
    allOff();
    drawYLine(2,1,18,white);
    drawYLine(3,17,2,red);
    update();
    delay(2000);
    allOff();
    drawRectangle(0,5,5,8,8,blue);
    drawRectangle(1,18,18,9,10,green);
    update();
    
}

void Grid :: splashSquares()
{
    int splashArray[7][5];
    int *spectrum;
    long colorArray[] = {red,yellow,green,cyan,blue,magenta,white};
    bool growing=0;
    int timeDelay = 20;
    
    while (1)
    {
        spectrum = freqChip->sample();      // read spectrum
        
        
        
        for (int n=0;n<7;n++)               // set initial vals
        {
            splashArray[n][0] = spectrum[n]/100;    // map 0-1023 to 0-10
            splashArray[n][1] = rand()%rows+1;
            splashArray[n][2] = rand()%cols+1;
            splashArray[n][3] = splashArray[n][1];
            splashArray[n][4] = splashArray[n][2];
            
            int r1 = splashArray[n][1];
            int c1 = splashArray[n][2];
            int r2 = splashArray[n][3];
            int c2 = splashArray[n][4];
            
            if (splashArray[n] !=0)
                drawRectangle(1,r1,c1,r2,c2,colorArray[n]);
        }
        update();
        delay(timeDelay);
        allOff();
        
        for (int n=0;n<7;n++)
        {
            growing = growing | splashArray[n][0];
        }
        
        while (growing)
        {
            for (int n=0;n<7;n++)
            {
                if (splashArray[n][4]-splashArray[n][2] >= splashArray[n][0] || splashArray[n][0] == 0)
                {
                    splashArray[n][0] = 0;
                }
                else
                {
                    splashArray[n][1] = splashArray[n][1]--;
                    splashArray[n][2] = splashArray[n][2]--;
                    splashArray[n][3] = splashArray[n][3]++;
                    splashArray[n][4] = splashArray[n][4]++;
                    
                    int r1 = splashArray[n][1];
                    int c1 = splashArray[n][2];
                    int r2 = splashArray[n][3];
                    int c2 = splashArray[n][4];
                    
                    drawRectangle(1,r1,c1,r2,c2,colorArray[n]);
                }
            }
            update();
            delay(timeDelay);
            allOff();
            
            for (int n=0;n<7;n++)
            {
                growing = !growing | splashArray[n][0];
            }
            //Serial.println(growing);
        }
    }
}

void Grid :: splashSquares2()
{
    int splashArray[7][5] = {0};
    int *spectrum;
    int colorArray[] = {red,yellow,green,cyan,blue,magenta,white};
    bool start=0;
    int timeDelay = 30;
    
    while (1)
    {
        spectrum = freqChip->sample();      // read spectrum
        
        for (int n=0;n<7;n++)               // set initial vals
        {
            int size    = splashArray[n][0];
            int r1      = splashArray[n][1];
            int c1      = splashArray[n][2];
            int r2      = splashArray[n][3];
            int c2      = splashArray[n][4];
            
            if (size == 0)
            {
                if (freqChip->detectBeat(spectrum,n,50))
                {
                    size = 1;
                    r1   = rand()%rows+1;
                    c1   = rand()%cols+1;
                    r2   = splashArray[n][1];
                    c2   = splashArray[n][2];
                    
                    drawRectangle(1,r1,c1,r2,c2,colorArray[n]);
                    
                    start = 1;
                    
                    splashArray[n][0] = size;
                    splashArray[n][1] = r1;
                    splashArray[n][2] = c1;
                    splashArray[n][3] = r2;
                    splashArray[n][4] = c2;
                }

            }
                        
            if (start !=1 && size !=0)
            {
                size    = splashArray[n][0];
                r1      = splashArray[n][1];
                c1      = splashArray[n][2];
                r2      = splashArray[n][3];
                c2      = splashArray[n][4];
                
                if (size < 7)
                {
                    size++;
                    r1--;
                    c1--;
                    r2++;
                    c2++;
                    drawRectangle(1,r1,c1,r2,c2,colorArray[n]);
                    
                    splashArray[n][0] = size;
                    splashArray[n][1] = r1;
                    splashArray[n][2] = c1;
                    splashArray[n][3] = r2;
                    splashArray[n][4] = c2;
                }
                else
                {
                    size    = 0;
                    r1      = 0;
                    c1      = 0;
                    r2      = 0;
                    c2      = 0;
                    
                    splashArray[n][0] = size;
                    splashArray[n][1] = r1;
                    splashArray[n][2] = c1;
                    splashArray[n][3] = r2;
                    splashArray[n][4] = c2;
                    
                }
            }
            
            update();
            start = 0;
            allOff();
            delay(timeDelay);
        }
    }
}
/*
void Grid :: bassPulse()
{
    allOff();
    int *spectrum = freqChip->sample();
    int bass = spectrum[1]/100;
    
    for (int n=0;n<bass;n++)
    {
        drawRectangle(0,9-n,9-n,10+n,10+n,cyan);
    }
    update();
}
*/
void Grid :: pulse(int channel,int row1,int col1,int maxSize)
{
    //int timeDelay = 30;     // get this out of function
    long colorArray[] = {red,yellow,green,cyan,blue,magenta,white};
    
    //allOff();
    int *spectrum = freqChip->sample();
    
    
    for (int n=0;n<spectrum[channel]*maxSize/2046;n++)
    {
        drawRectangle(0,row1-n,col1-n,row1+1+n,col1+1+n,colorArray[channel]);
    }
    //update();
    //delay(timeDelay);
}

void Grid :: squarePulses()
{
    allOff();
    /*
    for (int n=1;n<6;n++)
    {
        int a1=rand()%18+1;
        int a2=rand()%18+1;
        int a3;
        if (a1 < a2) a3 = 2*(18-a1);
        else a3 = 2*(18-a2);
        pulse(n,a1,a2,a3);
    }
    */
    pulse(5,3,15,6);
    pulse(4,4,4,8);
    pulse(3,14,5,10);
    pulse(2,15,15,8);
    pulse(1,9,9,12);
    
    update();
    delay(30);
    
}

void Grid :: equalizer()
{
    
    int* spectrum;
    int timeDelay = 30;
    int colorArray[] = {red,yellow,green,cyan,blue,magenta,white};
    
    while (1)
    {
        spectrum = freqChip->sample();
        for (int n=0;n<7;n++)
        {
            drawRectangle(1,18,2*n+1,18-spectrum[n]/50,2*n+2,blue);
        }
        update();
        delay(timeDelay);
        allOff();
    }
    
}

void Grid :: smiley1(long color)
{
    for(int i=0; i < 44; i++)
    {
        drawPixel(smiley1ymap[i], smiley1xmap[i], color);
    }
}

void Grid :: rightEyeOpen(long color)
{
    for(int i=0; i < 13; i++)
    {
        drawPixel(rightEyeOpenYmap[i], rightEyeOpenXmap[i], color);
    }
}

void Grid :: leftEyeOpen(long color)
{
    for(int i=0; i < 13; i++)
    {
        drawPixel(leftEyeOpenYmap[i], leftEyeOpenXmap[i], color);
    }
}

void Grid :: rightWink(long color)
{
    for(int i=0; i < 6; i++)
    {
        drawPixel(rightWinkYmap[i], rightWinkXmap[i], color);
    }
}

void Grid :: leftWink(long color)
{
    for(int i=0; i < 6; i++)
    {
        drawPixel(leftWinkYmap[i], leftWinkXmap[i], color);
    }
}

void Grid :: oFace(long color)
{
    for(int i=0; i < 90; i++)
    {
        drawPixel(oFaceYmap[i], oFaceXmap[i], color);
    }
}

void Grid :: faceFreq()
{
    
}






