#pragma once
#pragma once
#include "entity.h"

class Simulator;
class Fragment;

class DestructibleEntity : public Entity
{
public:
   // Generic collision behavior for things that break up
   void onCollision(Entity& /*other*/, Simulator& sim) override
   {
      breakup(sim); // Sppawn parts and fragments
      alive = false; // Mark this object as dead
   }

protected:
   // How many fragments should this object create?
   virtual int fragmentCountOnBreakup() const { return 0; }

   // Which parts should be created? (default: none)
   virtual void createParts(Simulator& /*sim*/) {}


private:
   void createFragments(Simulator& sim);

   virtual void breakup(Simulator& sim); // creates Parts and Fragments
};
