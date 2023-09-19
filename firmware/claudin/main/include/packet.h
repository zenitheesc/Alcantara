#include <stdint.h>
/* OBSAT Packet - Participant data */
typedef uint8_t obc_blob_t[91];

typedef struct {
  // packet identifier (packet count)
#ifdef RADIOAMIGO
  uint8_t amigo[sizeof(RADIOAMIGO) - 1];
#endif
  uint16_t counter;
  obc_blob_t data;
} __attribute__((packed)) radio_obsat_packet_values_t;

typedef union {
  radio_obsat_packet_values_t values;
  uint8_t raw[sizeof(radio_obsat_packet_values_t)];
} radio_obsat_packet_t;
