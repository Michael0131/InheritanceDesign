#include "starlink.h"
#include "simulator.h"
#include "fragment.h"
#include "part.h"


void Starlink::createParts(Simulator& sim)
{
   //cout << "Starlink breakup! Creating parts...\n";

   // Body
   {
      DebrisSpawn d = makeDebrisSpawn();
      sim.parts.push_back(new StarlinkBodyPart(d.pos, d.vel));
      //cout << "  Added Starlink body part\n";
   }

   // Solar array
   {
      DebrisSpawn d = makeDebrisSpawn();
      sim.parts.push_back(new StarlinkArrayPart(d.pos, d.vel));
      //cout << "  Added Starlink array part\n";
   }
}
