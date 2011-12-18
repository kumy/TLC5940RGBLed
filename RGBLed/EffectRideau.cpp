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
#include "EffectRideau.h"

void EffectRideau::init(Led leds[ledCount]) {
  Effect::storeLeds(leds);
  EffectRideau::presets = 0;
  EffectRideau::onOff = TRUE;

}

void EffectRideau::init(byte preset) {
  EffectRideau::presets = preset;
  EffectRideau::init();
}

void EffectRideau::init() {

  Effect::totalTime = 1;
  int pauseTime = 0;

  Effect::lastTime = 0;
  Effect::step = 0;

  Effect::setSpeed(totalTime*1000000/(ledCount - 1));
  Effect::setPause(pauseTime*1000000);
  Effect::effectEnded = FALSE;

  switch (EffectRideau::presets) {
  case 0:
    Effect::print("PRESETS 0");
    EffectRideau::startPoint = 0;
    EffectRideau::trainee = 0;
    getRandomColor(EffectRideau::color);
    break;
  case 1:
    Effect::print("PRESETS 1");
    EffectRideau::startPoint = ledCount - 1;
    EffectRideau::trainee = 0;
    getRandomColor(EffectRideau::color);
    break;
  case 2:
    Effect::print("PRESETS 2");
    EffectRideau::startPoint = 6;
    EffectRideau::trainee = 0;
    break;
  case 3:
    Effect::print("PRESETS 3");
    EffectRideau::startPoint = TrueRandom.random(ledCount);
    EffectRideau::trainee = 0;
    setColor(black, EffectRideau::color);
    break;
  case 4:
    Effect::print("PRESETS 4");
    EffectRideau::startPoint = 0;
    EffectRideau::trainee = 1;
    getRandomColor(EffectRideau::color);
    break;
  case 5:
    Effect::print("PRESETS 5");
    EffectRideau::startPoint = ledCount - 1;
    EffectRideau::trainee = 1;
    //getRandomColor(EffectRideau::color);
    break;
  case 6:
    Effect::print("PRESETS 6");
    EffectRideau::startPoint = TrueRandom.random(ledCount);
    EffectRideau::trainee = 1;
    break;
  case 7:
    Effect::print("PRESETS 7");
    EffectRideau::startPoint = 0;
    EffectRideau::trainee = 0;
    setColor(black, EffectRideau::color);
    break;
  case 8:
    Effect::print("PRESETS 8");
    EffectRideau::startPoint = ledCount - 1;
    EffectRideau::trainee = 0;
    setColor(black, EffectRideau::color);
    break;
  }
}

void EffectRideau::nextPreset() { 
  EffectRideau::presets = (++EffectRideau::presets)%7;
}

void EffectRideau::run () {
  EffectRideau::run_single();
}

void EffectRideau::runDemo () {
  EffectRideau::run();
  
  if(Effect::effectEnded == TRUE) {
   //EffectRideau::nextPreset();
    if (EffectRideau::onOff) {
      getRandomColor(EffectRideau::color);
    }     
    else {
      if (EffectRideau::presets< 4)
        setColor(black, EffectRideau::color);
        EffectRideau::nextPreset();
    }
    
    EffectRideau::onOff = abs(EffectRideau::onOff - 1);

    EffectRideau::init();
  }
}

void EffectRideau::run_single () {
  if (Effect::effectEnded && Effect::timeToRun(Effect::pause)) {
    Effect::effectEnded = FALSE;
  } 

  if (!Effect::effectEnded && Effect::timeToRun(Effect::speed)) {
    if (EffectRideau::startPoint + step - EffectRideau::trainee < ledCount) {
      if (EffectRideau::startPoint + step < ledCount)
        Effect::_leds[EffectRideau::startPoint + step].setColor(EffectRideau::color, min(1, (double)Effect::totalTime/ledCount)*1000000);
      if (EffectRideau::trainee && step >= EffectRideau::trainee)
        Effect::_leds[EffectRideau::startPoint + step -EffectRideau::trainee].setColor(black, min(1, (double)Effect::totalTime/ledCount)*1000000);
    }
    if (EffectRideau::startPoint - step + EffectRideau::trainee >= 0) {
      if (EffectRideau::startPoint - step < ledCount)
        Effect::_leds[EffectRideau::startPoint - step].setColor(EffectRideau::color, min(1, (double)Effect::totalTime/ledCount)*1000000);
      if (EffectRideau::trainee && step >= EffectRideau::trainee)
        Effect::_leds[EffectRideau::startPoint - step +EffectRideau::trainee].setColor(black, min(1, (double)Effect::totalTime/ledCount)*1000000);
    }

    Effect::step++;
    Effect::lastTime = micros();

    if (Effect::step >= ledCount + EffectRideau::trainee) {
      Effect::effectEnded = TRUE;
      //EffectRideau::nextPreset();
      //EffectRideau::init();
    }
  }
}

//void EffectRideau::run_double () {
//  if (Effect::effectEnded && Effect::timeToRun(Effect::pause)) {
//    Effect::effectEnded = FALSE;
//  } 
//
//  if (!Effect::effectEnded && Effect::timeToRun(Effect::speed)) {
//    if (EffectRideau::startPoint + step < ledCount)
//      Effect::_leds[EffectRideau::startPoint + step].setColor(EffectRideau::color, min(1, (double)Effect::totalTime/ledCount)*1000000);
//    if (EffectRideau::startPoint - step >= 0)
//      Effect::_leds[EffectRideau::startPoint - step].setColor(EffectRideau::color, min(1, (double)Effect::totalTime/ledCount)*1000000);
//
//    Effect::step++;
//    Effect::lastTime = micros();
//
//    if (Effect::step >= ledCount) {
//      Effect::effectEnded = TRUE;
//      EffectRideau::init();
//    }
//  }
//}
