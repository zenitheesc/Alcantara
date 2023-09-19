#include "freertos/queue.h"
#include <stdint.h>

#define N_PARTICIPANTES 4

/* OBSAT Packet - Participant data */
typedef char obc_blob_t[91];

typedef struct {
  uint8_t used_bytes;
  obc_blob_t bytes;
} queue_blob_t;

// typedef struct {
//   // packet identifier (packet count)
// #ifdef RADIOAMIGO
//   uint8_t amigo[sizeof(RADIOAMIGO) - 1];
// #endif
//   uint16_t counter;
//   obc_blob_t data;
// } __attribute__((packed)) radio_obsat_packet_values_t;
// 
// typedef union {
//   radio_obsat_packet_values_t values;
//   uint8_t raw[sizeof(radio_obsat_packet_values_t)];
// } radio_obsat_packet_t;

extern QueueHandle_t radio_queue; 
