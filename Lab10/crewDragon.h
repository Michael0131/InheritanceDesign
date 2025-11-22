#pragma once
#include "satellite.h"
#include <cmath>

class TestCrewDragon;

class CrewDragon : public Satellite
{
    friend TestCrewDragon;
public:
    CrewDragon()
    {
        // Crew Dragon orbit radius
        const double ORBIT_RADIUS_X = 0.0;
        const double ORBIT_RADIUS_Y = 8'000'000.0;

        // Correct Crew Dragon orbital speed
        const double ORBIT_SPEED_X = 7'900.0;
        const double ORBIT_SPEED_Y = 0.0;

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
        gout.drawCrewDragon(pos, angle);
    }
};
