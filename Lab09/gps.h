#pragma once
#include "satellite.h"
#include <cmath>

class TestGPS;

class GPS : public Satellite
{
    friend TestGPS;
public:
    GPS()
    {
        // GPS orbit radius (Earth radius + 20,200 km)
        const double ORBIT_RADIUS = 26'578'000.0;

        // Correct GPS orbital speed (~3,874 m/s)
        const double ORBIT_SPEED = 3874.0;

        // Place satellite at (0, R)
        pos.setMetersX(0.0);
        pos.setMetersY(ORBIT_RADIUS);

        // Velocity tangent to orbit: (-speed, 0)
        v.setDX(-ORBIT_SPEED);
        v.setDY(0.0);

        alive = true;
    }

    virtual void draw(ogstream& gout) override
    {
        // Let Simulator compute orientation (angleToEarth)
        gout.drawGPS(pos, angle);
    }
};
