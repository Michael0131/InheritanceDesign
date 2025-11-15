/***********************************************************************
 * Header File:
 *      TEST GPS
 * Author:
 *      Your Name
 * Summary:
 *      Unit tests for the GPS satellite class.
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
        testConstructor_position();
        testConstructor_velocity();
        testConstructor_aliveFlag();
        testInheritance_isSatellite();
        testConstructor_orbitRadiusAccuracy();
        testConstructor_velocityMagnitude();
        testDraw_noCrash();

        report("GPS");
    }

private:

    /*****************************************************************
     *****************************************************************
     * TEST GPS CONSTRUCTOR — POSITION
     *****************************************************************
     *****************************************************************/

     /*********************************************
      * name:    GPS CONSTRUCTOR sets starting position
      * input:   none (default constructor)
      * output:  pos = (0, ORBIT_RADIUS)
      *********************************************/
    void testConstructor_position()
    {
        // setup
        GPS gps;

        // exercise
        double x = gps.getPosition().getMetersX();
        double y = gps.getPosition().getMetersY();

        // verify
        assertEquals(x, 0.0, 0.0001);
        assertEquals(y, 26'578'000.0, 1.0);    // 1 meter tolerance

        // teardown
    }

    /*****************************************************************
     *****************************************************************
     * TEST GPS CONSTRUCTOR — VELOCITY
     *****************************************************************
     *****************************************************************/

     /*********************************************
      * name:    GPS CONSTRUCTOR sets starting velocity
      * input:   none
      * output:  dx = -3874, dy = 0
      *********************************************/
    void testConstructor_velocity()
    {
        // setup
        GPS gps;

        // exercise
        double dx = gps.getVelocity().getDX();
        double dy = gps.getVelocity().getDY();

        // verify
        assertEquals(dx, -3874.0, 0.001);
        assertEquals(dy, 0.0, 0.001);

        // teardown
    }


    /*****************************************************************
     *****************************************************************
     * TEST GPS CONSTRUCTOR — ALIVE FLAG
     *****************************************************************
     *****************************************************************/

     /*********************************************
      * name:    GPS starts alive
      * input:   none
      * output:  alive == true
      *********************************************/
    void testConstructor_aliveFlag()
    {
        // setup
        GPS gps;

        // exercise / verify
        assertUnit(gps.isAlive() == true);

        // teardown
    }


    /*****************************************************************
     *****************************************************************
     * TEST INHERITANCE
     *****************************************************************
     *****************************************************************/

     /*********************************************
      * name:    GPS inherits from Satellite
      * purpose: ensure correct type hierarchy
      *********************************************/
    void testInheritance_isSatellite()
    {
        // setup
        GPS gps;
        Satellite* pSat = &gps;

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
      * name:    GPS orbit radius is correct
      * input:   none
      * output:  sqrt(x² + y²) == 26,578,000
      *********************************************/
    void testConstructor_orbitRadiusAccuracy()
    {
        // setup
        GPS gps;

        double x = gps.getPosition().getMetersX();
        double y = gps.getPosition().getMetersY();

        // exercise
        double r = sqrt(x * x + y * y);

        // verify
        assertEquals(r, 26'578'000.0, 0.5);  // extremely small tolerance

        // teardown
    }


    /*****************************************************************
     *****************************************************************
     * TEST VELOCITY MAGNITUDE
     *****************************************************************
     *****************************************************************/

     /*********************************************
      * name:    GPS speed magnitude is correct
      * input:   none
      * output:  |v| = 3874 m/s
      *********************************************/
    void testConstructor_velocityMagnitude()
    {
        // setup
        GPS gps;

        double dx = gps.getVelocity().getDX();
        double dy = gps.getVelocity().getDY();

        // exercise
        double speed = sqrt(dx * dx + dy * dy);

        // verify
        assertEquals(speed, 3874.0, 0.5);

        // teardown
    }


    /*****************************************************************
     *****************************************************************
     * TEST DRAW
     *****************************************************************
     *****************************************************************/

     /*********************************************
      * name:    draw() does not crash
      * purpose: we cannot verify pixels, but ensure stability
      *********************************************/
    void testDraw_noCrash()
    {
        // setup
        GPS gps;
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
