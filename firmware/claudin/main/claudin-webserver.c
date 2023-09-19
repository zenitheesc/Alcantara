#include "claudin-webserver.h"
#include "claudin-util.h"
#include "esp_log.h"

// TODO: handle global declarations
queue_blob_t msg;
size_t offset = 0;
char aux[91];
uint8_t aux_offset;

// TODO: make a function that creates a index of values of JSON template
void template_scrapper() {
}

void json_deserialize_not_object(cJSON* element)
{
  if (element->type == cJSON_Invalid || element->type == cJSON_NULL) {
    // TODO: use sizeof(uint8_t) instead
    memcpy(&msg.bytes[offset], &element->type, sizeof(NULL));
    offset += sizeof(char);
    ESP_LOGI(webserver, "cJSON_Invalid");
  } else if (element->type == cJSON_False) {
    memcpy(&msg.bytes[offset], &element->type, sizeof(bool));
    offset += sizeof(bool);
    ESP_LOGI(webserver, "cJSON_False");
  } else if (element->type == cJSON_True) {
    memcpy(&msg.bytes[offset], &element->type, sizeof(bool));
    offset += sizeof(bool);
    ESP_LOGI(webserver, "cJSON_True");
  } else if (element->type == cJSON_Number) {
    if (element->valueint == element->valuedouble) {
      // TODO: cast int32_t to int16_t
      memcpy(&msg.bytes[offset], &element->valueint, sizeof(int));
      offset += sizeof(int);
      ESP_LOGI(webserver, "cJSON_Number int=%d", element->valueint);
    } else {
      // TODO: cast doubles to float
      memcpy(&msg.bytes[offset], &element->valuedouble, sizeof(double));
      offset += sizeof(double);
      ESP_LOGI(webserver, "cJSON_Number float=%.3f", element->valuedouble);
    }
  } else if (element->type == cJSON_String) {
    // This needs testing
    strcpy(aux,element->valuestring);
    aux_offset = strlen(element->valuestring);
    ESP_LOGI(webserver, "cJSON_String string=%s", element->valuestring);
  }
}

void json_deserialize(cJSON *element)
{
  // This snippet is unable to diferentiate a Object from a Array, needs more testing
  if (element->type == cJSON_Array) {
    int array_size = cJSON_GetArraySize(element);
    for (int i = 0; i < array_size; i++) {
      cJSON* aux = cJSON_GetArrayItem(element, i);
      json_deserialize(aux);
    }
  } else if (element->type == cJSON_Object) {
    ESP_LOGI(webserver, "cJSON_Object");
    cJSON *child_element = NULL;
    cJSON_ArrayForEach(child_element, element) {
      // needless recursion [NOT OPTIMIZED] 
      json_deserialize(child_element);
    }
  } else {
    json_deserialize_not_object(element);
  }
}

// TODO: add HTTP client with some tweaks and bad pratices
esp_err_t root_post_handler(httpd_req_t *req)
{
  // Recieve JSON string
  int total_len = req->content_len;
  int received;
  int remaining = total_len;
  char *buf = (char*)malloc(total_len + 1);
  while (remaining > 0) {
    received = httpd_req_recv(req, buf + (total_len - remaining), remaining);
    if (received <= 0) {
      if (received == HTTPD_SOCK_ERR_TIMEOUT) {
        // TODO: add actual timeout handle 
      }
      break;
    }
    remaining -= received;
  }

  buf[total_len] = '\0';
  // JSON deserialization
  // ! This function uses allocation !
  cJSON *root = cJSON_Parse(buf);
  // Check for object called payload
  cJSON *payload = cJSON_GetObjectItem(root, "payload");
  if (cJSON_IsObject(payload)) {
    int item_num = cJSON_GetArraySize(payload);
    ESP_LOGI(webserver, "Number of elements in payload: %d", item_num);
    for (int i = 0; i < item_num; i++) {
      cJSON *element = cJSON_GetArrayItem(payload, i);
      json_deserialize(element);
    }
    msg.used_bytes = offset;
    memcpy(&msg.bytes[offset], aux, aux_offset * sizeof(char));
    offset = 0;
  } else {
      ESP_LOGE(webserver, "Payload not found");
  }
  httpd_resp_send(req, "Payload recieved 👌", HTTPD_RESP_USE_STRLEN);
  cJSON_Delete(root);
  free(buf);
  // Send relevant data to queue
  xQueueSend(radio_queue, &msg, portMAX_DELAY);
  memset(msg.bytes, 0, sizeof(msg.bytes));
  msg.used_bytes = 0;
  return ESP_OK;
}

httpd_handle_t start_http_server(void)
{
  httpd_config_t config = HTTPD_DEFAULT_CONFIG();
  httpd_handle_t server = NULL;
  if (httpd_start(&server, &config) == ESP_OK) {
    httpd_uri_t root_post_uri = {
      .uri = "/",
      .method = HTTP_POST,
      .handler = root_post_handler,
      .user_ctx = NULL
    };
    httpd_register_uri_handler(server, &root_post_uri);
    return server;
  }
  return NULL;
}

void webserver_task()
{
  start_http_server();
  while(1) {
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}
