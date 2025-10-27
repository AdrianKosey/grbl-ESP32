#ifndef _HAL_STEPPER_H
#define _HAL_STEPPER_H

#include "../grbl.h"

void hal_stepper_init();
void hal_stepper_loop();
void hal_stepper_start_next_move();

#endif
