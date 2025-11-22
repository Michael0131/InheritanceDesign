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
   virtual void update(double dt) override;
   double angle;
};
