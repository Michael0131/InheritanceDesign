#pragma once
#include "satellite.h"
#include <cmath>

class TestGPS;

class GPS : public Satellite
{
    friend TestGPS;

public:
   static constexpr double COLLISION_RADIUS = 300000.0; // 300 km

   /***********************************************************
     * DEFAULT CONSTRUCTOR
     * (Not tested — but required for completeness)
    ***********************************************************/
   GPS()
   {
       pos.setMetersX(0.0);
       pos.setMetersY(0.0);

       v.setDX(0.0);
       v.setDY(0.0);

       double metersPerPixel = pos.getZoom();

       // GPS radius is 12 pixels
       setRadius(12.0 * metersPerPixel);

       alive = true;
   }

   /***********************************************************
    * PARAMETERIZED CONSTRUCTOR
    * This is what ALL your tests use.
   ***********************************************************/
   GPS(double x, double y, double dx, double dy)
   {
       pos.setMetersX(x);
       pos.setMetersY(y);

       v.setDX(dx);
       v.setDY(dy);

       setRadius(COLLISION_RADIUS);

       alive = true;
   }

   /***********************************************************
    * DRAW
    ***********************************************************/
   virtual void draw(ogstream& gout) override
   {
       // Let Simulator compute the angle to Earth
       gout.drawGPS(pos, angle);
   }

   virtual void breakup() override
   {
      // create 3 parts (GPSCenterPart, GPSLeftPart, GPSRightPart)
      

      // create 2 fragments
      const int NUM_FRAGMENTS = 2;
      for (int i = 0; i < NUM_FRAGMENTS; ++i)
      {
         Fragment(pos, v);
      }

      // add them to Simulator
   }
};
