#ifndef GCODE_H
#define GCODE_H

#include "../grbl.h"

// Estructura base de un comando G-code
typedef struct {
    uint8_t command_letter;  // 'G' o 'M'
    uint16_t command_number; // Ejemplo: 0, 1, 2, 3, 30, etc.
    
    // Parámetros comunes (coordenadas y otros)
    bool has_x;
    bool has_y;
    bool has_z;
    bool has_f;
    bool has_s;
    bool has_t;
    bool has_p;
    bool has_r;
    bool has_i;
    bool has_j;
    bool has_k;

    float x, y, z, f, s, t, p, r, i, j, k;
} gcode_t;

// Función principal del parser
bool gcode_parse(const char* line, gcode_t* out_cmd);

#endif
