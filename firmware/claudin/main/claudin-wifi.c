#include "claudin-wifi.h"

void wifi_event_handler(void* arg,esp_event_base_t event_base,int32_t event_id, void* event_data)
{
  //TODO: actully make a error handling for Wi-Fi
  if (event_id == WIFI_EVENT_AP_STACONNECTED) {
    wifi_event_ap_staconnected_t* event = (wifi_event_ap_staconnected_t*) event_data;
    ESP_LOGI(wifi, "station "MACSTR" join, AID=%d",MAC2STR(event->mac), event->aid);
  }
  else if (event_id == WIFI_EVENT_AP_STADISCONNECTED) {
    wifi_event_ap_stadisconnected_t* event = (wifi_event_ap_stadisconnected_t*) event_data;
    ESP_LOGI(wifi, "station "MACSTR" leave, AID=%d",MAC2STR(event->mac), event->aid);
  }
}

void wifi_init(void)
{
  ESP_ERROR_CHECK(esp_netif_init());
  ESP_ERROR_CHECK(esp_event_loop_create_default());
  esp_netif_create_default_wifi_ap();
  wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
  ESP_ERROR_CHECK(esp_wifi_init(&cfg));
  ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,ESP_EVENT_ANY_ID,&wifi_event_handler,NULL,NULL));
  wifi_config_t wifi_config = {
    .ap = {
      .ssid = CONFIG_WIFI_SSID,
      .ssid_len = strlen(CONFIG_WIFI_SSID),
      .channel = 1,
      .password = CONFIG_WIFI_PASSWORD,
      .max_connection = 3,
      .authmode = WIFI_AUTH_WPA2_PSK,
    },
  };
  ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
  ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &wifi_config));
  ESP_ERROR_CHECK(esp_wifi_start());
}

void start_wifi()
{
  esp_err_t ret = nvs_flash_init();
  if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
    ESP_ERROR_CHECK(nvs_flash_erase());
    ret = nvs_flash_init();
  }
  ESP_ERROR_CHECK(ret);
  wifi_init();
  ESP_LOGI(wifi, "Wi-Fi started correctly");
}
