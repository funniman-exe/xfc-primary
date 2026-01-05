#include "main.h"

#define turnTime90 425

void auton_ramIntake( int ramCount = 3 )
{
	xfc::globals::g_pMatchload.set_value( 1 );
	xfc::globals::g_mgGantry.move( 127 );

	pros::delay( 500 );

	xfc::globals::g_mgLeft.move( 127 );
	xfc::globals::g_mgRight.move( 127 );
	pros::delay( 600 );
	xfc::globals::g_mgLeft.brake();
	xfc::globals::g_mgRight.brake();

	if ( ramCount > 1 )
	{
		for ( int i = 0; i < ( ramCount - 1 ); ++i )
		{
			pros::delay( 50 );

			xfc::globals::g_mgLeft.move( -64 );
			xfc::globals::g_mgRight.move( -64 );
			pros::delay( 125 );
			xfc::globals::g_mgLeft.brake();
			xfc::globals::g_mgRight.brake();

			pros::delay( 50 );

			xfc::globals::g_mgLeft.move( 127 );
			xfc::globals::g_mgRight.move( 127 );
			pros::delay( 300 );
			xfc::globals::g_mgLeft.brake();
			xfc::globals::g_mgRight.brake();
		}
	}

	pros::delay( 250 );
	
	xfc::globals::g_mgGantry.brake();
	xfc::globals::g_pMatchload.set_value( 0 );
}

/// @brief Dummy auton -- Moves forward a tiny amount to leave park zone
void auton_dummy()
{
	xfc::globals::g_mgLeft.move( 64 );
	xfc::globals::g_mgRight.move( 64 );
	pros::delay( 250 );
	xfc::globals::g_mgLeft.brake();
	xfc::globals::g_mgRight.brake();

	while ( true ) { pros::delay( 20 ); }
}

/// @brief Skills auton
void auton_skills()
{
	xfc::globals::g_mgLeft.move( 64 );
	xfc::globals::g_mgRight.move( 64 );
	pros::delay( 1110 );
	xfc::globals::g_mgLeft.brake();
	xfc::globals::g_mgRight.brake();

	pros::delay( 250 );

	xfc::globals::g_mgLeft.move( -64 );
	xfc::globals::g_mgRight.move( 64 );
	pros::delay( turnTime90 );
	xfc::globals::g_mgLeft.brake();
	xfc::globals::g_mgRight.brake();

	pros::delay( 250 );

	xfc::globals::g_pMatchload.set_value( 1 );
	xfc::globals::g_mgGantry.move( 127 );

	pros::delay( 500 );

	xfc::globals::g_mgLeft.move( 127 );
	xfc::globals::g_mgRight.move( 127 );
	pros::delay( 600 );
	xfc::globals::g_mgLeft.brake();
	xfc::globals::g_mgRight.brake();

	pros::delay( 50 );

	xfc::globals::g_mgLeft.move( -64 );
	xfc::globals::g_mgRight.move( -64 );
	pros::delay( 125 );
	xfc::globals::g_mgLeft.brake();
	xfc::globals::g_mgRight.brake();

	pros::delay( 50 );

	xfc::globals::g_mgLeft.move( 127 );
	xfc::globals::g_mgRight.move( 127 );
	pros::delay( 300 );
	xfc::globals::g_mgLeft.brake();
	xfc::globals::g_mgRight.brake();

	pros::delay( 50 );

	xfc::globals::g_mgLeft.move( -64 );
	xfc::globals::g_mgRight.move( -64 );
	pros::delay( 125 );
	xfc::globals::g_mgLeft.brake();
	xfc::globals::g_mgRight.brake();

	pros::delay( 50 );

	xfc::globals::g_mgLeft.move( 127 );
	xfc::globals::g_mgRight.move( 127 );
	pros::delay( 300 );
	xfc::globals::g_mgLeft.brake();
	xfc::globals::g_mgRight.brake();

	pros::delay( 50 );

	xfc::globals::g_mgLeft.move( -64 );
	xfc::globals::g_mgRight.move( -64 );
	pros::delay( 125 );
	xfc::globals::g_mgLeft.brake();
	xfc::globals::g_mgRight.brake();

	pros::delay( 50 );

	xfc::globals::g_mgLeft.move( 127 );
	xfc::globals::g_mgRight.move( 127 );
	pros::delay( 300 );
	xfc::globals::g_mgLeft.brake();
	xfc::globals::g_mgRight.brake();

	pros::delay( 50 );

	xfc::globals::g_mgLeft.move( -64 );
	xfc::globals::g_mgRight.move( -64 );
	pros::delay( 125 );
	xfc::globals::g_mgLeft.brake();
	xfc::globals::g_mgRight.brake();

	pros::delay( 50 );

	xfc::globals::g_mgLeft.move( 127 );
	xfc::globals::g_mgRight.move( 127 );
	pros::delay( 300 );
	xfc::globals::g_mgLeft.brake();
	xfc::globals::g_mgRight.brake();

	pros::delay( 50 );

	xfc::globals::g_mgLeft.move( -64 );
	xfc::globals::g_mgRight.move( -64 );
	pros::delay( 125 );
	xfc::globals::g_mgLeft.brake();
	xfc::globals::g_mgRight.brake();

	pros::delay( 50 );

	xfc::globals::g_mgLeft.move( 127 );
	xfc::globals::g_mgRight.move( 127 );
	pros::delay( 300 );
	xfc::globals::g_mgLeft.brake();
	xfc::globals::g_mgRight.brake();

	pros::delay( 250 );
	
	xfc::globals::g_mgGantry.brake();
	xfc::globals::g_pMatchload.set_value( 0 );

	xfc::globals::g_mgLeft.move( -64 );
	xfc::globals::g_mgRight.move( -64 );
	pros::delay( 1000 );
	xfc::globals::g_mgLeft.brake();
	xfc::globals::g_mgRight.brake();

	pros::delay( 250 );

	xfc::globals::g_mgGantry.move( 127 );
	xfc::globals::g_mgOutput.move( 127 );

	pros::delay( 6000 );

	xfc::globals::g_mgGantry.brake();
	xfc::globals::g_mgOutput.brake();

	xfc::globals::g_mgLeft.move( 64 );
	xfc::globals::g_mgRight.move( 64 );
	pros::delay( 100 );
	xfc::globals::g_mgLeft.brake();
	xfc::globals::g_mgRight.brake();

	pros::delay( 250 );

	xfc::globals::g_mgLeft.move( -64 );
	xfc::globals::g_mgRight.move( 64 );
	pros::delay( turnTime90 );
	xfc::globals::g_mgLeft.brake();
	xfc::globals::g_mgRight.brake();

	pros::delay( 250 );

	xfc::globals::g_mgLeft.move( 64 );
	xfc::globals::g_mgRight.move( 64 );
	pros::delay( 1250 );
	xfc::globals::g_mgLeft.brake();
	xfc::globals::g_mgRight.brake();

	pros::delay( 250 );

	while ( true ) { pros::delay( 20 ); }
}

/// @brief Left side auton
void auton_left()
{
	xfc::globals::g_mgLeft.move( 64 );
	xfc::globals::g_mgRight.move( 64 );
	pros::delay( 1110 );
	xfc::globals::g_mgLeft.brake();
	xfc::globals::g_mgRight.brake();

	pros::delay( 250 );

	xfc::globals::g_mgLeft.move( -64 );
	xfc::globals::g_mgRight.move( 64 );
	pros::delay( turnTime90 );
	xfc::globals::g_mgLeft.brake();
	xfc::globals::g_mgRight.brake();

	pros::delay( 250 );

	xfc::globals::g_pMatchload.set_value( 1 );
	xfc::globals::g_mgGantry.move( 127 );

	pros::delay( 500 );

	xfc::globals::g_mgLeft.move( 127 );
	xfc::globals::g_mgRight.move( 127 );
	pros::delay( 600 );
	xfc::globals::g_mgLeft.brake();
	xfc::globals::g_mgRight.brake();

	pros::delay( 50 );

	xfc::globals::g_mgLeft.move( -64 );
	xfc::globals::g_mgRight.move( -64 );
	pros::delay( 125 );
	xfc::globals::g_mgLeft.brake();
	xfc::globals::g_mgRight.brake();

	pros::delay( 50 );

	xfc::globals::g_mgLeft.move( 127 );
	xfc::globals::g_mgRight.move( 127 );
	pros::delay( 300 );
	xfc::globals::g_mgLeft.brake();
	xfc::globals::g_mgRight.brake();

	pros::delay( 50 );

	xfc::globals::g_mgLeft.move( -64 );
	xfc::globals::g_mgRight.move( -64 );
	pros::delay( 125 );
	xfc::globals::g_mgLeft.brake();
	xfc::globals::g_mgRight.brake();

	pros::delay( 50 );

	xfc::globals::g_mgLeft.move( 127 );
	xfc::globals::g_mgRight.move( 127 );
	pros::delay( 300 );
	xfc::globals::g_mgLeft.brake();
	xfc::globals::g_mgRight.brake();

	pros::delay( 250 );
	
	xfc::globals::g_mgGantry.brake();
	xfc::globals::g_pMatchload.set_value( 0 );

	xfc::globals::g_mgLeft.move( -64 );
	xfc::globals::g_mgRight.move( -64 );
	pros::delay( 1000 );
	xfc::globals::g_mgLeft.brake();
	xfc::globals::g_mgRight.brake();

	pros::delay( 250 );

	xfc::globals::g_mgGantry.move( 127 );
	xfc::globals::g_mgOutput.move( 127 );

	while ( true ) { pros::delay( 20 ); }
}

/// @brief Right side auton
void auton_right()
{
	xfc::globals::g_mgLeft.move( 64 );
	xfc::globals::g_mgRight.move( 64 );
	pros::delay( 1110 );
	xfc::globals::g_mgLeft.brake();
	xfc::globals::g_mgRight.brake();

	pros::delay( 250 );

	xfc::globals::g_mgLeft.move( 64 );
	xfc::globals::g_mgRight.move( -64 );
	pros::delay( turnTime90 );
	xfc::globals::g_mgLeft.brake();
	xfc::globals::g_mgRight.brake();

	pros::delay( 250 );

	xfc::globals::g_pMatchload.set_value( 1 );
	xfc::globals::g_mgGantry.move( 127 );

	pros::delay( 500 );

	xfc::globals::g_mgLeft.move( 127 );
	xfc::globals::g_mgRight.move( 127 );
	pros::delay( 600 );
	xfc::globals::g_mgLeft.brake();
	xfc::globals::g_mgRight.brake();

	pros::delay( 50 );

	xfc::globals::g_mgLeft.move( -64 );
	xfc::globals::g_mgRight.move( -64 );
	pros::delay( 125 );
	xfc::globals::g_mgLeft.brake();
	xfc::globals::g_mgRight.brake();

	pros::delay( 50 );

	xfc::globals::g_mgLeft.move( 127 );
	xfc::globals::g_mgRight.move( 127 );
	pros::delay( 300 );
	xfc::globals::g_mgLeft.brake();
	xfc::globals::g_mgRight.brake();

	pros::delay( 50 );

	xfc::globals::g_mgLeft.move( -64 );
	xfc::globals::g_mgRight.move( -64 );
	pros::delay( 125 );
	xfc::globals::g_mgLeft.brake();
	xfc::globals::g_mgRight.brake();

	pros::delay( 50 );

	xfc::globals::g_mgLeft.move( 127 );
	xfc::globals::g_mgRight.move( 127 );
	pros::delay( 300 );
	xfc::globals::g_mgLeft.brake();
	xfc::globals::g_mgRight.brake();

	pros::delay( 250 );
	
	xfc::globals::g_mgGantry.brake();
	xfc::globals::g_pMatchload.set_value( 0 );

	xfc::globals::g_mgLeft.move( -64 );
	xfc::globals::g_mgRight.move( -64 );
	pros::delay( 1000 );
	xfc::globals::g_mgLeft.brake();
	xfc::globals::g_mgRight.brake();

	pros::delay( 250 );

	xfc::globals::g_mgGantry.move( 127 );
	xfc::globals::g_mgOutput.move( 127 );

	while ( true ) { pros::delay( 20 ); }
}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous()
{
	if ( !xfc::globals::g_bAutonEnabled )
		auton_dummy();
	else if ( xfc::globals::g_bIsSkillsMatch )
		auton_skills();
	else
	{
		if ( xfc::globals::g_bIsOnLeft )
			auton_left();
		else
			auton_right();
	}
}