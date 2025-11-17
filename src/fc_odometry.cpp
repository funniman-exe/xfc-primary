#include "vex.h"

using namespace vex;

#include "fc_odometry.h"
#include "fc_drivetrain.h"
#include "fc_log.h"

#include "fc_safe_thread.h"
#include "fc_threads.h"

#include "fc_instances.h"

#include <vector>

static fc_drivetrain *m_drivetrain = nullptr;
static fc_intake *m_intake = nullptr;
static fc_output *m_output = nullptr;

double time_toSecs( double timeMSECS )
{
    return timeMSECS / 1000;
}

double sgn( double val )
{
    if ( val > 0 ) return 1;
    if ( val < 0 ) return -1;
    return 0;
}

fc_pid::fc_pid() {}

fc_pid::fc_pid( double p, double i, double d, double windupRange /* = 0 */, bool signFlipReset /* = false */ )
{
    m_gains.kP = p;
    m_gains.kI = i;
    m_gains.kD = d;

    m_windupRange = windupRange;
    m_signFlipReset = signFlipReset;
}

fc_pid::fc_pid( fc_gains gains, double windupRange /* = 0 */, bool signFlipReset /* = false */ )
{
    m_gains = gains;
    m_windupRange = windupRange;
    m_signFlipReset = signFlipReset;
}

fc_gains fc_pid::getGains() { return m_gains; }

void fc_pid::setGains( double p, double i, double d ) { m_gains.kP = p; m_gains.kI = i; m_gains.kD = d; }

void fc_pid::setGains( fc_gains gains ) { m_gains = gains; }

double fc_pid::update( double error )
{
    const double now = g_brain.Timer.time( vex::timeUnits::msec );

    double deltaTime = ( m_prevTime == 0 ) ? 0 : now - m_prevTime;
    m_prevTime = now;

    const double derivative = ( deltaTime == 0 ) ? 0 : ( error - m_prevError ) / time_toSecs( deltaTime );
    m_prevError = error;

    m_integral += error * time_toSecs( deltaTime );

    // Sign Flip Reset -- If the sign of the error changes, reset integral to 0
    if ( sgn( error ) != sgn( m_prevError ) && m_signFlipReset ) m_integral = 0;

    // Anti-Windup Range -- Unless error is small enough, reset integral to 0
    if ( abs( error ) > m_windupRange && m_windupRange != 0 ) m_integral = 0;

    return error * m_gains.kP + m_integral * m_gains.kI + derivative * m_gains.kD;
}

void fc_pid::reset() { m_prevError = 0; m_integral = 0; }

void fc_pid::setSignFlipReset( bool shouldReset ) { m_signFlipReset = shouldReset; }

bool fc_pid::getSignFlipReset() { return m_signFlipReset; }

void fc_pid::setWindupRange( double range ) { m_windupRange = range; }

double fc_pid::getWindupRange() { return m_windupRange; }

void odomUpdateLoop( void* ___timeout )
{
    uint32_t timeout = ( uint32_t )___timeout;

//    m_trackingWheel1.resetPosition();
//    m_trackingWheel2.resetPosition();

//    while( g_competitionManager.PRE_AUTONOMOUS || !g_competitionManager.AUTONOMOUS )

//    while( g_competitionManager.AUTONOMOUS && !g_competitionManager.DRIVER_CONTROL )
    while( true )
    {
        

        wait( timeout, msec );
    }
}

void fc_odometry::startThread( uint32_t timeout )
{
    if ( odometryThread == nullptr )
        odometryThread = new fc_safe_thread( odomUpdateLoop, ( void* )timeout );
    else
        fc_log( logTypes::ERROR, false, true, __func__, "Odometry thread is already running!\n" );
}

void fc_odometry::killThread()
{
    if ( odometryThread != nullptr )
    {
        delete odometryThread;
        odometryThread = nullptr;
    }
    else
        fc_log( logTypes::ERROR, false, true, __func__, "Odometry thread is already NULL!\n" );
}

fc_odometry::fc_odometry() {}

fc_odometry::fc_odometry( fc_drivetrain *__drivetrain, fc_intake *__intake, fc_output *__output )
{
    m_drivetrain = __drivetrain;
    m_intake = __intake;
    m_output = __output;
}

fc_odometry::~fc_odometry()
{
    killThread();
    m_drivetrain = nullptr;
    m_intake = nullptr;
    m_output = nullptr;
}