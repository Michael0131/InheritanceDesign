#include "bullet.h"

void Bullet::update(double dt)
{
    if (!alive)
        return;

    // If this is the last frame of life, do NOT move.
    if (lifetime <= 1)
    {
        lifetime = 0;
        alive = false;
        return;
    }

    // MOVE
    pos.addMetersX(v.getDX() * dt);
    pos.addMetersY(v.getDY() * dt);

    // decrease lifetime
    lifetime--;
}


void Bullet::draw(ogstream& gout)
{
    gout.drawProjectile(pos);
}
