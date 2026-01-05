#include "main.h"

namespace xfc
{
	int32_t prevDir = 0;
	int32_t prevTurn = 0;

	bool prevMatchload = false;	// prev matchload status
	bool prevDeload = false; // prev deload status
	bool prevParking = false; // prev parking status

	bool matchloadStatus = false; // current matchload status
	bool deloadStatus = false; // current deload status
	bool parkingStatus = false; // current parking status

	bool parkingPressed = false; // are both parking switches pressed?

	bool autoparkEnabled = false; // is autopark enabled?

	void fc_awaitAutopark()
	{
		if ( !xfc::globals::g_bIsSkillsMatch )
			pros::delay( 95000 ); // 95 Seconds
		else
			pros::delay( 50000 ); // 50 Seconds
		
		autoparkEnabled = true;

		while ( true )
		{
			globals::g_cMaster->rumble( "-" );
			pros::delay( 250 );
		}
	}

	/// @brief INTERNAL
	void fc_updateArcade()
	{
		// Arcade control scheme
		int32_t dir = globals::g_cMaster->get_analog( ANALOG_LEFT_Y );    // Gets amount forward/backward from left joystick
		int32_t turn = globals::g_cMaster->get_analog( ANALOG_RIGHT_X );  // Gets the turn left/right from right joystick

		if ( ( dir != prevDir ) || ( turn != prevTurn ) )
		{
			// Pre-LemLib
			//globals::g_mgLeft.move( dir + ( turn / 1.5 ) );                      // Sets left motor voltage
			//globals::g_mgRight.move( dir - ( turn / 1.5 ) );                     // Sets right motor voltage

			// Post-LemLib
			//globals::g_cChassis.arcade( dir, turn );

			prevDir = dir;
			prevTurn = turn;
		}
	}

	#define targetGantryVoltage 127
	#define targetOutputVoltage 127

	/// @brief INTERNAL
	void fc_updateIntake()
	{
		if ( !globals::g_cMaster->get_digital( pros::controller_digital_e_t::E_CONTROLLER_DIGITAL_R1 )
			&& !globals::g_cMaster->get_digital( pros::controller_digital_e_t::E_CONTROLLER_DIGITAL_R2 ) )
		{
			globals::g_mgGantry.brake();
		}

		if ( globals::g_cMaster->get_digital( pros::controller_digital_e_t::E_CONTROLLER_DIGITAL_R1 )
			&& !globals::g_cMaster->get_digital( pros::controller_digital_e_t::E_CONTROLLER_DIGITAL_R2 ) )
		{
			globals::g_mgGantry.move( targetGantryVoltage );
		}

		if ( !globals::g_cMaster->get_digital( pros::controller_digital_e_t::E_CONTROLLER_DIGITAL_R1 )
			&& globals::g_cMaster->get_digital( pros::controller_digital_e_t::E_CONTROLLER_DIGITAL_R2 ) )
		{
			globals::g_mgGantry.move( -targetGantryVoltage );
		}
	}

	/// @brief INTERNAL
	void fc_updateOutput()
	{
		if ( !globals::g_cMaster->get_digital( pros::controller_digital_e_t::E_CONTROLLER_DIGITAL_L1 )
			&& !globals::g_cMaster->get_digital( pros::controller_digital_e_t::E_CONTROLLER_DIGITAL_L2 ) )
		{
			globals::g_mgOutput.brake();
		}

		if ( globals::g_cMaster->get_digital( pros::controller_digital_e_t::E_CONTROLLER_DIGITAL_L1 )
			&& !globals::g_cMaster->get_digital( pros::controller_digital_e_t::E_CONTROLLER_DIGITAL_L2 ) )
		{
			globals::g_mgOutput.move( targetOutputVoltage );
		}

		if ( !globals::g_cMaster->get_digital( pros::controller_digital_e_t::E_CONTROLLER_DIGITAL_L1 )
			&& globals::g_cMaster->get_digital( pros::controller_digital_e_t::E_CONTROLLER_DIGITAL_L2 ) )
		{
			globals::g_mgOutput.move( -targetOutputVoltage );
		}
	}

	/// @brief INTERNAL
	void fc_updateSolenoids()
	{
		// Matchload
		bool currMatchload = globals::g_cMaster->get_digital( pros::controller_digital_e_t::E_CONTROLLER_DIGITAL_A );

		if ( currMatchload != prevMatchload )
		{
			if ( currMatchload )
			{
				matchloadStatus = !matchloadStatus;
				globals::g_pMatchload.set_value( matchloadStatus );
			}

			prevMatchload = currMatchload;
		}

		// Deload
		bool currDeload = globals::g_cMaster->get_digital( pros::controller_digital_e_t::E_CONTROLLER_DIGITAL_B );

		if ( currDeload != prevDeload )
		{
			if ( currDeload )
			{
				deloadStatus = !deloadStatus;
				globals::g_pDeload.set_value( deloadStatus );
			}

			prevDeload = currDeload;
		}

		// Parking
		bool currParking = globals::g_cMaster->get_digital( pros::controller_digital_e_t::E_CONTROLLER_DIGITAL_Y );

		if ( currParking != prevParking )
		{
			if ( currParking )
			{
				parkingStatus = !parkingStatus;
				globals::g_pParking.set_value( parkingStatus );
			}

			prevParking = currParking;
		}

		// purpose of parkingPressed:
		// to track when both parking switches are pressed so that
		// if autopark is manually overridden it doesn't immediately retrigger

		if ( globals::g_sParkingSwitchA.get_value()
			&& globals::g_sParkingSwitchB.get_value()
			&& autoparkEnabled && !parkingPressed )
		{
			parkingPressed = true;
			parkingStatus = true;
			globals::g_pParking.set_value( parkingStatus );
		}

		if ( !globals::g_sParkingSwitchA.get_value()
			|| !globals::g_sParkingSwitchB.get_value() )
		{
			parkingPressed = false;			
		}
	}

	/// @brief Controller update routine
	void fc_updateControls()
	{
		fc_updateArcade();
		fc_updateIntake();
		fc_updateOutput();
		fc_updateSolenoids();
	}

	/// @brief Input Manager Initialization
	void fc_initInput()
	{
		globals::g_cMaster = new pros::Controller( pros::E_CONTROLLER_MASTER );
		globals::g_cSlave = new pros::Controller( pros::E_CONTROLLER_PARTNER );

		globals::g_cMaster->clear();
        globals::g_cSlave->clear();

		globals::g_pMatchload.set_value( 0 );
		globals::g_pDeload.set_value( 0 );
		globals::g_pParking.set_value( 0 );
	}

	/// @brief Input Manager Destructor
	void fc_deinitInput()
	{
		delete globals::g_cMaster;
		delete globals::g_cSlave;

		globals::g_cMaster = NULL;
		globals::g_cSlave = NULL;
	}
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol()
{
	if ( xfc::globals::g_bIsCompetitionMatch ) pros::Task autopark( xfc::fc_awaitAutopark );

	while ( true )
	{
		while ( !xfc::globals::g_cMaster->is_connected() ) { pros::delay( 20 ); }

		/*pros::lcd::print( 0, "%d %d %d", ( pros::lcd::read_buttons() & LCD_BTN_LEFT ) >> 2,
		                 ( pros::lcd::read_buttons() & LCD_BTN_CENTER ) >> 1,
		                 ( pros::lcd::read_buttons() & LCD_BTN_RIGHT ) >> 0 );  // Prints status of the emulated screen LCDs
		*/

		xfc::fc_updateControls();
		pros::delay( 20 );
	}
}