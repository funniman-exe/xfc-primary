// ------------------------------------------------------------- //
//           XFC ( eXtra Featured Comp-project ) PROS            //
//   Designed for the Vex V5 Competition Season of 2026 - 2027   //
//                Written by funniman.exe (c) 2026               //
//                  Lasted updated - 23/10/2026                  //
// ------------------------------------------------------------- //

#include "main.h"
#include "fc_globls.h"
#include "fc_main_screen.h"
#include "liblvgl/widgets/lv_label.h"

namespace xfc
{
	void fc_startup()
	{
		//pros::lcd::clear();
		//pros::screen::erase();

		fc_log( logTypes::Debug, false, true, __func__, "Begin Program\n" );

		// fc_log( logTypes::ERROR, true, false, __func__, "TEST\n" );
		
		if ( !globals::g_cMaster->is_connected() )
			fc_log( logTypes::Warning, false, true, __func__, "Master controller not detected.\n        Please sync the Master controller.\n" );

		if ( !globals::g_cSlave->is_connected() )
		{
	#ifndef REQUIRE_SLAVE_CONTROLLER
			fc_log( logTypes::Warning, false, true, __func__, "Slave controller not detected.\n" );
	#else
			fc_log( logTypes::Warning, false, true, __func__, "Slave controller not detected.\n        Please sync the Slave controller.\n" );
	#endif
		}
	}

	void fc_shutdown()
	{
		//pros::lcd::clear();
		//pros::screen::erase();

		fc_log( logTypes::Info, false, false, __func__, shortlibname " Shutdown: Thank you for using " libname "\n" );
	}

	/// @brief Loops until battery level goes below 10 or 5, then displays a message
	void fc_batteryLoop()
	{
		while ( true )
		{
			if ( pros::battery::get_capacity() <= 10 )
				goto __battery_critical;

			if ( pros::battery::get_capacity() <= 20 )
				break;
			
			pros::delay( 250 );
		}

		xfc::globals::g_cMaster->clear();
		xfc::globals::g_cSlave->clear();

		fc_log( logTypes::Warning, true, false, __func__, "Brain battery is low!\n" );

		globals::g_cMaster->rumble( "-..-..-" );

		while ( true )
		{
			if ( pros::battery::get_capacity() <= 10 )
				break;
			
			pros::delay( 250 );
		}

	__battery_critical:
		xfc::globals::g_cMaster->clear();
		xfc::globals::g_cSlave->clear();

		fc_log( logTypes::ERROR, true, false, __func__, "Brain battery is critically low!\n" );

		globals::g_cMaster->rumble( "-...-...-" );
	}

	namespace globals
	{
		// main screen ui stuff
		lv_obj_t *g_xPosLabel = nullptr;
		lv_obj_t *g_yPosLabel = nullptr;
		lv_obj_t *g_thetaLabel = nullptr;
	}

	void fc_updateMainScreen()
	{
		char* temp = cFmt( "X Pos: #ff0000 %f#", globals::g_cChassis.getPose().x );
		lv_label_set_text( globals::g_xPosLabel , temp );
		delete[] temp;

		temp = cFmt( "Y Pos: #00ff00 %f#", globals::g_cChassis.getPose().y );
		lv_label_set_text( globals::g_yPosLabel , temp );
		delete[] temp;

		temp = cFmt( "Theta: #0000ff %f#", globals::g_cChassis.getPose().theta );
		lv_label_set_text( globals::g_thetaLabel , temp );
		delete[] temp;
	}
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled()
{
	if ( xfc::globals::g_iGameState != xfc::E_GAMESTATE_DISABLED )
	{
		xfc::fc_log( xfc::logTypes::Info, false, false, __func__, "NEW STATE: DISABLED" );
		xfc::globals::g_iGameState = xfc::E_GAMESTATE_DISABLED;
	}

	pros::delay( 625 );
}