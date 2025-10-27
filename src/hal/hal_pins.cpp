#include "hal_pins.h"

void hal_pins_init() {
    // Configurar todos los pines como salida
    pinMode(X_STEP_PIN, OUTPUT);
    pinMode(X_DIR_PIN, OUTPUT);
    pinMode(X_ENABLE_PIN, OUTPUT);
    pinMode(Y_STEP_PIN, OUTPUT);
    pinMode(Y_DIR_PIN, OUTPUT);
    pinMode(Y_ENABLE_PIN, OUTPUT);
    pinMode(Z_STEP_PIN, OUTPUT);
    pinMode(Z_DIR_PIN, OUTPUT);
    pinMode(Z_ENABLE_PIN, OUTPUT);

    // Deshabilitar motores inicialmente
    hal_enable_motor(AXIS_X, false);
    hal_enable_motor(AXIS_Y, false);
    hal_enable_motor(AXIS_Z, false);
}

void hal_set_dir(uint8_t axis, bool dir) {
    switch(axis) {
        case AXIS_X: digitalWrite(X_DIR_PIN, dir ? HIGH : LOW); break;
        case AXIS_Y: digitalWrite(Y_DIR_PIN, dir ? HIGH : LOW); break;
        case AXIS_Z: digitalWrite(Z_DIR_PIN, dir ? HIGH : LOW); break;
    }
}

void hal_step(uint8_t axis) {
    switch(axis) {
        case AXIS_X:
            digitalWrite(X_STEP_PIN, HIGH);
            delayMicroseconds(2);
            digitalWrite(X_STEP_PIN, LOW);
            break;
        case AXIS_Y:
            digitalWrite(Y_STEP_PIN, HIGH);
            delayMicroseconds(2);
            digitalWrite(Y_STEP_PIN, LOW);
            break;
        case AXIS_Z:
            digitalWrite(Z_STEP_PIN, HIGH);
            delayMicroseconds(2);
            digitalWrite(Z_STEP_PIN, LOW);
            break;
    }
}

void hal_enable_motor(uint8_t axis, bool enable) {
    switch(axis) {
        case AXIS_X: digitalWrite(X_ENABLE_PIN, enable ? LOW : HIGH); break; // LOW = habilitado en A4988
        case AXIS_Y: digitalWrite(Y_ENABLE_PIN, enable ? LOW : HIGH); break;
        case AXIS_Z: digitalWrite(Z_ENABLE_PIN, enable ? LOW : HIGH); break;
    }
}

bool hal_get_dir_state(uint8_t axis){
    int pin_state = LOW;
    switch (axis) {
        case AXIS_X:
            pin_state = digitalRead(X_DIR_PIN);
            break;
        case AXIS_Y:
            pin_state = digitalRead(Y_DIR_PIN);
            break;
        case AXIS_Z:
            pin_state = digitalRead(Z_DIR_PIN);
            break;
    }
    return (pin_state == HIGH);
}