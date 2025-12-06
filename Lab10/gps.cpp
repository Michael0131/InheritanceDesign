#include "gps.h"
#include "simulator.h"
#include "fragment.h"

void GPS::breakup(Simulator& sim)
{
   // 3 parts
   // sim.parts.push_back(new GPSCenterPart(pos, v));
   // sim.parts.push_back(new GPSLeftPart(pos, v));
   // sim.parts.push_back(new GPSRightPart(pos, v));

   // 2 fragments
   std::cout << "GPS breakup! Creating fragments...\n";
   const int NUM_FRAGMENTS = 2;
   for (int i = 0; i < NUM_FRAGMENTS; ++i)
   {
      Fragment* f = new Fragment(pos, v);
      sim.fragments.push_back(f);
   }

   alive = false;
}
