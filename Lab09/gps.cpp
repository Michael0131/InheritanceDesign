#include "gps.h"
#include "uiDraw.h"
#include <cmath>

static const double GPS_RADIUS_M = 42164000.0;
static const double GPS_SPEED = 3074.6;

GPS::GPS()
{
   radius = 12.0;
   angle = 0.0;

   pos.setMeters(0.0, GPS_RADIUS_M);
   v.set((-1.0 * GPS_SPEED), 0.0);
}

void GPS::draw(ogstream& gout)
{
   gout.drawGPS(pos, angle);
}