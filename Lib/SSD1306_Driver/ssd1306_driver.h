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

typedef enum
{
  SSD1306_INIT_OK,
  SSD1306_INIT_FAIL
} ssd1306_error_t;

typedef struct ssd1306_i2c_driver
{
  void *i2c_handle;
  uint16_t i2c_addr;
  uint8_t frame_buffer[SSD1306_PAGE_SIZE][SSD1306_SCREEN_WIDTH];
  void (*i2c_write_cmd)(struct ssd1306_i2c_driver *self, uint8_t cmd);
  void (*i2c_write_data)(struct ssd1306_i2c_driver *self, const uint8_t *data, size_t len);
} ssd1306_i2c_driver_t;

ssd1306_error_t SSD1306_BasicInit(ssd1306_i2c_driver_t *driver);

void SSD1306_Draw_Pixel(ssd1306_i2c_driver_t *driver, uint8_t xpos, uint8_t ypos);
void SSD1306_Write_Display(ssd1306_i2c_driver_t *driver);

#endif /* SSD1306_DRIVER_H_ */