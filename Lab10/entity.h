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
class TestEntity;



class Entity
{
	friend TestEntity;
public:

   Entity() : pos(0.0, 0.0), v(0.0, 0.0), angle(0.0), radius(0.0), alive(true) {}

   // Setters
   void setRadius(double r) { radius = r; }

   // Getters
   Velocity& getVelocity() { return v; }
   const Velocity& getVelocity() const { return v; }

   Position& getPosition() { return pos; }
   const Position& getPosition() const { return pos; }

   double getRadius() const { return radius; }


   bool isAlive() const { return alive; }


   // Additional Methods
   virtual void update(double dt);

   virtual void draw(ogstream& gout);

   // Collision
   bool collidesWith(const Entity& other) const; // collision check

   virtual void onCollision(Entity& other) { alive = false; } // reaction to collision

protected:

   Position pos;
   Velocity v;

   double angle;
   double radius;

   bool alive;
};

