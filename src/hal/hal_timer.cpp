#include "../grbl.h"

static hw_timer_t* timer = nullptr;
static timer_callback_t user_callback = nullptr;

// Interrupción del timer
void IRAM_ATTR onTimer() {
    if (user_callback) user_callback();
}

// Inicializa el timer
void hal_timer_init() {
    // 1,000,000 Hz = 1MHz, lo que nos da ticks de 1 microsegundo (µs).
    timer = timerBegin(1000000); 
    timerAttachInterrupt(timer, &onTimer);
}

// Inicia el timer con intervalo en microsegundos
void hal_timer_start(uint32_t interval_us) {
    timerAlarm(timer, interval_us, true, 0);
    timerStart(timer);
}

// Detiene el timer
void hal_timer_stop() {
    if (timer) {
        timerStop(timer);
    }
}

// Adjunta función de callback que se llama en cada tick
void hal_timer_attach_callback(timer_callback_t cb) {
    user_callback = cb;
}