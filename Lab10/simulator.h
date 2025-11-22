
#include "position.h"
#include "gps.h"
#include "satellite.h"
#include "crewDragon.h"
#include "hubble.h"
#include "sputnik.h"
#include "starlink.h"
#include "dreamChaser.h"
#include <vector>

/***********************************************
 * SIMULATOR CLASS
 ***********************************************/
class Simulator
{
public:
    Simulator(Position ptUpperRight);
    
    Position ptUpperRight;

    // GPS Satellite
    Position ptGPS;
    GPS gps;

    //CrewDragon Satellite
    Position ptCrewDragon;
    CrewDragon crewDragon;

    //Hubble Satellite
    Position ptHubble;
    Hubble hubble;

    //Sputnik Satellite
    Position ptSputnik;
    Sputnik sputnik;

    //Starlink Satellite
    Position ptStarlink;
    Starlink starlink;

    std::vector<Satellite*> sats;

    // Dream Chaser
    DreamChaser dreamChaser;

    double earthAngle;   // <<< holds Earth's rotation angle
};


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

}
