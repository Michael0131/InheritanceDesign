/***********************************************************************
 * Header File:
 *      TEST DREAM CHASER
 * Summary:
 *      Unit tests for the DreamChaser controlled spacecraft.
 ************************************************************************/

#pragma once
#define _USE_MATH_DEFINES
#include <cmath>

#include "unitTest.h"
#include "dreamChaser.h"
#include "position.h"
#include "velocity.h"
#include "physics.h"


class TestDreamChaser : public UnitTest
{
public:

    void run()
    {
        testConstructor_initialPosition();
        testConstructor_initialVelocity();
        testConstructor_aliveFlag();
        testConstructor_thrustDefaults();

        testRotate_changesAngle();
        testThrustFlag_setsCorrectly();

        testUpdate_appliesGravity();
        testUpdate_appliesThrustToVelocity();
        testUpdate_movesPositionCorrectly();

        testUpdate_killsWhenBelowSurface();

        testDraw_noCrash();

        report("DreamChaser");
    }

private:

    /*****************************************************************
     * TEST: Starting position is (-450px, 450px)
     *****************************************************************/
    void testConstructor_initialPosition()
    {
        // setup
        DreamChaser dc;

        // exercise
        double x = dc.getPosition().getPixelsX();
        double y = dc.getPosition().getPixelsY();

        // verify
        assertEquals(x, -450.0, 0.01);
        assertEquals(y, 450.0, 0.01);
    }

    /*****************************************************************
     * TEST: Starting velocity is (0, -2000)
     *****************************************************************/
    void testConstructor_initialVelocity()
    {
        // setup
        DreamChaser dc;

        // exercise
        double dx = dc.getVelocity().getDX();
        double dy = dc.getVelocity().getDY();

        // verify
        assertEquals(dx, 0.0, 0.001);
        assertEquals(dy, -2000.0, 0.001);
    }

    /*****************************************************************
     * TEST: DreamChaser starts alive
     *****************************************************************/
    void testConstructor_aliveFlag()
    {
        // setup
        DreamChaser dc;

        // verify
        assertUnit(dc.isAlive() == true);
    }

    /*****************************************************************
     * TEST: Thrust OFF by default
     *****************************************************************/
    void testConstructor_thrustDefaults()
    {
        // setup
        DreamChaser dc;

        // verify
        assertUnit(dc.getThrust() == false);
    }

    /*****************************************************************
     * TEST: rotate() adjusts angle
     *****************************************************************/
    void testRotate_changesAngle()
    {
        // setup
        DreamChaser dc;
        double initial = dc.getRotation();

        // exercise
        dc.rotate(0.1);

        // verify
        assertEquals(dc.getRotation(), initial + 0.1, 0.0001);
    }

    /*****************************************************************
     * TEST: thrust(true/false) sets state correctly
     *****************************************************************/
    void testThrustFlag_setsCorrectly()
    {
        // setup
        DreamChaser dc;

        // exercise
        dc.thrust(true);

        // verify
        assertUnit(dc.getThrust() == true);

        // exercise
        dc.thrust(false);

        // verify
        assertUnit(dc.getThrust() == false);
    }

    /*****************************************************************
     * TEST: Gravity changes velocity after update()
     *****************************************************************/
    void testUpdate_appliesGravity()
    {
        // setup
        DreamChaser dc;
        double originalDX = dc.getVelocity().getDX();
        double originalDY = dc.getVelocity().getDY();

        // *** ensure ship is above surface ***
        dc.getPosition().setMetersY(Physics::EARTH_RADIUS + 100000);

        // exercise
        dc.update(1.0);

        // verify gravity makes DY more negative
        assertUnit(dc.getVelocity().getDY() < originalDY);
    }

    /*****************************************************************
     * TEST: Thrust increases velocity in facing direction
     *****************************************************************/
    void testUpdate_appliesThrustToVelocity()
    {
        // setup
        DreamChaser dc;

        // ensure above surface
        dc.getPosition().setMetersY(Physics::EARTH_RADIUS + 100000);

        dc.rotate(M_PI / 2.0);   // point right → thrust should increase +DX
        dc.thrust(true);

        double origDX = dc.getVelocity().getDX();

        // exercise
        dc.update(1.0);

        // verify
        assertUnit(dc.getVelocity().getDX() > origDX);
    }

    /*****************************************************************
     * TEST: update() moves position based on velocity
     *****************************************************************/
    void testUpdate_movesPositionCorrectly()
    {
        // setup
        DreamChaser dc;

        // ensure above surface
        dc.getPosition().setMetersY(Physics::EARTH_RADIUS + 100000);

        double oldY = dc.getPosition().getMetersY();

        // exercise
        dc.update(1.0);

        // verify → should move down (negative dy)
        assertUnit(dc.getPosition().getMetersY() < oldY);
    }

    /*****************************************************************
     * TEST: Falling into Earth surface causes death
     *****************************************************************/
    void testUpdate_killsWhenBelowSurface()
    {
        // setup
        DreamChaser dc;

        // place below Earth surface
        dc.getPosition().setMetersY(1000); // well inside radius

        // exercise
        dc.update(1.0);

        // verify
        assertUnit(dc.isAlive() == false);
    }

    /*****************************************************************
     * TEST: draw() does not crash
     *****************************************************************/
    void testDraw_noCrash()
    {
        // setup
        DreamChaser dc;
        Position p(0.0, 0.0);
        ogstream gout(p);

        bool crashed = false;

        // exercise
        try
        {
            dc.draw(gout);
        }
        catch (...)
        {
            crashed = true;
        }

        // verify
        assertUnit(crashed == false);
    }
};
