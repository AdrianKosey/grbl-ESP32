#include "../grbl.h"

static float parse_float(const char* str, int* index) {
    char buffer[16];
    int i = 0;
    while (isdigit(str[*index]) || str[*index] == '.' || str[*index] == '-' || str[*index] == '+') {
        if (i < 15)
            buffer[i++] = str[*index];
        (*index)++;
    }
    buffer[i] = '\0';
    return atof(buffer);
}

bool gcode_parse(const char* line, gcode_t* out_cmd) {
    if (!line || !out_cmd) return false;

    memset(out_cmd, 0, sizeof(gcode_t));

    int i = 0;
    while (line[i] != '\0') {
        char c = toupper(line[i]);

        if (c == ' ' || c == '\t') { i++; continue; }

        if (c == '(') { // comentario tipo ( ... )
            while (line[i] && line[i] != ')') i++;
            if (line[i] == ')') i++;
            continue;
        }

        if (c == ';') break; // comentario tipo ';'

        i++; // avanzar al número o valor
        float value = parse_float(line, &i);

        switch (c) {
            case 'G':
            case 'M':
                out_cmd->command_letter = c;
                out_cmd->command_number = (uint16_t)value;
                break;

            case 'X': out_cmd->x = value; out_cmd->has_x = true; break; // Coordenada x
            case 'Y': out_cmd->y = value; out_cmd->has_y = true; break; // Coordenada y 
            case 'Z': out_cmd->z = value; out_cmd->has_z = true; break; // Coordenada z
            case 'F': out_cmd->f = value; out_cmd->has_f = true; break; // Feedrate (Velocidad de avance del movimiento lineal)
            case 'S': out_cmd->s = value; out_cmd->has_s = true; break; // Spindle speed
            case 'T': out_cmd->t = value; out_cmd->has_t = true; break; // Tool number
            case 'P': out_cmd->p = value; out_cmd->has_p = true; break; // Dwell time (Pausas)
            case 'R': out_cmd->r = value; out_cmd->has_r = true; break; // Radio
            case 'I': out_cmd->i = value; out_cmd->has_i = true; break; // Desplazamiento X del centro del arco
            case 'J': out_cmd->j = value; out_cmd->has_j = true; break; // Desplazamiento Y del centro del arco
            case 'K': out_cmd->k = value; out_cmd->has_k = true; break; // Desplazamiento Z del centro del arco

            default:
                // caracter no reconocido
                break;
        }
    }

    return (out_cmd->command_letter != 0);
}
