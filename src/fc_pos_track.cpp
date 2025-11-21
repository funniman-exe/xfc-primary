#include "vex.h"

using namespace vex;

#include "fc_pos_track.h"

#include "fc_instances.h"
#include "fc_log.h"

rotation m_trackingWheelMotor1( PORT12 );
rotation m_trackingWheelMotor2( PORT4 );

int x = 0;
int y = 0;
int heading = 0;

int encoderX = 0;
int encoderY = 0;
int encoderX_prev = 0;
int encoderY_prev = 0;
int encoderX_change = 0;
int encoderY_change = 0;
int encoderX_change_dist = 0;
int encoderY_change_dist = 0;
int encoder_total_mm = 0;

const double omniTrackingWheelRadiusMM = 25.4;

double toRadians( double degrees )
{
	return degrees * ( M_PI / 180 );
}

double toDegrees( double radians )
{
	return radians * ( 180 / M_PI );
}

void fc_updatePos()
{
    // get encoder angles
    encoderX = m_trackingWheelMotor1.angle( rotationUnits::raw );
    encoderX = m_trackingWheelMotor2.angle( rotationUnits::raw );

    // detect if angle changed
    if ( encoderX != encoderX_prev )
        encoderX_change = encoderX - encoderX_prev;
    
    encoderX_prev = encoderX;

    // detect if angle changed
    if ( encoderY != encoderY_prev )
        encoderY_change = encoderY - encoderY_prev;
    
    encoderY_prev = encoderY;

    // get distance
    encoderX_change_dist = toRadians( encoderX_change / 100 ) * omniTrackingWheelRadiusMM;
    encoderY_change_dist = toRadians( encoderY_change / 100 ) * omniTrackingWheelRadiusMM;

    // average the two distances
    encoder_total_mm = ( encoderX_change_dist + encoderY_change_dist ) / 2.0;

    // adjust heading
    heading = m_inertial.angle();
    //heading += ( encoderY_change - encoderX_change ) / 9.2345;

    if ( heading > 180 )
        heading = heading - 360;

    if ( heading < -180 )
        heading = 360 + heading;

    // math
    x += encoder_total_mm * cos( toRadians( heading ) );
    y += encoder_total_mm * sin( toRadians( heading ) );

    //printf( "encoderA changed: %d || encoderB changed: %d", encoderA_change, encoderB_change );
    //printf( "encoderA changed: %d || encoderB changed: %d", encoderA, encoderB );
}