/*
 * @file ssd1306_driver.c
 *
 * @description Simple driver for SSD1306 oled screen
 *
 * @author Mikołaj Majewski
 * @created 31.05.26r
 *
 */

#include "ssd1306_driver.h"
#include "ssd1306_commands.h"

ssd1306_error_t SSD1306_Init(void) {
  // ssd1306_write_cmd(0xAE); // display OFF
  // ssd1306_write_cmd(0xD5); // clock
  // ssd1306_write_cmd(0x80);

  // ssd1306_write_cmd(0xA8); // multiplex
  // ssd1306_write_cmd(0x3F);

  // ssd1306_write_cmd(0xD3); // display offset
  // ssd1306_write_cmd(0x00);

  // ssd1306_write_cmd(0x40); // start line = 0

  // ssd1306_write_cmd(0x8D); // charge pump
  // ssd1306_write_cmd(0x14); // ENABLE

  // ssd1306_write_cmd(0x20); // memory mode
  // ssd1306_write_cmd(0x00); // horizontal

  // ssd1306_write_cmd(0xA1); // segment remap

  // ssd1306_write_cmd(0xC8); // COM scan dec

  // ssd1306_write_cmd(0xDA); // COM pins
  // ssd1306_write_cmd(0x12);

  // ssd1306_write_cmd(0x81); // contrast
  // ssd1306_write_cmd(0x7F);

  // ssd1306_write_cmd(0xD9); // precharge
  // ssd1306_write_cmd(0xF1);

  // ssd1306_write_cmd(0xDB); // VCOMH
  // ssd1306_write_cmd(0x40);

  // ssd1306_write_cmd(0xA4); // resume RAM
  // ssd1306_write_cmd(0xA6); // normal display

  // ssd1306_write_cmd(0xAF); // display ON
  return SSD1306_INIT_OK;
}
