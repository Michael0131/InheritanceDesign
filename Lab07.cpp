/*************************************************************
 * 1. Name:
 *      Simulator
 * 2. Assignment Name:
 *      Lab 07: Orbit Simulator
 * 3. Assignment Description:
 *      Simulate satellites orbiting the earth
 *****************************************************************/

#define _USE_MATH_DEFINES

#include <cassert>
#include <cmath>
#include "uiInteract.h"
#include "uiDraw.h"
#include "position.h"
#include "test.h"
#include "satellite.h"
#include "gps.h"
#include "dreamChaser.h"
#include <vector>

using namespace std;

/***********************************************
 * TIME CONSTANTS
 ***********************************************/
const double HOURS_PER_DAY = 24.0;
const double MINUTES_PER_HOUR = 60.0;
const double FRAMES_PER_SECOND = 30.0;

const double TIME_DILATION = HOURS_PER_DAY * MINUTES_PER_HOUR;     // 1440
const double TIME_PER_FRAME = TIME_DILATION / FRAMES_PER_SECOND;   // 48 sec/frame

// Earth rotates one full turn every 24 hours
const double SECONDS_PER_DAY = 24.0 * 60.0 * 60.0; // 86400 seconds
const double EARTH_ROTATION_PER_FRAME =
(2.0 * M_PI / SECONDS_PER_DAY) * TIME_PER_FRAME;   // radians per frame


/***********************************************
 * SIMULATOR CLASS
 ***********************************************/
class Simulator
{
public:
    Simulator(Position ptUpperRight);

    Position ptGPS;
    Position ptDreamChaser;
    Position ptUpperRight;

    DreamChaser dreamChaser;
    GPS gps;

    std::vector<Satellite*> sats;

    double earthAngle;   // <<< holds Earth's rotation angle
};


/***********************************************
 * SIMULATOR CONSTRUCTOR
 ***********************************************/
Simulator::Simulator(Position ptUpperRight)
    : ptUpperRight(ptUpperRight)
{
    sats.push_back(new GPS());

    earthAngle = 0.0;  // <<< start Earth at angle 0
}


/***********************************************
 * CALLBACK — This runs every frame
 ***********************************************/
void callBack(const Interface* pUI, void* p)
{
    Simulator* sim = (Simulator*)p;

    //
    // PHYSICS UPDATE
    //
    sim->gps.update(TIME_PER_FRAME);
    sim->dreamChaser.update(TIME_PER_FRAME);
    //
    // EARTH ROTATION UPDATE
    //
    sim->earthAngle -= EARTH_ROTATION_PER_FRAME;

    //
    // DRAWING
    //
    Position pt;
    ogstream gout(pt);

    // Draw Earth at (0,0)
    Position earthPos;
    earthPos.setMeters(0.0, 0.0);
    gout.drawEarth(earthPos, sim->earthAngle);

    // Draw orbiting satellite
    if (sim->gps.isAlive())
    {
        Position satPos;
        satPos.setMetersX(sim->gps.getPosition().getMetersX());
        satPos.setMetersY(sim->gps.getPosition().getMetersY());

        // compute angle so satellite faces Earth
        double x = satPos.getMetersX();
        double y = satPos.getMetersY();

        double angleToEarth = atan2(-x, -y);

        gout.drawGPS(satPos, angleToEarth);
    }
    if (sim->dreamChaser.isAlive())
    {
       Position shipPos;
       shipPos.setMetersX(sim->dreamChaser.getPosition().getMetersX());
       shipPos.setMetersY(sim->dreamChaser.getPosition().getMetersY());

        // control the Dream Chaser
        if (pUI->isDown())
            sim->dreamChaser.thrust(true);
        else
            sim->dreamChaser.thrust(false);
        if (pUI->isLeft())
            sim->dreamChaser.rotate(-0.1);
        if (pUI->isRight())
            sim->dreamChaser.rotate(0.1);
       
       double x = shipPos.getMetersX();
       double y = shipPos.getMetersY();
       double thrust = sim->dreamChaser.getThrust();

       double angle = sim->dreamChaser.getRotation();

       gout.drawShip(shipPos, angle, thrust);
    }

}


/***********************************************
 * MAIN — initializes the simulation
 ***********************************************/
double Position::metersFromPixels = 40.0;

#ifndef _WIN32_X
int main(int argc, char** argv)
#else
int WINAPI wWinMain(HINSTANCE, HINSTANCE, PWSTR, int)
#endif
{
    testRunner();

    // Setup OpenGL
    Position ptUpperRight;
    ptUpperRight.setZoom(128000.0);   // 128 km per pixel
    ptUpperRight.setPixelsX(1000.0);
    ptUpperRight.setPixelsY(1000.0);

    Interface ui(0, NULL, "Simulator", ptUpperRight);

    // Create simulator
    Simulator simulator(ptUpperRight);

    // Run loop
    ui.run(callBack, &simulator);

    return 0;
}
