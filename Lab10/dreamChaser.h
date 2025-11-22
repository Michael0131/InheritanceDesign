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
        isThrust = false;
    }
    void rotate(float direction)
    {
        angle += direction;
        return;
    }
    void thrust(bool isThrust)
    {
        this->isThrust = isThrust;
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

        // Check collision BEFORE movement
        if (physics.computeHeight(pos) <= 0)
        {
            alive = false;
            return;
        }

        double ddx, ddy;
        physics.computeAcceleration(pos, ddx, ddy);

        double dx = v.getDX();
        double dy = v.getDY();

        // APPLY THRUST FIRST
        if (isThrust)
        {
            dx += thrustPower * sin(angle) * dt;
            dy += thrustPower * cos(angle) * dt;
        }

        // APPLY GRAVITY
        dx += ddx * dt;
        dy += ddy * dt;

        // SAVE FINAL VELOCITY
        v.setDX(dx);
        v.setDY(dy);

        // MOVE USING UPDATED VELOCITY
        pos.setMetersX(pos.getMetersX() + dx * dt);
        pos.setMetersY(pos.getMetersY() + dy * dt);

        // Check collision AFTER movement
        if (physics.computeHeight(pos) <= 0)
            alive = false;
    }
protected:
    double thrustPower;
    bool isThrust;
};