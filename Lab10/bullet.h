#pragma once

#include "entity.h"
#include "position.h"
#include "velocity.h"

#include "uiDraw.h"
class testBullet;

class Bullet : public Entity
{
    friend testBullet;
public:
    Bullet()
    {
        setRadius(4.0 * metersPerPixel);
        
        lifetime = 70;    // frames until expiration
        alive = true;
    }

    Bullet(const Position& p, const Velocity& v)
    {
        pos = p;
        this->v = v;
        radius = 1.0;
        lifetime = 70;
        alive = true;

        setRadius(4.0 * metersPerPixel);
    }

    virtual void update(double dt) override;
    virtual void draw(ogstream& gout) override;

private:
    int lifetime;
};
