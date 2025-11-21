#pragma once

#define MAX_MOTORS 8
#define PATHFILE_MAX_SIZE 65536

//extern motor *g_motorArray[MAX_MOTORS];
extern int g_totalMotors;

class fc_drivetrain
{
    private:
    motor m_motorLeftA = motor( PORT11, gearSetting::ratio36_1, true );
    motor m_motorLeftB = motor( PORT20, gearSetting::ratio36_1, true );
    motor m_motorRightA = motor( PORT1, gearSetting::ratio36_1, false );
    motor m_motorRightB = motor( PORT10, gearSetting::ratio36_1, false );

    motor_group m_motorsLeft = motor_group( m_motorLeftA, m_motorLeftB );
    motor_group m_motorsRight = motor_group( m_motorRightA, m_motorRightB );

    drivetrain m_drivetrain = drivetrain( m_motorsLeft, m_motorsRight, 3.25, 12, 8, inches, 14.5 );

    //bool disableUse = false;

    public:
    fc_drivetrain();

    void setSpeed( double velocity, velocityUnits units = velocityUnits::rpm );
    void setTurnSpeed( double velocity, velocityUnits units = velocityUnits::rpm );

    void drive( directionType direction = directionType::fwd );
    void driveFor( double distance, directionType direction = directionType::fwd, distanceUnits units = distanceUnits::cm, bool waitForFinish = false );

    void turn( turnType direction );
    void turnFor( double angle, turnType direction, rotationUnits units = rotationUnits::deg, bool waitForFinish = false );

    void arcade( double drivePower, double turnPower, percentUnits units = percentUnits::pct );

    void stop();
    void stop( brakeType mode );
};

/*class fc_gantry
{
    private:
    motor m_motorLeft = motor( PORT12, true );
    motor m_motorRight = motor( PORT13, false );

    motor_group m_gantryMotors = motor_group( m_motorLeft, m_motorRight );

    //bool disableUse = false;

    public:
    fc_gantry();

    void setSpeed( double velocity, velocityUnits units );

    void spin( directionType direction );
    void spinFor( double distance, directionType direction, rotationUnits units, bool waitForFinish );

    void stop();
    void stop( brakeType mode );
};*/

class fc_intake
{
    private:
    motor m_motorA = motor( PORT18, gearSetting::ratio36_1, false );
    motor m_motorB = motor( PORT17, gearSetting::ratio36_1, true );
    motor_group m_intakeMotors = motor_group( m_motorA, m_motorB );

    //bool disableUse = false;

    public:
    fc_intake();

    void setSpeed( double velocity, velocityUnits units );

    void spin( directionType direction );
    void spinFor( double distance, directionType direction, rotationUnits units, bool waitForFinish );

    void stop();
    void stop( brakeType mode );
};

class fc_output
{
    private:
    motor m_outputMotor = motor( PORT9, gearSetting::ratio36_1, false );

    //bool disableUse = false;

    public:
    fc_output();

    void setSpeed( double velocity, velocityUnits units );

    void spin( directionType direction );
    void spinFor( double distance, directionType direction, rotationUnits units, bool waitForFinish );

    void stop();
    void stop( brakeType mode );
};

class fc_parking
{
    private:
    motor m_parkingMotor = motor( PORT19, gearSetting::ratio36_1, true );

    //bool disableUse = false;

    public:
    fc_parking();

    void setSpeed( double velocity, velocityUnits units );

    double getPower( powerUnits power = powerUnits::watt );
    double getPosition( rotationUnits units = rotationUnits::raw );

    void spin( directionType direction );
    void spinFor( double distance, directionType direction, rotationUnits units, bool waitForFinish );

    void stop();
    void stop( brakeType mode );
};