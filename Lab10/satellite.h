#pragma once


#include "entity.h"
#include "fragment.h"

class TestSatellite;


class Satellite : public Entity
{
public:
   friend TestSatellite;

   // Constructors
   Satellite() {}


   // Collision
   virtual void onCollision(Entity& other, Simulator& sim) override
   {
      alive = false;
      breakup(sim); // satellite-specific
   }

   // Additional Methods
   virtual void draw(ogstream& gout) override;
   virtual void update(double dt) override;
   

   double angle;

protected:
   virtual void breakup(Simulator& sim); // creates Parts and Fragments

};
