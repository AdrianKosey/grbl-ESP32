#pragma once
// Inicializa el puerto serial
void serial_iface_init();

// Debe llamarse en loop(); revisa si llegaron comandos
void serial_iface_poll();

// Permite enviar mensajes al host (consola, PC, etc.)
void serial_iface_send(const char* msg);

// Retorna si hay una línea lista
bool serial_iface_line_available();
String serial_iface_get_line();
