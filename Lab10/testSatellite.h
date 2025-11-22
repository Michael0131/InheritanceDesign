/***********************************************************************
 * Header File:
 *    Test Satellite : Test the Satellite class
 * Author:
 *    ChatGPT (modeled after Br. Helfrich's test format)
 * Summary:
 *    Complete unit tests validating Satellite motion, gravity effects,
 *    collision detection, alive/dead logic, and update correctness.
 ************************************************************************/

#pragma once

#include "unitTest.h"
#include "satellite.h"
 /***********************************************************************
  * Header File:
  *    Test Satellite : Test the Satellite class
  * Author:
  *    ChatGPT (modeled after Br. Helfrich's test format)
  * Summary:
  *    Complete unit tests validating Satellite motion, gravity effects,
  *    collision detection, alive/dead logic, and update correctness.
  ************************************************************************/

#pragma once

#include "unitTest.h"
#include "satellite.h"
#include "physics.h"

class TestSatellite : public UnitTest
{
public:
    void run()
    {
        constructor_default();
        update_noGravity();
        update_withGravity();
        update_velocityChange();
        update_diesOnCollision();
        update_noMovementWhenDead();
        draw_noCrash();

        report("Satellite");
    }

private:

    /*****************************************************************
     * name:    CONSTRUCTOR DEFAULT
     * desc:    Verifies that a Satellite created with the default
     *          constructor initializes at (0,0), with zero velocity,
     *          and is marked alive.
     *****************************************************************/
    void constructor_default()
    {
        // setup — nothing required

        // exercise
        Satellite s;

        // verify
        assertUnit(s.pos.getMetersX() == 0.0);
        assertUnit(s.pos.getMetersY() == 0.0);
        assertUnit(s.v.getDX() == 0.0);
        assertUnit(s.v.getDY() == 0.0);
        assertUnit(s.alive == true);

        // teardown — none
    }

    /*****************************************************************
     * name:    UPDATE NO GRAVITY
     * desc:    Places the satellite extremely far away so gravitational
     *          acceleration is effectively zero. The update() call
     *          should produce pure linear motion: p = p0 + v·t.
     *****************************************************************/
    void update_noGravity()
    {
        // setup
        Satellite s;
        s.pos.setMetersX(1e9);
        s.pos.setMetersY(1e9);
        s.v.set(100.0, -50.0);
        double dt = 1.0;

        // exercise
        s.update(dt);

        // verify
        assertEquals(s.pos.getMetersX(), 1e9 + 100.0);
        assertEquals(s.pos.getMetersY(), 1e9 - 50.0);

        // teardown — none
    }

    /*****************************************************************
     * name:    UPDATE WITH GRAVITY
     * desc:    Places the satellite 100 km above Earth and performs
     *          one physics update. Gravity must pull the satellite down.
     *****************************************************************/
    void update_withGravity()
    {
        // setup
        Satellite s;
        s.pos.setMetersX(0.0);
        s.pos.setMetersY(Physics::EARTH_RADIUS + 100000.0);
        s.v.set(0.0, 0.0);
        double dt = 1.0;

        // exercise
        s.update(dt);

        // verify — height should decrease
        assertUnit(s.pos.getMetersY() < Physics::EARTH_RADIUS + 100000.0);

        // teardown — none
    }

    /*****************************************************************
     * name:    UPDATE VELOCITY CHANGE
     * desc:    Verifies that velocity is updated according to gravity
     *          (v = v0 + a·t). Satellite is above Earth with zero
     *          initial velocity; after update it should have
     *          a downward dy.
     *****************************************************************/
    void update_velocityChange()
    {
        // setup
        Satellite s;
        s.pos.setMetersX(0.0);
        s.pos.setMetersY(Physics::EARTH_RADIUS + 100000.0);
        s.v.set(0.0, 0.0);
        double dt = 1.0;

        // exercise
        s.update(dt);

        // verify — must now have downward velocity
        assertUnit(s.v.getDY() < 0.0);

        // teardown — none
    }

    /*****************************************************************
     * name:    UPDATE DIES ON COLLISION
     * desc:    Places the satellite below Earth's surface and confirms
     *          that update() sets alive = false due to collision logic.
     *****************************************************************/
    void update_diesOnCollision()
    {
        // setup
        Satellite s;
        s.pos.setMetersX(0.0);
        s.pos.setMetersY(Physics::EARTH_RADIUS - 10.0);
        s.v.set(0.0, 0.0);

        // exercise
        s.update(1.0);

        // verify
        assertUnit(s.alive == false);

        // teardown — none
    }

    /*****************************************************************
     * name:    UPDATE NO MOVEMENT WHEN DEAD
     * desc:    Ensures that once a satellite is dead, update() performs
     *          no motion or physics. Position must not change.
     *****************************************************************/
    void update_noMovementWhenDead()
    {
        // setup
        Satellite s;
        s.pos.setMetersX(5000.0);
        s.pos.setMetersY(5000.0);
        s.v.set(1000.0, 1000.0);
        s.alive = false;   // force-dead

        // exercise
        s.update(10.0);

        // verify
        assertEquals(s.pos.getMetersX(), 5000.0);
        assertEquals(s.pos.getMetersY(), 5000.0);

        // teardown — none
    }

    /*****************************************************************
     * name:    DRAW NO CRASH
     * desc:    Simply verifies that draw() can be called without
     *          throwing exceptions. No rendering correctness tested.
     *****************************************************************/
    void draw_noCrash()
    {
        // setup
        Satellite s;
        Position pt;
        ogstream gout(pt);
        bool crashed = false;

        // exercise
        try
        {
            s.draw(gout);
        }
        catch (...)
        {
            crashed = true;
        }

        // verify
        assertUnit(crashed == false);

        // teardown — none
    }
};


