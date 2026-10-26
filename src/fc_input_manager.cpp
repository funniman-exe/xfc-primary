#include "fc_globls.h"
#include "main.h"
#include "pros/motors.h"
#include <cstdint>

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
		int32_t dir = globals::g_cMaster->get_analog( ANALOG_LEFT_Y );		// Gets amount forward/backward from left joystick
		int32_t turn = globals::g_cMaster->get_analog( ANALOG_RIGHT_X );	// Gets the turn left/right from right joystick

		if ( ( dir != prevDir ) || ( turn != prevTurn ) )
		{
#ifndef __XFC_USE_LEMLIB
			globals::g_mgLeft.move( dir + ( turn / 1.5 ) );					// Sets left motor voltage
			globals::g_mgRight.move( dir - ( turn / 1.5 ) );				// Sets right motor voltage
#else
			globals::g_cChassis.arcade( dir, turn );						// Arcade controls
#endif

			prevDir = dir;
			prevTurn = turn;
		}
	}

	#define targetGantryVoltage 96
	#define targetGantryVoltageDown 32

	#define gantryLowestDegrees 78
	#define gantryHighestDegrees 0

	/// @brief Formula to slow motor speed near the limit of the motor range
	/// @param maxVoltage uint8_t voltage to pass to motors (clamped to a range from 0 to 127)
	/// @param minVoltage uint8_t voltage to pass to motors (clamped to a range from 0 to 127)
	/// @param limitInitial degrees of encoder to begin enforcing speed decrease
	/// @param limitFinal degrees of encoder defining the absolute limit of the motor position
	/// @return adjusted motor voltage (clamped to a range from minVoltage to maxVoltage)
	double fc_gantryLimitFormula( uint8_t maxVoltage, uint8_t minVoltage, double limitInitial, double limitFinal )
	{
		// clamp voltages
		maxVoltage = std::max( static_cast<uint8_t>( 0 ), std::min( static_cast<uint8_t>( 127 ), maxVoltage ) );
		minVoltage = std::max( static_cast<uint8_t>( 0 ), std::min( static_cast<uint8_t>( 127 ), minVoltage ) );

		// angle returned by get_angle() is represented in centidegrees, we must convert it to standard degrees
		double angle = static_cast<double>( globals::g_eGantryMonitor.get_angle() ) / static_cast<double>( 100 );

		// the actual formula
		double result = ( limitFinal - angle ) / ( limitFinal - limitInitial );

		// converting the formula to voltage, and clamping the result
		return std::max( static_cast<double>( minVoltage ), static_cast<double>( maxVoltage ) * std::min( static_cast<double>( 1 ), result ) );
	}
	
	/// @brief INTERNAL
	void fc_updateGantry()
	{
		static int8_t lastMoveDir = 0;
		static double lastMovingAngle = 0;

		if ( !globals::g_cMaster->get_digital( pros::controller_digital_e_t::E_CONTROLLER_DIGITAL_R1 )
			&& !globals::g_cMaster->get_digital( pros::controller_digital_e_t::E_CONTROLLER_DIGITAL_R2 ) )
		{
			if ( lastMovingAngle == 0 )
				lastMovingAngle = static_cast<double>( globals::g_eGantryMonitor.get_angle() ) / static_cast<double>( 100 );

			double angle = static_cast<double>( globals::g_eGantryMonitor.get_angle() ) / static_cast<double>( 100 );

			if ( lastMoveDir > 0 )
			{
				if ( angle > 0 && lastMoveDir < 0 )
				{
					globals::g_mgGantry.set_brake_mode( pros::E_MOTOR_BRAKE_HOLD );
					globals::g_mgGantry.brake();
				}
				else if ( angle >= 19.4 && lastMoveDir <= 19.4 )
				{
					globals::g_mgGantry.set_brake_mode( pros::E_MOTOR_BRAKE_HOLD );
					globals::g_mgGantry.brake();
				}
				else if ( angle >= 33.75 && lastMoveDir <= 33.75 )
				{
					globals::g_mgGantry.set_brake_mode( pros::E_MOTOR_BRAKE_HOLD );
					globals::g_mgGantry.brake();
				}
				else if ( angle >= 48.4 && lastMoveDir <= 48.4 )
				{
					globals::g_mgGantry.set_brake_mode( pros::E_MOTOR_BRAKE_HOLD );
					globals::g_mgGantry.brake();
				}
				else if ( angle >= 60.8 && lastMoveDir <= 60.8 )
				{
					globals::g_mgGantry.set_brake_mode( pros::E_MOTOR_BRAKE_HOLD );
					globals::g_mgGantry.brake();
				}
				else if ( angle >= 73.2 && lastMoveDir <= 73.2 )
				{
					globals::g_mgGantry.set_brake_mode( pros::E_MOTOR_BRAKE_HOLD );
					globals::g_mgGantry.brake();
				}
			}
			else if ( lastMoveDir < 0 )
			{
				if ( angle < 73.2 && lastMoveDir > 73.2 )
				{
					globals::g_mgGantry.set_brake_mode( pros::E_MOTOR_BRAKE_HOLD );
					globals::g_mgGantry.brake();
				}
				else if ( angle <= 60.8 && lastMoveDir >= 60.8 )
				{
					globals::g_mgGantry.set_brake_mode( pros::E_MOTOR_BRAKE_HOLD );
					globals::g_mgGantry.brake();
				}
				else if ( angle <= 48.4 && lastMoveDir >= 48.4 )
				{
					globals::g_mgGantry.set_brake_mode( pros::E_MOTOR_BRAKE_HOLD );
					globals::g_mgGantry.brake();
				}
				else if ( angle <= 33.75 && lastMoveDir >= 33.75 )
				{
					globals::g_mgGantry.set_brake_mode( pros::E_MOTOR_BRAKE_HOLD );
					globals::g_mgGantry.brake();
				}
				else if ( angle <= 19.4 && lastMoveDir >= 19.4 )
				{
					globals::g_mgGantry.set_brake_mode( pros::E_MOTOR_BRAKE_HOLD );
					globals::g_mgGantry.brake();
				}
				else if ( angle <= 0 && lastMoveDir >= 0 )
				{
					globals::g_mgGantry.set_brake_mode( pros::E_MOTOR_BRAKE_HOLD );
					globals::g_mgGantry.brake();
				}
			}
		}

		if ( globals::g_cMaster->get_digital( pros::controller_digital_e_t::E_CONTROLLER_DIGITAL_R1 )
			&& !globals::g_cMaster->get_digital( pros::controller_digital_e_t::E_CONTROLLER_DIGITAL_R2 ) )
		{
			lastMoveDir = 1;
			lastMovingAngle = 0;

			if ( ( static_cast<double>( globals::g_eGantryMonitor.get_angle() ) / static_cast<double>( 100 ) ) < 80 )
			{
				// globals::g_mgGantry.set_brake_mode( pros::E_MOTOR_BRAKE_HOLD );
				globals::g_mgGantry.move( fc_gantryLimitFormula( targetGantryVoltage, 0, 55, gantryHighestDegrees ) );
			}
			else
			 {
				globals::g_mgGantry.set_brake_mode( pros::E_MOTOR_BRAKE_COAST );
				globals::g_mgGantry.brake();
			 }
		}

		if ( !globals::g_cMaster->get_digital( pros::controller_digital_e_t::E_CONTROLLER_DIGITAL_R1 )
			&& globals::g_cMaster->get_digital( pros::controller_digital_e_t::E_CONTROLLER_DIGITAL_R2 ) )
		{
			lastMoveDir = -1;
			lastMovingAngle = 0;

			if ( ( static_cast<double>( globals::g_eGantryMonitor.get_angle() ) / static_cast<double>( 100 ) ) < 40 )
			{
				globals::g_mgGantry.set_brake_mode( pros::E_MOTOR_BRAKE_COAST );
				globals::g_mgGantry.brake();
			}
			else
			{
				// globals::g_mgGantry.set_brake_mode( pros::E_MOTOR_BRAKE_HOLD );
				globals::g_mgGantry.move( 0 - ( fc_gantryLimitFormula( targetGantryVoltageDown, 0, 57, gantryLowestDegrees ) ) );
			}
		}

		std::cout << fc_gantryLimitFormula( targetGantryVoltage, 0, 40, gantryHighestDegrees ) << std::endl;
	}

	/// @brief INTERNAL
	void fc_updateOutput()
	{
		/*
		if ( !globals::g_cMaster->get_digital( pros::controller_digital_e_t::E_CONTROLLER_DIGITAL_L1 )
			&& !globals::g_cMaster->get_digital( pros::controller_digital_e_t::E_CONTROLLER_DIGITAL_L2 ) )
		{
			//globals::g_mgOutput.brake();
			globals::g_mOutput.brake();
		}

		if ( globals::g_cMaster->get_digital( pros::controller_digital_e_t::E_CONTROLLER_DIGITAL_L1 )
			&& !globals::g_cMaster->get_digital( pros::controller_digital_e_t::E_CONTROLLER_DIGITAL_L2 ) )
		{
			//globals::g_mgOutput.move( targetOutputVoltage );
			globals::g_mOutput.move( targetOutputVoltage );
		}

		if ( !globals::g_cMaster->get_digital( pros::controller_digital_e_t::E_CONTROLLER_DIGITAL_L1 )
			&& globals::g_cMaster->get_digital( pros::controller_digital_e_t::E_CONTROLLER_DIGITAL_L2 ) )
		{
			//globals::g_mgOutput.move( -targetOutputVoltage );
			globals::g_mOutput.move( -targetOutputVoltage );
		}
		*/
	}

	/// @brief INTERNAL
	void fc_updateSolenoids()
	{
		/*
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
		*/
	}

	/// @brief Controller update routine
	void fc_updateControls()
	{
		fc_updateArcade();
		fc_updateGantry();
		fc_updateOutput();
		fc_updateSolenoids();
	}

	/// @brief Input Manager Initialization
	void fc_initInput()
	{
		fc_log( logTypes::Debug, false, true, __func__, "Input library started initializing\n" );
		
		globals::g_cMaster = new pros::Controller( pros::E_CONTROLLER_MASTER );
		globals::g_cSlave = new pros::Controller( pros::E_CONTROLLER_PARTNER );

		globals::g_cMaster->clear();
        globals::g_cSlave->clear();

		globals::g_mgGantry.set_brake_mode( pros::E_MOTOR_BRAKE_COAST );

		//globals::g_pMatchload.set_value( 0 );
		//globals::g_pDeload.set_value( 0 );
		//globals::g_pParking.set_value( 0 );

		fc_log( logTypes::Debug, false, true, __func__, "Input library finished initializing\n" );
	}

	/// @brief Input Manager Destructor
	void fc_deinitInput()
	{
		delete globals::g_cMaster;
		delete globals::g_cSlave;

		globals::g_cMaster = NULL;
		globals::g_cSlave = NULL;
	}

	bool fc_checkSmartDeviceInstalled( uint8_t port )
	{
		pros::DeviceType tempType = pros::Device::get_plugged_type( port );

		return ( tempType != pros::DeviceType::none );
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
		if ( xfc::globals::g_cMaster->is_connected() )
			xfc::fc_updateControls();

		xfc::fc_updateMainScreen();
		pros::delay( 20 );
	}
}