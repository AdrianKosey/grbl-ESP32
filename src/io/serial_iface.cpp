#include "../grbl.h"

static String serial_input_line = "";

void serial_iface_init() {
    Serial.begin(BAUD_RATE);
    Serial.println("[INFO] Serial interface ready");
}

void serial_iface_task() {
    while (Serial.available() > 0) {
        char c = Serial.read();

        if (c == '\n' || c == '\r') {
            if (serial_input_line.length() > 0) {
                gcode_push_raw(serial_input_line.c_str());
                serial_input_line = "";
            }
        } else {
            if (serial_input_line.length() < GCODE_LINE_MAX_LENGTH - 1) {
                serial_input_line += c;
            }
        }
    }
}