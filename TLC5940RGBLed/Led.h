// Copyright (c) 2011 Mathieu Alorent
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef Led_h
#define Led_h

#include "WProgram.h"

#include "Tlc5940.h"
#include "RGBConverter.h"

// Set this to the number of color of each strip
#define LED_COLORS 3

// Set this to the number of individual RGB Led
#define LED_COUNT 15

// comment/uncomment acording to you're led type
#define COMMON_ANODE

//#define DEBUG

#define RED   0
#define GREEN 0.66
#define BLUE  0.33

#define YELLOW  0.83
#define CYAN    0.5
#define MAGENTA 0.16

#define TRUE  1
#define FALSE 0

#define MAX_POWER 16

const double blue[]    = { BLUE   , 1, 1 };
const double red[]     = { RED    , 1, 1 };
const double green[]   = { GREEN  , 1, 1 };

const double yellow[]  = { YELLOW , 1, 1 };
const double cyan[]    = { CYAN   , 1, 1 };
const double magenta[] = { MAGENTA, 1, 1 };

const double white[]   = { RED    , 0, 1 };
const double black[]   = { RED    , 0, 0 };

typedef struct  {
  byte red;
  byte green;
  byte blue;
} t_rgbColor;

class Led {
  public:
    
    Led ();
    void init ();
    void init (byte ledNumber);
    
    void setColor (const double hsv[LED_COLORS]);
    void setColor (const double hsv[LED_COLORS], unsigned long timeChange);

    double* getColor();
    
    void setPuissance(const byte puissance);
    
    void upColor   (const double   upStep);
    void downColor (const double downStep);
    
    void show();
    void printPins(byte pin, byte color, int puissance);
    
    void runMotion();
    
  private:
	 RGBConverter _converter;

    byte       _pins[LED_COLORS];
    double     _hsv[LED_COLORS];  // CurColor
    t_rgbColor _rgb;  // CurColor
    int        _puissance;
    
    t_rgbColor toColor;
    t_rgbColor fromColor;
    double Steps;
    byte curStep;
    
    unsigned long transitionBegin;
    unsigned long transitionEnd;
    unsigned long timeChange;
    boolean       transitionEnded;
    
    inline void hsvToRgb() { Led::hsvToRgb(Led::_hsv, Led::_rgb); };
    void hsvToRgb(const double hsv[LED_COLORS], t_rgbColor& rgb);
    
    inline void rgbToHsv() { Led::rgbToHsv(Led::_rgb, Led::_hsv); };
    void rgbToHsv(const t_rgbColor rgb, double hsv[]);
    
};

#endif
