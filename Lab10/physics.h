#pragma once
#include <cmath>

#include "position.h"


class TestPhysics;

class Physics
{
	friend TestPhysics;
public:

   static constexpr double EARTH_RADIUS = 6378000.0;
   static constexpr double GRAVITY_SEA_LEVEL = 9.80665;

   double computeHeight(const Position& pos);
   double computeGravity(double h);
   double computeGravityAngle(const Position& pos);
   void computeAcceleration(const Position& pos, double& ddx, double& ddy);


};

