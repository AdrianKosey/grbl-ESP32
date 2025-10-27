#ifndef _CONFIG.H
#define _CONFIG.H

#include "../grbl.h"

// Serial baud rate
// #define BAUD_RATE 9600
// #define BAUD_RATE 230400
#define BAUD_RATE 115200

// Gcode command buffer size
#define GCODE_BUFFER_SIZE 16      // Numero maximo de lineas pendientes
#define GCODE_LINE_MAX_LENGTH 100 // Longitud maxima por linea

// Planner buffer size
#define PLANNER_BUFFER_SIZE 16

// CNC default variables
#define FEEDRATE_DEFAULT 1000.0
#define DEFAULT_MODE_ABS_REL true
#define STEPS_PER_MM_X 8
#define STEPS_PER_MM_Y 10
#define STEPS_PER_MM_Z 200
#endif