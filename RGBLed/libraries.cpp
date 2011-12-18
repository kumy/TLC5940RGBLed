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

#include "WProgram.h"

#include "libraries.h"


void setColor(const double fromColor[ledColors], double toColor[ledColors]) {
  for (byte col = 0; col < ledColors; ++col) {
    toColor[col] = fromColor[col];
  }
}

void setColorAll(Led leds[ledCount], const double couleur[ledColors]) {
  for (byte led = 0; led < ledCount; ++led) {
    leds[led].setColor(couleur);
  }
}

void setPuissanceAll(Led leds[ledCount], const byte puissance) {
  for (byte led = 0; led < ledCount; ++led) {
    leds[led].setPuissance(puissance);
  }
}

void setColorRainbow(Led leds[ledCount], double salt) {
#ifdef DEBUG
  Serial.println("RAINBOW ");
#endif
  byte gradStep = HSV_DEFINITION / ledCount;

  double hsv[] = { 
    0.5, 1, 1
  };

  for (byte led = 0; led < ledCount; ++led) {
    hsv[0] = (double) gradStep * led / HSV_DEFINITION + salt;
    leds[led].setColor(hsv);
  }
}


void render(Led leds[ledCount]) {

  for (byte led = 0; led < ledCount; ++led) {
    leds[led].runMotion();
    leds[led].show();
  }

  Tlc.update();
}

void getRandomColor(double randColor[ledColors]) {
  double lastColor = randColor[0];
  while (abs(randColor[0] - lastColor) < 0.10)
  {
    randColor[0] = (1.0* (TrueRandom.random(1001)))/1000;
  } 

  randColor[1] = 1.0;
  randColor[2] = 1.0;
#ifdef DEBUG
  Serial.print("Rand: ");
  Serial.println(randColor[0]);
#endif
}



void printColor(const t_rgbColor color) {
#ifdef DEBUG
  Serial.print("(");
  Serial.print((int) color.red);
  Serial.print(";");
  Serial.print((int) color.green);
  Serial.print(";");
  Serial.print((int) color.blue);
  Serial.println(")");
#endif
}

void printColor(const double color[ledColors]) {
#ifdef DEBUG
  Serial.print("(");
  Serial.print(color[0]);
  Serial.print(";");
  Serial.print(color[1]);
  Serial.print(";");
  Serial.print(color[2]);
  Serial.println(")");
#endif
}





