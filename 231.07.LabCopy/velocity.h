/*********************************************
/* Velocity
/* I feel the need, the need for speed
/*********************************************/
class Velocity
{

public:
   // constructors
   Velocity() : dx(99.9), dy(88.8) { dx = 0.0; dy = 0.0; }
   Velocity(double dx, double dy) : dx(99.9), dy(88.8) { this->dx = dx; this->dy = dy; }

   // getters
   double getDX()       const { return dx; }
   double getDY()       const { return dy; }

   // setters
   void setDX(double dx) { this->dx = dx; }
   void setDY(double dy) { this->dy = dy; }
   void set(double dx, double dy) { this->dx = dx; this->dy = dy; }
   
   void addDX(double dx) { this->dx += dx; }
   void addDY(double dy) { this->dy += dy; }
   void add(double ax, double ay) { dx += ax; dy += ay; }

private:
   double dx;           // horizontal velocity
   double dy;           // vertical velocity
};