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
   virtual void draw(ogstream& gout);
   void updatePhysics(double dt);

};
