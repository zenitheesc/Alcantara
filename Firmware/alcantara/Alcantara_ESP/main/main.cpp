#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include "driver/ledc.h"
#include "driver/uart.h"
#include "esp_log.h"

TaskHandle_t RGBLEDTaskHandle;
TaskHandle_t ParseFunctionsTaskHandle;
TaskHandle_t RadioDataTaskHandle;
QueueHandle_t xNewRadioDataQueue;

enum class PARSE_ERROR_CODES {
    PARSE_SUCCESS,
    PARSE_DATA_NOT_APPENDED,
    PARSE_DATA_NOT_PRINTED
};

using parse_error_t = PARSE_ERROR_CODES;

#define UART_INSTRUCTION_BUFFER_SIZE 3
#define RADIO_DATA_INPUT_BUFFER_SIZE 256
#define OBC_BLOB_SIZE 92

#define GPIO_BUZZER GPIO_NUM_23
#define GPIO_RGB_LED_B GPIO_NUM_13

#define BUZZER_PWM_CHANNEL LEDC_CHANNEL_0 //Avoid use of channels 2, 3, 10, 11, as they make use of timer 1, which is being used for other purposes.
//More info in: https://github.com/espressif/arduino-esp32/blob/master/cores/esp32/esp32-hal-ledc.c
#define NO_TONE_FREQUENCY 0
#define BUZZER_FREQUENCY 6000
#define BUZZER_RESOLUTION LEDC_TIMER_13_BIT
#define BUZZER_DURATION 750

#define LED_TIMER_HARDWARE_NUMBER 1
#define LED_TIMER_DIVIDER 80000
#define LED_TIMER_ALARM_GENERATION_RATE 5000000 //microseconds

#define TOTAL_STATES 3
typedef enum {FSK, LoRa} radio_com_protocol_t;
typedef uint8_t obc_blob_t[OBC_BLOB_SIZE]; //More info about packet's structs definitions in: https://github.com/zenitheesc/Probe-CDH/blob/architecture/firmware/CDH_Firmware/Core/Inc/CDH.h

//------------OBSAT PACKET---------------
typedef struct {
    uint8_t id;
    obc_blob_t data;
} __attribute__((packed)) obsat_packet_t;
//---------------------------------------

//----------------ZENITH PACKETS--------------------
typedef struct {
    float latitude, longitude, altitude;
    float preassure_primary;
    float temp_1, temp_2, temp_3;
    float v_1, v_2, v_3;
    float i_1, i_2, i_3;
    float batt_charge;
    uint8_t seconds, minutes, hours;
    uint8_t packet_id;
} __attribute__((packed)) zenith_full_packet_t;

typedef struct {
    float latitude, longitude, altitude;
    float preassure_primary;
    float batt_charge;
    uint8_t seconds, minutes, hours;
    uint8_t packet_id;
} __attribute__((packed)) zenith_reduced_packet_t;
//-------------------------------------------------

typedef union {
    obsat_packet_t obsat_pkt;
    zenith_full_packet_t zen_full_pkt;
    zenith_reduced_packet_t zen_reduced_pkt;
    uint8_t raw[RADIO_DATA_INPUT_BUFFER_SIZE];
} last_packet_t;

//Define um tipo que é um ponteiro pra uma função de parse
typedef parse_error_t (* radio_parse_function_t) (last_packet_t *);

typedef enum {OBSAT, ZENITH} net_t;
typedef enum {SINGLE_BLINK, DOUBLE_BLINK, TRIPLE_BLINK} n_blinks_t;

typedef struct {
    radio_com_protocol_t comunication_protocol;
    radio_parse_function_t parse_function;
    net_t radio_net;
    n_blinks_t led_blinks;
} radio_configuration_state_t;

typedef union {
    float floating_point;
    uint8_t binary[4];
} binary_float_t;

volatile radio_configuration_state_t g_selected_state;
volatile last_packet_t * g_pxLastPacket;

void buzzer_init(){

    ledc_timer_config_t buzzer_timer = {
        .speed_mode         = LEDC_LOW_SPEED_MODE,
        .duty_resolution    = BUZZER_RESOLUTION,
        .timer_num          = LEDC_TIMER_0,
        .freq_hz            = BUZZER_FREQUENCY,
        .clk_cfg            = LEDC_AUTO_CLK
    };
    ESP_ERROR_CHECK(ledc_timer_config(&buzzer_timer));

    ledc_channel_config_t buzzer_channel = {
        .gpio_num           = GPIO_BUZZER,
        .speed_mode         = LEDC_LOW_SPEED_MODE,
        .channel            = BUZZER_PWM_CHANNEL,
        .intr_type          = LEDC_INTR_DISABLE,
        .timer_sel          = LEDC_TIMER_0,
        .duty               = 0,
        .hpoint             = 0
    };
    ESP_ERROR_CHECK(ledc_channel_config(&buzzer_channel));
    printf("Buzzer inicializado!");
}

void led_init(){
    
    gpio_config_t led_config = {
        .pin_bit_mask = (1ULL<<GPIO_RGB_LED_B),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    ESP_ERROR_CHECK(gpio_config(&led_config));
    printf("Led inicializado!");
}

void buzz() {

    ledc_set_duty(LEDC_LOW_SPEED_MODE, BUZZER_PWM_CHANNEL, 4096);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, BUZZER_PWM_CHANNEL);

    vTaskDelay(BUZZER_DURATION / portTICK_PERIOD_MS);

    ledc_set_duty(LEDC_LOW_SPEED_MODE, BUZZER_PWM_CHANNEL, 0);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, BUZZER_PWM_CHANNEL);

    // ledcWriteTone(BUZZER_PWM_CHANNEL, BUZZER_FREQUENCY);
    // delay(BUZZER_DURATION);
    // ledcWriteTone(BUZZER_PWM_CHANNEL, NO_TONE_FREQUENCY);

    #ifdef ISDEBUG
    printf("BIP!\n");
    #endif
}

void serial_init() {

    uart_config_t uart_config ={
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT
    };

    ESP_ERROR_CHECK(uart_param_config(UART_NUM_0, &uart_config));

    ESP_ERROR_CHECK(uart_set_pin(UART_NUM_0, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));
    ESP_ERROR_CHECK(uart_driver_install(UART_NUM_0, 1024, 0, 0, NULL, 0));

    printf("Serial inicializada\n");

}

void parse_radio (void * pvParameters) {
  for( ; ; ) {
    if (xNewRadioDataQueue != 0) {
    //   /*parse_radio_library_function*/(((last_packet_t *) pvParameters)->raw);
      if (xQueueSend(xNewRadioDataQueue, (void *) &pvParameters, (TickType_t) 10) != pdPASS) {
        printf("The message was not posted in the queue!\n (Timed out after 10 ticks)!\n\n");   
      }
    }
  }
}

void parse_functions_selector(void * pvParameters) {
  last_packet_t * last_pkt;

  for( ; ; ) {
    if(xNewRadioDataQueue != NULL) {
      if (xQueueReceive(xNewRadioDataQueue, &last_pkt, (TickType_t) 10) == pdPASS) {
        printf("The message was received from the queue!\n\n");   
      }
    }
    g_selected_state.parse_function(last_pkt);
  }
}

void blink_RGB_LED (void * pvParameters) {
  for( ; ; ) {
    for (int i = 0; i <= g_selected_state.led_blinks; i++) {
      gpio_set_level(GPIO_RGB_LED_B, 1);
      vTaskDelay(750 / portTICK_PERIOD_MS);
      gpio_set_level(GPIO_RGB_LED_B, 0);
      vTaskDelay(500 / portTICK_PERIOD_MS);
  }
  
  #ifdef ISDEBUG
  printf("%d PULSOS DO LED!\n", (g_selected_state.led_blinks + 1));
  #endif

  }
}

parse_error_t parse_obsat (last_packet_t * last_pkt) {
  //UART data transmission
  uart_write_bytes(UART_NUM_0, &last_pkt->obsat_pkt.id, 1);
  printf(";");
  uart_write_bytes(UART_NUM_0, last_pkt->obsat_pkt.data, OBC_BLOB_SIZE);
//   Serial.write(last_pkt->obsat_pkt.id);
//   Serial.print(";");
//   Serial.write(last_pkt->obsat_pkt.data, OBC_BLOB_SIZE);
//   #ifdef ISPRETTYDEBUG
//   Serial.println("Pacote: " + (String)last_pkt->obsat_pkt.id + "\n");
//   Serial.print("Dados: ");
//   Serial.write(last_pkt->obsat_pkt.data, OBC_BLOB_SIZE);
//   Serial.print("\n");
//   #endif

  //Porque retorna algo se não recebe em nenhum lugar?
  return PARSE_ERROR_CODES::PARSE_SUCCESS;
}

parse_error_t parse_zenith_reduced (last_packet_t * last_pkt) {
  binary_float_t binary_float;
  
  uart_write_bytes(UART_NUM_0, &last_pkt->zen_reduced_pkt.packet_id, 1);
  printf(";");
  binary_float.floating_point = last_pkt->zen_reduced_pkt.latitude;
  uart_write_bytes(UART_NUM_0, binary_float.binary, 4);
  printf(";");
  binary_float.floating_point = last_pkt->zen_reduced_pkt.longitude;
  uart_write_bytes(UART_NUM_0, binary_float.binary, 4);
  printf(";");
  binary_float.floating_point = last_pkt->zen_reduced_pkt.altitude;
  uart_write_bytes(UART_NUM_0, binary_float.binary, 4);
  printf(";");
  binary_float.floating_point = last_pkt->zen_reduced_pkt.preassure_primary;
  uart_write_bytes(UART_NUM_0, binary_float.binary, 4);
  printf(";");
  binary_float.floating_point = last_pkt->zen_reduced_pkt.batt_charge;
  uart_write_bytes(UART_NUM_0, binary_float.binary, 4);
  printf(";");
  uart_write_bytes(UART_NUM_0, &last_pkt->zen_reduced_pkt.seconds, 1);
  printf(";");
  uart_write_bytes(UART_NUM_0, &last_pkt->zen_reduced_pkt.minutes, 1);
  printf(";");
  uart_write_bytes(UART_NUM_0, &last_pkt->zen_reduced_pkt.hours, 1);
  printf("\n");

  //UART data transmission
//   Serial.write(last_pkt->zen_reduced_pkt.packet_id);
//   Serial.print(";");
//   binary_float.floating_point = last_pkt->zen_reduced_pkt.latitude;
//   Serial.write(binary_float.binary, 4);
//   Serial.print(";");
//   binary_float.floating_point = last_pkt->zen_reduced_pkt.longitude;
//   Serial.write(binary_float.binary, 4);
//   Serial.print(";");
//   binary_float.floating_point = last_pkt->zen_reduced_pkt.altitude;
//   Serial.write(binary_float.binary, 4);
//   Serial.print(";");
//   binary_float.floating_point = last_pkt->zen_reduced_pkt.preassure_primary;
//   Serial.write(binary_float.binary, 4);
//   Serial.print(";");
//   binary_float.floating_point = last_pkt->zen_reduced_pkt.batt_charge;
//   Serial.write(binary_float.binary, 4);
//   Serial.print(";");
//   Serial.write(last_pkt->zen_reduced_pkt.seconds);
//   Serial.print(";");
//   Serial.write(last_pkt->zen_reduced_pkt.minutes);
//   Serial.print(";");
//   Serial.write(last_pkt->zen_reduced_pkt.hours);
//   Serial.print("\n");
//   #ifdef ISPRETTYDEBUG
//   Serial.println("Pacote: " + (String)last_pkt->zen_reduced_pkt.packet_id + "\n");
//   Serial.println("Latitude: " + (String)last_pkt->zen_reduced_pkt.latitude + ". Longitude: " + (String)last_pkt->zen_reduced_pkt.longitude + ". Altitude: " + (String)last_pkt->zen_reduced_pkt.altitude + "\n");
//   Serial.println("Pressão Primária: " + (String)last_pkt->zen_reduced_pkt.preassure_primary + "\n");
//   Serial.println("Carga da Bateria: " + (String)last_pkt->zen_reduced_pkt.batt_charge + "\n");
//   Serial.println("Horário: Segundos: " + (String)last_pkt->zen_reduced_pkt.seconds + ". Minutos: " + (String)last_pkt->zen_reduced_pkt.minutes + ". Horas: " + (String)last_pkt->zen_reduced_pkt.hours + "\n\n");
//   #endif

  //Porque retorna algo se não recebe em nenhum lugar?
  return PARSE_ERROR_CODES::PARSE_SUCCESS;
}

parse_error_t parse_zenith_full (last_packet_t * last_pkt) {
  binary_float_t binary_float;
  
  uart_write_bytes(UART_NUM_0, &last_pkt->zen_full_pkt.packet_id, 1);
  printf(";");
  binary_float.floating_point = last_pkt->zen_full_pkt.latitude;
  uart_write_bytes(UART_NUM_0, binary_float.binary, 4);
  printf(";");
  binary_float.floating_point = last_pkt->zen_full_pkt.longitude;
  uart_write_bytes(UART_NUM_0, binary_float.binary, 4);
  printf(";");
  binary_float.floating_point = last_pkt->zen_full_pkt.altitude;
  uart_write_bytes(UART_NUM_0, binary_float.binary, 4);
  printf(";");
  binary_float.floating_point = last_pkt->zen_full_pkt.preassure_primary;
  uart_write_bytes(UART_NUM_0, binary_float.binary, 4);
  printf(";");
  binary_float.floating_point = last_pkt->zen_full_pkt.temp_1;
  uart_write_bytes(UART_NUM_0, binary_float.binary, 4);
  printf(";");
  binary_float.floating_point = last_pkt->zen_full_pkt.temp_2;
  uart_write_bytes(UART_NUM_0, binary_float.binary, 4);
  printf(";");
  binary_float.floating_point = last_pkt->zen_full_pkt.temp_3;
  uart_write_bytes(UART_NUM_0, binary_float.binary, 4);
  printf(";");
  binary_float.floating_point = last_pkt->zen_full_pkt.v_1;
  uart_write_bytes(UART_NUM_0, binary_float.binary, 4);
  printf(";");
  binary_float.floating_point = last_pkt->zen_full_pkt.v_2;
  uart_write_bytes(UART_NUM_0, binary_float.binary, 4);
  printf(";");
  binary_float.floating_point = last_pkt->zen_full_pkt.v_3;
  uart_write_bytes(UART_NUM_0, binary_float.binary, 4);
  printf(";");
  binary_float.floating_point = last_pkt->zen_full_pkt.i_1;
  uart_write_bytes(UART_NUM_0, binary_float.binary, 4);
  printf(";");
  binary_float.floating_point = last_pkt->zen_full_pkt.i_2;
  uart_write_bytes(UART_NUM_0, binary_float.binary, 4);
  printf(";");
  binary_float.floating_point = last_pkt->zen_full_pkt.i_3;
  uart_write_bytes(UART_NUM_0, binary_float.binary, 4);
  printf(";");
  binary_float.floating_point = last_pkt->zen_full_pkt.batt_charge;
  uart_write_bytes(UART_NUM_0, binary_float.binary, 4);
  printf(";");
  uart_write_bytes(UART_NUM_0, &last_pkt->zen_full_pkt.seconds, 1);
  printf(";");
  uart_write_bytes(UART_NUM_0, &last_pkt->zen_full_pkt.minutes, 1);
  printf(";");
  uart_write_bytes(UART_NUM_0, &last_pkt->zen_full_pkt.hours, 1);
  printf("\n");

//   //UART data transmission
//   Serial.write(last_pkt->zen_full_pkt.packet_id);
//   Serial.print(";");
//   binary_float.floating_point = last_pkt->zen_full_pkt.latitude;
//   Serial.write(binary_float.binary, 4);
//   Serial.print(";");
//   binary_float.floating_point = last_pkt->zen_full_pkt.longitude;
//   Serial.write(binary_float.binary, 4);
//   Serial.print(";");
//   binary_float.floating_point = last_pkt->zen_full_pkt.altitude;
//   Serial.write(binary_float.binary, 4);
//   Serial.print(";");
//   binary_float.floating_point = last_pkt->zen_full_pkt.preassure_primary;
//   Serial.write(binary_float.binary, 4);
//   Serial.print(";");
//   binary_float.floating_point = last_pkt->zen_full_pkt.temp_1;
//   Serial.write(binary_float.binary, 4);
//   Serial.print(";");
//   binary_float.floating_point = last_pkt->zen_full_pkt.temp_2;
//   Serial.write(binary_float.binary, 4);
//   Serial.print(";");
//   binary_float.floating_point = last_pkt->zen_full_pkt.temp_3;
//   Serial.write(binary_float.binary, 4);
//   Serial.print(";");
//   binary_float.floating_point = last_pkt->zen_full_pkt.v_1;
//   Serial.write(binary_float.binary, 4);
//   Serial.print(";");
//   binary_float.floating_point = last_pkt->zen_full_pkt.v_2;
//   Serial.write(binary_float.binary, 4);
//   Serial.print(";");
//   binary_float.floating_point = last_pkt->zen_full_pkt.v_3;
//   Serial.write(binary_float.binary, 4);
//   Serial.print(";");
//   binary_float.floating_point = last_pkt->zen_full_pkt.i_1;
//   Serial.write(binary_float.binary, 4);
//   Serial.print(";");
//   binary_float.floating_point = last_pkt->zen_full_pkt.i_2;
//   Serial.write(binary_float.binary, 4);
//   Serial.print(";");
//   binary_float.floating_point = last_pkt->zen_full_pkt.i_3;
//   Serial.write(binary_float.binary, 4);
//   Serial.print(";");
//   binary_float.floating_point = last_pkt->zen_full_pkt.batt_charge;
//   Serial.write(binary_float.binary, 4);
//   Serial.print(";");
//   Serial.write(last_pkt->zen_full_pkt.seconds);
//   Serial.print(";");
//   Serial.write(last_pkt->zen_full_pkt.minutes);
//   Serial.print(";");
//   Serial.write(last_pkt->zen_full_pkt.hours);
//   Serial.print("\n");
  
//   #ifdef ISPRETTYDEBUG
//   Serial.println("Pacote: " + (String)last_pkt->zen_full_pkt.packet_id + "\n");
//   Serial.println("Latitude: " + (String)last_pkt->zen_full_pkt.latitude + ". Longitude: " + (String)last_pkt->zen_full_pkt.longitude + ". Altitude: " + (String)last_pkt->zen_full_pkt.altitude + "\n");
//   Serial.println("Pressão Primária: " + (String)last_pkt->zen_full_pkt.preassure_primary + "\n");
//   Serial.println("Temperaturas: Temp1: " + (String)last_pkt->zen_full_pkt.temp_1 + ". Temp2: " + (String)last_pkt->zen_full_pkt.temp_2 + ". Temp3: " + (String)last_pkt->zen_full_pkt.temp_3 + "\n");
//   Serial.println("Tensões: V1: " + (String)last_pkt->zen_full_pkt.v_1 + ". V2: " + (String)last_pkt->zen_full_pkt.v_2 + ". V3: " + (String)last_pkt->zen_full_pkt.v_3 + "\n");
//   Serial.println("Correntes: i1: " + (String)last_pkt->zen_full_pkt.i_1 + ". i2: " + (String)last_pkt->zen_full_pkt.i_2 + ". i3: " + (String)last_pkt->zen_full_pkt.i_3 + "\n");
//   Serial.println("Carga da Bateria: " + (String)last_pkt->zen_full_pkt.batt_charge + "\n");
//   Serial.println("Horário: Segundos: " + (String)last_pkt->zen_full_pkt.seconds + ". Minutos: " + (String)last_pkt->zen_full_pkt.minutes + ". Horas: " + (String)last_pkt->zen_full_pkt.hours + "\n\n");
//   #endif

  //Porque retorna algo se não recebe em nenhum lugar?
  return PARSE_ERROR_CODES::PARSE_SUCCESS;
}

extern "C" void app_main(void)
{

    // Não vamos utilizar mais FSK, somente LoRa
    char UART_configuration_instruction[UART_INSTRUCTION_BUFFER_SIZE]; //Instrução da forma ("PROTOCOLO_DO_RÁDIO"[0]+"NET")\0 - Ex: "FZ\0";
    // parse_function inicia as funções: parse_obsat, parse_zenith_reduced e parse_zenith_full
    radio_configuration_state_t radio_state[3] = {{.comunication_protocol = FSK, .parse_function = parse_obsat, .radio_net = OBSAT, .led_blinks = SINGLE_BLINK},
                                                {.comunication_protocol = LoRa, .parse_function = parse_zenith_reduced, .radio_net = ZENITH, .led_blinks = DOUBLE_BLINK},
                                                {.comunication_protocol = FSK, .parse_function = parse_zenith_full, .radio_net = ZENITH, .led_blinks = TRIPLE_BLINK}};

    buzzer_init();
    led_init();
    serial_init();

    printf("Entre com: FO-FSKOBSAT; FZ-FSKZENITH; L-LoRa");

    unsigned int length = 0;
    while(length <= 0){
            uart_get_buffered_data_len(UART_NUM_0, (size_t*) &length);
            vTaskDelay(10 / portTICK_PERIOD_MS);
        }
    uart_read_bytes(UART_NUM_0, UART_configuration_instruction, length, 100);
    uart_flush(UART_NUM_0);


    switch (UART_configuration_instruction[0]) {
    case 'F': {
        switch (UART_configuration_instruction[1]) {
        case 'O': {
            ///radio.config(FSK, O);
            g_selected_state.comunication_protocol = radio_state[0].comunication_protocol;
            g_selected_state.radio_net = radio_state[0].radio_net;
            g_selected_state.led_blinks = radio_state[0].led_blinks;
            break;
        }
        case 'Z': {
            ///radio.config(FSK, Z);
            g_selected_state.comunication_protocol = radio_state[1].comunication_protocol;
            g_selected_state.radio_net = radio_state[1].radio_net;
            g_selected_state.led_blinks = radio_state[1].led_blinks;
            break;
        }
        }
        break;
    }
    case 'L': {
        ///radio.config(LoRa, Z);
        g_selected_state.comunication_protocol = radio_state[2].comunication_protocol;
        g_selected_state.radio_net = radio_state[2].radio_net;
        g_selected_state.led_blinks = radio_state[2].led_blinks;
        break;
    }
    }
    printf("Configuração do rádio bem sucedida!\n");
    //**
    UBaseType_t uxHighWaterMarkRGBLED = 100 * configMINIMAL_STACK_SIZE;

    if ((xTaskCreate(blink_RGB_LED, "Blink RGB LED", uxHighWaterMarkRGBLED, NULL, 2, &RGBLEDTaskHandle)) == pdPASS) {
    printf("Tarefa 'Blink RGB LED' criada com sucesso!\n");
    }

    UBaseType_t uxHighWaterMarkParseFunctions = 100 * configMINIMAL_STACK_SIZE;

    if ((xTaskCreate(parse_functions_selector, "Parse Function", uxHighWaterMarkParseFunctions, NULL, 4, &ParseFunctionsTaskHandle)) == pdPASS) {
    printf("Tarefa 'Parse Function' criada com sucesso!\n");
    }

    UBaseType_t uxHighWaterMarkReceiveRadioData = 100 * configMINIMAL_STACK_SIZE;

    if ((xTaskCreate(parse_radio, "Receive Radio Data", uxHighWaterMarkReceiveRadioData, (void *) &g_pxLastPacket, 5, &RadioDataTaskHandle)) == pdPASS) {
    printf("Tarefa 'Receive Radio Data' criada com sucesso!\n");
    }


    xNewRadioDataQueue = xQueueCreate(10, sizeof(last_packet_t *));

    if(xNewRadioDataQueue == NULL) {
    printf("Queue was not created!\n");
    // Dar um jeito de matar o código, sem a fila, não há como continuar (ou implementar um backup que processa diretamente as coisas sem a fila)
    }
    //**
    //attachInterrupt(digitalPinToInterrupt(GPIO_RADIO_INTERRUPT_PIN), parse_handler, ?FALLING?); *******************

    buzz();
}