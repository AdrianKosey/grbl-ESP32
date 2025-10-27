#include "../grbl.h"

// Bloque activo
static plan_block_t current_block;
static bool block_active = false;

// Posición actual en pasos
static long position_steps[3] = {0,0,0};
// Diferencia de pasos por eje
static long delta_steps[3];
// Total de pasos del movimiento
static long total_steps = 0;
static long step_counter = 0;

// ------------------------------------
// Callback del timer que genera pasos
// ------------------------------------
static void IRAM_ATTR stepper_callback() {
    if (!block_active) return;

    for (int i = 0; i < 3; i++) {
        if (delta_steps[i] == 0) continue;
        long step_pos = (delta_steps[i] * step_counter) / total_steps;
        long prev_pos = (delta_steps[i] * (step_counter-1)) / total_steps;
        if (step_pos != prev_pos) hal_step(i); // genera pulso
    }

    step_counter++;
    if (step_counter >= total_steps) {
        block_active = false;
        hal_timer_stop(); // Detener timer hasta el siguiente bloque
    }
}

// ------------------------------------
// Inicialización
// ------------------------------------
void hal_stepper_init() {
    hal_pins_init();
    hal_timer_init();
    hal_timer_attach_callback(stepper_callback);

    Serial.println("HAL Stepper inicializado");
}

// ------------------------------------
// Convierte siguiente bloque en movimiento fisico
// ------------------------------------
void hal_stepper_start_next_move() {
    if (block_active || planner_buffer_empty()) return;
    if (!planner_get_next_block(current_block)) return;

    // Diferencia en mm
    float dx = current_block.target[0] - (position_steps[0] / STEPS_PER_MM_X);
    float dy = current_block.target[1] - (position_steps[1] / STEPS_PER_MM_Y);
    float dz = current_block.target[2] - (position_steps[2] / STEPS_PER_MM_Z);

    // Convertir a pasos
    delta_steps[0] = lround(dx * STEPS_PER_MM_X);
    delta_steps[1] = lround(dy * STEPS_PER_MM_Y);
    delta_steps[2] = lround(dz * STEPS_PER_MM_Z);

    // Direccion
    hal_set_dir(AXIS_X, delta_steps[0]>=0);
    hal_set_dir(AXIS_Y, delta_steps[1]>=0);
    hal_set_dir(AXIS_Z, delta_steps[2]>=0);

    // Absoluto para contar pasos
    delta_steps[0] = abs(delta_steps[0]);
    delta_steps[1] = abs(delta_steps[1]);
    delta_steps[2] = abs(delta_steps[2]);

    total_steps = max({delta_steps[0], delta_steps[1], delta_steps[2]});
    if (total_steps==0) return; // nada que mover
    step_counter = 0;
    block_active = true;

    // Actualizar posición en pasos al final del bloque
    position_steps[0] += (hal_get_dir_state(AXIS_X)? delta_steps[0] : -delta_steps[0]);
    position_steps[1] += (hal_get_dir_state(AXIS_Y)? delta_steps[1] : -delta_steps[1]);
    position_steps[2] += (hal_get_dir_state(AXIS_Z)? delta_steps[2] : -delta_steps[2]);

    // Calcular intervalo de timer segun feedrate
    float steps_per_sec = (current_block.feed_rate * STEPS_PER_MM_X) / 60.0f; // simplificado eje X
    uint32_t interval_us = (uint32_t)(1e6 / steps_per_sec);
    interval_us = max(interval_us, 50UL); // limitar intervalo minimo
    hal_timer_start(interval_us);

    Serial.println("HAL Stepper ejecutando bloque...");
}

// ------------------------------------
// Loop principal: llama al siguiente bloque si está libre
// ------------------------------------
void hal_stepper_loop() {
    if (!block_active) hal_stepper_start_next_move();
}
