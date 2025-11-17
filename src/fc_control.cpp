#include "vex.h"

using namespace vex;

#include "fc_control.h"
#include "fc_drivetrain.h"

#include "fc_instances.h"
#include "fc_log.h"

int32_t iPrevSpeed;
int32_t iPrevTurnSpeed;

bool isPistonExtended = false;

char intakeCurrent[4];
char outputCurrent[4];

void fc_updateControl()
{
    int32_t iSpeed = g_controller.Axis3.position();
    int32_t iTurnSpeed = g_controller.Axis1.position();

    if ( ( iSpeed != iPrevSpeed ) || ( iTurnSpeed != iPrevTurnSpeed ) )
    {
        /*if ( g_controller.ButtonL2.pressing() )
        {
            iSpeed = iSpeed / 2;
            iTurnSpeed = iTurnSpeed / 2;
            g_controller.rumble( ". " );
        }
        else
            g_controller.rumble( " " );*/

        g_fcDrivetrain->arcade( iSpeed, iTurnSpeed / 1.5 );
    }

    iPrevSpeed = iSpeed;
    iPrevTurnSpeed = iTurnSpeed;
}

void fc_checkIntakeStatus()
{
    if ( !g_controller.ButtonR1.pressing() && !g_controller.ButtonR2.pressing() )
        strcpy( intakeCurrent, "" );

    if ( strcmp( intakeCurrent, "fwd" ) == 0 )
        g_fcIntake->spin( directionType::fwd );
    else if ( strcmp( intakeCurrent, "rev" ) == 0 )
        g_fcIntake->spin( directionType::rev );
    else
        g_fcIntake->stop();
}

void fc_checkOutputStatus()
{
    if ( !g_controller.ButtonL1.pressing() && !g_controller.ButtonL2.pressing() )
        strcpy( outputCurrent, "" );

    if ( strcmp( outputCurrent, "fwd" ) == 0 )
        g_fcOutput->spin( directionType::fwd );
    else if ( strcmp( outputCurrent, "rev" ) == 0 )
        g_fcOutput->spin( directionType::rev );
    else
        g_fcOutput->stop();
}

void intakeFwdDepressed()
{
    strcpy( intakeCurrent, "fwd" );
    fc_checkIntakeStatus();
}

void intakeRevDepressed()
{
    strcpy( intakeCurrent, "rev" );
    fc_checkIntakeStatus();
}

void intakeReleased()
{
    fc_checkIntakeStatus();
}

void outputFwdDepressed()
{
    strcpy( outputCurrent, "fwd" );
    fc_checkOutputStatus();
}

void outputRevDepressed()
{
    strcpy( outputCurrent, "rev" );
    fc_checkOutputStatus();
}

void outputReleased()
{
    fc_checkOutputStatus();
}

/*void buttonL1Depressed()
{
    g_fcGantry->spin( directionType::fwd );
}

void buttonL1Released()
{
    g_fcGantry->stop();
}*/

void pneumaticsADepressed()
{
    isPistonExtended = !isPistonExtended;
    g_pneumatics->set( isPistonExtended );
    fc_log( logTypes::Debug, false, true, __func__, "piston toggled\n" );
}

void testAuton()
{
    g_competitionManager.test_auton();
}

void testUser()
{
    g_competitionManager.test_driver();
}

void fc_initControl()
{
    g_controller.ButtonL1.pressed( outputFwdDepressed );
    g_controller.ButtonL1.released( outputReleased );
    g_controller.ButtonL2.pressed( outputRevDepressed );
    g_controller.ButtonL2.released( outputReleased );

    g_controller.ButtonR1.pressed( intakeFwdDepressed );
    g_controller.ButtonR1.released( intakeReleased );
    g_controller.ButtonR2.pressed( intakeRevDepressed );
    g_controller.ButtonR2.released( intakeReleased );

    g_controller.ButtonA.pressed( pneumaticsADepressed );
    
    g_controller.ButtonX.pressed( testAuton );
    g_controller.ButtonY.pressed( testUser );

    strcpy( intakeCurrent, "" );
    strcpy( outputCurrent, "" );
}