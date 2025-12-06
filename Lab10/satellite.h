#pragma once


#include "destructibleEntity.h"
#include "fragment.h"

class TestSatellite;


class Satellite : public DestructibleEntity
{
public:
   friend TestSatellite;

   // Constructors
   Satellite() {}


   // Additional Methods
   virtual void draw(ogstream& gout) override;
   virtual void update(double dt) override;
   

   double angle;
};
