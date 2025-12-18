// ------------------------------------------------------------- //
//           XFC ( eXtra Featured Comp-project ) PROS            //
//   Designed for the Vex V5 Competition Season of 2025 - 2026   //
//                Written by funniman.exe (c) 2026               //
//                  Lasted updated - 18/12/2025                  //
// ------------------------------------------------------------- //

#include "main.h"

namespace xfc
{
	void fc_startup()
	{
		//pros::lcd::clear();
		//pros::screen::erase();

		fc_log( logTypes::Info, false, false, __func__, "Hewwo :3 I am " botname "!!!\n" );
		fc_log( logTypes::Info, false, false, __func__, "-- Welcome to " libname " (configured for " gamename ") --\n" );
		//fc_log( logTypes::Info, false, false, __func__, "ich bin das krankenhaus" );
		fc_log( logTypes::Info, false, false, __func__, "  (c) 2025 funniman.exe\n" );
		fc_log( logTypes::Debug, false, true, __func__, "Begin Program\n" );

		if ( !globals::g_cMaster->is_connected() )
		{
			fc_log( logTypes::Warning, false, true, __func__, "Master controller not detected.\n        Please sync the Master controller.\n" );
		}

		if ( !globals::g_cSlave->is_connected() )
		{
	#ifndef REQUIRE_SLAVE_CONTROLLER
			fc_log( logTypes::Warning, false, true, __func__, "Slave controller not detected.\n" );
	#else
			fc_log( logTypes::Warning, false, true, __func__, "Slave controller not detected.\n        Please sync the Slave controller.\n" );
	#endif
		}

		fc_log( logTypes::ERROR, false, true, __func__, ":3\n" );
	}

	void fc_shutdown()
	{
		pros::lcd::clear();
		//pros::screen::erase();

		fc_log( logTypes::Info, false, false, __func__, shortlibname " Shutdown: Thank you for using " libname "\n" );
	}

	/// @brief Loops until battery level goes below 10 or 5, then displays a message
	void fc_batteryLoop()
	{
		while ( true )
		{
			if ( pros::battery::get_capacity() <= 5 )
				goto __battery_critical;

			if ( pros::battery::get_capacity() <= 10 )
				break;
			
			pros::delay( 125 );
		}

		xfc::globals::g_cMaster->clear();
		xfc::globals::g_cSlave->clear();

		fc_log( logTypes::Info, true, false, __func__, "Brain battery is low!\n" );

		globals::g_cMaster->rumble( "-..-..-" );

		while ( true )
		{
			if ( pros::battery::get_capacity() <= 5 )
				break;
			
			pros::delay( 125 );
		}

	__battery_critical:
		xfc::globals::g_cMaster->clear();
		xfc::globals::g_cSlave->clear();

		fc_log( logTypes::Info, true, false, __func__, "Brain battery is critically low!\n" );

		globals::g_cMaster->rumble( "-...-...-" );
	}
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled()
{
	static int loadingAnimCounter = 0;
	static bool disabled = false;

	if ( !disabled )
	{
		xfc::fc_log( xfc::logTypes::Info, false, false, __func__, "XFC is currently in a disabled state." );
		disabled = true;
	}

	static std::string loadingText = "Awaiting ";

	switch ( loadingAnimCounter++ )
	{
	case 0:
		loadingText += "/";
		break;
	
	case 1:
		loadingText += "-";
		break;

	case 2:
		loadingText += "\\";
		break;

	case 3:
		loadingAnimCounter = 0;
		loadingText += "|";
		break;
	
	default:
		break;
	}


	pros::delay( 625 );
}