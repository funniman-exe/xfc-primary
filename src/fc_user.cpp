#include "vex.h"

using namespace vex;

#include "fc_user.h"
#include "fc_control.h"
#include "fc_threads.h"
#include "fc_pos_track.h"

#include "fc_instances.h"
#include "fc_log.h"

//#include "../data/horse.h"

bool shownBrainBatteryWarn = false;

// y += heading / 90;

// x += ( 0 - ( heading - 90 ) ) / 90;

void fc_user()
{
	fc_log( logTypes::Info, true, false, __func__, "Begin Usercontrol!\n" );

//	g_brain.Screen.clearScreen();
//	g_brain.Screen.drawImageFromBuffer( horse_png, 0, 0, horse_png_len );

	if ( odometryThread != nullptr ) g_fcOdometry->killThread();

	while ( true ) {
		//g_brain.Screen.clearScreen();
		fc_updateControl();

		fc_updatePos();

		g_brain.Screen.clearScreen();
		g_brain.Screen.setCursor( 1, 1 );
		fc_log( logTypes::Info, false, false, __func__, "x: %d\n", x );
		fc_log( logTypes::Info, false, false, __func__, "y: %d\n", y );
		//(add position tracking via intertial)

	    wait( 5, msec ); // Do nothing
	}
}