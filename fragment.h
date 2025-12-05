#pragma once
#include "entity.h"
#include <cmath>

class TestStarlink;

class Fragment : public Entity
{
    //friend TestFragment;
public:
    Fragment(const Position& inPos, const Velocity& inVel)
    {
        // 
        double theta = random(0, 360) * M_PI / 180.0;
        double kick = random(5000, 9000);

        // Place fragment
        pos.setMetersX(inPos.getMetersX() + kick * cos(theta));
        pos.setMetersY(inPos.getMetersY() + kick * sin(theta));

        // set Velocity
        v.setDX(inVel.getDX() + 4 * cos(theta));
        v.setDY(inVel.getDY() + 4 * sin(theta));

        timeToLive = random(50, 100);
        
        alive = true;
        rotation = random (-60, 60); 
    }
    void decay()
    {
        timeToLive -= 1;
        if (timeToLive <= 0)
            alive = false;
    }
    void spin()
    {
        angle += rotation;
    }
    void update(double dt) override
    {
        double dx = v.getDX();
        double dy = v.getDY();
        
        pos.setMetersX(pos.getMetersX() + dx * dt);
        pos.setMetersY(pos.getMetersY() + dy * dt);
    }
    virtual void draw(ogstream& gout) override
    {
        // Let Simulator compute orientation (angleToEarth)
        gout.drawFragment(pos, angle);
    }
protected:
    double rotation;
    int timeToLive;
};