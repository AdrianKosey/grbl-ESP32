#include "gcode_buffer.h"

static gcode_buffer_t gcode_buffer;

void gcode_buffer_init() {
    gcode_buffer.head = 0;
    gcode_buffer.tail = 0;
    gcode_buffer.count = 0;
}

void gcode_push_raw(const char* line) {
    if (!line || line[0] == '\0') return; // linea vacia

    if (gcode_buffer.count >= GCODE_BUFFER_SIZE) {
        Serial.println("[WARN] G-code buffer overflow, line discarded");
        return;
    }

    // Copiar la linea al buffer
    strncpy(gcode_buffer.lines[gcode_buffer.head], line, GCODE_LINE_MAX_LENGTH - 1);
    gcode_buffer.lines[gcode_buffer.head][GCODE_LINE_MAX_LENGTH - 1] = '\0';

    // Avanzar el indice circular
    gcode_buffer.head = (gcode_buffer.head + 1) % GCODE_BUFFER_SIZE;
    gcode_buffer.count++;
}

bool gcode_pop_raw(char* outLine) {
    if (gcode_buffer.count == 0) return false;

    strncpy(outLine, gcode_buffer.lines[gcode_buffer.tail], GCODE_LINE_MAX_LENGTH);
    gcode_buffer.tail = (gcode_buffer.tail + 1) % GCODE_BUFFER_SIZE;
    gcode_buffer.count--;

    return true;
}
