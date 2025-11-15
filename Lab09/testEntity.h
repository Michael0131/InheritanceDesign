/***********************************************************************
 * Header File:
 *    Test Entity : Test the Entity base class
 * Author:
 *    (your name)
 * Summary:
 *    Unit tests for the Entity class.
 ************************************************************************/

#pragma once

#include "unitTest.h"
#include "entity.h"

 /***************************************
  * TEST ENTITY
  * A friend class for Entity for unit testing
  ***************************************/
class TestEntity : public UnitTest
{
public:
    void run()
    {
        constructor_default();
        getters_initialValues();
        aliveFlag();
        update_linearMotion();

        report("Entity");
    }

private:

    /*********************************************
     * DEFAULT CONSTRUCTOR
     *********************************************/
    void constructor_default()
    {
        // setup / exercise
        Entity e;

        // verify
        assertEquals(e.pos.getMetersX(), 0.0);
        assertEquals(e.pos.getMetersY(), 0.0);

        assertEquals(e.v.getDX(), 0.0);
        assertEquals(e.v.getDY(), 0.0);

        assertEquals(e.angle, 0.0);
        assertEquals(e.radius, 0.0);
        assertEquals(e.alive, true);
    }

    /*********************************************
     * GETTERS RETURN INTERNAL VALUES
     *********************************************/
    void getters_initialValues()
    {
        // setup
        Entity e;
        e.pos.setMetersX(12.3);
        e.pos.setMetersY(45.6);
        e.v.setDX(7.8);
        e.v.setDY(9.1);

        // exercise
        Position& p = e.getPosition();
        Velocity& v = e.getVelocity();

        // verify
        assertEquals(p.getMetersX(), 12.3);
        assertEquals(p.getMetersY(), 45.6);
        assertEquals(v.getDX(), 7.8);
        assertEquals(v.getDY(), 9.1);
    }

    /*********************************************
    * ALIVE FLAG
    *********************************************/
    void aliveFlag()
    {
        // setup
        Entity e;

        // verify default is TRUE
        assertUnit(e.isAlive() == true);

        // change state (allowed because TestEntity is a friend)
        e.alive = false;

        // verify new state
        assertUnit(e.isAlive() == false);
    }

    /*********************************************
     * UPDATE — linearly updates position
     *    pos = pos + v * dt
     *********************************************/
    void update_linearMotion()
    {
        // setup
        Entity e;
        e.pos.setMetersX(100.0);
        e.pos.setMetersY(200.0);
        e.v.setDX(3.0);
        e.v.setDY(-4.0);

        double dt = 2.0;   // 2 seconds

        // exercise
        e.update(dt);

        // verify: newX = 100 + 3*2 = 106
        //         newY = 200 - 4*2 = 192
        assertEquals(e.pos.getMetersX(), 106.0);
        assertEquals(e.pos.getMetersY(), 192.0);
    }
};

