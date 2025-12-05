#include "main.h"

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize()
{
	//lv_init();
	pros::lcd::initialize();

	//xfc::globals::scr = lv_obj_create( NULL );
	//lv_screen_load( xfc::globals::scr );

	//xfc::globals::win = lv_win_create( lv_screen_active() );

    //xfc::fc_log_init();

	xfc::fc_initInput();

	//xfc::fc_log( xfc::logTypes::Info, true, false, __func__, "Testerooni" );

	//pros::lcd::register_btn1_cb( on_center_button );

	//xfc::fc_startup();
}

/// @brief Runs destruction/deinitialization code. Cleans up variables.
void destruct()
{
	xfc::fc_shutdown();

	xfc::fc_deinitInput();

	xfc::fc_log_deinit();
	pros::lcd::shutdown();
}