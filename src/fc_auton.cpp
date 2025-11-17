#include "vex.h"

using namespace vex;

#include "fc_auton.h"

#include "fc_instances.h"
#include "fc_log.h"

void fc_autonomous() 
{
    fc_log( logTypes::Info, true, false, __func__, "Begin Autonomous\n" );

//    g_fcOdometry->startThread( 10 );
    /*g_fcDrivetrain->driveFor( 22, fwd, inches, true );
    wait( 500, msec );
    g_fcDrivetrain->turnFor( 90, left, deg, true );
    wait( 500, msec );
    g_fcDrivetrain->driveFor( 42.5, fwd, inches, true ); 
    wait( 500, msec );
    g_fcDrivetrain->turnFor( 90, left, deg, true );
    wait( 500, msec );
    g_pneumatics->open();
    wait( 500, msec );
    g_fcDrivetrain->setSpeed( 666, rpm );
    g_fcDrivetrain->driveFor( 15.5, fwd, inches, true );
    wait( 500, msec );
    g_fcDrivetrain->setSpeed( 333, rpm );
    g_fcIntake->spinFor( 3, fwd, rev, true );
    wait( 500, msec );
    g_fcDrivetrain->driveFor( 20, reverse, inches, true );
    wait( 500, msec );*/
}