#pragma once
/***********************************************************************
 * Header File:
 *    Test Fragment : Test the Fragment class
 * Author:
 *    (your name)
 * Summary:
 *    Unit tests for Fragment construction, motion, decay, and draw().
 ************************************************************************/

#include "unitTest.h"
#include "fragment.h"
#include "position.h"
#include "velocity.h"
#include "uiDraw.h"

class TestFragment : public UnitTest
{
public:
   void run()
   {
      constructor_basic();
      update_movesCorrectly();
      decay_expires();
      draw_noCrash();

      report("Fragment");
   }

private:

   /*****************************************************************
    * name:    CONSTRUCTOR BASIC
    * desc:    Fragment should copy pos/vel, start alive, and
    *          have a positive radius.
    *****************************************************************/
   void constructor_basic()
   {
      // setup zoom so we know radius should be > 0
      Position zoomSetter;
      zoomSetter.setZoom(128000.0); // any positive zoom

      Position p;
      p.setMeters(100.0, 200.0);
      Velocity v(10.0, -5.0);

      // exercise
      Fragment f(p, v);

      // verify
      assertEquals(f.getPosition().getMetersX(), 100.0);
      assertEquals(f.getPosition().getMetersY(), 200.0);
      assertEquals(f.getVelocity().getDX(), 10.0);
      assertEquals(f.getVelocity().getDY(), -5.0);
      assertUnit(f.isAlive());
      assertUnit(f.getRadius() > 0.0);
   }

   /*****************************************************************
    * name:    UPDATE MOVES CORRECTLY
    * desc:    Fragment motion: p = p0 + v * dt
    *****************************************************************/
   void update_movesCorrectly()
   {
      // setup
      Position p;
      p.setMeters(0.0, 0.0);
      Velocity v(30.0, -40.0);
      Fragment f(p, v);

      // exercise: dt = 2.0
      f.update(2.0);

      // verify
      assertEquals(f.getPosition().getMetersX(), 60.0);
      assertEquals(f.getPosition().getMetersY(), -80.0);
      assertUnit(f.isAlive());
   }

   /*****************************************************************
    * name:    DECAY EXPIRES
    * desc:    timeToLive is 50–100. After enough calls to decay(),
    *          fragment must be dead.
    *****************************************************************/
   void decay_expires()
   {
      // setup
      Position p;
      Velocity v(0.0, 0.0);
      Fragment f(p, v);

      // exercise — decay a bunch of times
      // TTL is at most 100, so 200 decays is definitely enough.
      for (int i = 0; i < 200 && f.isAlive(); ++i)
         f.decay();

      // verify
      assertUnit(!f.isAlive());
   }

   /*****************************************************************
    * name:    DRAW NO CRASH
    * desc:    draw() should not throw or crash.
    *****************************************************************/
   void draw_noCrash()
   {
      // setup
      Position zoomSetter;
      zoomSetter.setZoom(128000.0);

      Position p;
      Velocity v;
      Fragment f(p, v);

      Position pt;
      ogstream gout(pt);
      bool crashed = false;

      // exercise
      try
      {
         f.draw(gout);
      }
      catch (...)
      {
         crashed = true;
      }

      // verify
      assertUnit(crashed == false);
   }
};
