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
        radius = 1.0;     // small collision radius
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
    }

    virtual void update(double dt) override;
    virtual void draw(ogstream& gout) override;

private:
    int lifetime;
};
