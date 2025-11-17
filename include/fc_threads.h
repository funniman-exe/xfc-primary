#pragma once

#include "fc_safe_thread.h"

extern void fc_initThreads();

// stores threads
extern fc_safe_thread *batteryCheck;
extern fc_safe_thread *odometryThread;