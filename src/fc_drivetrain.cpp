#include "vex.h"

using namespace vex;

#include "fc_drivetrain.h"
#include "fc_log.h"

#include "fc_safe_thread.h"

#include "fc_instances.h"

#include <vector>

//motor *g_motorArray[MAX_MOTORS];

int g_totalMotors = 0;

//
// fc_drivetrain -- The main robot drivetrain
//

/*fc_drivetrain::fc_drivetrain( int32_t indexLeft1, int32_t indexLeft2,
                              int32_t indexRight1, int32_t indexRight2,
                              gearSetting ratioLeft1, gearSetting ratioLeft2,
                              gearSetting ratioRight1, gearSetting ratioRight2 )
{
    m_motorLeftA = motor( indexLeft1, ratioLeft1, true );
    m_motorLeftB = motor( indexLeft2, ratioLeft2, true );
    m_motorRightA = motor( indexRight1, ratioRight1, false );
    m_motorRightB = motor( indexRight2, ratioRight2, false );

    motor_group motorsLeftTemp = motor_group( m_motorLeftA, m_motorLeftB );
    motor_group motorsRightTemp = motor_group( m_motorRightA, m_motorRightB );

    m_motorsLeft = &motorsLeftTemp;
    m_motorsRight = &motorsRightTemp;

    drivetrain drivetrainTemp = drivetrain( *m_motorsLeft, *m_motorsRight );

    m_drivetrain = &drivetrainTemp;

    initMain();
}

fc_drivetrain::fc_drivetrain( int32_t indexLeft1, int32_t indexLeft2,
                              int32_t indexRight1, int32_t indexRight2 )
{
    m_motorLeftA = motor( indexLeft1, true );
    m_motorLeftB = motor( indexLeft2, true );
    m_motorRightA = motor( indexRight1, false );
    m_motorRightB = motor( indexRight2, false );

    motor_group motorsLeftTemp = motor_group( m_motorLeftA, m_motorLeftB );
    motor_group motorsRightTemp = motor_group( m_motorRightA, m_motorRightB );

    m_motorsLeft = &motorsLeftTemp;
    m_motorsRight = &motorsRightTemp;

    drivetrain drivetrainTemp = drivetrain( *m_motorsLeft, *m_motorsRight );

    m_drivetrain = &drivetrainTemp;

    initMain();
}*/

//void fc_drivetrain::initMain()
fc_drivetrain::fc_drivetrain()
{
    try
    {
        if ( g_totalMotors + 4 > MAX_MOTORS )
        {
            fc_log( logTypes::ERROR, false, true, __func__, "Too many Motors! (get rid of some)\n" );
            return;
        }

        int totalMotorsPrev = g_totalMotors;

        if ( m_motorLeftA.installed() )
            g_totalMotors++;

        if ( m_motorLeftB.installed() )
            g_totalMotors++;

        if ( m_motorRightA.installed() )
            g_totalMotors++;

        if ( m_motorRightB.installed() )
            g_totalMotors++;

        if ( totalMotorsPrev + 4 != g_totalMotors )
        {
            //disableUse = true;
            fc_log( logTypes::ERROR, false, true, __func__, "Missing Drivetrain motors! (paralized)\n" );
            //fc_log( logTypes::ERROR, false, false, true, __func__, "Drivetrain has been disabled. durrrrr" );
        }

        //m_drivetrain.setDriveVelocity( 333, velocityUnits::rpm );
        m_drivetrain.setDriveVelocity( 333, velocityUnits::rpm );
        m_drivetrain.setTurnVelocity( 333, velocityUnits::rpm );
        m_drivetrain.setStopping( brakeType::brake );
    }
    catch( std::exception e )
    {
        fc_log( logTypes::FATAL, false, true, __func__, e.what() );
    }
}

// pass-through functions

void fc_drivetrain::setSpeed( double velocity, velocityUnits units )
{
    //if ( !disableUse )
        m_drivetrain.setDriveVelocity( velocity, units );
}

void fc_drivetrain::setTurnSpeed( double velocity, velocityUnits units )
{
    //if ( !disableUse )
        m_drivetrain.setTurnVelocity( velocity, units );
}

void fc_drivetrain::drive( directionType direction )
{
    //if ( !disableUse )
        m_drivetrain.drive( direction );
}

void fc_drivetrain::driveFor( double distance, directionType direction, distanceUnits units, bool waitForFinish )
{
    //if ( !disableUse )
        m_drivetrain.driveFor( direction, distance, units, waitForFinish );
}

void fc_drivetrain::turn( turnType direction )
{
    //if ( !disableUse )
        m_drivetrain.turn( direction );
}

void fc_drivetrain::turnFor( double angle, turnType direction, rotationUnits units, bool waitForFinish )
{
    //if ( !disableUse )
        m_drivetrain.turnFor( direction, angle, units, waitForFinish );
}

void fc_drivetrain::arcade( double drivePower, double turnPower, percentUnits units )
{
    //if ( !disableUse )
        m_drivetrain.arcade( drivePower, turnPower, units );
}

void fc_drivetrain::stop()
{
    //if ( !disableUse )
        m_drivetrain.stop();
}

void fc_drivetrain::stop( brakeType mode )
{
    //if ( !disableUse )
        m_drivetrain.stop( mode );
}

//
// fc_gantry -- The gantry mechanism for storing and depositing the blocks
//

/*fc_gantry::fc_gantry( int32_t indexLeft, int32_t indexRight,
                gearSetting ratioLeft, gearSetting ratioRight )
{
    m_motorLeft = motor( indexLeft, ratioLeft, true );
    m_motorRight = motor( indexRight, ratioRight, false );

    *m_gantryMotors = motor_group( m_motorLeft, m_motorRight );

    initMain();
}

fc_gantry::fc_gantry( int32_t indexLeft, int32_t indexRight )
{
    m_motorLeft = motor( indexLeft, true );
    m_motorRight = motor( indexRight, false );

    *m_gantryMotors = motor_group( m_motorLeft, m_motorRight );

    initMain();
}*/

//void fc_gantry::initMain()
/*fc_gantry::fc_gantry()
{
    try
    {
        if ( g_totalMotors + 2 > MAX_MOTORS )
        {
            fc_log( logTypes::ERROR, false, true, true, __func__, "ERROR! Too many Motors!" );
            return;
        }
        
        int totalMotorsPrev = g_totalMotors;

        if ( m_motorLeft.installed() )
            g_totalMotors++;

        if ( m_motorRight.installed() )
            g_totalMotors++;

        if ( totalMotorsPrev + 2 != g_totalMotors )
        {
            disableUse = true;
            fc_log( logTypes::ERROR, false, true, true, __func__, "Missing Gantry motors!" );
            fc_log( logTypes::ERROR, false, false, true, __func__, "Block gantry has been disabled." );
        }

        m_gantryMotors.setVelocity( 50, velocityUnits::rpm );
    }
    catch( std::exception e )
    {
        fc_log( logTypes::FATAL, false, true, true, __func__, e.what() );
    }
}

void fc_gantry::setSpeed( double velocity, velocityUnits units )
{
    if ( !disableUse )
        m_gantryMotors.setVelocity( velocity, units );
}

void fc_gantry::spin( directionType direction )
{
    if ( !disableUse )
        m_gantryMotors.spin( direction );
}

void fc_gantry::spinFor( double distance, directionType direction, rotationUnits units, bool waitForFinish )
{
    if ( !disableUse )
        m_gantryMotors.spinFor( direction, distance, units, waitForFinish );
}

void fc_gantry::stop()
{
    if ( !disableUse )
        m_gantryMotors.stop();
}

void fc_gantry::stop( brakeType mode )
{
    if ( !disableUse )
        m_gantryMotors.stop( mode );
}*/

fc_intake::fc_intake()
{
    try
    {
        if ( g_totalMotors + 1 > MAX_MOTORS )
        {
            fc_log( logTypes::ERROR, false, true, __func__, "Too many Motors! E\n" );
            return;
        }
        
        int totalMotorsPrev = g_totalMotors;

        if ( m_motorA.installed() )
            g_totalMotors++;

        if ( m_motorB.installed() )
            g_totalMotors++;

        if ( totalMotorsPrev + 2 != g_totalMotors )
        {
            //disableUse = true;
            fc_log( logTypes::ERROR, false, true, __func__, "Missing Intake motors! you suck!\n" );
            //fc_log( logTypes::ERROR, false, false, true, __func__, "Intake system has been disabled. Durrrrrr" );
        }

        m_intakeMotors.setVelocity( 50, velocityUnits::rpm );
    }
    catch( std::exception e )
    {
        fc_log( logTypes::FATAL, false, true, __func__, e.what() );
    }
}

void fc_intake::setSpeed( double velocity, velocityUnits units )
{
    //if ( !disableUse )
        m_intakeMotors.setVelocity( velocity, units );
}

void fc_intake::spin( directionType direction )
{
    //if ( !disableUse )
        m_intakeMotors.spin( direction );
}

void fc_intake::spinFor( double distance, directionType direction, rotationUnits units, bool waitForFinish )
{
    //if ( !disableUse )
        m_intakeMotors.spinFor( direction, distance, units, waitForFinish );
}

void fc_intake::stop()
{
    //if ( !disableUse )
        m_intakeMotors.stop();
}

void fc_intake::stop( brakeType mode )
{
    //if ( !disableUse )
        m_intakeMotors.stop( mode );
}

fc_output::fc_output()
{
    try
    {
        if ( g_totalMotors + 1 > MAX_MOTORS )
        {
            fc_log( logTypes::ERROR, false, true, __func__, "Too many Motors! (remove some dumbshit)\n" );
            return;
        }
        
        int totalMotorsPrev = g_totalMotors;

        if ( m_outputMotor.installed() )
            g_totalMotors++;

        if ( totalMotorsPrev + 1 != g_totalMotors )
        {
            //disableUse = true;
            fc_log( logTypes::ERROR, false, true, __func__, "No Output motor! (Can't shit)\n" );
            //fc_log( logTypes::ERROR, false, false, true, __func__, "Output system has been disabled. Durrrr" );
        }

        m_outputMotor.setVelocity( 50, velocityUnits::rpm );
    }
    catch( std::exception e )
    {
        fc_log( logTypes::FATAL, false, true, __func__, e.what() );
    }
}

void fc_output::setSpeed( double velocity, velocityUnits units )
{
    //if ( !disableUse )
        m_outputMotor.setVelocity( velocity, units );
}

void fc_output::spin( directionType direction )
{
    //if ( !disableUse )
        m_outputMotor.spin( direction );
}

void fc_output::spinFor( double distance, directionType direction, rotationUnits units, bool waitForFinish )
{
    //if ( !disableUse )
        m_outputMotor.spinFor( direction, distance, units, waitForFinish );
}

void fc_output::stop()
{
    //if ( !disableUse )
        m_outputMotor.stop();
}

void fc_output::stop( brakeType mode )
{
    //if ( !disableUse )
        m_outputMotor.stop( mode );
}

fc_parking::fc_parking()
{
    try
    {
        if ( g_totalMotors + 1 > MAX_MOTORS )
        {
            fc_log( logTypes::ERROR, false, true, __func__, "Too many Motors! (remove some fucker)\n" );
            return;
        }
        
        int totalMotorsPrev = g_totalMotors;

        if ( m_parkingMotor.installed() )
            g_totalMotors++;

        if ( totalMotorsPrev + 1 != g_totalMotors )
        {
            //disableUse = true;
            fc_log( logTypes::ERROR, false, true, __func__, "No Output motor! (Can't shit)\n" );
            //fc_log( logTypes::ERROR, false, false, true, __func__, "Output system has been disabled. Durrrr" );
        }

        m_parkingMotor.setVelocity( 50, velocityUnits::rpm );
    }
    catch( std::exception e )
    {
        fc_log( logTypes::FATAL, false, true, __func__, e.what() );
    }
}

void fc_parking::setSpeed( double velocity, velocityUnits units )
{
    //if ( !disableUse )
        m_parkingMotor.setVelocity( velocity, units );
}

void fc_parking::spin( directionType direction )
{
    //if ( !disableUse )
        m_parkingMotor.spin( direction );
}

void fc_parking::spinFor( double distance, directionType direction, rotationUnits units, bool waitForFinish )
{
    //if ( !disableUse )
        m_parkingMotor.spinFor( direction, distance, units, waitForFinish );
}

void fc_parking::stop()
{
    //if ( !disableUse )
        m_parkingMotor.stop();
}

void fc_parking::stop( brakeType mode )
{
    //if ( !disableUse )
        m_parkingMotor.stop( mode );
}