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
#include "EffectRainbow.h"

void EffectRainbow::init(Led leds[ledCount]) {
  Effect::storeLeds(leds);
}

void EffectRainbow::init() {
  Effect::totalTime = 0;
  Effect::lastTime = 0;
  delai = 50;
  way = 1;
  EffectRainbow::salt = 0.0;

  Effect::setSpeed(totalTime);
}

void EffectRainbow::run () {
  EffectRainbow::run_rainbow();
}

void EffectRainbow::run_rainbow () {

  //if (Effect::timeToRun(Effect::speed)) {
    setColorRainbow(EffectRainbow::_leds, EffectRainbow::salt);

    //if (++delai > 10) {
      //delai = 0;
      if (way && ++Effect::totalTime >= 2 * delai) {
        way = 0;
      }
      else if (!way && --Effect::totalTime == 1) {
        way = 1;
      }
    EffectRainbow::salt += 0.01/delai*Effect::totalTime;
    //}
    //Effect::lastTime = micros();
  //}
}


