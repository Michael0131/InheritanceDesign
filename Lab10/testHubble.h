/***********************************************************************
 * Header File:
 *      TEST HUBBLE
 * Author:
 *      Your Name
 * Summary:
 *      Unit tests for the Hubble satellite class.
 ************************************************************************/

#pragma once

#include "unitTest.h"
#include "hubble.h"
#include "position.h"
#include "velocity.h"
#include <cmath>

class TestHubble : public UnitTest
{
public:

    void run()
    {
        testConstructor_position();
        testConstructor_velocity();
        testConstructor_aliveFlag();
        testInheritance_isSatellite();
        testConstructor_orbitRadiusAccuracy();
        testConstructor_velocityMagnitude();
        testDraw_noCrash();

        report("Hubble");
    }

private:

    /*****************************************************************
     *****************************************************************
     * TEST HUBBLE CONSTRUCTOR — POSITION
     *****************************************************************
     *****************************************************************/

     /*********************************************
      * name:    HUBBLE CONSTRUCTOR sets starting position
      * input:   none (default constructor)
      * output:  pos = (0, ORBIT_RADIUS)
      *********************************************/
    void testConstructor_position()
    {
        // setup
        Hubble h;

        // exercise
        double x = h.getPosition().getMetersX();
        double y = h.getPosition().getMetersY();

        // verify
        assertEquals(x, 0.0, 0.0001);
        assertEquals(y, -42'164'000.0, 1.0);   // matches your constructor

        // teardown
    }

    /*****************************************************************
     *****************************************************************
     * TEST HUBBLE CONSTRUCTOR — VELOCITY
     *****************************************************************
     *****************************************************************/

     /*********************************************
      * name:    HUBBLE CONSTRUCTOR sets starting velocity
      * input:   none
      * output:  dx = -3100, dy = 0
      *********************************************/
    void testConstructor_velocity()
    {
        // setup
        Hubble h;

        // exercise
        double dx = h.getVelocity().getDX();
        double dy = h.getVelocity().getDY();

        // verify
        assertEquals(dx, -3100.0, 0.001);
        assertEquals(dy, 0.0, 0.001);

        // teardown
    }


    /*****************************************************************
     *****************************************************************
     * TEST HUBBLE CONSTRUCTOR — ALIVE FLAG
     *****************************************************************
     *****************************************************************/

     /*********************************************
      * name:    Hubble starts alive
      * input:   none
      * output:  alive == true
      *********************************************/
    void testConstructor_aliveFlag()
    {
        // setup
        Hubble h;

        // exercise / verify
        assertUnit(h.isAlive() == true);

        // teardown
    }


    /*****************************************************************
     *****************************************************************
     * TEST INHERITANCE
     *****************************************************************
     *****************************************************************/

     /*********************************************
      * name:    Hubble inherits from Satellite
      * purpose: ensure correct type hierarchy
      *********************************************/
    void testInheritance_isSatellite()
    {
        // setup
        Hubble h;
        Satellite* pSat = &h;

        // exercise / verify
        assertUnit(pSat != nullptr);

        // teardown
    }


    /*****************************************************************
     *****************************************************************
     * TEST ORBIT RADIUS ACCURACY
     *****************************************************************
     *****************************************************************/

     /*********************************************
      * name:    Hubble orbit radius is correct
      * input:   none
      * output:  sqrt(x² + y²) == |ORBIT_RADIUS|
      *********************************************/
    void testConstructor_orbitRadiusAccuracy()
    {
        // setup
        Hubble h;

        double x = h.getPosition().getMetersX();
        double y = h.getPosition().getMetersY();

        // exercise
        double r = sqrt(x * x + y * y);

        // verify
        assertEquals(r, 42'164'000.0, 0.5);

        // teardown
    }


    /*****************************************************************
     *****************************************************************
     * TEST VELOCITY MAGNITUDE
     *****************************************************************
     *****************************************************************/

     /*********************************************
      * name:    Hubble speed magnitude is correct
      * input:   none
      * output:  |v| = 3100 m/s
      *********************************************/
    void testConstructor_velocityMagnitude()
    {
        // setup
        Hubble h;

        double dx = h.getVelocity().getDX();
        double dy = h.getVelocity().getDY();

        // exercise
        double speed = sqrt(dx * dx + dy * dy);

        // verify
        assertEquals(speed, 3100.0, 0.5);

        // teardown
    }


    /*****************************************************************
     *****************************************************************
     * TEST DRAW
     *****************************************************************
     *****************************************************************/

     /*********************************************
      * name:    draw() does not crash
      * purpose: ensure stability (cannot verify pixels)
      *********************************************/
    void testDraw_noCrash()
    {
        // setup
        Hubble h;
        Position p(0.0, 0.0);
        ogstream gout(p);

        bool crashed = false;

        // exercise
        try
        {
            h.draw(gout);
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
