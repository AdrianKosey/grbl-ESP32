#include "gcode.h"
#include <vector>
#include <string>

static std::vector<GCode> queue;

void gcode_init() {
  queue.clear();
}

bool gcode_available() {
  return !queue.empty();
}

void gcode_push_raw(const char* line) {
  // parseo sencillo: separar por espacios, detectar G/M y parámetros
  // Implementar parser robusto (manejo de comentarios, números negativos, etc)
  GCode g; // parsear aquí
  // ... (parseo)
  queue.push_back(g);
}

GCode gcode_pop() {
  GCode g = queue.front();
  queue.erase(queue.begin());
  return g;
}
