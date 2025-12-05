// ------------------------------------------------------------- //
//              XFC ( eXtra Featured Comp-project )              //
//   Designed for the Vex V5 Competition Season of 2025 - 2026   //
//                Written by funniman.exe (c) 2025               //
//                  Lasted updated - 25/11/2025                  //
// ------------------------------------------------------------- //

#include "main.h"

namespace xfc
{
	void fc_startup()
	{
		pros::lcd::clear();
		//pros::screen::erase();

		fc_log( logTypes::Info, false, false, __func__, "Hewwo :3 I am " botname "!!!\n" );
		fc_log( logTypes::Info, false, false, __func__, "-- Welcome to " libname " (configured for " gamename ") --\n" );
		//fc_log( logTypes::Info, false, false, __func__, "ich bin das krankenhaus" );
		fc_log( logTypes::Info, false, false, __func__, "  (c) 2025 funniman.exe\n" );
		fc_log( logTypes::Debug, false, true, __func__, "Begin Program\n" );

		if ( !globals::g_cMaster->is_connected() )
		{
			fc_log( logTypes::ERROR, false, true, __func__, "Master controller not detected.\n" );
			fc_log( logTypes::ERROR, false, false, __func__, "Please sync the Master controller.\n" );
		}

		if ( !globals::g_cSlave->is_connected() )
		{
	#ifndef REQUIRE_SLAVE_CONTROLLER
			fc_log( logTypes::Warning, false, true, __func__, "Slave controller not detected.\n" );
	#else
			fc_log( logTypes::ERROR, false, true, __func__, "Slave controller not detected.\n" );
			fc_log( logTypes::ERROR, false, false, __func__, "Please sync the Slave controller.\n" );
	#endif
		}
	}

	void fc_shutdown()
	{
		pros::lcd::clear();
		//pros::screen::erase();

		fc_log( logTypes::Info, false, false, __func__, "Thank you for using " libname "\n" );
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
		xfc::fc_log( xfc::logTypes::Info, false, false, __func__, "XFC is currently disabled." );
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

	pros::lcd::set_text( xfc::fc_logProperties::m_iCurrLine + 1, loadingText.c_str() );
	//pros::screen::print( pros::text_format_e_t::E_TEXT_MEDIUM, xfc::fc_logProperties::m_iCurrLine + 1, loadingText.c_str() );
	pros::delay( 625 );
}

void llemu_switch_matchtype()
{
	//if ( xfc::globals::g_llemu_options_lockedin )
	//	return;

	xfc::globals::g_bIsSkillsMatch = !xfc::globals::g_bIsSkillsMatch;

	std::string matchType = "Match Type: ";

	if ( !xfc::globals::g_bIsSkillsMatch )
		matchType += "NORMAL";
	else
		matchType += "SKILLS";

	pros::lcd::set_text( 4, matchType );
	printf( matchType.c_str() );
}

void llemu_switch_auton()
{
	//if ( xfc::globals::g_llemu_options_lockedin )
	//	return;

	xfc::globals::g_bAutonEnabled = !xfc::globals::g_bAutonEnabled;
	
	std::string autonStatus = "Auton Status: ";
		
	if ( xfc::globals::g_bAutonEnabled )
		autonStatus += "ENABLED";
	else
		autonStatus += "DUMMY";

	pros::lcd::set_text( 5, autonStatus );
	printf( autonStatus.c_str() );
}

void llemu_switch_side()
{
	//if ( xfc::globals::g_llemu_options_lockedin )
	//	return;

	xfc::globals::g_bIsOnLeft = !xfc::globals::g_bIsOnLeft;

	std::string sideOfField = "Side of Field: ";
		
	if ( xfc::globals::g_bIsOnLeft )
		sideOfField += "LEFT";
	else
		sideOfField += "RIGHT";

	pros::lcd::set_text( 3, sideOfField );
	printf( sideOfField.c_str() );
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize()
{
	pros::lcd::register_btn0_cb( llemu_switch_side );
	pros::lcd::register_btn1_cb( llemu_switch_auton );
	pros::lcd::register_btn2_cb( llemu_switch_matchtype );

	pros::lcd::set_text( 3, "Side of Field: LEFT" );
	pros::lcd::set_text( 4, "Match Type: NORMAL" );
	pros::lcd::set_text( 5, "Auton Status: ENABLED" );
}

void auton_dummy()
{
	xfc::globals::g_mgLeft.move( 64 );
	xfc::globals::g_mgRight.move( 64 );
	pros::delay( 250 );
	xfc::globals::g_mgLeft.brake();
	xfc::globals::g_mgRight.brake();

	while ( true ) { pros::delay( 20 ); }
}

void auton_skills()
{

	while ( true ) { pros::delay( 20 ); }
}

void auton_left()
{

	while ( true ) { pros::delay( 20 ); }
}

void auton_right()
{

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
	{
		auton_dummy();
	}
	else if ( xfc::globals::g_bIsSkillsMatch )
	{
		auton_skills();
	}
	else
	{
		if ( xfc::globals::g_bIsOnLeft )
			auton_left();
		else
			auton_right();
	}
}