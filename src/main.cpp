// --------------------------------------------------------- //
//            XFC ( eXtra Featured Comp-project )            //
// Designed for the Vex V5 Competition Season of 2025 - 2026 //
//              Written by funniman.exe (c) 2025             //
//                Lasted updated - 11/10/2025                //
// --------------------------------------------------------- //

#include "vex.h"

using namespace vex;

#include "fc_auton.h"
#include "fc_user.h"
#include "fc_drivetrain.h"
#include "fc_control.h"
#include "fc_threads.h"

#include "fc_instances.h"

#include "fc_log.h"

#define botname "Jumbo"
#define gamename "Pushback"

// standard initialization
void init()
{
    try
    {
        fc_log( logTypes::Debug, false, true, __func__, "Init\n" );

        g_fcDrivetrain = new fc_drivetrain();
        /*g_fcDrivetrain = new fc_drivetrain( PORT10, PORT20, PORT1, PORT11,
                                            gearSetting::ratio36_1,
                                            gearSetting::ratio36_1,
                                            gearSetting::ratio36_1,
                                            gearSetting::ratio36_1 );*/
        
        //g_fcGantry = new fc_gantry( PORT12, PORT13 );
        //g_fcGantry = new fc_gantry();
        //g_fcGantry->setSpeed( 110, velocityUnits::pct );

        g_fcIntake = new fc_intake();
        g_fcIntake->setSpeed( 70, velocityUnits::pct );

        g_fcOutput = new fc_output();
        g_fcOutput->setSpeed( 70, velocityUnits::pct );

        g_fcParking = new fc_parking();
        g_fcParking->setSpeed( 70, velocityUnits::pct );

        g_pneumatics = new pneumatics( g_brain.ThreeWirePort.A );
        g_pneumatics->close();

        g_fcOdometry = new fc_odometry( g_fcDrivetrain, g_fcIntake, g_fcOutput );

        // callback setup
        g_competitionManager.autonomous( fc_autonomous );
        g_competitionManager.drivercontrol( fc_user );

        // additional initializations
        fc_initThreads();

        fc_initControl();
    }
    catch( std::exception e )
    {
        fc_log( logTypes::FATAL, false, true, __func__, e.what() );
    }
}

// kill everything
void deinit()
{
    try
    {
        fc_log( logTypes::Debug, false, true, __func__, "Deinit\n" );

        delete g_fcOdometry;
        g_fcOdometry = nullptr;

        delete g_fcDrivetrain;
        g_fcDrivetrain = nullptr;

        //delete g_fcGantry;
        //g_fcGantry = nullptr;

        delete g_fcIntake;
        g_fcIntake = nullptr;

        delete g_fcOutput;
        g_fcOutput = nullptr;

        delete g_fcParking;
        g_fcParking = nullptr;

        delete g_pneumatics;
        g_pneumatics = nullptr;
    }
    catch( std::exception e )
    {
        fc_log( logTypes::FATAL, false, true, __func__, e.what() );
    }
}

int main()
{
    // clears debug log
    printf( "\033[2J\n" );
    g_brain.Screen.clearScreen();
    g_brain.Screen.setCursor( 1, 1 );

    fc_log( logTypes::Info, false, false, __func__, "Hewwo :3 I am " botname "!!!\n" );
    fc_log( logTypes::Info, false, false, __func__, "-- Welcome to XFC (configured for " gamename ") --\n" );
    fc_log( logTypes::Info, false, false, __func__, "  (c) 2025 funniman.exe\n" );
    fc_log( logTypes::Debug, false, true, __func__, "Begin Program\n" );

    if ( !g_controller.installed() )
    {
        fc_log( logTypes::ERROR, false, true, __func__, "Controller not detected.\n" );
        fc_log( logTypes::ERROR, false, false, __func__, "Please sync a controller dumbass.\n" );
    }

    //  while ( !g_controller.installed() );

    // init functions go here
    init();
    //g_fcDrivetrain.init();

    fc_log( logTypes::Debug, false, true, __func__, "entered main loop\n" );
    // Prevent main from exiting with an infinite loop.

//    g_competitionManager.test_driver();

    while ( true )
    {
        wait( 100, msec ); // Do nothing
    }
}

/*
22in forward
turn left 90 degrees
25in forward
turn left 90 degrees
bring down matchload
15.5in forward
intake in for 1 sec
20in backward
*/