#include "__use_lemlib.h"

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
        pros::MotorGroup g_mgLeft( { -19, -20 }, pros::MotorGearset::green );
        pros::MotorGroup g_mgRight( { 16, 17 }, pros::MotorGearset::green );

        pros::MotorGroup g_mgGantry( { 2, -18 }, pros::MotorGearset::blue );

        //pros::MotorGroup g_mgOutput( { 15, 3 }, pros::MotorGearset::blue );
        pros::Motor g_mOutput( 15, pros::MotorGearset::blue );

        // Digital IO
        pros::adi::DigitalOut g_pParking = pros::adi::DigitalOut( 1, false );
        pros::adi::DigitalOut g_pMatchload = pros::adi::DigitalOut( 2, false );

        pros::adi::Button g_sParkingSwitchA = pros::adi::Button( 3 );
        pros::adi::Button g_sParkingSwitchB = pros::adi::Button( 4 );

        pros::adi::DigitalOut g_pDeload = pros::adi::DigitalOut( 5, false );

#ifdef __XFC_USE_LEMLIB
        // LemLib Stuff
        lemlib::Drivetrain g_dDrivetrain( &g_mgLeft, &g_mgRight, 12.25, lemlib::Omniwheel::NEW_325, 360, 2 );

        pros::Imu g_iImu( 12 );
        pros::Rotation g_eHoriz( 13 );
        pros::Rotation g_eVert( 14 );

        lemlib::TrackingWheel g_tHorizTrackingWheel( &g_eHoriz, lemlib::Omniwheel::NEW_275, -2.5 );
        lemlib::TrackingWheel g_tVertTrackingWheel( &g_eVert, lemlib::Omniwheel::NEW_275, -2.5 );

        lemlib::OdomSensors g_sSensors( &g_tVertTrackingWheel, nullptr, &g_tHorizTrackingWheel, nullptr, &g_iImu );

        lemlib::ControllerSettings g_pidConLateral(10, // proportional gain (kP)
                                                    0, // integral gain (kI)
                                                    3, // derivative gain (kD)
                                                    3, // anti windup
                                                    1, // small error range, in inches
                                                    100, // small error range timeout, in milliseconds
                                                    3, // large error range, in inches
                                                    500, // large error range timeout, in milliseconds
                                                    20 // maximum acceleration (slew)
        );

        lemlib::ControllerSettings g_pidConAngular(2, // proportional gain (kP)
                                                    0, // integral gain (kI)
                                                    10, // derivative gain (kD)
                                                    3, // anti windup
                                                    1, // small error range, in degrees
                                                    100, // small error range timeout, in milliseconds
                                                    3, // large error range, in degrees
                                                    500, // large error range timeout, in milliseconds
                                                    0 // maximum acceleration (slew)
        );

        lemlib::Chassis g_cChassis( g_dDrivetrain, g_pidConLateral, g_pidConAngular, g_sSensors );
#endif
    }
}