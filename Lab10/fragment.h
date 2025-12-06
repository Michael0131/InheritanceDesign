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
      double metersPerPixel = pos.getZoom();

      // 
      double theta = random(0, 360) * PI / 180.0;
      double kick = random(5000, 9000);

      // Place fragment
      pos.setMetersX(inPos.getMetersX() + (4 * metersPerPixel) * cos(theta));
      pos.setMetersY(inPos.getMetersY() + (4 * metersPerPixel) * sin(theta));

      // set Velocity
      v.setDX(inVel.getDX() + kick * cos(theta));
      v.setDY(inVel.getDY() + kick * sin(theta));

      timeToLive = random(50, 100);

      alive = true;
      rotation = random(-60, 60);

      

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
