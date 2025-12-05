#pragma once

#include "satellite.h"
#include "physics.h"


void Satellite::update(double dt)
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

    // Update position (x = x + v*t + 1/2 a t²)
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



void Satellite::draw(ogstream& /*gout*/)
{
   // Base satellite does nothing. Specific satellites (GPS, etc.) override this.
}


void Satellite::breakup()
{
   // 
}