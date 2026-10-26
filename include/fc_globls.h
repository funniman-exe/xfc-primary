#pragma once

#include "__use_lemlib.h"
#include "main.h"

#define libname "XFC [PROS]"
#define shortlibname "XFC"
#define botname "Anita Job"
#define gamename "Override"

#define scr_width 480
#define scr_height 240
#define scr_height_full ( scr_height + 32 )

#define MGLeft1Port 1
#define MGLeft2Port 2
#define MGLeft3Port 3

#define MGRight1Port 6
#define MGRight2Port 8
#define MGRight3Port 9

#define MGGantry1Port 13
#define MGGantry2Port 14

#define GantryTrackingPort 19

#define IMUPort 11

// NOT SET UP
#define HorizTrackingPort 13

#define VertTrackingPort 20

namespace xfc
{
    enum GAMESTATE
    {
        E_GAMESTATE_NULL = -1,
        E_GAMESTATE_DISABLED = 0,
        E_GAMESTATE_INIT,
        E_GAMESTATE_SHUTDOWN,
        E_GAMESTATE_COMPINIT,
        E_GAMESTATE_AUTON,
        E_GAMESTATE_DRIVER
    };

    namespace globals
    {
        extern int g_iGameState; // Gamestate (use GAMESTATE enum)

        // UI Stuff
        extern lv_obj_t *g_tTabber; // LVGL Tabber
        extern lv_obj_t *g_tTabBtns; // LVGL Tabber (Buttons)

        extern lv_obj_t *g_tTabMain; // LVGL Main Tab
        extern lv_obj_t *g_tTabCon; // LVGL Console Tab

        // Match config options
        extern bool g_bIsSkillsMatch;
        extern bool g_bIsOnLeft;
        extern bool g_bAutonEnabled;

        extern bool g_bIsCompetitionMatch;

        // Controllers
        extern pros::Controller *g_cMaster; // Master Controller
        extern pros::Controller *g_cSlave; // Slave Controller (no use as of yet)

        // Motors
        extern pros::MotorGroup g_mgLeft; // Drivetrain Left Motorgroup
        extern pros::MotorGroup g_mgRight; // Drivetrain Right Motorgroup

        extern pros::MotorGroup g_mgGantry; // Pin Gantry Motorgroup

        extern pros::Rotation g_eGantryMonitor; // Pin Gantry Rotation Sensor

#ifdef __XFC_USE_LEMLIB
        // LemLib Stuff
        extern lemlib::Drivetrain g_dDrivetrain; // Drivetrain

        extern pros::Imu g_iImu; // PID IMU 
        // extern pros::Rotation g_eHoriz; // PID Horizontal Rotation Sensor
        extern pros::Rotation g_eVert; // PID Vertical Rotation Sensor

        // extern lemlib::TrackingWheel g_tHorizTrackingWheel; // PID Horizontal Tracking Wheel
        extern lemlib::TrackingWheel g_tVertTrackingWheel; // PID Vertical Tracking Wheel

        extern lemlib::OdomSensors g_sSensors; // PID Odom Sensors

        extern lemlib::ControllerSettings g_pidConLateral; // PID Controller (Lateral)
        extern lemlib::ControllerSettings g_pidConAngular; // PID Controller (Angular)

        extern lemlib::Chassis g_cChassis; // Chassis
#endif
    }
}