#include "claudin-gps.h"

void gps_init() {
  uart_init();
  gps_config();
}

void gps_config() {
  // TODO: find a library, duh
}

void gps_task() {
  gps_init();
  while (1) {
    vTaskDelay(1000);
  }
}
