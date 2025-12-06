#include "simulator.h"
#include "velocity.h" 


/***********************************************
 * SIMULATOR CONSTRUCTOR
 ***********************************************/
Simulator::Simulator(Position ptUpperRight)
   : ptUpperRight(ptUpperRight)
{

   earthAngle = 0.0;  // <<< start Earth at angle 0

   // A set of 6 GPS Satellites
   sats.push_back(new GPS(
      0.0, 26'560'000.0,
      -3880.0, 0.0
   ));

   sats.push_back(new GPS(
      23'001'634.72, 13'280'000.0,
      -1940.0, 3360.18
   ));

   sats.push_back(new GPS(
      23'001'634.72, -13'280'000.0,
      1940.0, 3360.18
   ));

   sats.push_back(new GPS(
      0.0, -26'560'000.0,
      3880.0, 0.0
   ));

   sats.push_back(new GPS(
      -23'001'634.72, -13'280'000.0,
      1940.0, -3360.18
   ));

   sats.push_back(new GPS(
      -23'001'634.72, 13'280'000.0,
      -1940.0, -3360.18
   ));


   sats.push_back(new CrewDragon);
   sats.push_back(new Hubble);
   sats.push_back(new Sputnik);
   sats.push_back(new Starlink);


   // Fragments
   Position fragPos(-23'001'634.72, 13'280'000.0);
   Velocity fragVel(-1940.0, -3360.18);

}