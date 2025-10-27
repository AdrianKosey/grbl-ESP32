#include "src/grbl.h"

void setup()
{
  gcode_buffer_init(); // Inicializa buffer de G-code
  serial_iface_init(); // Inicializa comunicación USB/UART
  hal_stepper_init();  // Inicializa pines y timer del stepper
  planner_init();      // Inicializa buffer del planner
}

void loop()
{
  serial_iface_task(); // Recolecta líneas del USB/UART
  char line[GCODE_LINE_MAX_LENGTH];
  if (gcode_pop_raw(line))
  {
    gcode_t cmd;
    /*Serial.print("[EXEC] Procesando: ");
    Serial.println(line);*/
    if (gcode_parse(line, &cmd))
    {
      /*Serial.printf("[PARSED] %c%d", cmd.command_letter, cmd.command_number);
      if (cmd.has_x) Serial.printf(" X%.3f", cmd.x);
      if (cmd.has_y) Serial.printf(" Y%.3f", cmd.y);
      if (cmd.has_z) Serial.printf(" Z%.3f", cmd.z);
      if (cmd.has_f) Serial.printf(" F%.3f", cmd.f);
      Serial.println();*/
      gcode_execute(&cmd);
    }
    else
    {
      Serial.println("[ERROR] G-code inválido");
    }
  }
  // Ejecuta bloques pendientes del planner
  hal_stepper_loop(); // Se llama siempre, solo activa bloque si hay uno disponible
}
