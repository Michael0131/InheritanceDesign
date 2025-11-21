#pragma once
#include "entity.h"
#include "physics.h"
#include <cmath>

class TestDreamChaser;

class DreamChaser : public Entity
{
   friend TestDreamChaser;
public:
   DreamChaser()
   {
      // GPS orbit radius (Earth radius + 20,200 km)
      //const double ORBIT_RADIUS = 26'578'000.0;

      // Correct GPS orbital speed (~3,874 m/s)
      //const double ORBIT_SPEED = 3874.0;

      // Place ship at (-450.0px, 450.0px)
      pos.setPixelsX(-450.0);
      pos.setPixelsY(450.0);

      // Velocity: (0.0 m/s, -2,000 m/s)
      v.setDX(0.0);
      v.setDY(-2000.0);

      thrustPower = 2.0;
      alive = true;
      angle = 0.0;
   }
   void rotate(float direction)
   {
      angle += direction;
      return;
   }
   void thrust(bool isThrust)
   {
      this->isThrust = isThrust;
      return;
   }
   bool getThrust() {
      return isThrust;
   }
   double getRotation() {
      return angle;
   }
   void fire()
   {
      // Empty for now
   }
   void draw(ogstream& gout) override
   {
      // Let Simulator compute orientation (angleToEarth)
      gout.drawShip(pos, angle, isThrust);
   }
   void update(double dt)
   {
      if (!alive)
         return;

      Physics physics;

      // Get current position
      double x = pos.getMetersX();
      double y = pos.getMetersY();

      // Check collision BEFORE moving
      double h = physics.computeHeight(pos);
      if (h <= 0)
      {
         alive = false;
         return;
      }

      // Compute acceleration (gravity)
      double ddx = 0.0;
      double ddy = 0.0;
      physics.computeAcceleration(pos, ddx, ddy);

      // Get velocity
      double dx = v.getDX();
      double dy = v.getDY();

      // Update position (x = x + v*t + 1/2 a t�)
      x += dx * dt + 0.5 * ddx * dt * dt;
      y += dy * dt + 0.5 * ddy * dt * dt;

      pos.setMetersX(x);
      pos.setMetersY(y);

      // Update velocity (v = v + a*t)
      dx += ddx * dt;
      dy += ddy * dt;

      v.setDX(dx);
      v.setDY(dy);

      // Check collision AFTER moving
      h = physics.computeHeight(pos);
      if (h <= 0)
      {
         alive = false;
      }
   }
protected:
   double thrustPower;
   bool isThrust;
};