#include "entity.h"


void Entity::update(double dt)
{
   if (!alive)
      return;

   // simple linear motion: s = s0 + v * t
   pos.addMetersX(v.getDX() * dt);
   pos.addMetersY(v.getDY() * dt);
}


void Entity::draw(ogstream& /*gout*/)
{
   // base Entity doesn't know how to draw itself
}