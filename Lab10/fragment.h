#pragma once
#include "entity.h"
#include "constants.h"
#include <cmath>

class TestStarlink;


class Fragment : public Entity
{
   //friend TestFragment;
public:
   Fragment(const Position& inPos, const Velocity& inVel)
   {
      pos = inPos;
      v = inVel;

      timeToLive = random(50, 100);
      rotation = random(-60, 60);
      alive = true;

      // Fragment radius is 2 pixels
      setRadius(2.0 * metersPerPixel);
   }
   void decay()
   {
      timeToLive -= 1;
      if (timeToLive <= 0)
         alive = false;
   }
   void spin()
   {
      angle += rotation;
   }
   void update(double dt) override
   {
      double dx = v.getDX();
      double dy = v.getDY();

      pos.setMetersX(pos.getMetersX() + dx * dt);
      pos.setMetersY(pos.getMetersY() + dy * dt);
   }
   virtual void draw(ogstream& gout) override
   {
      /*std::cout << "Drawing fragment at ("
         << pos.getMetersX() << ", "
         << pos.getMetersY() << ")\n";*/

      gout.drawFragment(pos, angle);
   }
protected:
   double rotation;
   int timeToLive;
};
