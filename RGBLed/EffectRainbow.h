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

#ifndef EffectRainbow_h
#define EffectRainbow_h

#include "WProgram.h"
#include "Led.h"
#include "libraries.h"
#include "config.h"
#include "Effect.h"
#include "constants.h"

class EffectRainbow : 
public Effect {
public:
  inline EffectRainbow() { /* nothing*/
  };

  void init();
  void init(Led leds[ledCount]);
  void run();

private:

  void run_rainbow ();

  double color[ledColors];

  //boolean onOff;
  byte presets;
  double salt;
  //byte trainee;
  byte delai;
  byte way;

  void nextPreset();
};
#endif


