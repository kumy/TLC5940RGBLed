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
#include "Effect.h"

void Effect::setSpeed(unsigned long  speed) {
  Effect::speed = speed;
}

void Effect::setPause(unsigned long  pause) {
  Effect::pause = pause;
}

void Effect::storeLeds(Led leds[LED_COUNT]) {
    Effect::_leds = leds;
}

boolean Effect::isEnded(){
  return Effect::effectEnded;
}

void Effect::print (const char* txt) {
#ifdef DEBUG
  Serial.print("Effect: ");
  Serial.println(txt);
#endif
}

