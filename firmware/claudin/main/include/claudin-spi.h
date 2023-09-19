#include "driver/spi_master.h"
#include "esp_log.h"

#define GPIO_RADIO_DIO_0 	26
#define GPIO_RADIO_DIO_1 	35

#define GPIO_RADIO_NRST 	16

#define GPIO_RADIO_SS 		18
#define VSPI_MISO 		19
#define VSPI_MOSI 		27 
#define VSPI_SCLK 		5

static const char *spi = "spi";

esp_err_t spi_add_device(spi_device_handle_t* spi_bus, uint32_t spi_clk);
esp_err_t spi_init();
esp_err_t spi_read_buffer(spi_device_handle_t spi_bus,uint8_t reg_addr,uint8_t* pvalue,uint16_t len);
esp_err_t spi_read_register(spi_device_handle_t spi_bus,uint8_t reg_addr,uint8_t* pvalue);
esp_err_t spi_write_buffer(spi_device_handle_t spi_bus,uint8_t reg_addr,uint8_t* pvalue,uint16_t len);
esp_err_t spi_write_register(spi_device_handle_t spi_bus,uint8_t reg_addr,uint8_t pvalue);
esp_err_t test_register(spi_device_handle_t spi_bus);
