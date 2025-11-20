#include "vex.h"

using namespace vex;

#include "fc_auton.h"
#include "fc_user.h"
#include "fc_drivetrain.h"
#include "fc_odometry.h"

#include "fc_instances.h"

// instances
competition g_competitionManager;
brain g_brain;
controller g_controller = controller( controllerType::primary );
fc_drivetrain *g_fcDrivetrain = nullptr;
// fc_gantry *g_fcGantry = nullptr;
fc_intake *g_fcIntake = nullptr;
fc_output *g_fcOutput = nullptr;
fc_parking *g_fcParking = nullptr;
pneumatics *g_pneumatics = nullptr;
fc_odometry *g_fcOdometry = nullptr;