#pragma once
#include "satellite.h"
#include <cmath>

class TestSputnik;

class Sputnik : public Satellite
{
    friend TestSputnik;
public:
    Sputnik()
    {
        // Sputnik orbit radius
        const double ORBIT_RADIUS_X = -36'515'095.13;
        const double ORBIT_RADIUS_Y = 21'082'000.0;

        // Correct Sputnik orbital speed
        const double ORBIT_SPEED_X = 2'050.0;
        const double ORBIT_SPEED_Y = 2'684.68;

        // Place satellite
        pos.setMetersX(ORBIT_RADIUS_X);
        pos.setMetersY(ORBIT_RADIUS_Y);

        // Velocity tangent to orbit
        v.setDX(-ORBIT_SPEED_X);
        v.setDY(-ORBIT_SPEED_Y);

        alive = true;
    }

    virtual void draw(ogstream& gout) override
    {
        // Let Simulator compute orientation (angleToEarth)
        gout.drawSputnik(pos, angle);
    }
};
