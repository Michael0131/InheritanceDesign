
#pragma once

#include "position.h"
#include "gps.h"
#include "crewDragon.h"
#include "hubble.h"
#include "sputnik.h"
#include "starlink.h"
#include "dreamChaser.h"
#include "bullet.h"
#include "fragment.h"
#include "part.h"
#include "star.h"
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

    // CrewDragon Satellite
    Position ptCrewDragon;
    CrewDragon crewDragon;

    // Hubble Satellite
    Position ptHubble;
    Hubble hubble;

    // Sputnik Satellite
    Position ptSputnik;
    Sputnik sputnik;

    // Starlink Satellite
    Position ptStarlink;
    Starlink starlink;

    std::vector<Satellite*> sats;

    std::vector<Bullet> bullets;

    // Dream Chaser
    DreamChaser dreamChaser;

    // Part
    std::vector<Part*> parts;
    // Fragment
    std::vector<Fragment*> fragments;

    // Stars
    std::vector<Star*> stars;

    std::vector<Entity*> getEntities()
    {
       std::vector<Entity*> entities;

       // all satellites (GPS, CrewDragon, Hubble, Sputnik, Starlink...)
       for (Satellite* s : sats)
          entities.push_back(s);

       // ship
       entities.push_back(&dreamChaser);

       // bullets
       for (Bullet& b : bullets)
          entities.push_back(&b);

       // all fragments and parts
       for (Fragment* f : fragments)
          entities.push_back(f);

       for (Part* p : parts)
          entities.push_back(p);

       return entities;
    }

    double earthAngle;   // <<< holds Earth's rotation angle
};
