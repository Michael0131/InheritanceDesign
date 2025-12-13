#include "crewDragon.h"
#include "simulator.h"
#include "fragment.h"
#include "part.h"



void CrewDragon::createParts(Simulator& sim)
{
   //cout << "CrewDragon breakup! Creating parts...\n";

   // Center
   {
      DebrisSpawn d = makeDebrisSpawn();
      sim.parts.push_back(new CrewDragonCenterPart(d.pos, d.vel));
      //cout << "  Added CrewDragon center part\n";
   }

   // Left solar array
   {
      DebrisSpawn d = makeDebrisSpawn();
      sim.parts.push_back(new CrewDragonLeftPart(d.pos, d.vel));
      //cout << "  Added CrewDragon left part\n";
   }

   // Right solar array
   {
      DebrisSpawn d = makeDebrisSpawn();
      sim.parts.push_back(new CrewDragonRightPart(d.pos, d.vel));
      //cout << "  Added CrewDragon right part\n";
   }
}
