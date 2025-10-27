#ifndef _PLANNER.H
#define _PLANNER.H

// Estructura que representa un movimiento planificado
typedef struct {
    float target[3];      // X, Y, Z destino en mm
    float feed_rate;      // Velocidad en mm/min
    bool is_arc;          // true si es G2/G3
    float i, j, k;        // Centro del arco
    float radius;         // Radio del arco
    bool absolute;        // true si es modo absoluto
    bool rapid;           // true si es G0
} plan_block_t;

void planner_init();
void planner_reset();
bool planner_buffer_full();
bool planner_buffer_empty();
void planner_push_block(const plan_block_t& block);
bool planner_get_next_block(plan_block_t& block_out);

#endif
