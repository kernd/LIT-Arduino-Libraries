

#include <iostream>

#include "Grid.h"

// constructor
Grid :: Grid(int rows, int cols)
:rows(rows),
cols(cols),
num(rows*cols)

{
    strip       = new LPD8806(num,dataPin,clockPin);
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

void Grid :: drawPixel(int r,int c,uint32_t color)
{
    strip->setPixelColor(address(r,c),color);
}

void Grid :: drawXLine(int r,int c1,int c2,int color)
{
    swap(c1,c2);
    
    for (int n=c1;n<=c2;n++)
    {
        drawPixel(r,n,color);
    }
}

void Grid :: drawYLine(int c,int r1,int r2,int color)
{
    swap(r1,r2);
    
    for (int n=r1;n<=r2;n++)
    {
        drawPixel(n,c,color);
    }
}

void Grid :: drawRectangle(bool fill,int r1,int c1,int r2,int c2,int color)
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
    int colorArray[] = {red,yellow,green,cyan,blue,magenta,white};
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




