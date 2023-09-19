#include "driver/uart.h"
#include "driver/gpio.h"

// TODO: figure out the correct pins
#define CLAUDIN_UART_PORT 2
#define CLAUDIN_TXD_PIN 17
#define CLAUDIN_RXD_PIN 16

void set_pin(int8_t pin);
esp_err_t serial_send(const char* command, uint16_t timeout);
esp_err_t uart_init();
