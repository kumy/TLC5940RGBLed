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
#include "Led.h"

Led::Led () {
  Led::init();
}

void Led::init () {
  Led::setPuissance(0);
  Led::setColor(white);
  Led::runMotion();
}

void Led::init (byte ledNumber) {
  for (byte i = 0; i < LED_COLORS; ++i) {
    Led::_pins[i] = ledNumber * LED_COLORS + i;
  }
  Led::init();
}

void Led::setColor(const double hsv[LED_COLORS]) {
  Led::setColor(hsv, 0);
}

void Led::setColor(const double hsv[LED_COLORS], unsigned long timeChange) {
  hsvToRgb(Led::_hsv, Led::fromColor);
  hsvToRgb(hsv,       Led::toColor);

  Led::transitionEnded = FALSE;
  Led::curStep = 0;
  Led::timeChange = timeChange;
}

void Led::runMotion () {
  if (Led::transitionEnded == TRUE)
    return;

  switch (Led::curStep) {
  case 0:
    Led::transitionBegin = micros();
    Led::transitionEnd = Led::transitionBegin + Led::timeChange;
    Led::curStep++;
  case 1:
    unsigned long timeNow = micros();

    if (timeNow >= Led::transitionEnd || Led::timeChange == 0) {
      Led::rgbToHsv(Led::toColor, Led::_hsv);
      Led::transitionEnded = TRUE;
    } 
    else {
      double ratioTemps = 1.0* (timeNow - Led::transitionBegin) / Led::timeChange;

      Led::_rgb.red   = Led::fromColor.red   + (Led::toColor.red   - Led::fromColor.red)   * ratioTemps;
      Led::_rgb.green = Led::fromColor.green + (Led::toColor.green - Led::fromColor.green) * ratioTemps;
      Led::_rgb.blue  = Led::fromColor.blue  + (Led::toColor.blue  - Led::fromColor.blue)  * ratioTemps;

      Led::rgbToHsv(Led::_rgb, Led::_hsv);
    }
    break;
  }

  //Led::show();
}


void Led::setPuissance(const byte puissance) {
  if (puissance >= MAX_POWER) {
    Led::_puissance = MAX_POWER;
  } 
  else {
    Led::_puissance = puissance;
  }
}

void Led::upColor   (const double   upStep) {
  Led::_hsv[0] += upStep;

  if (Led::_hsv[0] >= 1) {
    Led::_hsv[0] = 0;
  } 
  else if (Led::_hsv[0] <= 0) {
    Led::_hsv[0] = 1;
  }
}
void Led::downColor (const double downStep) {
  Led::upColor(- downStep);
}

double* Led::getColor() {
  return Led::_hsv;
}

void Led::hsvToRgb(const double hsv[LED_COLORS], t_rgbColor& rgb) {
  byte rgbArray[3];
  Led::_converter.hsvToRgb(hsv[0], hsv[1], hsv[2], rgbArray);
  rgb.red   = rgbArray[0];
  rgb.green = rgbArray[1];
  rgb.blue  = rgbArray[2];
}

void Led::rgbToHsv(const t_rgbColor rgb, double hsv[]) {
  Led::_converter.rgbToHsv(rgb.red, rgb.green, rgb.blue, hsv);
}

void Led::show () {

  Led::hsvToRgb();

#ifdef COMMON_ANODE
  Tlc.set((int) Led::_pins[0], Led::_rgb.green * Led::_puissance);
  Tlc.set((int) Led::_pins[1], Led::_rgb.blue  * Led::_puissance);
  Tlc.set((int) Led::_pins[2], Led::_rgb.red   * Led::_puissance);
#endif
#ifndef COMMON_ANODE
  Tlc.set((int) Led::_pins[0], 4095 - (Led::_rgb.green * Led::_puissance) - 1);
  Tlc.set((int) Led::_pins[1], 4095 - (Led::_rgb.blue  * Led::_puissance) - 1);
  Tlc.set((int) Led::_pins[2], 4095 - (Led::_rgb.red   * Led::_puissance) - 1);
#endif
}

void Led::printPins (byte pin, byte color, int puissance) {
#ifdef DEBUG
  Serial.print("set pin ");
  Serial.print((int) pin);
  Serial.print(" to color (");
  Serial.print((int) color);
  Serial.print(") ");
  Serial.print(" [");
  Serial.print(puissance);
  Serial.print("] ");
  Serial.print(" => ");
  Serial.print((int) color * puissance);
  Serial.print(" ::> ");
#ifdef COMMON_ANODE
  Serial.println((int)  4094 - (4095 - (color * puissance)-1));
#endif
#ifndef COMMON_ANODE
  Serial.println((int)  4095 - (color * puissance) -1);
#endif
#endif
}























