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

#ifndef Effect_h
#define Effect_h

#include "WProgram.h"
#include "Led.h"

class Effect {
  public:
        
    inline Effect() {};
    inline Effect(Led leds[ledCount]) { storeLeds(leds); };
    
    void inline init() { /*nothing*/ };
    
    void setNext();
    void setSpeed(unsigned long speed);
    void setPause(unsigned long pause);
    
    boolean isEnded();
    
  protected:
    unsigned long lastTime;
    unsigned long totalTime;
    unsigned long speed;
    unsigned long pause;
    boolean effectEnded;
    byte step;
    Led *_leds;
    
    void storeLeds(Led leds[ledCount]);
    inline boolean timeToRun(unsigned long speed) { return !Effect::lastTime || micros() - Effect::lastTime >= speed; };
    
    void print (const char* txt);
  
};

#endif
