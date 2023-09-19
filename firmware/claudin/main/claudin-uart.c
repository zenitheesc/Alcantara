#include "claudin-uart.h"

void set_pin(int8_t pin) {
  // TODO: add input, pullup options
  gpio_config_t io_conf;
  io_conf.pin_bit_mask = (1ULL << pin);
  io_conf.intr_type = GPIO_INTR_DISABLE;
  io_conf.mode = GPIO_MODE_OUTPUT; 
  io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
  io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
  gpio_config(&io_conf);
}
// Equivalent to Serial.print?
esp_err_t serial_send(const char* cmd, uint16_t timeout) {
  uart_write_bytes(CLAUDIN_UART_PORT, cmd, strlen(cmd));
  vTaskDelay(timeout / portTICK_PERIOD_MS);
}
esp_err_t uart_init() {
  // TODO: params for uart initialization, for now it "works"
  // - https://github.com/espressif/arduino-esp32/blob/master/cores/esp32/esp32-hal-uart.h
  uint32_t config = 0x800001c;
  uart_config_t uart_config;
  uart_config.data_bits = (config & 0xc) >> 2;
  uart_config.parity = (config & 0x3);
  uart_config.stop_bits = (config & 0x30) >> 4;
  uart_config.flow_ctrl = UART_HW_FLOWCTRL_DISABLE;
  uart_config.rx_flow_ctrl_thresh = 112;
  uart_config.source_clk = UART_SCLK_APB;
  uart_config.baud_rate = 115200;
  esp_err_t ret = uart_driver_install(CLAUDIN_UART_PORT, 256, 0, 0, NULL, 0);
  if (ret != ESP_OK) {
    return ret;
  }
  ret = uart_param_config(CLAUDIN_UART_PORT, &uart_config);
  if (ret != ESP_OK) {
    return ret;
  }
  ret = uart_set_pin(CLAUDIN_UART_PORT, CLAUDIN_TXD_PIN, CLAUDIN_RXD_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
  if (ret != ESP_OK) {
    return ret;
  }
  ret = uart_flush_input(CLAUDIN_UART_PORT);
  if (ret != ESP_OK) {
    return ret;
  }
  return ESP_OK;
}
