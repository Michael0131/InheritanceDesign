#pragma once

#include "satellite.h"
#include "physics.h"


void Satellite::updatePhysics(double dt)
{
   if (!alive) return;

  /* if (checkCollison(s))
      return;*/

   // update acceleration from the gravity at our current position
   double ddx = 0.0;
   double ddy = 0.0;

   Physics::computeAcceleration(pos, ddx, ddy);

   // update position
   pos.getMetersX() += dx * dt + 0.5 * ddx * dt * dt; // distance formula
   y += dy * dt + 0.5 * ddy * dt * dt; // distance formula

   // update velocity
   dx += ddx * dt;
   dy += ddy * dt;

   /*if (checkCollison(s))
      return;*/
};

