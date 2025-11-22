/*********************************************
/* Velocity
/* I feel the need, the need for speed
/*********************************************/

#pragma once

#include <math.h>

class TestVelocity;

class Velocity
{
	friend class TestVelocity;

public:
	// default constructor
	Velocity() : dx(0.0), dy(0.0) {}

	// non-default constructor
	Velocity(double dx, double dy) : dx(dx), dy(dy) {}

	// getters
	double getDX() const { return dx; }
	double getDY() const { return dy; }

	// setters
	void setDX(double dx) { this->dx = dx; }
	void setDY(double dy) { this->dy = dy; }
	void set(double dx, double dy) { this->dx = dx; this->dy = dy; }

	// modifiers
	void addDX(double dx) { this->dx += dx; }
	void addDY(double dy) { this->dy += dy; }
	void add(double ax, double ay) { dx += ax; dy += ay; }

private:
	double dx;  // horizontal velocity
	double dy;  // vertical velocity
};
