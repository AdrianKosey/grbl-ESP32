#include "../grbl.h"

void gcode_execute(const gcode_t* cmd) {
    if (!cmd) return;

    switch (cmd->command_letter) {
        case 'G': {
            switch (cmd->command_number) {
                case 0: // G0: movimiento rapido
                    Serial.println("[G0] Movimiento rapido");
                    if (cmd->has_x) Serial.printf("  X: %.3f\n", cmd->x);
                    if (cmd->has_y) Serial.printf("  Y: %.3f\n", cmd->y);
                    if (cmd->has_z) Serial.printf("  Z: %.3f\n", cmd->z);
                    break;

                case 1: // G1: movimiento lineal
                    Serial.println("[G1] Movimiento lineal");
                    if (cmd->has_x) Serial.printf("  X: %.3f\n", cmd->x);
                    if (cmd->has_y) Serial.printf("  Y: %.3f\n", cmd->y);
                    if (cmd->has_z) Serial.printf("  Z: %.3f\n", cmd->z);
                    if (cmd->has_f) Serial.printf("  F: %.3f\n", cmd->f);
                    break;

                case 4: // G4: pausa (dwell)
                    Serial.printf("[G4] Esperar %.3f segundos\n", cmd->p);
                    delay((int)(cmd->p * 1000));
                    break;

                default:
                    Serial.printf("[WARN] Comando G%d no implementado\n", cmd->command_number);
                    break;
            }
        } break;

        case 'M': {
            switch (cmd->command_number) {
                case 3: Serial.println("[M3] Spindle ON (sentido horario)"); break;
                case 4: Serial.println("[M4] Spindle ON (sentido antihorario)"); break;
                case 5: Serial.println("[M5] Spindle OFF"); break;
                case 30: Serial.println("[M30] Fin del programa"); break;
                default:
                    Serial.printf("[WARN] Comando M%d no implementado\n", cmd->command_number);
                    break;
            }
        } break;

        default:
            Serial.println("[ERROR] Tipo de comando desconocido");
            break;
    }
}
