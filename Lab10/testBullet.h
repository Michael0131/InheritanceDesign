#pragma once
/***********************************************************************
 * Header File:
 *    Test Bullet : Test the Bullet class
 * Author:
 *    Michael Johnson
 * Summary:
 *    Complete unit tests validating Bullet motion, lifetime expiration,
 *    constructor correctness, alive/dead logic, and draw() safety.
 ************************************************************************/

#pragma once

#include "unitTest.h"
#include "bullet.h"

 /***************************************************
  * TEST BULLET
  ***************************************************/
class TestBullet : public UnitTest
{
public:
    void run()
    {
        constructor_default();
        constructor_nonDefault();
        update_movesCorrectly();
        update_expires();
        update_noMovementWhenDead();
        draw_noCrash();

        report("Bullet");
    }

private:

    /*****************************************************************
     * name:    CONSTRUCTOR DEFAULT
     * desc:    Ensures the default bullet sets reasonable defaults:
     *          pos=(0,0), velocity=(0,0), alive=true, radius=1.0.
     *****************************************************************/
    void constructor_default()
    {
        // exercise
        Bullet b;

        // verify
        assertEquals(b.getPosition().getMetersX(), 0.0);
        assertEquals(b.getPosition().getMetersY(), 0.0);
        assertEquals(b.getVelocity().getDX(), 0.0);
        assertEquals(b.getVelocity().getDY(), 0.0);
        assertUnit(b.isAlive() == true);

        // teardown — none
    }

    /*****************************************************************
     * name:    CONSTRUCTOR NON-DEFAULT
     * desc:    Ensures bullet is created with supplied position
     *          and velocity values.
     *****************************************************************/
    void constructor_nonDefault()
    {
        // setup
        Position p;
        p.setMeters(100.0, 200.0);
        Velocity v(50.0, -25.0);

        // exercise
        Bullet b(p, v);

        // verify
        assertEquals(b.getPosition().getMetersX(), 100.0);
        assertEquals(b.getPosition().getMetersY(), 200.0);
        assertEquals(b.getVelocity().getDX(), 50.0);
        assertEquals(b.getVelocity().getDY(), -25.0);
        assertUnit(b.isAlive());
    }

    /*****************************************************************
     * name:    UPDATE MOVES CORRECTLY
     * desc:    For dt=1.0, verifies bullet moves linearly:
     *          p = p0 + v·t
     *****************************************************************/
    void update_movesCorrectly()
    {
        // setup
        Position p;
        p.setMeters(0.0, 0.0);
        Velocity v(30.0, -40.0);
        Bullet b(p, v);

        // exercise
        b.update(1.0);   // dt = 1 second

        // verify
        assertEquals(b.getPosition().getMetersX(), 30.0);
        assertEquals(b.getPosition().getMetersY(), -40.0);
        assertUnit(b.isAlive());
    }

    /*****************************************************************
     * name:    UPDATE EXPIRES
     * desc:    Bullet lifetime = 70 frames.
     *          After 70 calls to update(), bullet must be dead.
     *****************************************************************/
    void update_expires()
    {
        // setup
        Bullet b;
        double dt = 1.0;

        // exercise — call update 70 times
        for (int i = 0; i < 70; i++)
            b.update(dt);

        // verify
        assertUnit(!b.isAlive());
    }

    /*****************************************************************
    * name:    UPDATE NO MOVEMENT WHEN DEAD
    * desc:    Once a bullet is dead, additional calls to update()
    *          must not change its position.
    *****************************************************************/
    void update_noMovementWhenDead()
    {
        // setup
        Bullet b;
        b.getPosition().setMeters(500.0, 500.0);
        b.getVelocity().set(100.0, 100.0);

        // kill the bullet by exhausting its lifetime
        for (int i = 0; i < 70; i++)
            b.update(1.0);

        // record bullet's final resting position when it dies
        double xDead = b.getPosition().getMetersX();
        double yDead = b.getPosition().getMetersY();

        // exercise — updating again must NOT move it
        b.update(4.0);

        // verify — position must match the last alive position
        assertEquals(b.getPosition().getMetersX(), xDead);
        assertEquals(b.getPosition().getMetersY(), yDead);
    }

    /*****************************************************************
     * name:    DRAW NO CRASH
     * desc:    Calling draw() should never throw an exception.
     *****************************************************************/
    void draw_noCrash()
    {
        // setup
        Bullet b;
        Position pt;
        ogstream gout(pt);
        bool crashed = false;

        // exercise
        try
        {
            b.draw(gout);
        }
        catch (...)
        {
            crashed = true;
        }

        // verify
        assertUnit(crashed == false);
    }
};