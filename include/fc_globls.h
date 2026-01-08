#pragma once

#include "__use_lemlib.h"

#define libname "XFC [PROS]"
#define shortlibname "XFC"
#define botname "Jumbo"
#define gamename "Pushback"

#define scr_width 480
#define scr_height 240
#define scr_height_full ( scr_height + 32 )

namespace xfc
{
    namespace globals
    {
        // UI Stuff
        extern lv_obj_t *g_tTabber; // LVGL Tabber
        extern lv_obj_t *g_tTabBtns; // LVGL Tabber (Buttons)

        extern lv_obj_t *g_tTabMain; // LVGL Main Tab
        extern lv_obj_t *g_tTabCon; // LVGL Console Tab

        // Match config options
        extern int g_bIsSkillsMatch;
        extern int g_bIsOnLeft;
        extern bool g_bAutonEnabled;

        extern bool g_bIsCompetitionMatch;

        // Controllers
        extern pros::Controller *g_cMaster; // Master Controller
        extern pros::Controller *g_cSlave; // Slave Controller (no use as of yet)

        // Motors
        extern pros::MotorGroup g_mgLeft; // Drivetrain Left Motorgroup
        extern pros::MotorGroup g_mgRight; // Drivetrain Right Motorgroup

        extern pros::MotorGroup g_mgGantry; // Gantry Motorgroup

        //extern pros::MotorGroup g_mgOutput; // Output Motorgroup
        extern pros::Motor g_mOutput; // Output Motor

        // Digital IO
        extern pros::adi::DigitalOut g_pParking; // Parking Pneumatics
        extern pros::adi::DigitalOut g_pMatchload; // Matchload Pneumatics

        extern pros::adi::Button g_sParkingSwitchA; // Parking Switch A
        extern pros::adi::Button g_sParkingSwitchB; // Parking Switch B

        extern pros::adi::DigitalOut g_pDeload; // Deload Pneumatics

#ifdef __XFC_USE_LEMLIB
        // LemLib Stuff
        extern lemlib::Drivetrain g_dDrivetrain; // Drivetrain

        extern pros::Imu g_iImu; // PID IMU 
        extern pros::Rotation g_eHoriz; // PID Horizontal Rotation Sensor
        extern pros::Rotation g_eVert; // PID Vertical Rotation Sensory

        extern lemlib::TrackingWheel g_tHorizTrackingWheel; // PID Horizontal Tracking Wheel
        extern lemlib::TrackingWheel g_tVertTrackingWheel; // PID Vertical Tracking Wheel

        extern lemlib::OdomSensors g_sSensors; // PID Odom Sensors

        extern lemlib::ControllerSettings g_pidConLateral; // PID Controller (Lateral)
        extern lemlib::ControllerSettings g_pidConAngular; // PID Controller (Angular)

        extern lemlib::Chassis g_cChassis; // Chassis
#endif
    }
}