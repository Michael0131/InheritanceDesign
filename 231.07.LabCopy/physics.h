#pragma once
#include <cmath>

#include "position.h"

// Constants
const double GRAVITY_SEA_LEVEL = 9.80665;
const double EARTH_RADIUS = 6'378'000.0;


class Physics
{
public:

   double computeHeight(const Position& pos);
   double computeGravity(double h);
   double computeGravityAngle(const Position& pos);
   void computeAcceleration(const Position& pos, double& ddx, double& ddy);


};

