#pragma once


#include "entity.h"


class TestSatellite;


class Satellite : public Entity
{
public:
   friend TestSatellite;

   // Constructors
   Satellite() {}


   // Methods
   virtual void draw(ogstream& gout) override;
   void updatePhysics(double dt);

};
