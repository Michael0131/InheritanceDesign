#pragma once

#include "uiInteract.h" // for INTERFACE
#include "uiDraw.h"     // for RANDOM and DRAW*

#include "position.h"      // for POINT
#include "velocity.h"

#include "test.h"
#include <cmath>


#include <iostream>
using namespace std;


class Position;
class Velocity;




class Entity
{
public:

   Entity() : pos(0.0, 0.0), v(0.0, 0.0), angle(0.0), radius(0.0), alive(true) {}

   // Getters
   Velocity& getVelocity() { return v; }
   const Velocity& getVelocity() const { return v; }

   Position& getPosition() { return pos; }
   const Position& getPosition() const { return pos; }


   bool isAlive() const { return alive; }


   // Additional Methods
   virtual void update(double dt);

   virtual void draw(ogstream& gout);


protected:

   Position pos;
   Velocity v;

   double angle;
   double radius;

   bool alive;
};

