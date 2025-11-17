#pragma once

#include "fc_drivetrain.h"

struct fc_gains
{
    double kP = 0;
    double kI = 0;
    double kD = 0;
};

class fc_pid
{
    fc_gains m_gains;
    double m_windupRange = 0;
    bool m_signFlipReset = false;

    double m_prevTime = 0;
    double m_prevError = 0;
    double m_integral = 0;

    fc_pid();
    fc_pid( double p, double i, double d, double windupRange = 0, bool signFlipReset = false );
    fc_pid( fc_gains gains, double windupRange = 0, bool signFlipReset = false );

    fc_gains getGains();
    void setGains( double p, double i, double d );
    void setGains( fc_gains gains );

    /// @brief Updates PID Controller
    /// @param error The error of the current point
    /// @return The control signal
    double update( double error );

    void reset();

    void setSignFlipReset( bool shouldReset );
    bool getSignFlipReset();

    void setWindupRange( double range );
    double getWindupRange();
};

class fc_odometry
{
    public:
    /// @brief Sets up and starts the Odometry Thread
    /// @param timeout The delay time (in ms) between loops of the thread
    void startThread( uint32_t timeout );

    /// @brief Terminates and nulls the Odometry Thread
    void killThread();

    fc_odometry();
    fc_odometry( fc_drivetrain *drivetrain, fc_intake *intake, fc_output *output );
    ~fc_odometry();
};