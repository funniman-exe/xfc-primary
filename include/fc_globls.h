#pragma once

#define libname "XFC [PROS]"
#define botname "Jumbo"
#define gamename "Pushback"

namespace xfc
{
    namespace globals
    {
        //extern lv_obj_t *scr; // LVGL Screen
        //extern lv_obj_t *win; // LVGL Window

        enum fieldSide
        {
            LEFT,
            RIGHT
        };

        enum matchType
        {
            NORMAL,
            SKILLS
        };

        extern int g_iMatchType;
        extern int g_iFieldSide;

        extern bool g_llemu_options_lockedin;

        // Controllers
        extern pros::Controller *g_cMaster; // Master Controller
        extern pros::Controller *g_cSlave; // Slave Controller (no use as of yet)

        // Motors
        extern pros::MotorGroup g_mgLeft; // Drivetrain Left Motorgroup
        extern pros::MotorGroup g_mgRight; // Drivetrain Right Motorgroup

        extern pros::MotorGroup g_mgGantry; // Gantry Motorgroup

        extern pros::MotorGroup g_mgOutput; // Output Motorgroup

        // Digital IO
        extern pros::adi::DigitalOut g_pParking; // Parking Pneumatics
        extern pros::adi::DigitalOut g_pMatchload; // Matchload Pneumatics

        extern pros::adi::Button g_sParkingSwitchA; // Parking Switch A
        extern pros::adi::Button g_sParkingSwitchB; // Parking Switch B

        extern pros::adi::DigitalOut g_pDeload; // Deload Pneumatics
    }
}