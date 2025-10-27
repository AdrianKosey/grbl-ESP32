#pragma once
#include <string>

struct GCode {
  char cmd; // 'G' o 'M' u otra
  int code; // número
  float x, y, z, f; // parámetros posibles
  bool hasX, hasY, hasZ, hasF;
  // agregar más según necesidades
};

void gcode_init();
bool gcode_available();
void gcode_push_raw(const char* line);
GCode gcode_pop();