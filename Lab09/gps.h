#pragma once
#include "satellite.h"

class GPS : public Satellite
{
public:
   GPS();
   virtual void draw(ogstream& gout) override;
};