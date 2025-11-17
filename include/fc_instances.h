#pragma once

#include "fc_auton.h"
#include "fc_user.h"
#include "fc_drivetrain.h"
#include "fc_odometry.h"

// instances
extern competition g_competitionManager;
extern brain g_brain;
extern controller g_controller;
extern fc_drivetrain *g_fcDrivetrain;
// extern fc_gantry *g_fcGantry;
extern fc_intake *g_fcIntake;
extern fc_output* g_fcOutput;
extern pneumatics *g_pneumatics;
extern fc_odometry *g_fcOdometry;