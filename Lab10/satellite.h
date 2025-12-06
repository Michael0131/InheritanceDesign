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
   virtual void onCollision(Entity& other) override
   {
      alive = false;
      breakup(); // satellite-specific
   }

   // Additional Methods
   virtual void draw(ogstream& gout) override;
   virtual void update(double dt) override;
   

   double angle;

private:
   void breakup(); // creates Parts and Fragments

};
