/*Board - Arduino IDE: ESP32 Dev Module*/
//#include 'biblioteca_do_radio.h'
//#define ISDEBUG 1

#include "FS.h"
#include "SD.h"
#include "SPI.h"
#define SD_CARD_CS 5
#define SD_CARD_ERROR_INSTRUCTION_BUFFER_SIZE 2
#define SD_CARD_ERROR_INSTRUCTION_INPUT_DURATION 7000
volatile bool ignore_SD_CARD = false;
enum class SD_CARD_ERROR_CODES {
  SD_CARD_NOT_MOUNTED,
  SD_CARD_TYPE_NONE,
  SD_CARD_BEGIN_FAIL,
  FS_FAIL_FILE_OPEN_WRITE,
  FS_FAIL_FILE_OPEN_APPEND
};
using SD_CARD_error_t = uint8_t;

#define UART_INSTRUCTION_BUFFER_SIZE 3

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
//typedef enum {parse_obsat(), parse_Z_reduced(), parse_Z_full()} radio_parse_function_t;
typedef enum {OBSAT, ZENITH} net_t;
typedef enum {SINGLE_BLINK, DOUBLE_BLINK, TRIPLE_BLINK} n_blinks_t;
typedef struct {
    radio_com_protocol_t comunication_protocol;
    //radio_parse_function_t parse_function;
    net_t radio_net;
    n_blinks_t led_blinks;
} radio_configuration_state_t;
static const char * const radio_com_protocol_type[] = {
  [FSK] = "FSK",
  [LoRa] = "LoRa"
};

volatile radio_configuration_state_t g_selected_state;

volatile unsigned int g_interruptCounter;
hw_timer_t * timer = nullptr;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

void IRAM_ATTR blink_RGB_LED() {
  portENTER_CRITICAL_ISR(&timerMux);
  for (int i = 0; i <= g_selected_state.led_blinks; i++) {
    digitalWrite(GPIO_RGB_LED_B, HIGH);
    delay(750);
    digitalWrite(GPIO_RGB_LED_B, LOW);
    delay(500);
  }

  #ifdef ISDEBUG
  Serial.println("%d PULSOS DO LED!\n", (g_selected_state.led_blinks + 1));
  #endif
  
  portEXIT_CRITICAL_ISR(&timerMux);
}

void setup() {
  char UART_configuration_instruction[UART_INSTRUCTION_BUFFER_SIZE]; //Instrução da forma ("PROTOCOLO_DO_RÁDIO"[0]+"NET")\0 - Ex: "FZ\0";
  radio_configuration_state_t radio_state[3] = {{.comunication_protocol = FSK, .radio_net = OBSAT, .led_blinks = SINGLE_BLINK},
                                                {.comunication_protocol = LoRa, .radio_net = ZENITH, .led_blinks = DOUBLE_BLINK},
                                                {.comunication_protocol = FSK, .radio_net = ZENITH, .led_blinks = TRIPLE_BLINK}};
  
  Serial.begin(115200);
  Serial.println("Comunicação SERIAL estabelecida!\n");
  
  //Iniciar o Rádio
  //Serial.println("Rádio Iniciado!\n");

  if(!SD.begin(SD_CARD_CS)) {
    SD_CARD_error_handler((SD_CARD_error_t) SD_CARD_ERROR_CODES::SD_CARD_NOT_MOUNTED);
  }
  if (!ignore_SD_CARD) {
    uint8_t cardType = SD.cardType();
    if(cardType == CARD_NONE) {
      SD_CARD_error_handler((SD_CARD_error_t) SD_CARD_ERROR_CODES::SD_CARD_TYPE_NONE);
    }
    if (!ignore_SD_CARD) {
      Serial.println("Iniciando cartão SD...s\n");
      if(!SD.begin(SD_CARD_CS)) {
        SD_CARD_error_handler((SD_CARD_error_t) SD_CARD_ERROR_CODES::SD_CARD_BEGIN_FAIL);
      }
      if (!ignore_SD_CARD) {
        Serial.println("Cartão SD corretamente configurado!\n");
      } else {
        Serial.println("Cartão SD não configurado! Envio de dados da Alcântara exclusivamente via UART!\n");
      }
    } else {
      Serial.println("Cartão SD não configurado! Envio de dados da Alcântara exclusivamente via UART!\n");
    }
  } else {
    Serial.println("Cartão SD não configurado! Envio de dados da Alcântara exclusivamente via UART!\n");
  }

  if (!ignore_SD_CARD) {
    File file = SD.open("data.txt");
    if (!file) {
      Serial.println("O arquivo 'data.txt' não existe. Criando arquivo...!\n");
      writeFile(SD, "data.txt", "Dados Recebidos da Sonda:\r\n");
    } else {
      Serial.println("O arquivo 'data.txt' já existe!\n");
    }
    file.close();
  }

  //pinMode(GPIO_BTN_SELECT, INPUT);
  //pinMode(GPIO_BTN_ENTER, INPUT);
  pinMode(GPIO_BUZZER, OUTPUT);
  pinMode(GPIO_RGB_LED_B, OUTPUT);
  Serial.println("Modo dos pinos definidos!\n");

  //The function above will be used to vinculate the buzzer pin with one of the PWM channel, in order to generate the waveform needed
  ledcSetup(GPIO_BUZZER, BUZZER_FREQUENCY, BUZZER_FREQUENCY_RESOLUTION);
  ledcAttachPin(GPIO_BUZZER, BUZZER_PWM_CHANNEL);
  Serial.println("Canal PWM do buzzer configurado!\n");

  //Recebe configuração via UART
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

  buzz();

  timer = timerBegin(LED_TIMER_HARDWARE_NUMBER, LED_TIMER_DIVIDER, true);
  timerAttachInterrupt(timer, &blink_RGB_LED, true);
  timerAlarmWrite(timer, LED_TIMER_ALARM_GENERATION_RATE, true);
  timerAlarmEnable(timer);
  Serial.println("Timer do LED configurado!\n");
}

void loop() {
  if(g_interruptCounter > 0) {
    portENTER_CRITICAL(&timerMux);
    g_interruptCounter--;
    portEXIT_CRITICAL(&timerMux);
  }
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

void SD_CARD_error_handler(SD_CARD_error_t err) {
  char SD_CARD_error_instruction[SD_CARD_ERROR_INSTRUCTION_BUFFER_SIZE]; //Instrução da forma: "Y\0", "S\0", ou "N\0";
  
  switch (err) {
    case (SD_CARD_error_t) SD_CARD_ERROR_CODES::SD_CARD_NOT_MOUNTED: {
      Serial.println("Falha na montagem do cartão SD!\n");
      break;
    }
    case (SD_CARD_error_t) SD_CARD_ERROR_CODES::SD_CARD_TYPE_NONE: {
      Serial.println("Nenhum cartão SD foi inserido!\n");
      break;
    }
    case (SD_CARD_error_t) SD_CARD_ERROR_CODES::SD_CARD_BEGIN_FAIL: {
      Serial.println("Falha na inicialização do cartão SD!\n");
      break;
    }
  }

  if (err == (SD_CARD_error_t) SD_CARD_ERROR_CODES::FS_FAIL_FILE_OPEN_WRITE || err == (SD_CARD_error_t) SD_CARD_ERROR_CODES::FS_FAIL_FILE_OPEN_APPEND) {
    switch (err) {
      case (SD_CARD_error_t) SD_CARD_ERROR_CODES::FS_FAIL_FILE_OPEN_WRITE: {
        Serial.println("Falha na abertura do arquivo para operação de escrita!\n");
        break;
      }
      case (SD_CARD_error_t) SD_CARD_ERROR_CODES::FS_FAIL_FILE_OPEN_APPEND: {
        Serial.println("Falha na abertura do arquivo para operação de concatenamento!\n");
        break;
      }
    }
  } else {
    Serial.println("Deseja prosseguir com a inicialização do sistema? (Y/N)(S/N)\n");
    Serial.println("Aviso: o sistema somente enviará dados via UART caso seja inicializado!\n");
    Serial.println("(Y/S/N) - ");
    delay(SD_CARD_ERROR_INSTRUCTION_INPUT_DURATION);
    if (Serial.available() > 0) {
      Serial.readBytes(SD_CARD_error_instruction, SD_CARD_ERROR_INSTRUCTION_BUFFER_SIZE);
    }
    if (SD_CARD_error_instruction[0] == 'Y' || SD_CARD_error_instruction[0] == 'S') {
      Serial.println("Prosseguindo com a inicialização do sistema!\n");
      ignore_SD_CARD = true;
    } else if (SD_CARD_error_instruction[0] == 'N') {
      Serial.println("Encerrando...!\n");
      exit(0);
    } else {
      Serial.println("Instrução não compreendida, prosseguindo com a inicialização!\n");
      ignore_SD_CARD = true;
    }
  }
}

void writeFile(fs::FS &fs, const char *path, const char *message) {
  #ifdef ISDEBUG
  Serial.printf("Writing file: %s\n", path);
  #endif

  File file = fs.open(path, FILE_WRITE);
  if(!file) {
    #ifdef ISDEBUG
    Serial.println("Failed to open file for writing!\n");
    #endif
    SD_CARD_error_handler((SD_CARD_error_t) SD_CARD_ERROR_CODES::FS_FAIL_FILE_OPEN_WRITE);
  }
  if (file.print(message)) {
    #ifdef ISDEBUG
    Serial.println("File written!\n");
    #endif
  } else {
    #ifdef ISDEBUG
    Serial.println("Write failed!\n");
    #endif
  }
  file.close();
}

void appendFile(fs::FS &fs, const char *path, const char *message) {
  #ifdef ISDEBUG
  Serial.printf("Appending to file: %s\n", path);
  #endif

  File file = fs.open(path, FILE_APPEND);
  if(!file) {
    #ifdef ISDEBUG
    Serial.println("Failed to open file for appending!\n");
    #endif
    SD_CARD_error_handler((SD_CARD_error_t) SD_CARD_ERROR_CODES::FS_FAIL_FILE_OPEN_APPEND);
  }
  if (file.print(message)) {
    #ifdef ISDEBUG
    Serial.println("Message appended!\n");
    #endif
  } else {
    #ifdef ISDEBUG
    Serial.println("Append failed!\n");
    #endif
  }
  file.close();
}
