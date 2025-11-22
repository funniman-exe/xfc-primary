#include "vex.h"

using namespace vex;

#include "fc_auton.h"

#include "fc_instances.h"
#include "fc_log.h"

//#include "../data/peetah.h"

void fc_autonomous() 
{
    fc_log( logTypes::Info, true, false, __func__, "Begin Autonomous\n" );

//    g_brain.Screen.clearScreen();
//	g_brain.Screen.drawImageFromBuffer( peetah_png, 0, 0, peetah_png_len );

//    g_fcOdometry->startThread( 10 );
    g_fcDrivetrain->driveFor( 65 + 20, fwd, distanceUnits::cm, true );
    //g_fcDrivetrain->driveFor( 45, fwd, distanceUnits::cm, true );
    g_fcDrivetrain->stop();
    wait( 500, msec );
    g_fcDrivetrain->turnFor( 22.5, left, deg, true );
    //g_fcDrivetrain->turnFor( 22.5, right, deg, true );
    g_fcDrivetrain->stop();
    wait( 500, msec );
    g_fcIntake->spin( fwd );
    wait( 500, msec );
    g_fcDrivetrain->driveFor( 43 + 20, fwd, distanceUnits::cm, true );
    g_fcDrivetrain->stop();
    wait( 500, msec );
    g_fcDrivetrain->turnFor( 112.5, left, deg, true );
    //g_fcDrivetrain->turnFor( 112.5, right, deg, true );
    g_fcDrivetrain->stop();
    wait( 500, msec );
    g_fcDrivetrain->driveFor( 96 + 20, fwd, distanceUnits::cm, true );
    g_fcDrivetrain->stop();
    wait( 500, msec );
    g_fcDrivetrain->turnFor( 45, left, deg, true );
    //g_fcDrivetrain->turnFor( 45, right, deg, true );
    g_fcDrivetrain->stop();
    wait( 500, msec );
    g_fcDrivetrain->driveFor( 36, reverse, distanceUnits::cm, true );
    g_fcDrivetrain->stop();
    wait( 500, msec );
    g_fcOutput->spinFor( 5, fwd, rev, true );
    g_fcIntake->stop();
}