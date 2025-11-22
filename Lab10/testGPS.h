/***********************************************************************
 * Header File:
 *      TEST GPS
 * Summary:
 *      Unit tests for the updated GPS satellite class.
 ************************************************************************/

#pragma once

#include "unitTest.h"
#include "gps.h"
#include "position.h"
#include "velocity.h"
#include <cmath>

class TestGPS : public UnitTest
{
public:

    void run()
    {
        testDefaultConstructor_position();
        testDefaultConstructor_velocity();
        testDefaultConstructor_alive();

        testParameterizedConstructor_position();
        testParameterizedConstructor_velocity();
        testParameterizedConstructor_alive();

        testInheritance_isSatellite();
        testVelocityMagnitude();
        testDraw_noCrash();

        report("GPS");
    }

private:

    /*****************************************************************
     * DEFAULT CONSTRUCTOR TESTS
     *****************************************************************/

     /*********************************************
      * name:    DEFAULT CTOR sets position to 0,0
      *********************************************/
    void testDefaultConstructor_position()
    {
        // setup
        GPS gps;

        // exercise
        double x = gps.getPosition().getMetersX();
        double y = gps.getPosition().getMetersY();

        // verify
        assertEquals(x, 0.0, 0.0001);
        assertEquals(y, 0.0, 0.0001);

        // teardown
    }

    /*********************************************
     * name:    DEFAULT CTOR sets velocity to 0,0
     *********************************************/
    void testDefaultConstructor_velocity()
    {
        // setup
        GPS gps;

        // exercise
        double dx = gps.getVelocity().getDX();
        double dy = gps.getVelocity().getDY();

        // verify
        assertEquals(dx, 0.0, 0.0001);
        assertEquals(dy, 0.0, 0.0001);

        // teardown
    }

    /*********************************************
     * name:    DEFAULT CTOR sets alive = true
     *********************************************/
    void testDefaultConstructor_alive()
    {
        // setup
        GPS gps;

        // exercise/verify
        assertUnit(gps.isAlive() == true);

        // teardown
    }


    /*****************************************************************
     * PARAMETERIZED CONSTRUCTOR TESTS
     *****************************************************************/

     /*********************************************
      * name:    Parameterized ctor sets position
      *********************************************/
    void testParameterizedConstructor_position()
    {
        // setup
        GPS gps(10.0, 20.0, 0.0, 0.0);

        // exercise
        double x = gps.getPosition().getMetersX();
        double y = gps.getPosition().getMetersY();

        // verify
        assertEquals(x, 10.0, 0.0001);
        assertEquals(y, 20.0, 0.0001);

        // teardown
    }

    /*********************************************
     * name:    Parameterized ctor sets velocity
     *********************************************/
    void testParameterizedConstructor_velocity()
    {
        // setup
        GPS gps(0.0, 0.0, -123.45, 678.9);

        // exercise
        double dx = gps.getVelocity().getDX();
        double dy = gps.getVelocity().getDY();

        // verify
        assertEquals(dx, -123.45, 0.0001);
        assertEquals(dy, 678.9, 0.0001);

        // teardown
    }

    /*********************************************
     * name:    Parameterized ctor sets alive=true
     *********************************************/
    void testParameterizedConstructor_alive()
    {
        // setup
        GPS gps(1.0, 1.0, 1.0, 1.0);

        // verify
        assertUnit(gps.isAlive() == true);

        // teardown
    }


    /*****************************************************************
     * INHERITANCE TEST
     *****************************************************************/

     /*********************************************
      * name:    GPS must inherit Satellite
      *********************************************/
    void testInheritance_isSatellite()
    {
        // setup
        GPS gps(0.0, 0.0, 0.0, 0.0);
        Satellite* pSat = &gps;

        // verify
        assertUnit(pSat != nullptr);

        // teardown
    }


    /*****************************************************************
     * VELOCITY MAGNITUDE TEST
     *****************************************************************/

     /*********************************************
      * name:    Velocity magnitude computed correctly
      *********************************************/
    void testVelocityMagnitude()
    {
        // setup
        GPS gps(0.0, 0.0, 3.0, 4.0);

        // exercise
        double dx = gps.getVelocity().getDX();
        double dy = gps.getVelocity().getDY();
        double speed = sqrt(dx * dx + dy * dy);

        // verify
        assertEquals(speed, 5.0, 0.0001);

        // teardown
    }


    /*****************************************************************
     * DRAW TEST
     *****************************************************************/

     /*********************************************
      * name:    draw() does not crash
      *********************************************/
    void testDraw_noCrash()
    {
        // setup
        GPS gps(0.0, 0.0, 0.0, 0.0);
        Position p(0.0, 0.0);
        ogstream gout(p);

        bool crashed = false;

        // exercise
        try
        {
            gps.draw(gout);
        }
        catch (...)
        {
            crashed = true;
        }

        // verify
        assertUnit(crashed == false);

        // teardown
    }
};
