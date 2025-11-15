/*************************************************************
 * 1. Name:
 *      Simulator
 * 2. Assignment Name:
 *      Lab 07: Orbit Simulator
 * 3. Assignment Description:
 *      Simulate satellites orbiting the earth
 * 4. What was the hardest part? Be as specific as possible.
 *      ??
 * 5. How long did it take for you to complete the assignment?
 *      ??
 *****************************************************************/
#define _USE_MATH_DEFINES

#include <cassert>      // for ASSERT
#include "uiInteract.h" // for INTERFACE
#include "uiDraw.h"     // for RANDOM and DRAW*
#include "position.h"      // for POINT
#include "test.h"
#include <cmath>
using namespace std;

#include "satellite.h"


/***********************************************
 * CONSTANTS FOR ORBIT SIMULATION
 ***********************************************/

const double HOURS_PER_DAY = 24.0;      // hours in a day
const double MINUTES_PER_HOUR = 60.0;      // minutes in an hour
const double FRAMES_PER_SECOND = 30.0;      // 30 FPS simulation rate

// Time dilation: sim runs 1440x faster than real time
const double TIME_DILATION = HOURS_PER_DAY * MINUTES_PER_HOUR; // 24 * 60 = 1440

// Each frame represents 48 real-world seconds
const double TIME_PER_FRAME = TIME_DILATION / FRAMES_PER_SECOND; // 1440 / 30 = 48



/*************************************************************************
 * Simulator
 * Test structure to capture the LM that will move around the screen
 *************************************************************************/
class Simulator
{
public:
   Simulator(Position ptUpperRight) :
      ptUpperRight(ptUpperRight)
   {
      ptGPS.setPixelsX(ptUpperRight.getPixelsX() * random(-0.5, 0.5));
      ptGPS.setPixelsY(ptUpperRight.getPixelsY() * random(-0.5, 0.5));
   }
  
   Position ptGPS;
   Position ptUpperRight;

   Satellite gps;
};

/*************************************
 * All the interesting work happens here, when
 * I get called back from OpenGL to draw a frame.
 * When I am finished drawing, then the graphics
 * engine will wait until the proper amount of
 * time has passed and put the drawing on the screen.
 **************************************/
void callBack(const Interface* pUI, void* p)
{
   // the first step is to cast the void pointer into a game object. This
   // is the first step of every single callback function in OpenGL. 
   Simulator* pSimulator = (Simulator*)p;

  


   //
   // perform all the game logic
   //

   

   pSimulator->gps.updatePhysics(TIME_PER_FRAME);

   //
   // draw everything
   //

   Position pt;
   ogstream gout(pt);

   // draw satellites
   // gout.drawCrewDragon(pSimulator->ptCrewDragon, pSimulator->angleShip);
   // gout.drawHubble    (pSimulator->ptHubble,     pSimulator->angleShip);
   // gout.drawSputnik   (pSimulator->ptSputnik,    pSimulator->angleShip);
   // gout.drawStarlink  (pSimulator->ptStarlink,   pSimulator->angleShip);
   // gout.drawShip      (pSimulator->ptShip,       pSimulator->angleShip, pUI->isSpace());
   if (pSimulator->gps.isAlive())
   {
      Position satPos;
      satPos.setMetersX(pSimulator->gps.getPosition().getMetersX());
      satPos.setMetersY(pSimulator->gps.getPosition().getMetersY());
      gout.drawGPS(satPos, 0.0);
   }

}

double Position::metersFromPixels = 40.0;

/*********************************
 * Initialize the simulation and set it in motion
 *********************************/
#ifdef _WIN32_X
#include <windows.h>
int WINAPI wWinMain(
   _In_ HINSTANCE hInstance,
   _In_opt_ HINSTANCE hPrevInstance,
   _In_ PWSTR pCmdLine,
   _In_ int nCmdShow)
#else // !_WIN32
int main(int argc, char** argv)
#endif // !_WIN32
{


   testRunner();

   // Initialize OpenGL
   Position ptUpperRight;
   ptUpperRight.setZoom(128000.0 /* 128km equals 1 pixel */);
   ptUpperRight.setPixelsX(1000.0);
   ptUpperRight.setPixelsY(1000.0);
   Interface ui(0, NULL,
      "Simulator",   /* name on the window */
      ptUpperRight);

   // Initialize the Simulator
   Simulator Simulator(ptUpperRight);

   // set everything into action
   ui.run(callBack, &Simulator);

   return 0;
}
