#include "SX127X.h"

static const char *radio = "radio";

#ifdef CONFIG_MODE_RECEIVER
static TaskHandle_t handle_interrupt;
static uint8_t rssi;
static bool crc_status;
static uint8_t received_data_size;
static uint8_t rx_data[255];
static bool dio0 = false;

static void IRAM_ATTR handle_dio0_interrupt(void *arg) {
	dio0 = true;
}

// Interrupt Service Routine for DIO1 pin
static void IRAM_ATTR handle_dio1_interrupt(void *arg) {
	ESP_LOGE(radio,"Coisas de Lora");
}
#endif

void radio_task();
