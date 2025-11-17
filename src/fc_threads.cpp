#include "vex.h"

using namespace vex;

#include "fc_safe_thread.h"
#include "fc_instances.h"
#include "fc_log.h"

// threads
fc_safe_thread *batteryCheck = nullptr;
fc_safe_thread *odometryThread = nullptr;

void thread_checkBattery()
{
    while ( true )
    {
        if ( g_brain.Battery.capacity() <= 10 )
            break;
    }
    
    g_controller.Screen.clearScreen();
    fc_log( logTypes::Warning, true, false, __func__, "Brain Battery Low!\n" );

    g_controller.rumble( ". .  " );

    while ( true )
    {
        if ( g_brain.Battery.capacity() <= 5 )
            break;
    }

    g_controller.Screen.clearScreen();
    fc_log( logTypes::Warning, true, false, __func__, "Brain Battery Critical!\n" );

    g_controller.rumble( ". " );
}

void fc_initThreads()
{
    batteryCheck = new fc_safe_thread( thread_checkBattery );
}