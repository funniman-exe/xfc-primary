
#include "pros.h"
#include "fc_globls.h"

namespace xfc
{
    namespace globals
    {
        // UI Stuff
        lv_obj_t *g_tTabber = nullptr;
        lv_obj_t *g_tTabBtns = nullptr;

        lv_obj_t *g_tTabMain = nullptr;
        lv_obj_t *g_tTabCon = nullptr;

        // Match config options
        int g_bIsSkillsMatch = false;
        int g_bIsOnLeft = true;
        bool g_bAutonEnabled = true;

        bool g_bIsCompetitionMatch = false;

        // Controllers
        pros::Controller *g_cMaster = nullptr;
        pros::Controller *g_cSlave = nullptr;

        // Motors -- negitive numbers denote reversed motors
        pros::MotorGroup g_mgLeft( { -19, -20 } );
        pros::MotorGroup g_mgRight( { 16, 17 } );

        pros::MotorGroup g_mgGantry( { 2, -18 } );

        pros::MotorGroup g_mgOutput( { 15, 3 } );

        // Digital IO
        pros::adi::DigitalOut g_pParking = pros::adi::DigitalOut( 1, false );
        pros::adi::DigitalOut g_pMatchload = pros::adi::DigitalOut( 2, false );

        pros::adi::Button g_sParkingSwitchA = pros::adi::Button( 3 );
        pros::adi::Button g_sParkingSwitchB = pros::adi::Button( 4 );

        pros::adi::DigitalOut g_pDeload = pros::adi::DigitalOut( 5, false );
    }
}