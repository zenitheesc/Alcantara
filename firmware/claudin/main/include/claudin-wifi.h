#include <string.h>
#include "nvs_flash.h"
#include "esp_wifi.h"
#include "esp_mac.h"
#include "esp_log.h"

static const char *wifi = "Wi-Fi";

void wifi_event_handler(void* arg,esp_event_base_t event_base,int32_t event_id, void* event_data);
void wifi_init(void);
void start_wifi();
