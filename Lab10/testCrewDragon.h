/***********************************************************************
 * Header File:
 *      TEST CREW DRAGON
 * Author:
 *      Your Name
 * Summary:
 *      Unit tests for the CrewDragon satellite class.
 ************************************************************************/

#pragma once

#include "unitTest.h"
#include "crewDragon.h"
#include "position.h"
#include "velocity.h"
#include <cmath>

class TestCrewDragon : public UnitTest
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

        report("CrewDragon");
    }

private:

    /*****************************************************************
     *****************************************************************
     * TEST CREW DRAGON CONSTRUCTOR — POSITION
     *****************************************************************
     *****************************************************************/

     /*********************************************
      * name:    CREWDRAGON CONSTRUCTOR sets starting position
      * input:   none (default constructor)
      * output:  pos = (0, ORBIT_RADIUS)
      *********************************************/
    void testConstructor_position()
    {
        // setup
        CrewDragon cd;

        // exercise
        double x = cd.getPosition().getMetersX();
        double y = cd.getPosition().getMetersY();

        // verify
        assertEquals(x, 0.0, 0.0001);
        assertEquals(y, 8'000'000.0, 1.0);  // 1 meter tolerance

        // teardown
    }

    /*****************************************************************
     *****************************************************************
     * TEST CREW DRAGON CONSTRUCTOR — VELOCITY
     *****************************************************************
     *****************************************************************/

     /*********************************************
      * name:    CREWDRAGON CONSTRUCTOR sets starting velocity
      * input:   none
      * output:  dx = -7900, dy = 0
      *********************************************/
    void testConstructor_velocity()
    {
        // setup
        CrewDragon cd;

        // exercise
        double dx = cd.getVelocity().getDX();
        double dy = cd.getVelocity().getDY();

        // verify
        assertEquals(dx, -7900.0, 0.001);
        assertEquals(dy, 0.0, 0.001);

        // teardown
    }


    /*****************************************************************
     *****************************************************************
     * TEST CREW DRAGON CONSTRUCTOR — ALIVE FLAG
     *****************************************************************
     *****************************************************************/

     /*********************************************
      * name:    CrewDragon starts alive
      * input:   none
      * output:  alive == true
      *********************************************/
    void testConstructor_aliveFlag()
    {
        // setup
        CrewDragon cd;

        // exercise / verify
        assertUnit(cd.isAlive() == true);

        // teardown
    }


    /*****************************************************************
     *****************************************************************
     * TEST INHERITANCE
     *****************************************************************
     *****************************************************************/

     /*********************************************
      * name:    CrewDragon inherits from Satellite
      * purpose: ensure correct type hierarchy
      *********************************************/
    void testInheritance_isSatellite()
    {
        // setup
        CrewDragon cd;
        Satellite* pSat = &cd;

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
      * name:    CrewDragon orbit radius is correct
      * input:   none
      * output:  sqrt(x² + y²) == 8,000,000
      *********************************************/
    void testConstructor_orbitRadiusAccuracy()
    {
        // setup
        CrewDragon cd;

        double x = cd.getPosition().getMetersX();
        double y = cd.getPosition().getMetersY();

        // exercise
        double r = sqrt(x * x + y * y);

        // verify
        assertEquals(r, 8'000'000.0, 0.5);

        // teardown
    }


    /*****************************************************************
     *****************************************************************
     * TEST VELOCITY MAGNITUDE
     *****************************************************************
     *****************************************************************/

     /*********************************************
      * name:    CrewDragon speed magnitude is correct
      * input:   none
      * output:  |v| = 7900 m/s
      *********************************************/
    void testConstructor_velocityMagnitude()
    {
        // setup
        CrewDragon cd;

        double dx = cd.getVelocity().getDX();
        double dy = cd.getVelocity().getDY();

        // exercise
        double speed = sqrt(dx * dx + dy * dy);

        // verify
        assertEquals(speed, 7900.0, 0.5);

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
        CrewDragon cd;
        Position p(0.0, 0.0);
        ogstream gout(p);

        bool crashed = false;

        // exercise
        try
        {
            cd.draw(gout);
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

