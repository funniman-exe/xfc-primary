#include "vex.h"

using namespace vex;

#include "fc_user.h"
#include "fc_control.h"
#include "fc_threads.h"

#include "fc_instances.h"
#include "fc_log.h"

#include "../data/horse.h"

bool shownBrainBatteryWarn = false;

#define ticksPerRotation 36000

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

// y += heading / 90;

// x += ( 0 - ( heading - 90 ) ) / 90;

double toRadians( double degrees )
{
	return degrees * ( M_PI / 180 );
}

double toDegrees( double radians )
{
	return radians * ( 180 / M_PI );
}

void fc_user()
{
	fc_log( logTypes::Info, true, false, __func__, "Begin Usercontrol!\n" );

	g_brain.Screen.clearScreen();
	g_brain.Screen.drawImageFromBuffer( horse_png, 0, 0, horse_png_len );

	if ( odometryThread != nullptr ) g_fcOdometry->killThread();

	while ( true ) {
		//g_brain.Screen.clearScreen();
		fc_updateControl();

		// get encoder angles
		/*encoderX = m_trackingWheelMotor1.angle( rotationUnits::raw );
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
		heading += ( encoderY_change - encoderX_change ) / 9.2345;

		if ( heading > 180 )
			heading = heading - 360;

		if ( heading < -180 )
			heading = 360 + heading;

		// math
		x += encoder_total_mm * cos( toRadians( heading ) );
		y += encoder_total_mm * sin( toRadians( heading ) );

		//printf( "encoderA changed: %d || encoderB changed: %d", encoderA_change, encoderB_change );
		//printf( "encoderA changed: %d || encoderB changed: %d", encoderA, encoderB );

		g_brain.Screen.clearScreen();
		g_brain.Screen.setCursor( 1, 1 );
		fc_log( logTypes::Info, false, false, __func__, "x: %d\n", x );
		fc_log( logTypes::Info, false, false, __func__, "y: %d\n", y );*/

	    wait( 5, msec ); // Do nothing
	}
}