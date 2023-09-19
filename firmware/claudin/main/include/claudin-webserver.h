#include "esp_http_server.h"
#include "cJSON.h"
#include <stdint.h>

static const char *webserver = "webserver";

void json_deserialize_not_object(cJSON* element);
void json_deserialize(cJSON *element);
esp_err_t root_post_handler(httpd_req_t *req);
httpd_handle_t start_http_server(void);
void webserver_task();
