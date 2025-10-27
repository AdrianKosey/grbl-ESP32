#include "src/grbl.h"

void setup() {
  serial_iface_init();
  gcode_init();
}

void loop() {
  serial_iface_poll(); // leer datos puerto serial
  // temporal
  if (gcode_available()) {
    GCode cmd = gcode_pop();
    Serial.printf("Comando recibido: %c%d -> X%.2f Y%.2f Z%.2f F%.2f\n",
                  cmd.cmd, cmd.code, cmd.x, cmd.y, cmd.z, cmd.f);
  }
  delay(10);
}
