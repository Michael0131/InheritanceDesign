#include "gps.h"
#include "simulator.h"
#include "fragment.h"
#include "part.h"

void GPS::createParts(Simulator& sim)
{
   // Add parts to parts vector in Simulator
   cout << "GPS Breakup! Creating parts!" << endl;
   // center
   {
      DebrisSpawn d = makeDebrisSpawn();
      sim.parts.push_back(new GPSCenterPart(d.pos, d.vel));
      cout << "Added a GPSCenterPart" << endl;
   }

   // left
   {
      DebrisSpawn d = makeDebrisSpawn();
      sim.parts.push_back(new GPSLeftPart(d.pos, d.vel));
      cout << "Added a GPSLeftPart" << endl;
   }

   // right
   {
      DebrisSpawn d = makeDebrisSpawn();
      sim.parts.push_back(new GPSRightPart(d.pos, d.vel));
      cout << "Added a GPSRightPart" << endl;
   }
}
