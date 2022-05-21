/*Board - Arduino IDE: ESP32 Dev Module*/
//#include 'biblioteca_do_radio.h'
//#define ISDEBUG 1

#define UART_INSTRUCTION_BUFFER_SIZE 3

//#define GPIO_BTN_SELECT 1
//#define GPIO_BTN_ENTER 2
//#define DEBOUNCE_TIME 50

#define GPIO_BUZZER 24
#define GPIO_RGB_LED_B 13

#define BUZZER_PWM_CHANNEL 0 //Avoid use of channels 2, 3, 10, 11, as they make use of timer 1, which is being used for other purposes. More info in: https://github.com/espressif/arduino-esp32/blob/master/cores/esp32/esp32-hal-ledc.c
#define NO_TONE_FREQUENCY 0
#define BUZZER_FREQUENCY 6000
#define BUZZER_FREQUENCY_RESOLUTION 13 //bits
#define BUZZER_DURATION 750

#define LED_TIMER_HARDWARE_NUMBER 1
#define LED_TIMER_DIVIDER 80000
#define LED_TIMER_ALARM_GENERATION_RATE 5000000 //microseconds

#define TOTAL_STATES 3
typedef enum {FSK, LoRa} radio_com_protocol;
//typedef enum {parse_obsat(), parse_Z_reduced(), parse_Z_full()} radio_collect_function;
typedef enum {O, Z} net;
typedef enum {B, BB, BBB} n_blinks;
typedef struct {
    radio_com_protocol RCP;
    //radio_collect_function RCF;
    net NET;
    n_blinks BLINKS;
} radio_configuration_state;
static const char * const radio_com_protocol_type[] = {
  [FSK] = "FSK",
  [LoRa] = "LoRa"
};

volatile radio_configuration_state selected_state;

volatile unsigned int interruptCounter;
hw_timer_t * timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

void IRAM_ATTR blink_RGB_LED() {
  portENTER_CRITICAL_ISR(&timerMux);
  switch (selected_state.BLINKS) {
    case B: {
      blink_RGB_LED_once();
    }
    case BB: {
      blink_RGB_LED_twice();
    }
    case BBB: {
      blink_RGB_LED_three_times();
    }
  }
  portEXIT_CRITICAL_ISR(&timerMux);
}

void setup() {
  char UART_configuration_instruction[UART_INSTRUCTION_BUFFER_SIZE]; //Instrução da forma ("PROTOCOLO_DO_RÁDIO"[0]+"NET")\0 - Ex: "FZ\0";
  radio_configuration_state radio_state[3];
  
  radio_state[0].RCP = FSK;
  radio_state[0].NET = O;
  radio_state[0].BLINKS = B;
  
  radio_state[1].RCP = LoRa;
  radio_state[1].NET = Z;
  radio_state[1].BLINKS = BB;
  
  radio_state[2].RCP = FSK;
  radio_state[2].NET = Z;
  radio_state[2].BLINKS = BBB;
  
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
          selected_state.RCP = radio_state[0].RCP;
          selected_state.NET = radio_state[0].NET;
          selected_state.BLINKS = radio_state[0].BLINKS;
          break;
        }
        case 'Z': {
          ///radio.config(FSK, Z);
          selected_state.RCP = radio_state[1].RCP;
          selected_state.NET = radio_state[1].NET;
          selected_state.BLINKS = radio_state[1].BLINKS;
          break;
        }
      }
      break;
    }
    case 'L': {
      ///radio.config(LoRa, Z);
      selected_state.RCP = radio_state[2].RCP;
      selected_state.NET = radio_state[2].NET;
      selected_state.BLINKS = radio_state[2].BLINKS;
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
  if(interruptCounter > 0) {
    portENTER_CRITICAL(&timerMux);
    interruptCounter--;
    portEXIT_CRITICAL(&timerMux);
  }
}

void blink_RGB_LED_once() {
  digitalWrite(GPIO_RGB_LED_B, HIGH);
  delay(750);
  digitalWrite(GPIO_RGB_LED_B, LOW);

  #ifdef ISDEBUG
  Serial.println("UM PULSO DO LED!\n");
  #endif
}

void blink_RGB_LED_twice() {
  digitalWrite(GPIO_RGB_LED_B, HIGH);
  delay(750);
  digitalWrite(GPIO_RGB_LED_B, LOW);
  delay(500);
  digitalWrite(GPIO_RGB_LED_B, HIGH);
  delay(750);
  digitalWrite(GPIO_RGB_LED_B, LOW);
  
  #ifdef ISDEBUG
  Serial.println("DOIS PULSOS DO LED!\n");
  #endif
}

void blink_RGB_LED_three_times() {
  digitalWrite(GPIO_RGB_LED_B, HIGH);
  delay(750);
  digitalWrite(GPIO_RGB_LED_B, LOW);
  delay(500);
  digitalWrite(GPIO_RGB_LED_B, HIGH);
  delay(750);
  digitalWrite(GPIO_RGB_LED_B, LOW);
  delay(500);
  digitalWrite(GPIO_RGB_LED_B, HIGH);
  delay(750);
  digitalWrite(GPIO_RGB_LED_B, LOW);

  #ifdef ISDEBUG
  Serial.println("TRÊS PULSOS DO LED!\n");
  #endif
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
