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

#include "string.h"

ssd1306_error_t SSD1306_BasicInit(ssd1306_i2c_driver_t *driver)
{
  driver->i2c_write_cmd(driver, 0xAE); // display OFF
  driver->i2c_write_cmd(driver, 0xD5); // clock
  driver->i2c_write_cmd(driver, 0x80);

  driver->i2c_write_cmd(driver, 0xA8); // multiplex
  driver->i2c_write_cmd(driver, 0x3F);

  driver->i2c_write_cmd(driver, 0xD3); // display offset
  driver->i2c_write_cmd(driver, 0x00);

  driver->i2c_write_cmd(driver, 0x40); // start line = 0

  driver->i2c_write_cmd(driver, 0x8D); // charge pump
  driver->i2c_write_cmd(driver, 0x14); // ENABLE

  driver->i2c_write_cmd(driver, 0x20); // memory mode
  driver->i2c_write_cmd(driver, 0x00); // horizontal

  driver->i2c_write_cmd(driver, 0xA1); // segment remap

  driver->i2c_write_cmd(driver, 0xC8); // COM scan dec

  driver->i2c_write_cmd(driver, 0xDA); // COM pins
  driver->i2c_write_cmd(driver, 0x12);

  driver->i2c_write_cmd(driver, 0x81); // contrast
  driver->i2c_write_cmd(driver, 0x7F);

  driver->i2c_write_cmd(driver, 0xD9); // precharge
  driver->i2c_write_cmd(driver, 0xF1);

  driver->i2c_write_cmd(driver, 0xDB); // VCOMH
  driver->i2c_write_cmd(driver, 0x40);

  driver->i2c_write_cmd(driver, 0xA4); // resume RAM
  driver->i2c_write_cmd(driver, 0xA6); // normal display

  driver->i2c_write_cmd(driver, 0xAF); // display ON

  // Reset Display

  driver->i2c_write_cmd(driver, 0x21); // column address
  driver->i2c_write_cmd(driver, 0);
  driver->i2c_write_cmd(driver, 127);

  driver->i2c_write_cmd(driver, 0x22); // page address
  driver->i2c_write_cmd(driver, 0);
  driver->i2c_write_cmd(driver, 7);

  uint8_t buf[129];

  buf[0] = 0x40; // data

  memset(&buf[1], 0x00, 128);

  for (int page = 0; page < 8; page++)
  {
    driver->i2c_write_data(driver, (const uint8_t *)buf, sizeof(buf));
  }

  return SSD1306_INIT_OK;
}

void SSD1306_Draw_Pixel(ssd1306_i2c_driver_t *driver, uint8_t xpos, uint8_t ypos)
{
  if (xpos >= SSD1306_SCREEN_WIDTH)
    return; // TODO: Add Error Handle
  if (ypos >= SSD1306_SCREEN_HIGHT)
    return; // TODO: Add Error Handle

  uint8_t page_number = ypos / SSD1306_PAGE_SIZE;
  uint8_t bit_y = 1 << (ypos % SSD1306_PAGE_SIZE);

  driver->frame_buffer[page_number][xpos] = bit_y;
}

void SSD1306_Write_Display(ssd1306_i2c_driver_t *driver)
{
  driver->i2c_write_data(driver,
                         (const uint8_t *)driver->frame_buffer,
                         sizeof(driver->frame_buffer));
}