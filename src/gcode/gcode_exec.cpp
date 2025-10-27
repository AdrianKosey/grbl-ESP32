#include "../grbl.h"

static float current_position[3] = {0.0f, 0.0f, 0.0f};
// true = absolute ; false = relative
static bool absolute_mode = DEFAULT_MODE_ABS_REL;

void gcode_execute(const gcode_t *cmd)
{
    if (!cmd)
        return;
    plan_block_t block;
    switch (cmd->command_letter)
    {
    case 'G':
    {
        switch (cmd->command_number)
        {
        // -------------------------------
        // Comandos de movimiento G0 / G1
        // -------------------------------
        case 0: // G0: movimiento rapido
            Serial.println("[G0] Movimiento rapido");
            if (cmd->has_x)
                Serial.printf("  X: %.3f\n", cmd->x);
            if (cmd->has_y)
                Serial.printf("  Y: %.3f\n", cmd->y);
            if (cmd->has_z)
                Serial.printf("  Z: %.3f\n", cmd->z);

            block.feed_rate = (cmd->has_f) ? cmd->f : FEEDRATE_DEFAULT;
            block.rapid = true;
            block.is_arc = false;
            block.absolute = absolute_mode;

            // Calcular destino
            for (int i = 0; i < 3; i++)
                block.target[i] = current_position[i];
            if (cmd->has_x)
                block.target[0] = absolute_mode ? cmd->x : current_position[0] + cmd->x;
            if (cmd->has_y)
                block.target[1] = absolute_mode ? cmd->y : current_position[1] + cmd->y;
            if (cmd->has_z)
                block.target[2] = absolute_mode ? cmd->z : current_position[2] + cmd->z;

            // Guardar movimiento
            planner_push_block(block);
            // Actualizar posición actual
            memcpy(current_position, block.target, sizeof(current_position));
            Serial.printf("[SUCCESS] Movimiento agregado al planner G0\n");
            break;

        case 1: // G1: movimiento lineal
            Serial.println("[G1] Movimiento lineal");
            if (cmd->has_x)
                Serial.printf("  X: %.3f\n", cmd->x);
            if (cmd->has_y)
                Serial.printf("  Y: %.3f\n", cmd->y);
            if (cmd->has_z)
                Serial.printf("  Z: %.3f\n", cmd->z);
            if (cmd->has_f)
                Serial.printf("  F: %.3f\n", cmd->f);

            block.feed_rate = (cmd->has_f) ? cmd->f : FEEDRATE_DEFAULT;
            block.rapid = false;
            block.is_arc = false;
            block.absolute = absolute_mode;

            // Calcular destino
            for (int i = 0; i < 3; i++)
                block.target[i] = current_position[i];
            if (cmd->has_x)
                block.target[0] = absolute_mode ? cmd->x : current_position[0] + cmd->x;
            if (cmd->has_y)
                block.target[1] = absolute_mode ? cmd->y : current_position[1] + cmd->y;
            if (cmd->has_z)
                block.target[2] = absolute_mode ? cmd->z : current_position[2] + cmd->z;

            // Guardar movimiento
            planner_push_block(block);
            // Actualizar posición actual
            memcpy(current_position, block.target, sizeof(current_position));
            Serial.printf("[SUCCESS] Movimiento agregado al planner G1\n");
            break;

        // -------------------------------
        // Arcos G2 / G3
        // -------------------------------
        case 2:
        case 3:
            Serial.println("[G2/G3] Arco");
            plan_block_t block;
            block.feed_rate = (cmd->has_f) ? cmd->f : 1000.0f;
            block.rapid = false;
            block.is_arc = true;
            block.absolute = absolute_mode;
            block.i = cmd->i;
            block.j = cmd->j;
            block.k = cmd->k;
            block.radius = cmd->r;

            for (int i = 0; i < 3; i++) block.target[i] = current_position[i];
            if (cmd->has_x) block.target[0] = absolute_mode ? cmd->x : current_position[0] + cmd->x;
            if (cmd->has_y) block.target[1] = absolute_mode ? cmd->y : current_position[1] + cmd->y;
            if (cmd->has_z) block.target[2] = absolute_mode ? cmd->z : current_position[2] + cmd->z;

            memcpy(current_position, block.target, sizeof(current_position));

            Serial.printf("[SUCCESS] Arco agregado al planner\n");
            break;
        // -------------------------------
        // Pausa
        // -------------------------------
        case 4: // G4: pausa (dwell)
            Serial.printf("[G4] Esperar %.3f segundos\n", cmd->p);
            delay((int)(cmd->p * 1000));
            break;
        // -------------------------------
        // Modo absoluto o relativo
        // -------------------------------
        case 90:
            absolute_mode = true;
            Serial.printf("[G90] Absolute Mode\n");
            break;
        case 91:
            absolute_mode = false;
            Serial.printf("[G91] Relative Mode\n");
            break;
        default:
            Serial.printf("[WARN] Comando G%d no implementado\n", cmd->command_number);
            break;
        }
    }
    break;

    case 'M':
    {
        switch (cmd->command_number)
        {
        case 3:
            Serial.println("[M3] Spindle ON (sentido horario)\n");
            break;
        case 4:
            Serial.println("[M4] Spindle ON (sentido antihorario)\n");
            break;
        case 5:
            Serial.println("[M5] Spindle OFF\n");
            break;
        case 30:
            Serial.println("[M30] Fin del programa\n");
            break;
        default:
            Serial.printf("[WARN] Comando M%d no implementado\n", cmd->command_number);
            break;
        }
    }
    break;
    default:
        Serial.println("[ERROR] Tipo de comando desconocido\n");
        break;
    }
}
