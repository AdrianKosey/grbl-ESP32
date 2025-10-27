#ifndef GCODE_BUFFER_H
#define GCODE_BUFFER_H

#include "../grbl.h"

// Estructura del buffer circular
typedef struct {
    char lines[GCODE_BUFFER_SIZE][GCODE_LINE_MAX_LENGTH];
    uint8_t head;
    uint8_t tail;
    uint8_t count;
} gcode_buffer_t;

void gcode_buffer_init();
void gcode_push_raw(const char* line);
bool gcode_pop_raw(char* outLine);

#endif
