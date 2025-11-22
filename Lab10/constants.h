
#define _USE_MATH_DEFINES
#include <cmath>



/***********************************************
 * TIME CONSTANTS
 ***********************************************/
const double HOURS_PER_DAY = 24.0;
const double MINUTES_PER_HOUR = 60.0;
const double FRAMES_PER_SECOND = 30.0;

const double TIME_DILATION = HOURS_PER_DAY * MINUTES_PER_HOUR;     // 1440
const double TIME_PER_FRAME = TIME_DILATION / FRAMES_PER_SECOND;   // 48 sec/frame

// Earth rotates one full turn every 24 hours
const double SECONDS_PER_DAY = 24.0 * 60.0 * 60.0; // 86400 seconds
const double EARTH_ROTATION_PER_FRAME =
(2.0 * M_PI / SECONDS_PER_DAY) * TIME_PER_FRAME;   // radians per frame

