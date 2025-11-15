/***********************************************************************
 * Header File:
 *    TEST PHYSICS
 * Author:
 *    Your Name
 * Summary:
 *    Unit tests for the Physics class.
 ************************************************************************/

#pragma once

#include "unitTest.h"
#include "physics.h"
#include "position.h"
#include <cmath>

class TestPhysics : public UnitTest
{
public:

    void run()
    {
        testComputeHeight_atSurface();
        testComputeHeight_aboveSurface();
        testComputeHeight_farAway();

        testComputeGravity_atSurface();
        testComputeGravity_1000m();
        testComputeGravity_highAltitude();

        testComputeGravityAngle_straightUp();
        testComputeGravityAngle_horizontalRight();
        testComputeGravityAngle_quadrantII();

        testComputeAcceleration_downward();
        testComputeAcceleration_angle45();
        testComputeAcceleration_magnitudeCorrect();

        report("Physics");
    }

private:

    /*****************************************************************
     *****************************************************************
     * TEST COMPUTE HEIGHT
     *****************************************************************
     *****************************************************************/

     /*********************************************
      * name:    COMPUTE HEIGHT at surface
      * input:   pos = (0, EARTH_RADIUS)
      * output:  0
      *********************************************/
    void testComputeHeight_atSurface()
    {
        // setup
        Physics p;
        Position pos(0.0, Physics::EARTH_RADIUS);

        // exercise
        double h = p.computeHeight(pos);

        // verify
        assertEquals(h, 0.0);

        // teardown
    }

    /*********************************************
     * name:    COMPUTE HEIGHT above surface
     * input:   pos = (0, EARTH_RADIUS + 1000)
     * output:  1000
     *********************************************/
    void testComputeHeight_aboveSurface()
    {
        // setup
        Physics p;
        Position pos(0.0, Physics::EARTH_RADIUS + 1000.0);

        // exercise
        double h = p.computeHeight(pos);

        // verify
        assertEquals(h, 1000.0);

        // teardown
    }

    /*********************************************
     * name:    COMPUTE HEIGHT far away
     * input:   pos = (0, EARTH_RADIUS + 1,000,000)
     * output:  1,000,000
     *********************************************/
    void testComputeHeight_farAway()
    {
        // setup
        Physics p;
        Position pos(0.0, Physics::EARTH_RADIUS + 1'000'000.0);

        // exercise
        double h = p.computeHeight(pos);

        // verify
        assertEquals(h, 1'000'000.0);

        // teardown
    }


    /*****************************************************************
     *****************************************************************
     * TEST COMPUTE GRAVITY
     *****************************************************************
     *****************************************************************/

     /*********************************************
      * name:    GRAVITY at surface
      * input:   h = 0
      * output:  ≈ 9.80665
      *********************************************/
    void testComputeGravity_atSurface()
    {
        // setup
        Physics p;

        // exercise
        double g = p.computeGravity(0.0);

        // verify
        assertEquals(g, Physics::GRAVITY_SEA_LEVEL, 0.00001);

        // teardown
    }

    /*********************************************
     * name:    GRAVITY at 1000 meters
     * input:   h = 1000
     * output:  slightly less than surface g
     *********************************************/
    void testComputeGravity_1000m()
    {
        // setup
        Physics p;

        // exercise
        double g = p.computeGravity(1000.0);

        // verify
        assertUnit( g < Physics::GRAVITY_SEA_LEVEL);

        // teardown
    }

    /*********************************************
     * name:    GRAVITY at high altitude
     * input:   h = 1,000,000 meters
     * output:  significantly reduced g
     *********************************************/
    void testComputeGravity_highAltitude()
    {
        // setup
        Physics p;

        // exercise
        double g = p.computeGravity(1'000'000.0);

        // verify
        assertUnit(g < Physics::GRAVITY_SEA_LEVEL);  // must be lower than 9.8
        assertUnit(g > 5.0);  // gravity must drop significantly

        // teardown
    }


    /*****************************************************************
     *****************************************************************
     * TEST COMPUTE GRAVITY ANGLE
     *****************************************************************
     *****************************************************************/

     /*********************************************
     * name:    GRAVITY ANGLE: straight up
    * input:   (0, +R)
    * output:  angle is ±π (straight down)
    *********************************************/
    void testComputeGravityAngle_straightUp()
    {
        // setup
        Physics p;
        Position pos(0.0, Physics::EARTH_RADIUS);

        // exercise
        double angle = p.computeGravityAngle(pos);

        // verify: angle should be π or –π
        assertEquals(fabs(angle), 3.14159, 0.001);

        // teardown
    }

    /*********************************************
     * name:    GRAVITY ANGLE: horizontal right
     * input:   (R, 0)
     * output:  -π/2
     *********************************************/
    void testComputeGravityAngle_horizontalRight()
    {
        // setup
        Physics p;
        Position pos(Physics::EARTH_RADIUS, 0.0);

        // exercise
        double angle = p.computeGravityAngle(pos);

        // verify
        assertEquals(angle, -3.14159 / 2.0, 0.01);

        // teardown
    }

    /*********************************************
     * name:    GRAVITY ANGLE: quadrant II
     * input:   (-R/√2, R/√2)
     * output:  135 degrees → angle ≈ 2.356
     *********************************************/
    void testComputeGravityAngle_quadrantII()
    {
        // setup
        Physics p;
        Position pos(-1000.0, 1000.0);

        // exercise
        double angle = p.computeGravityAngle(pos);

        // verify
        assertUnit(angle > 1.5 && angle < 3.0);

        // teardown
    }


    /*****************************************************************
     *****************************************************************
     * TEST COMPUTE ACCELERATION
     *****************************************************************
     *****************************************************************/

     /*********************************************
      * name:    ACCELERATION downward
      * input:   (0, R + 1000)
      * output:  ddx = 0, ddy < 0
      *********************************************/
    void testComputeAcceleration_downward()
    {
        // setup
        Physics p;
        Position pos(0.0, Physics::EARTH_RADIUS + 1000.0);
        double ddx, ddy;

        // exercise
        p.computeAcceleration(pos, ddx, ddy);

        // verify
        assertEquals(ddx, 0.0, 0.0001);
        assertUnit(ddy < 0.0);

        // teardown
    }

    /*********************************************
     * name:    ACCELERATION at 45 degrees
     * input:   pos = (R+1000, R+1000)
     * output:  ddx < 0, ddy < 0
     *********************************************/
    void testComputeAcceleration_angle45()
    {
        // setup
        Physics p;
        Position pos(1000.0 + Physics::EARTH_RADIUS,
            1000.0 + Physics::EARTH_RADIUS);
        double ddx, ddy;

        // exercise
        p.computeAcceleration(pos, ddx, ddy);

        // verify
        assertUnit(ddx < 0);
        assertUnit(ddy < 0);

        // teardown
    }

    /*********************************************
     * name:    ACCELERATION magnitude check
     * purpose: ensures g value matches computeGravity()
     *********************************************/
    void testComputeAcceleration_magnitudeCorrect()
    {
        // setup
        Physics p;
        Position pos(0.0, Physics::EARTH_RADIUS + 1000.0);
        double ddx, ddy;

        double h = p.computeHeight(pos);
        double gExpected = p.computeGravity(h);

        // exercise
        p.computeAcceleration(pos, ddx, ddy);

        double magnitude = sqrt(ddx * ddx + ddy * ddy);

        // verify
        assertEquals(magnitude, gExpected, 0.0001);

        // teardown
    }
};
