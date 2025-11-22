/***********************************************************************
 * Header File:
 *      TEST STARLINK
 * Author:
 *      Your Name
 * Summary:
 *      Unit tests for the Starlink satellite class.
 ************************************************************************/

#pragma once

#include "unitTest.h"
#include "starlink.h"
#include "position.h"
#include "velocity.h"
#include <cmath>

class TestStarlink : public UnitTest
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

        report("Starlink");
    }

private:

    /*****************************************************************
     *****************************************************************
     * TEST STARLINK CONSTRUCTOR — POSITION
     *****************************************************************
     *****************************************************************/

     /*********************************************
      * name:    STARLINK CONSTRUCTOR sets starting position
      * input:   none
      * output:  pos = (0, -13,020,000)
      *********************************************/
    void testConstructor_position()
    {
        // setup
        Starlink s;

        // exercise
        double x = s.getPosition().getMetersX();
        double y = s.getPosition().getMetersY();

        // verify
        assertEquals(x, 0.0, 0.0001);
        assertEquals(y, -13'020'000.0, 1.0);

        // teardown
    }

    /*****************************************************************
     *****************************************************************
     * TEST STARLINK CONSTRUCTOR — VELOCITY
     *****************************************************************
     *****************************************************************/

     /*********************************************
      * name:    STARLINK CONSTRUCTOR sets starting velocity
      * input:   none
      * output:  dx = -5800, dy = 0
      *********************************************/
    void testConstructor_velocity()
    {
        // setup
        Starlink s;

        // exercise
        double dx = s.getVelocity().getDX();
        double dy = s.getVelocity().getDY();

        // verify
        assertEquals(dx, -5800.0, 0.01);
        assertEquals(dy, 0.0, 0.01);

        // teardown
    }

    /*****************************************************************
     *****************************************************************
     * TEST STARLINK CONSTRUCTOR — ALIVE FLAG
     *****************************************************************
     *****************************************************************/

     /*********************************************
      * name:    Starlink starts alive
      * input:   none
      * output:  alive == true
      *********************************************/
    void testConstructor_aliveFlag()
    {
        // setup
        Starlink s;

        // exercise / verify
        assertUnit(s.isAlive() == true);

        // teardown
    }

    /*****************************************************************
     *****************************************************************
     * TEST INHERITANCE
     *****************************************************************
     *****************************************************************/

     /*********************************************
      * name:    Starlink inherits from Satellite
      * purpose: ensure correct hierarchy
      *********************************************/
    void testInheritance_isSatellite()
    {
        // setup
        Starlink s;
        Satellite* pSat = &s;

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
      * name:    Starlink orbit radius is correct
      * input:   none
      * output:  sqrt(x² + y²) == |13,020,000|
      *********************************************/
    void testConstructor_orbitRadiusAccuracy()
    {
        // setup
        Starlink s;

        double x = s.getPosition().getMetersX();
        double y = s.getPosition().getMetersY();

        // exercise
        double r = sqrt(x * x + y * y);

        // verify
        assertEquals(r, 13'020'000.0, 0.5);

        // teardown
    }

    /*****************************************************************
     *****************************************************************
     * TEST VELOCITY MAGNITUDE
     *****************************************************************
     *****************************************************************/

     /*********************************************
      * name:    Starlink speed magnitude is correct
      * input:   none
      * output:  |v| = 5800
      *********************************************/
    void testConstructor_velocityMagnitude()
    {
        // setup
        Starlink s;

        double dx = s.getVelocity().getDX();
        double dy = s.getVelocity().getDY();

        // exercise
        double speed = sqrt(dx * dx + dy * dy);

        // verify
        assertEquals(speed, 5800.0, 0.5);

        // teardown
    }

    /*****************************************************************
     *****************************************************************
     * TEST DRAW
     *****************************************************************
     *****************************************************************/

     /*********************************************
      * name:    draw() does not crash
      * purpose: ensure renderer safety
      *********************************************/
    void testDraw_noCrash()
    {
        // setup
        Starlink s;
        Position p(0.0, 0.0);
        ogstream gout(p);

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

        // teardown
    }
};
