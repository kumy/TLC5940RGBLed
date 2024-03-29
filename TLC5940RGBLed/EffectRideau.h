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

#ifndef EffectRideau_h
#define EffectRideau_h

#include "WProgram.h"
#include "TrueRandom.h"

#include "Led.h"
#include "Effect.h"
#include "libraries.h"

class EffectRideau : 
public Effect {
public:
  inline EffectRideau() { /* nothing*/ };
  EffectRideau(Led leds[LED_COUNT]);

  void init();
  void init(byte preset);
  void run();
  void runDemo();

private:

  byte startPoint;
  void run_single();
  void run_double();

  double color[LED_COLORS];

  boolean onOff;
  byte presets;

  byte trainee;

  void nextPreset();
};
#endif


