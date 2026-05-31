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
// #include <stdio.h>

/* Importent SSD1306 settings */
#define SSD1306_SCREEN_HIGHT 128
#define SSD1306_SCREEN_WIDTH 64

#define SSD1306_I2C_ADDRESS 0x78

typedef enum { SSD1306_INIT_OK, SSD1306_INIT_FAIL } ssd1306_error_t;

typedef struct {
    void (*write_cmd) (uint8_t cmd);
    void (*write_data) (const uint8_t *data, int len);
} ssd1306_io_t;

ssd1306_error_t SSD1306_Init(void);

#endif /* SSD1306_DRIVER_H_ */
