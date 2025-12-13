#include "hubble.h"
#include "simulator.h"
#include "fragment.h"
#include "part.h"

void Hubble::createParts(Simulator& sim)
{
   //cout << "Hubble breakup! Creating parts...\n";

   // Telescope
   {
      DebrisSpawn d = makeDebrisSpawn();
      sim.parts.push_back(new HubbleTelescopePart(d.pos, d.vel));
      //cout << "  Added Hubble telescope part\n";
   }

   // Computer module
   {
      DebrisSpawn d = makeDebrisSpawn();
      sim.parts.push_back(new HubbleComputerPart(d.pos, d.vel));
      //cout << "  Added Hubble computer part\n";
   }

   // Left solar array
   {
      DebrisSpawn d = makeDebrisSpawn();
      sim.parts.push_back(new HubbleLeftPart(d.pos, d.vel));
      //cout << "  Added Hubble left array part\n";
   }

   // Right solar array
   {
      DebrisSpawn d = makeDebrisSpawn();
      sim.parts.push_back(new HubbleRightPart(d.pos, d.vel));
      //cout << "  Added Hubble right array part\n";
   }
}
