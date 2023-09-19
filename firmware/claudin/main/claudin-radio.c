#include "claudin-radio.h"
#include "claudin-util.h"

// TODO: handle global declarations
// TODO: add IDF option for FSK and LoRa

SX127X_t SX127X;

void radio_task() {
  spi_init();
  spi_add_device(&SX127X.spi_bus, 1000000);
  // Pin setup
#ifdef CONFIG_MODE_TRANSMITTER
  gpio_set_direction(GPIO_RADIO_NRST, GPIO_MODE_OUTPUT);

  gpio_set_direction(GPIO_RADIO_DIO_0, GPIO_MODE_INPUT);
  gpio_pulldown_en(GPIO_RADIO_DIO_0);
  gpio_pullup_dis(GPIO_RADIO_DIO_0);

  gpio_set_direction(GPIO_RADIO_DIO_1, GPIO_MODE_INPUT);
  gpio_pulldown_en(GPIO_RADIO_DIO_1);
  gpio_pullup_dis(GPIO_RADIO_DIO_1);
#elif CONFIG_MODE_RECEIVER
  gpio_install_isr_service(0);

  gpio_set_direction(GPIO_RADIO_NRST, GPIO_MODE_OUTPUT);

  gpio_set_direction(GPIO_RADIO_DIO_0, GPIO_MODE_INPUT);
  gpio_pulldown_en(GPIO_RADIO_DIO_0);
  gpio_pullup_dis(GPIO_RADIO_DIO_0);
  gpio_set_intr_type(GPIO_RADIO_DIO_0, GPIO_INTR_POSEDGE);
  gpio_isr_handler_add(GPIO_RADIO_DIO_0, handle_dio0_interrupt, NULL);

  // Need to be confirmed (needs to do what pciSetup do)
  // gpio_set_direction(GPIO_RADIO_DIO_1, GPIO_MODE_INPUT);
  // gpio_pulldown_en(GPIO_RADIO_DIO_1);
  // gpio_pullup_dis(GPIO_RADIO_DIO_1);
  // gpio_set_intr_type(GPIO_RADIO_DIO_1, GPIO_INTR_POSEDGE);
  // gpio_isr_handler_add(GPIO_RADIO_DIO_1, handle_dio0_interrupt, NULL);
#endif
  // ESP_LOGI(radio,"Setting FSK config");
  // esp_err_t ret = FSK_Config(&SX127X);
  // if (ret != ESP_OK)
  //{
  //   	ESP_LOGI(radio,"Failed initialization");
  //   	while (1);
  // }
  //
  ESP_LOGI(radio, "Setting LoRa config");
  esp_err_t ret = LoRa_Config(&SX127X);
  if (ret != ESP_OK) {
    ESP_LOGI(radio, "Failed initialization");
    while (1)
      ;
  }

#ifdef CONFIG_MODE_TRANSMITTER
  radio_queue = xQueueCreate(N_PARTICIPANTES + 1, sizeof(queue_blob_t));
  if (radio_queue == NULL) {
    ESP_LOGE(radio, "Failed to create queue");
    while (1)
      ;
  }
  queue_blob_t packet;
  ESP_LOGI(radio, "Queue created");
  SX127X_set_op_mode(&SX127X, RX);
  ESP_LOGI(radio, "Starting radio-loop");
  // TODO: Solve Lora/FSK dilemma [USE ONLY ONE MODULATION PLZ]
  while (1) {
    xQueueReceive(radio_queue, &packet, portMAX_DELAY);
    LoRa_Transmit(&SX127X, packet.bytes, packet.used_bytes);
    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }
#elif CONFIG_MODE_RECEIVER
  SX127X_set_op_mode(&SX127X, RX);
  while (1) {
    if (dio0) {
      esp_err_t ret = LoRa_ReadPacket(&SX127X, rx_data, sizeof(rx_data),&received_data_size, &crc_status);
      for (int i = 0; i < received_data_size; i++) {
        // TODO: add deserialization logic LOL.
      }
      if (ret != ESP_OK)
        ESP_LOGE(radio, "Error reading packet!");
      ret = LoRa_get_packet_rssi(&SX127X, &rssi);
      if (ret != ESP_OK) {
        ESP_LOGE(radio, "Error getting packet RSSI!");
      } else {
        ESP_LOGI(radio, "\nPacket RSSI: - %d", rssi);
      }

      if (crc_status) {
        ESP_LOGI(radio, "CRC is BAD :(");
      } else {
        ESP_LOGI(radio, "CRC is OK! :)");
      }
      dio0 = false;
    }
    vTaskDelay(10 / portTICK_PERIOD_MS);
  }
#endif
};
