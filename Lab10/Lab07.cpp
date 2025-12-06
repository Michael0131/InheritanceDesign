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
#include "simulator.h"
#include "gps.h"
#include "constants.h"
#include "dreamChaser.h"
#include "bullet.h"
#include "fragment.h"
#include <vector>

using namespace std;



/***********************************************
 * CALLBACK — This runs every frame
 ***********************************************/
void callBack(const Interface* pUI, void* p)
{
    Simulator* sim = (Simulator*)p;

    // EARTH ROTATION UPDATE
    //
    sim->earthAngle -= EARTH_ROTATION_PER_FRAME;
    sim->dreamChaser.update(TIME_PER_FRAME);

    //
    // DRAWING
    //
    Position pt;
    ogstream gout(pt);

    // Draw Earth at (0,0)
    Position earthPos;
    earthPos.setMeters(0.0, 0.0);
    gout.drawEarth(earthPos, sim->earthAngle);

    for (Fragment* frag : sim->fragments)
    {
       if (!frag->isAlive())
          continue;
       frag->update(TIME_PER_FRAME);
       frag->decay();
       frag->spin();
       frag->draw(gout);
    }

    for (Satellite* sat : sim->sats)
    {
        if (!sat->isAlive())
            continue;

        // update physics
        sat->update(TIME_PER_FRAME);

        Position Pos = sat->getPosition();

        double x = Pos.getMetersX();
        double y = Pos.getMetersY();

        double angleToEarth = atan2(-x, -y);

        sat->angle = angleToEarth;

        sat->draw(gout);

    }

    // Update and draw bullets
    for (Bullet& b : sim->bullets)
    {
        if (b.isAlive())
        {
            b.update(TIME_PER_FRAME);
            b.draw(gout);
        }
    }

    // Remove bullets that are no longer alive
    sim->bullets.erase(
        remove_if(sim->bullets.begin(), sim->bullets.end(),
            [](const Bullet& b) { return !b.isAlive(); }),
        sim->bullets.end()
    );


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

        // Fire bullet when spacebar is pressed
        if (pUI->isSpace())
        {
            sim->bullets.push_back(sim->dreamChaser.fire());
        }

        gout.drawShip(shipPos, angle, thrust);
    }

    // Collision Detection
    std::vector<Entity*> entities = sim->getEntities();
    int n = (int)entities.size();

    // O(n^2) -- but that's okay for the scope of this assignment 
    // (since the total number of parts, fragments, and satellites is fairly small)
    for (int i = 0; i < n; ++i)
    {
       Entity* a = entities[i];
       if (!a->isAlive()) continue;

       for (int j = i + 1; j < n; ++j)
       {
          Entity* b = entities[j];
          if (!b->isAlive()) continue;

          if (a->collidesWith(*b))     // geometric test
          {
             cout << "Collided!" << endl;
             a->onCollision(*b, *sim);      // response
             b->onCollision(*a, *sim);
          }
       }
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
