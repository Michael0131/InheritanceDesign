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


bool Entity::collidesWith(const Entity& other) const
{
   double dx = pos.getMetersX() - other.getPosition().getMetersX();
   double dy = pos.getMetersY() - other.getPosition().getMetersY();

   double r = radius + other.getRadius();
   return dx * dx + dy * dy <= r * r;   // distance^2 <= (r1 + r2)^2
}