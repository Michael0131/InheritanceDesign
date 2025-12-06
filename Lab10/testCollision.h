#pragma once
/***********************************************************************
 * Header File:
 *    Test Collision : Test Entity collision detection
 * Author:
 *    (your name)
 * Summary:
 *    Unit tests for Entity::collidesWith().
 ************************************************************************/

#include "unitTest.h"
#include "entity.h"
#include "position.h"
#include "velocity.h"

class TestCollision : public UnitTest
{
public:
   void run()
   {
      noCollision_whenFarApart();
      collision_whenOverlapping();
      symmetric_result();

      report("Collision");
   }

private:

   /*****************************************************************
    * name:    NO COLLISION WHEN FAR APART
    * desc:    Entities that are far apart must not collide.
    *****************************************************************/
   void noCollision_whenFarApart()
   {
      // setup
      Entity a;
      Entity b;

      a.getPosition().setMeters(0.0, 0.0);
      b.getPosition().setMeters(1'000'000.0, 0.0);

      a.setRadius(1000.0);
      b.setRadius(1000.0);

      // exercise
      bool ab = a.collidesWith(b);
      bool ba = b.collidesWith(a);

      // verify
      assertUnit(ab == false);
      assertUnit(ba == false);
   }

   /*****************************************************************
    * name:    COLLISION WHEN OVERLAPPING
    * desc:    Entities closer than sum of radii must collide.
    *****************************************************************/
   void collision_whenOverlapping()
   {
      // setup
      Entity a;
      Entity b;

      // place them 50 meters apart
      a.getPosition().setMeters(0.0, 0.0);
      b.getPosition().setMeters(50.0, 0.0);

      // give them large radii so they overlap
      a.setRadius(40.0);
      b.setRadius(40.0);
      // distance = 50, sum radii = 80 → should collide

      // exercise
      bool ab = a.collidesWith(b);
      bool ba = b.collidesWith(a);

      // verify
      assertUnit(ab == true);
      assertUnit(ba == true);
   }

   /*****************************************************************
    * name:    SYMMETRIC RESULT
    * desc:    a.collidesWith(b) must equal b.collidesWith(a).
    *****************************************************************/
   void symmetric_result()
   {
      // setup
      Entity a;
      Entity b;

      a.getPosition().setMeters(10.0, 20.0);
      b.getPosition().setMeters(30.0, 25.0);

      a.setRadius(15.0);
      b.setRadius(10.0);

      // exercise
      bool ab = a.collidesWith(b);
      bool ba = b.collidesWith(a);

      // verify
      assertEquals(ab, ba);
   }
};
