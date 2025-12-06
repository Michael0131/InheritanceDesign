#pragma once
#include "satellite.h"
#include <cmath>

class TestHubble;

class Hubble : public Satellite
{
    friend TestHubble;
public:
    Hubble()
    {
        // Hubble orbit radius 
        const double ORBIT_RADIUS_X = 0.0;
        const double ORBIT_RADIUS_Y = -42'164'000.0;

        // Correct Hubble orbital speed
        const double ORBIT_SPEED_X = 3'100.0;
        const double ORBIT_SPEED_Y = 0.0;

        // Place satellite
        pos.setMetersX(ORBIT_RADIUS_X);
        pos.setMetersY(ORBIT_RADIUS_Y);

        // Velocity tangent to orbit
        v.setDX(-ORBIT_SPEED_X);
        v.setDY(-ORBIT_SPEED_Y);

        alive = true;

        // Hubble radius is 10 pixels
        setRadius(10.0 * metersPerPixel);
    }

    virtual void draw(ogstream& gout) override
    {
        // Let Simulator compute orientation (angleToEarth)
        gout.drawHubble(pos, angle);
    }
protected:
   // Hubble breaks into 4 parts; fragments only come from those parts,
   // so whole-Hubble can have 0 fragments on breakup
   int fragmentCountOnBreakup() const override { return 0; }

   void createParts(Simulator& sim) override;
};
