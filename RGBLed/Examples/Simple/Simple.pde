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
