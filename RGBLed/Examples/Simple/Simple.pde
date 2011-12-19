// Copyright (c) 2011 Mathieu Alorent
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.

#include <Tlc5940.h>
#include <RGBConverter.h>
#include <TrueRandom.h>
#include <Effect.h>
#include <EffectRainbow.h>


Led leds[ledCount];
EffectRainbow effect;

void setup()
{
  effect.init(leds);
}


void loop()
{
  effect.run();
}
