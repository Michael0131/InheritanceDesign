#include "physics.h"

#include "position.h"


double Physics::computeHeight(const Position& pos)
{
   double distanceFromCenter = sqrt(pos.getMetersX() * pos.getMetersX() + pos.getMetersY() * pos.getMetersY());
   return distanceFromCenter - EARTH_RADIUS;
}

double Physics::computeGravity(double h)
{
   return GRAVITY_SEA_LEVEL * pow(EARTH_RADIUS / (EARTH_RADIUS + h), 2.0);
}

double Physics::computeGravityAngle(const Position& pos)
{
   return atan2(-pos.getMetersX(), -pos.getMetersY());
}

double Physics::computeAcceleration(const Position& pos, double& ddx, double& ddy)
{
   double h = computeHeight(pos);
   double g = computeGravity(h);
   double angle = computeGravityAngle(pos);

   ddx = g * sin(angle);
   ddy = g * cos(angle);

   return ddx, ddy;
}