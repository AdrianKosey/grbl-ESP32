#ifndef _HAL_TIMER_H
#define _HAL_TIMER_H

#include "../grbl.h"

typedef void (*timer_callback_t)();

void hal_timer_init();
void hal_timer_start(uint32_t interval_us);
void hal_timer_stop();
void hal_timer_attach_callback(timer_callback_t cb);

#endif