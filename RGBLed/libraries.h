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

#ifndef Libraries_h
#define Libraries_h

#include <TrueRandom.h>

#include "WProgram.h"
#include "Led.h"

#define ON  1
#define OFF 0

//#define MAX_LED_COLOR 255
#define HSV_DEFINITION 360

boolean getGlobalStatus ();

void setStatus (boolean ledStatus);
boolean getStatus ();

void setStatusOn ();
void setStatusOff ();

void setColor(const double fromColor[ledColors], double toColor[ledColors]);

void setColorAll(Led leds[ledCount], const double couleur[ledColors]);
void setPuissanceAll(Led leds[ledCount], const byte puissance);

void setColorRainbow(Led leds[ledCount], double salt = 0.0);
void render(Led leds[ledCount]);

void getRandomColor(double randColor[ledColors]);

void printColor(const t_rgbColor color);
void printColor(const double color[ledColors]);

#endif
