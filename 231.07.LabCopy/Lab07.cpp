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
    Position ptUpperRight;

    Satellite gps;

    double earthAngle;   // <<< holds Earth's rotation angle
};


/***********************************************
 * SIMULATOR CONSTRUCTOR
 ***********************************************/
Simulator::Simulator(Position ptUpperRight)
    : ptUpperRight(ptUpperRight)
{
    // Decorative GPS (ignore)
    ptGPS.setPixelsX(ptUpperRight.getPixelsX() * random(-0.5, 0.5));
    ptGPS.setPixelsY(ptUpperRight.getPixelsY() * random(-0.5, 0.5));

    // REAL GPS satellite initialization
    gps.getPosition().setMetersX(0.0);
    gps.getPosition().setMetersY(26'578'000.0);   // GPS orbit radius

    gps.getVelocity().setDX(-3874.0);  // m/s
    gps.getVelocity().setDY(0.0);

    gps.isAlive();

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
    sim->gps.updatePhysics(TIME_PER_FRAME);

    //
    // EARTH ROTATION UPDATE
    //
    sim->earthAngle += EARTH_ROTATION_PER_FRAME;

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
        gout.drawGPS(satPos, 0.0);
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
