#pragma once
/***********************************************************************
 * Header File:
 *    Test Part : Test Part subclasses and behavior
 * Author:
 *    (your name)
 * Summary:
 *    Unit tests for Part: construction, collision delay,
 *    and breakup → fragments.
 ************************************************************************/

#include "unitTest.h"
#include "part.h"
#include "fragment.h"
#include "simulator.h"
#include "position.h"
#include "velocity.h"
#include "uiDraw.h"

class TestPart : public UnitTest
{
public:
   void run()
   {
      constructor_GPSCenterPart();
      canCollide_delay();
      onCollision_createsFragments();
      draw_noCrash();

      report("Part");
   }

private:

   /*****************************************************************
    * name:    CONSTRUCTOR GPS CENTER PART
    * desc:    Basic wiring: position, velocity, alive, radius > 0.
    *****************************************************************/
   void constructor_GPSCenterPart()
   {
      // setup zoom so radius is deterministic
      Position zoomSetter;
      zoomSetter.setZoom(128000.0);
      double mpp = zoomSetter.getZoom();

      Position p;
      p.setMeters(1000.0, -2000.0);
      Velocity v(50.0, 25.0);

      // exercise
      GPSCenterPart part(p, v);

      // verify
      assertEquals(part.getPosition().getMetersX(), 1000.0);
      assertEquals(part.getPosition().getMetersY(), -2000.0);
      assertEquals(part.getVelocity().getDX(), 50.0);
      assertEquals(part.getVelocity().getDY(), 25.0);
      assertUnit(part.isAlive());
      // radius should match 7 pixels * metersPerPixel
      assertEquals(part.getRadius(), 7.0 * mpp);
      // and initially not collidable due to delay
      assertUnit(!part.canCollide());
   }

   /*****************************************************************
    * name:    CAN COLLIDE DELAY
    * desc:    Part should not collide for the first 24 frames,
    *          and should become collidable afterwards.
    *****************************************************************/
   void canCollide_delay()
   {
      // setup
      Position zoomSetter;
      zoomSetter.setZoom(128000.0);

      Position p;
      Velocity v;
      GPSCenterPart part(p, v);

      // exercise - step fewer than 24 frames
      for (int i = 0; i < 20; ++i)
         part.update(1.0);

      // verify: still not collidable
      assertUnit(!part.canCollide());

      // exercise - finish remaining frames
      for (int i = 0; i < 10; ++i)
         part.update(1.0);

      // verify: now collidable
      assertUnit(part.canCollide());
   }

   /*****************************************************************
    * name:    ON COLLISION CREATES FRAGMENTS
    * desc:    GPSCenterPart should break into 3 fragments on collision.
    *****************************************************************/
   void onCollision_createsFragments()
   {
      // setup simulator
      Position world;
      world.setZoom(128000.0);
      world.setMeters(0.0, 0.0);
      Simulator sim(world);

      // record initial fragment count
      size_t before = sim.fragments.size();

      // part to break
      Position p;
      p.setMeters(0.0, 0.0);
      Velocity v(0.0, 0.0);
      GPSCenterPart part(p, v);

      // dummy other entity
      Entity other;

      // exercise
      part.onCollision(other, sim);

      // verify: part is dead and exactly +3 fragments were added
      assertUnit(!part.isAlive());
      size_t after = sim.fragments.size();
      assertEquals(after, before + 3);
   }

   /*****************************************************************
    * name:    DRAW NO CRASH
    * desc:    Drawing parts should never throw.
    *****************************************************************/
   void draw_noCrash()
   {
      // setup
      Position zoomSetter;
      zoomSetter.setZoom(128000.0);

      Position p;
      Velocity v;
      GPSCenterPart part(p, v);

      Position pt;
      ogstream gout(pt);
      bool crashed = false;

      // exercise
      try
      {
         part.draw(gout);
      }
      catch (...)
      {
         crashed = true;
      }

      // verify
      assertUnit(crashed == false);
   }
};
