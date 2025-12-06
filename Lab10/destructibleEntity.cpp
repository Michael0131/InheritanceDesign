#include "destructibleEntity.h"
#include "simulator.h"
#include "fragment.h"


void DestructibleEntity::breakup(Simulator& sim)
{
   // Spawn parts (GPS pieces, Hubble pieces, etc.)
   createParts(sim);

   // Spawn fragments
   createFragments(sim);
}


void DestructibleEntity::createFragments(Simulator& sim)
{
   int n = fragmentCountOnBreakup();
   cout << "Breakup! Creating fragments" << endl;
   for (int i = 0; i < n; ++i)
   {
      Fragment* f = new Fragment(pos, v);
      sim.fragments.push_back(f);
      cout << "Added fragment to fragments vector" << endl;
   }
}