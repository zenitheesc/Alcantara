#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
//#include "claudin-util.h"
#include "claudin-gps.h"
#include "claudin-radio.h"
#include "claudin-webserver.h"
#ifdef CONFIG_MODE_TRANSMITTER
#include "claudin-wifi.h"
#endif
#include "esp_log.h"

static const char *main = "Main";

QueueHandle_t radio_queue;

void app_main(void)
{
#ifdef CONFIG_MODE_TRANSMITTER
  start_wifi();
  vTaskDelay(3000 / portTICK_PERIOD_MS);
  xTaskCreate(radio_task, "TX Task", configMINIMAL_STACK_SIZE * 5, NULL, 5, NULL);
  ESP_LOGI(main,"Started Transmitter Task");
  // TODO: all GPS stuff
  xTaskCreate(webserver_task, "GPS Task", configMINIMAL_STACK_SIZE * 5, NULL, 5, NULL);
  ESP_LOGI(main,"Started GPS Task");
  xTaskCreate(webserver_task, "Webserver Task", configMINIMAL_STACK_SIZE * 5, NULL, 5, NULL);
  ESP_LOGI(main,"Started Webserver Task");
#elif CONFIG_MODE_RECEIVER
  vTaskDelay(2000 / portTICK_PERIOD_MS);
  xTaskCreate(radio_task, "Reciever Task", configMINIMAL_STACK_SIZE * 5, NULL, 2, NULL);
  ESP_LOGI(main,"Started RX Task");
  xTaskCreate(parser_task, "Parser Task", configMINIMAL_STACK_SIZE * 5, NULL, 3, NULL);
  ESP_LOGI(main,"Started Parser Task");
#endif
}
