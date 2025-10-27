#include "../grbl.h"
// Buffer temporal donde guardamos los caracteres entrantes
static String inputBuffer = "";
static bool lineReady = false;

void serial_iface_init(){
    // Colocar baud rate
    Serial.begin(BAUD_RATE);
    while (!Serial) {
        delay(10); // Espera si es USB-Serial (útil en PC)
    }
    Serial.println("Serial interface initialized.");
    inputBuffer.reserve(100); // reservamos espacio para evitar fragmentación
}

void serial_iface_poll() {
  while (Serial.available()) {
    char c = Serial.read();

    // Ignorar retornos de carro si llegan
    if (c == '\r') continue;

    if (c == '\n') {
      // Línea completa recibida
      if (inputBuffer.length() > 0) {
        // Mandar al parser
        gcode_push_raw(inputBuffer.c_str());

        // Marcar la línea disponible
        lineReady = true;

        // Eco opcional
        Serial.print(">> ");
        Serial.println(inputBuffer);

        // Limpia el buffer para la siguiente línea
        inputBuffer = "";
      }
    } else {
      // Agregar carácter al buffer
      inputBuffer += c;

      // Protección básica: si la línea es demasiado larga, resetea
      if (inputBuffer.length() > 120) {
        Serial.println("Error: línea demasiado larga, se descartará.");
        inputBuffer = "";
      }
    }
  }
}

bool serial_iface_line_available() {
  return lineReady;
}

String serial_iface_get_line() {
  lineReady = false;
  return inputBuffer;
}

void serial_iface_send(const char* msg){
    Serial.print(msg);
}
