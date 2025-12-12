#include "main.h"

namespace xfc
{
	void fc_vis_init()
	{
		globals::g_tTabber = lv_tabview_create( lv_scr_act(), LV_DIR_TOP, 10 );
		globals::g_tTabBtns = lv_tabview_get_tab_btns( globals::g_tTabber );

		lv_obj_set_style_bg_color( globals::g_tTabBtns, lv_palette_darken( LV_PALETTE_GREY, 3 ), 0 );
    	lv_obj_set_style_text_color( globals::g_tTabBtns, lv_palette_lighten( LV_PALETTE_GREY, 5 ), 0 );
		lv_obj_set_size( globals::g_tTabBtns, 200, 25 );

		globals::g_tTabMain = lv_tabview_add_tab( globals::g_tTabber, "Main" );
		globals::g_tTabCon = lv_tabview_add_tab( globals::g_tTabber, "Console" );

		lv_obj_align( globals::g_tTabBtns, LV_ALIGN_TOP_RIGHT, 0, 0 );

		lv_obj_clear_flag( lv_tabview_get_content( globals::g_tTabber ), LV_OBJ_FLAG_SCROLLABLE );
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize()
{
	//lv_init();
	//pros::lcd::initialize();

	//xfc::globals::scr = lv_obj_create( NULL );
	//lv_screen_load( xfc::globals::scr );

	//xfc::globals::win = lv_win_create( lv_screen_active() );

	pros::Task batteryLoop( xfc::fc_batteryLoop );

	xfc::fc_vis_init();

    xfc::fc_log_init();

	xfc::fc_initInput();

	//xfc::fc_log( xfc::logTypes::Info, true, false, __func__, "Testerooni" );

	//pros::lcd::register_btn1_cb( on_center_button );

	xfc::fc_startup();
}

/// @brief Runs destruction/deinitialization code. Cleans up variables.
void destruct()
{
	xfc::fc_shutdown();

	xfc::fc_deinitInput();

	xfc::fc_log_deinit();
	pros::lcd::shutdown();
}

void llemu_switch_matchtype()
{
	//if ( xfc::globals::g_llemu_options_lockedin )
	//	return;

	xfc::globals::g_bIsSkillsMatch = !xfc::globals::g_bIsSkillsMatch;

	std::string matchType = "Match Type: ";

	if ( !xfc::globals::g_bIsSkillsMatch )
		matchType += "NORMAL";
	else
	{
		matchType += "SKILLS";
		pros::lcd::clear_line( 3 );
	}

	pros::lcd::set_text( 4, matchType );
	printf( matchType.c_str() );
}

void llemu_switch_auton()
{
	//if ( xfc::globals::g_llemu_options_lockedin )
	//	return;

	xfc::globals::g_bAutonEnabled = !xfc::globals::g_bAutonEnabled;
	
	std::string autonStatus = "Auton Status: ";
		
	if ( xfc::globals::g_bAutonEnabled )
		autonStatus += "ENABLED";
	else
		autonStatus += "DUMMY";

	pros::lcd::set_text( 5, autonStatus );
	printf( autonStatus.c_str() );
}

void llemu_switch_side()
{
	//if ( xfc::globals::g_llemu_options_lockedin )
	//	return;

	if ( xfc::globals::g_bIsSkillsMatch )
		return;

	xfc::globals::g_bIsOnLeft = !xfc::globals::g_bIsOnLeft;

	std::string sideOfField = "Side of Field: ";
		
	if ( xfc::globals::g_bIsOnLeft )
		sideOfField += "LEFT";
	else
		sideOfField += "RIGHT";

	pros::lcd::set_text( 3, sideOfField );
	printf( sideOfField.c_str() );
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize()
{
	xfc::globals::g_bIsCompetitionMatch = true;

	/*pros::lcd::register_btn0_cb( llemu_switch_side );
	pros::lcd::register_btn1_cb( llemu_switch_auton );
	pros::lcd::register_btn2_cb( llemu_switch_matchtype );

	pros::lcd::set_text( 3, "Side of Field: LEFT" );
	pros::lcd::set_text( 4, "Match Type: NORMAL" );
	pros::lcd::set_text( 5, "Auton Status: ENABLED" );*/
}