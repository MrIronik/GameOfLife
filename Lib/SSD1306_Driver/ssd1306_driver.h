/*
 * @file ssd1306_driver.h
 *
 * @description Simple driver for SSD1306 oled screen
 *
 * @author Mikołaj Majewski
 * @created 31.05.26r
 *
 */

#ifndef SSD1306_DRIVER_H_
#define SSD1306_DRIVER_H_

#include <stdint.h>
#include <stdio.h>

/* Importent SSD1306 settings */
#define SSD1306_SCREEN_HIGHT 64
#define SSD1306_SCREEN_WIDTH 128

#define SSD1306_I2C_ADDRESS 0x78

#define SSD1306_PAGE_SIZE 8

/* Error Handle enums */

typedef enum
{
  SSD1306_INIT_OK,
  SSD1306_INIT_FAIL
} ssd1306_error_t;

typedef enum
{
  SSD1306_CLOCK_OK,
  SSD1306_CLOCK_FAIL,
} ssd1306_config_clock_error_t;

typedef enum
{
  SSD1306_MULTIPLEXER_OK,
  SSD1306_MULTIPLEXER_FAIL
} ssd1306_config_multiplexer_error_t;

typedef enum
{
  SSD1306_OFFSET_OK,
  SSD1306_OFFSET_FAIL
} ssd1306_config_offset_error_t;

typedef enum
{
  SSD1306_CHARGEPUMP_OK,
  SSD1306_CHARGEPUMP_FAIL
} ssd1306_config_chargepump_error_t;

typedef enum
{
  SSD1306_MEMORYMODE_OK,
  SSD1306_MEMORYMODE_FAIL
} ssd1306_config_mem_mode_error_t;

typedef enum
{
  SSD1306_MAPPING_OK,
  SSD1306_MAPPING_FAIL
} ssd1306_config_mapping_error_t;

typedef enum
{
  SSD1306_COM_SCAN_OK,
  SSD1306_COM_SCAN_FAIL
} ssd1306_config_com_scan_error_t;

typedef enum
{
  SSD1306_COM_PINS_OK,
  SSD1306_COM_PINS_FAIL
} ssd1306_config_com_pins_error_t;

typedef enum
{
  SSD1306_CONTRAST_OK,
  SSD1306_CONTRAST_FAIL
} ssd1306_config_contrast_error_t;

typedef enum
{
  SSD1306_PRECHARGE_OK,
  SSD1306_PRECHARGE_FAIL
} ssd1306_config_precharge_error_t;

typedef enum
{
  SSD1306_VOLTAGE_OK,
  SSD1306_VOLTAGE_FAIL
} ssd1306_config_voltage_error_t;

typedef enum
{
  SSD1306_INVERSE_OK,
  SSD1306_INVERSE_FAIL
} ssd1306_config_inverse_error_t;

typedef struct ssd1306_i2c_driver
{
  void *i2c_handle;
  uint16_t i2c_addr;
  uint8_t frame_buffer[SSD1306_PAGE_SIZE][SSD1306_SCREEN_WIDTH];
  void (*i2c_write_cmd)(struct ssd1306_i2c_driver *self, uint8_t cmd);
  void (*i2c_write_data)(struct ssd1306_i2c_driver *self, const uint8_t *data, size_t len);
} ssd1306_i2c_driver_t;

ssd1306_error_t SSD1306_BasicInit(ssd1306_i2c_driver_t *driver);
void SSD1306_Display_OnOff(ssd1306_i2c_driver_t *driver, uint8_t state);

void SSD1306_Draw_Pixel(ssd1306_i2c_driver_t *driver, uint8_t xpos, uint8_t ypos);
void SSD1306_Write_Display(ssd1306_i2c_driver_t *driver);
void SSD1306_Clear_Display(ssd1306_i2c_driver_t *driver);

#endif /* SSD1306_DRIVER_H_ */