#ifndef _GRBL_H
#define _GRBL_H

// Grbl versioning system
#define GRBL_VERSION "1.0"

// Define standard libraries used by Grbl.

// Define the Grbl system include files.
#include "platform_config.h"
#include "hal/hal_pins.h"
#include "io/serial_iface.h"
#include "parser/gcode.h"
#include "motion/planner.h"
#include "hal/hal_stepper.h"
#include "safety/estop.h"

#endif