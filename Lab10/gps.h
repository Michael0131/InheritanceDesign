#pragma once
#include "satellite.h"
#include <cmath>

class TestGPS;

class GPS : public Satellite
{
    friend TestGPS;

public:

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
};
