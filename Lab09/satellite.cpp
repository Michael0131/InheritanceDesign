#pragma once

#include "satellite.h"
#include "physics.h"


void Satellite::updatePhysics(double dt)
{
   if (!alive) return;

   // update acceleration from the gravity at our current position
   double ddx = 0.0;
   double ddy = 0.0;

   Physics p;
   p.computeAcceleration(pos, ddx, ddy);

   // get current position and velocity  
   double x = pos.getMetersX();
   double y = pos.getMetersY();
   double dx = v.getDX();
   double dy = v.getDY();

   // update position
   x += dx * dt + 0.5 * ddx * dt * dt; // distance formula
   y += dy * dt + 0.5 * ddy * dt * dt; // distance formula
   pos.setMetersX(x);
   pos.setMetersY(y);

   // update velocity
   dx += ddx * dt;
   dy += ddy * dt;
   v.setDX(dx);
   v.setDY(dy);

   pos.setMetersX(x);

};


void Satellite::draw(ogstream& /*gout*/)
{
   // Base satellite does nothing. Specific satellites (GPS, etc.) override this.
}


//bool checkCollison(Satellite& s)
//{
//   double h = computeHeight(s.x, s.y);
//   if (h <= 0)
//   {
//      s.alive = false;
//      return true;
//   }
//   return false;
//}