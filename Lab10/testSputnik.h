/***********************************************************************
 * Header File:
 *      TEST SPUTNIK
 * Author:
 *      Your Name
 * Summary:
 *      Unit tests for the Sputnik satellite class.
 ************************************************************************/

#pragma once

#include "unitTest.h"
#include "sputnik.h"
#include "position.h"
#include "velocity.h"
#include <cmath>

class TestSputnik : public UnitTest
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

        report("Sputnik");
    }

private:

    /*****************************************************************
     *****************************************************************
     * TEST SPUTNIK CONSTRUCTOR — POSITION
     *****************************************************************
     *****************************************************************/

     /*********************************************
      * name:    SPUTNIK CONSTRUCTOR sets starting position
      * input:   none
      * output:  pos = (-36,515,095.13 , 21,082,000.0)
      *********************************************/
    void testConstructor_position()
    {
        // setup
        Sputnik s;

        // exercise
        double x = s.getPosition().getMetersX();
        double y = s.getPosition().getMetersY();

        // verify
        assertEquals(x, -36'515'095.13, 0.01);
        assertEquals(y, 21'082'000.0, 0.01);

        // teardown
    }


    /*****************************************************************
     *****************************************************************
     * TEST SPUTNIK CONSTRUCTOR — VELOCITY
     *****************************************************************
     *****************************************************************/

     /*********************************************
      * name:    SPUTNIK CONSTRUCTOR sets starting velocity
      * input:   none
      * output:  dx = -2050, dy = -2684.68
      *********************************************/
    void testConstructor_velocity()
    {
        // setup
        Sputnik s;

        // exercise
        double dx = s.getVelocity().getDX();
        double dy = s.getVelocity().getDY();

        // verify
        assertEquals(dx, -2050.0, 0.01);
        assertEquals(dy, -2684.68, 0.01);

        // teardown
    }


    /*****************************************************************
     *****************************************************************
     * TEST SPUTNIK CONSTRUCTOR — ALIVE FLAG
     *****************************************************************
     *****************************************************************/

     /*********************************************
      * name:    Sputnik starts alive
      * input:   none
      * output:  alive == true
      *********************************************/
    void testConstructor_aliveFlag()
    {
        // setup
        Sputnik s;

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
      * name:    Sputnik inherits from Satellite
      * purpose: ensure correct hierarchy
      *********************************************/
    void testInheritance_isSatellite()
    {
        // setup
        Sputnik s;
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
      * name:    Sputnik orbit radius is correct
      * input:   none
      * output:  sqrt(x² + y²) matches assignment data
      *********************************************/
    void testConstructor_orbitRadiusAccuracy()
    {
        // setup
        Sputnik s;

        double x = s.getPosition().getMetersX();
        double y = s.getPosition().getMetersY();

        // exercise
        double r = sqrt(x * x + y * y);

        // verify
        double expectedR = sqrt(
            (-36'515'095.13) * (-36'515'095.13) +
            21'082'000.0 * 21'082'000.0
        );

        assertEquals(r, expectedR, 0.01);

        // teardown
    }


    /*****************************************************************
     *****************************************************************
     * TEST VELOCITY MAGNITUDE
     *****************************************************************
     *****************************************************************/

     /*********************************************
      * name:    Sputnik speed magnitude is correct
      * input:   none
      * output:  |v| = sqrt(dx² + dy²)
      *********************************************/
    void testConstructor_velocityMagnitude()
    {
        // setup
        Sputnik s;

        double dx = s.getVelocity().getDX();
        double dy = s.getVelocity().getDY();

        // exercise
        double speed = sqrt(dx * dx + dy * dy);

        // verify
        double expectedSpeed = sqrt(2050.0 * 2050.0 +
            2684.68 * 2684.68);

        assertEquals(speed, expectedSpeed, 0.01);

        // teardown
    }


    /*****************************************************************
     *****************************************************************
     * TEST DRAW
     *****************************************************************
     *****************************************************************/

     /*********************************************
      * name:    draw() does not crash
      * purpose: cannot verify pixels; only stability
      *********************************************/
    void testDraw_noCrash()
    {
        // setup
        Sputnik s;
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
