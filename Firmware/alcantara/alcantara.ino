/*Board - Arduino IDE: ESP32 Dev Module*/
//#include 'biblioteca_do_radio.h'
//#define ISDEBUG 1
//#define ISPRETTYDEBUG 1

TaskHandle_t RGBLEDTaskHandle;
TaskHandle_t ParseFunctionsTaskHandle;
TaskHandle_t RadioDataTaskHandle;
QueueHandle_t xNewRadioDataQueue;

#include "FS.h"
#include "SPI.h"

enum class PARSE_ERROR_CODES {
  PARSE_SUCCESS,
  PARSE_DATA_NOT_APPENDED,
  PARSE_DATA_NOT_PRINTED
};

using parse_error_t = PARSE_ERROR_CODES;

#define UART_INSTRUCTION_BUFFER_SIZE 3
#define RADIO_DATA_INPUT_BUFFER_SIZE 256
#define OBC_BLOB_SIZE 92

//#define GPIO_BTN_SELECT 1
//#define GPIO_BTN_ENTER 2
//#define DEBOUNCE_TIME 50

#define GPIO_BUZZER 24
#define GPIO_RGB_LED_B 13

#define BUZZER_PWM_CHANNEL 0 //Avoid use of channels 2, 3, 10, 11, as they make use of timer 1, which is being used for other purposes.
//More info in: https://github.com/espressif/arduino-esp32/blob/master/cores/esp32/esp32-hal-ledc.c
#define NO_TONE_FREQUENCY 0
#define BUZZER_FREQUENCY 6000
#define BUZZER_FREQUENCY_RESOLUTION 13 //bits
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
  byte raw[RADIO_DATA_INPUT_BUFFER_SIZE];
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

//NÃO ENTENDI
static const char * const radio_com_protocol_type[] = {
  [FSK] = "FSK",
  [LoRa] = "LoRa"
};

typedef union {
  float floating_point;
  byte binary[4];
} binary_float_t;

volatile radio_configuration_state_t g_selected_state;
volatile last_packet_t * g_pxLastPacket;

//--------------Porque fez tudo isso se não vai usar?-------------------
volatile unsigned int g_interruptCounter;
hw_timer_t * timer = nullptr;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;
portMUX_TYPE parseMux = portMUX_INITIALIZER_UNLOCKED;
//----------------------------------------------------------------------

void blink_RGB_LED (void * pvParameters) {
  for( ; ; ) {
    for (int i = 0; i <= g_selected_state.led_blinks; i++) {
      digitalWrite(GPIO_RGB_LED_B, HIGH);
      vTaskDelay(750 / portTICK_PERIOD_MS);
      digitalWrite(GPIO_RGB_LED_B, LOW);
      vTaskDelay(500 / portTICK_PERIOD_MS);
  }

// ???????????????????????????????????
  #ifdef ISDEBUG
  Serial.println("%d PULSOS DO LED!\n", (g_selected_state.led_blinks + 1));
  #endif

  }
}

//------------------Envia as informações do pacote por serial-------------------------
parse_error_t parse_obsat (last_packet_t * last_pkt) {
  //UART data transmission
  Serial.write(last_pkt->obsat_pkt.id);
  Serial.print(";");
  Serial.write(last_pkt->obsat_pkt.data, OBC_BLOB_SIZE);
  #ifdef ISPRETTYDEBUG
  Serial.println("Pacote: " + (String)last_pkt->obsat_pkt.id + "\n");
  Serial.print("Dados: ");
  Serial.write(last_pkt->obsat_pkt.data, OBC_BLOB_SIZE);
  Serial.print("\n");
  #endif

  //Porque retorna algo se não recebe em nenhum lugar?
  return PARSE_ERROR_CODES::PARSE_SUCCESS;
}

parse_error_t parse_zenith_reduced (last_packet_t * last_pkt) {
  binary_float_t binary_float;
  
  //UART data transmission
  Serial.write(last_pkt->zen_reduced_pkt.packet_id);
  Serial.print(";");
  binary_float.floating_point = last_pkt->zen_reduced_pkt.latitude;
  Serial.write(binary_float.binary, 4);
  Serial.print(";");
  binary_float.floating_point = last_pkt->zen_reduced_pkt.longitude;
  Serial.write(binary_float.binary, 4);
  Serial.print(";");
  binary_float.floating_point = last_pkt->zen_reduced_pkt.altitude;
  Serial.write(binary_float.binary, 4);
  Serial.print(";");
  binary_float.floating_point = last_pkt->zen_reduced_pkt.preassure_primary;
  Serial.write(binary_float.binary, 4);
  Serial.print(";");
  binary_float.floating_point = last_pkt->zen_reduced_pkt.batt_charge;
  Serial.write(binary_float.binary, 4);
  Serial.print(";");
  Serial.write(last_pkt->zen_reduced_pkt.seconds);
  Serial.print(";");
  Serial.write(last_pkt->zen_reduced_pkt.minutes);
  Serial.print(";");
  Serial.write(last_pkt->zen_reduced_pkt.hours);
  Serial.print("\n");
  #ifdef ISPRETTYDEBUG
  Serial.println("Pacote: " + (String)last_pkt->zen_reduced_pkt.packet_id + "\n");
  Serial.println("Latitude: " + (String)last_pkt->zen_reduced_pkt.latitude + ". Longitude: " + (String)last_pkt->zen_reduced_pkt.longitude + ". Altitude: " + (String)last_pkt->zen_reduced_pkt.altitude + "\n");
  Serial.println("Pressão Primária: " + (String)last_pkt->zen_reduced_pkt.preassure_primary + "\n");
  Serial.println("Carga da Bateria: " + (String)last_pkt->zen_reduced_pkt.batt_charge + "\n");
  Serial.println("Horário: Segundos: " + (String)last_pkt->zen_reduced_pkt.seconds + ". Minutos: " + (String)last_pkt->zen_reduced_pkt.minutes + ". Horas: " + (String)last_pkt->zen_reduced_pkt.hours + "\n\n");
  #endif

  //Porque retorna algo se não recebe em nenhum lugar?
  return PARSE_ERROR_CODES::PARSE_SUCCESS;
}

parse_error_t parse_zenith_full (last_packet_t * last_pkt) {
  binary_float_t binary_float;
  
  //UART data transmission
  Serial.write(last_pkt->zen_full_pkt.packet_id);
  Serial.print(";");
  binary_float.floating_point = last_pkt->zen_full_pkt.latitude;
  Serial.write(binary_float.binary, 4);
  Serial.print(";");
  binary_float.floating_point = last_pkt->zen_full_pkt.longitude;
  Serial.write(binary_float.binary, 4);
  Serial.print(";");
  binary_float.floating_point = last_pkt->zen_full_pkt.altitude;
  Serial.write(binary_float.binary, 4);
  Serial.print(";");
  binary_float.floating_point = last_pkt->zen_full_pkt.preassure_primary;
  Serial.write(binary_float.binary, 4);
  Serial.print(";");
  binary_float.floating_point = last_pkt->zen_full_pkt.temp_1;
  Serial.write(binary_float.binary, 4);
  Serial.print(";");
  binary_float.floating_point = last_pkt->zen_full_pkt.temp_2;
  Serial.write(binary_float.binary, 4);
  Serial.print(";");
  binary_float.floating_point = last_pkt->zen_full_pkt.temp_3;
  Serial.write(binary_float.binary, 4);
  Serial.print(";");
  binary_float.floating_point = last_pkt->zen_full_pkt.v_1;
  Serial.write(binary_float.binary, 4);
  Serial.print(";");
  binary_float.floating_point = last_pkt->zen_full_pkt.v_2;
  Serial.write(binary_float.binary, 4);
  Serial.print(";");
  binary_float.floating_point = last_pkt->zen_full_pkt.v_3;
  Serial.write(binary_float.binary, 4);
  Serial.print(";");
  binary_float.floating_point = last_pkt->zen_full_pkt.i_1;
  Serial.write(binary_float.binary, 4);
  Serial.print(";");
  binary_float.floating_point = last_pkt->zen_full_pkt.i_2;
  Serial.write(binary_float.binary, 4);
  Serial.print(";");
  binary_float.floating_point = last_pkt->zen_full_pkt.i_3;
  Serial.write(binary_float.binary, 4);
  Serial.print(";");
  binary_float.floating_point = last_pkt->zen_full_pkt.batt_charge;
  Serial.write(binary_float.binary, 4);
  Serial.print(";");
  Serial.write(last_pkt->zen_full_pkt.seconds);
  Serial.print(";");
  Serial.write(last_pkt->zen_full_pkt.minutes);
  Serial.print(";");
  Serial.write(last_pkt->zen_full_pkt.hours);
  Serial.print("\n");
  
  #ifdef ISPRETTYDEBUG
  Serial.println("Pacote: " + (String)last_pkt->zen_full_pkt.packet_id + "\n");
  Serial.println("Latitude: " + (String)last_pkt->zen_full_pkt.latitude + ". Longitude: " + (String)last_pkt->zen_full_pkt.longitude + ". Altitude: " + (String)last_pkt->zen_full_pkt.altitude + "\n");
  Serial.println("Pressão Primária: " + (String)last_pkt->zen_full_pkt.preassure_primary + "\n");
  Serial.println("Temperaturas: Temp1: " + (String)last_pkt->zen_full_pkt.temp_1 + ". Temp2: " + (String)last_pkt->zen_full_pkt.temp_2 + ". Temp3: " + (String)last_pkt->zen_full_pkt.temp_3 + "\n");
  Serial.println("Tensões: V1: " + (String)last_pkt->zen_full_pkt.v_1 + ". V2: " + (String)last_pkt->zen_full_pkt.v_2 + ". V3: " + (String)last_pkt->zen_full_pkt.v_3 + "\n");
  Serial.println("Correntes: i1: " + (String)last_pkt->zen_full_pkt.i_1 + ". i2: " + (String)last_pkt->zen_full_pkt.i_2 + ". i3: " + (String)last_pkt->zen_full_pkt.i_3 + "\n");
  Serial.println("Carga da Bateria: " + (String)last_pkt->zen_full_pkt.batt_charge + "\n");
  Serial.println("Horário: Segundos: " + (String)last_pkt->zen_full_pkt.seconds + ". Minutos: " + (String)last_pkt->zen_full_pkt.minutes + ". Horas: " + (String)last_pkt->zen_full_pkt.hours + "\n\n");
  #endif

  //Porque retorna algo se não recebe em nenhum lugar?
  return PARSE_ERROR_CODES::PARSE_SUCCESS;
}
//------------------------------------------------------------------------------------


//**
//Recebe o ultimo pacote e inicia alguma função de parse presente no pacote
void parse_functions_selector(void * pvParameters) {
  last_packet_t * last_pkt;

  for( ; ; ) {
    if(xNewRadioDataQueue != NULL) {
      if (xQueueReceive(xNewRadioDataQueue, &last_pkt, (TickType_t) 10) == pdPASS) {
        Serial.println("The message was received from the queue!\n\n");   
      }
    }
    g_selected_state.parse_function(last_pkt);
  }
}

//Envia dados do ultimo pacote para fila
void parse_radio (void * pvParameters) {
  for( ; ; ) {
    if (xNewRadioDataQueue != 0) {
      /*parse_radio_library_function*/(((last_packet_t *) pvParameters)->raw);
      if (xQueueSend(xNewRadioDataQueue, (void *) &pvParameters, (TickType_t) 10) != pdPASS) {
        Serial.println("The message was not posted in the queue!\n (Timed out after 10 ticks)!\n\n");   
      }
    }
  }
}
//**

void setup() {
  // Não vamos utilizar mais FSK, somente LoRa
  char UART_configuration_instruction[UART_INSTRUCTION_BUFFER_SIZE]; //Instrução da forma ("PROTOCOLO_DO_RÁDIO"[0]+"NET")\0 - Ex: "FZ\0";
  // parse_function inicia as funções: parse_obsat, parse_zenith_reduced e parse_zenith_full
  radio_configuration_state_t radio_state[3] = {{.comunication_protocol = FSK, .parse_function = parse_obsat, .radio_net = OBSAT, .led_blinks = SINGLE_BLINK},
                                                {.comunication_protocol = LoRa, .parse_function = parse_zenith_reduced, .radio_net = ZENITH, .led_blinks = DOUBLE_BLINK},
                                                {.comunication_protocol = FSK, .parse_function = parse_zenith_full, .radio_net = ZENITH, .led_blinks = TRIPLE_BLINK}};
  
  Serial.begin(115200);
  Serial.println("Comunicação SERIAL estabelecida!\n");
  
  //Iniciar o Rádio
  //Serial.println("Rádio Iniciado!\n");

  //pinMode(GPIO_BTN_SELECT, INPUT);
  //pinMode(GPIO_BTN_ENTER, INPUT);
  pinMode(GPIO_BUZZER, OUTPUT);
  pinMode(GPIO_RGB_LED_B, OUTPUT);
  Serial.println("Modo dos pinos definidos!\n");

  //The function above will be used to vinculate the buzzer pin with one of the PWM channel, in order to generate the waveform needed
  ledcSetup(GPIO_BUZZER, BUZZER_FREQUENCY, BUZZER_FREQUENCY_RESOLUTION);
  ledcAttachPin(GPIO_BUZZER, BUZZER_PWM_CHANNEL);
  Serial.println("Canal PWM do buzzer configurado!\n");

  //Recebe configuração via UART ["FO", "FZ" ou "L"]//CONSERTAR AQUI COM DELAY ANTES DO IF E PRINTS DE LINHA COM O PASSO A PASSO PARA AJUDAR A PESSOA QUE VAI INSERIR A INSTRUÇÃO
  if (Serial.available() > 0) {
    Serial.readBytes(UART_configuration_instruction, UART_INSTRUCTION_BUFFER_SIZE);
    Serial.println("Instruções de configuração recebidas com sucesso!\n");
  }

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
  Serial.println("Configuração do rádio bem sucedida!\n");
//**
  UBaseType_t uxHighWaterMarkRGBLED = 100 * configMINIMAL_STACK_SIZE;

  if ((xTaskCreate(blink_RGB_LED, "Blink RGB LED", uxHighWaterMarkRGBLED, NULL, 2, &RGBLEDTaskHandle)) == pdPASS) {
    Serial.println("Tarefa 'Blink RGB LED' criada com sucesso!\n");
  }

  UBaseType_t uxHighWaterMarkParseFunctions = 100 * configMINIMAL_STACK_SIZE;

  if ((xTaskCreate(parse_functions_selector, "Parse Function", uxHighWaterMarkParseFunctions, NULL, 4, &ParseFunctionsTaskHandle)) == pdPASS) {
    Serial.println("Tarefa 'Parse Function' criada com sucesso!\n");
  }

  UBaseType_t uxHighWaterMarkReceiveRadioData = 100 * configMINIMAL_STACK_SIZE;

  if ((xTaskCreate(parse_radio, "Receive Radio Data", uxHighWaterMarkReceiveRadioData, (void *) &g_pxLastPacket, 5, &RadioDataTaskHandle)) == pdPASS) {
    Serial.println("Tarefa 'Receive Radio Data' criada com sucesso!\n");
  }

  xNewRadioDataQueue = xQueueCreate(10, sizeof(last_packet_t *));

  if(xNewRadioDataQueue == NULL) {
    Serial.println("Queue was not created!\n");
    // Dar um jeito de matar o código, sem a fila, não há como continuar (ou implementar um backup que processa diretamente as coisas sem a fila)
  }
//**
  //attachInterrupt(digitalPinToInterrupt(GPIO_RADIO_INTERRUPT_PIN), parse_handler, ?FALLING?); *******************

  buzz();
}

void loop() {

}

void buzz() {
  ledcWriteTone(BUZZER_PWM_CHANNEL, BUZZER_FREQUENCY);
  delay(BUZZER_DURATION);
  ledcWriteTone(BUZZER_PWM_CHANNEL, NO_TONE_FREQUENCY);
  
  //digitalWrite(GPIO_BUZZER, HIGH);
  //delay(500);
  //digitalWrite(GPIO_BUZZER, LOW);

  #ifdef ISDEBUG
  Serial.println("BIP!\n");
  #endif
}