#ifndef _HAL_PINS_H
#define _HAL_PINS_H

#include "../grbl.h"

// Ejes disponibles
#define AXIS_X 0
#define AXIS_Y 1
#define AXIS_Z 2

// Pines de STEP/DIR/ENABLE para cada eje (Realizada pora ESP32)
#define X_STEP_PIN   2
#define X_DIR_PIN    15
#define X_ENABLE_PIN 21
#define Y_STEP_PIN   4
#define Y_DIR_PIN    16
#define Y_ENABLE_PIN 22
#define Z_STEP_PIN   17
#define Z_DIR_PIN    5
#define Z_ENABLE_PIN 23

void hal_pins_init();
void hal_set_dir(uint8_t axis, bool dir);
void hal_step(uint8_t axis);
void hal_enable_motor(uint8_t axis, bool enable);
bool hal_get_dir_state(uint8_t axis);

#endif
