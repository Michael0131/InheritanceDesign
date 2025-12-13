#pragma once


#include "entity.h"

class Star : public Entity
{
public:
   Star(const Position& ptUpperRight)
   {
      pos.setPixelsX(ptUpperRight.getPixelsX() * random(-0.5, 0.5));
      pos.setPixelsY(ptUpperRight.getPixelsY() * random(-0.5, 0.5));
      phase = random(0, 255);
   }

   virtual void update() { phase++; }

   virtual void draw(ogstream& gout) { gout.drawStar(pos, phase); }

private: 
   unsigned char phase;
};
