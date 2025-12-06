#include "destructibleEntity.h"
#include "simulator.h"
#include "fragment.h"
#include "constants.h"   // for PI
#include <cmath>


DestructibleEntity::DebrisSpawn DestructibleEntity::makeDebrisSpawn() const
{
   DebrisSpawn d;

   // random direction
   double theta = random(0.0, 2.0 * PI);
   //double theta = random(0, 360) * PI / 180.0;

   // 4-pixel offset
   double offset = 4.0 * metersPerPixel;
   d.pos = pos;
   d.pos.setMetersX(pos.getMetersX() + offset * cos(theta));
   d.pos.setMetersY(pos.getMetersY() + offset * sin(theta));

   // velocity: inherit + kick 5000–9000 m/s
   double kick = random(5000.0, 9000.0);
   d.vel = v;
   d.vel.setDX(v.getDX() + kick * cos(theta));
   d.vel.setDY(v.getDY() + kick * sin(theta));

   return d;
}

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
   if (n <= 0)
      return;

   //cout << "Breakup! Creating fragments" << endl;
   for (int i = 0; i < n; ++i)
   {
      // construct fragment from computed pos/vel
      DebrisSpawn d = makeDebrisSpawn();
      Fragment* f = new Fragment(d.pos, d.vel);
      sim.fragments.push_back(f);
      //cout << "Added fragment to fragments vector" << endl;
   }
}
  
