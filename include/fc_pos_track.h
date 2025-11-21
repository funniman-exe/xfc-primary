#include "vex.h"

using namespace vex;

#define ticksPerRotation 36000

extern rotation m_trackingWheelMotor1;
extern rotation m_trackingWheelMotor2;

extern int x;
extern int y;
extern int heading;

extern int encoderX;
extern int encoderY;
extern int encoderX_prev;
extern int encoderY_prev;
extern int encoderX_change;
extern int encoderY_change;
extern int encoderX_change_dist;
extern int encoderY_change_dist;
extern int encoder_total_mm;

extern const double omniTrackingWheelRadiusMM;

double toRadians( double degrees );
double toDegrees( double radians );

void fc_updatePos();