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


#endif