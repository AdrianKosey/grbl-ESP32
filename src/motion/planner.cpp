#include "../grbl.h"

// Buffer circular
static plan_block_t plan_buffer[PLANNER_BUFFER_SIZE];
static uint8_t head = 0;
static uint8_t tail = 0;

// Inicializacion
void planner_init() {
    head = 0;
    tail = 0;
}

// Reinicia el buffer
void planner_reset() {
    head = 0;
    tail = 0;
}

// Verifica si el buffer está lleno
bool planner_buffer_full() {
    return ((head + 1) % PLANNER_BUFFER_SIZE) == tail;
}

// Verifica si el buffer está vacío
bool planner_buffer_empty() {
    return head == tail;
}

// Agrega un bloque al buffer
void planner_push_block(const plan_block_t& block) {
    if (planner_buffer_full()) return; // Descartar si esta lleno
    plan_buffer[head] = block;
    head = (head + 1) % PLANNER_BUFFER_SIZE;
}

// Obtiene el siguiente bloque para ejecutar
bool planner_get_next_block(plan_block_t& block_out) {
    if (planner_buffer_empty()) return false;
    block_out = plan_buffer[tail];
    tail = (tail + 1) % PLANNER_BUFFER_SIZE;
    return true;
}
