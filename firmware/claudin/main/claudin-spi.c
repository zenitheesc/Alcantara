#include "claudin-spi.h"

esp_err_t spi_read_buffer(spi_device_handle_t spi_bus, uint8_t reg_addr,
                          uint8_t *pvalue, uint16_t len) {
  spi_transaction_t t = {.flags = 0,
                         .cmd = 0,
                         .addr = reg_addr & 0x7F,
                         .length = 8 * len,
                         .rxlength = 8 * len,
                         .tx_buffer = NULL,
                         .rx_buffer = pvalue};
  esp_err_t ret = spi_device_polling_transmit(spi_bus, &t);
  if (ret != ESP_OK) {
    ESP_LOGE(spi, "Failed to read 0x%X", reg_addr);
  } else {
    // for (uint8_t i = 0; i < len; i++)
    //{
    //	printf("r0x%X ", pvalue[i]);
    // }
    // printf("\n");
  }
  return ret;
}

esp_err_t spi_read_register(spi_device_handle_t spi_bus, uint8_t reg_addr,
                            uint8_t *pvalue) {
  return spi_read_buffer(spi_bus, reg_addr, pvalue, 1);
}

esp_err_t spi_write_buffer(spi_device_handle_t spi_bus, uint8_t reg_addr,
                           uint8_t *pvalue, uint16_t len) {
  spi_transaction_t t = {.flags = 0,
                         .cmd = 0,
                         .addr = reg_addr | 0x80,
                         .length = len * 8,
                         .rxlength = len * 8,
                         .tx_buffer = pvalue,
                         .rx_buffer = NULL};
  esp_err_t ret = spi_device_polling_transmit(spi_bus, &t);
  if (ret != ESP_OK) {
    ESP_LOGE(spi, "Failed to start writing at 0x%X", reg_addr);
  }
  return ret;
}

esp_err_t spi_write_register(spi_device_handle_t spi_bus, uint8_t reg_addr,
                             uint8_t pvalue) {
  return spi_write_buffer(spi_bus, reg_addr, &pvalue, 1);
}

esp_err_t test_register(spi_device_handle_t spi_bus) {
  uint8_t register_value = 0;
  spi_read_register(spi_bus, 0x42, &register_value);
  if (register_value != 0x12) {
    return ESP_FAIL;
  }
  ESP_LOGI(spi, "Register 0x42 returned the correct value when read");
  return ESP_OK;
}

esp_err_t spi_init() {
  spi_bus_config_t bus_config = {
      .miso_io_num = VSPI_MISO,
      .mosi_io_num = VSPI_MOSI,
      .sclk_io_num = VSPI_SCLK,
      .quadwp_io_num = -1,
      .quadhd_io_num = -1,
      .max_transfer_sz = 0,
  };
  return spi_bus_initialize(VSPI_HOST, &bus_config, 1);
}
esp_err_t spi_add_device(spi_device_handle_t *spi_bus, uint32_t spi_clk) {
  spi_device_interface_config_t dev_config = {
      .command_bits = 0,
      .address_bits = 8,
      .dummy_bits = 0,
      .mode = 0,
      .clock_speed_hz = spi_clk,
      .spics_io_num = GPIO_RADIO_SS,
      .queue_size = 8,
      .flags = 0,
  };
  return spi_bus_add_device(VSPI_HOST, &dev_config, spi_bus);
}
