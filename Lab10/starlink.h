#pragma once
#include "satellite.h"
#include <cmath>

class TestStarlink;

class Starlink : public Satellite
{
    friend TestStarlink;
public:
    Starlink()
    {
        // Starlink orbit radius
        const double ORBIT_RADIUS_X = 0.0;
        const double ORBIT_RADIUS_Y = -13'020'000.0;

        // Correct Starlink orbital speed
        const double ORBIT_SPEED_X = 5'800.0;
        const double ORBIT_SPEED_Y = 0.0;

        // Place satellite
        pos.setMetersX(ORBIT_RADIUS_X);
        pos.setMetersY(ORBIT_RADIUS_Y);

        // Velocity tangent to orbit
        v.setDX(-ORBIT_SPEED_X);
        v.setDY(-ORBIT_SPEED_Y);

        alive = true;

        double metersPerPixel = pos.getZoom();

        // Starlink radius is 6 pixels
        setRadius(6.0 * metersPerPixel);
    }

    virtual void draw(ogstream& gout) override
    {
        // Let Simulator compute orientation (angleToEarth)
        gout.drawStarlink(pos, angle);
    }
};
