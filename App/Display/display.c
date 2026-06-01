/*
 * Example of how to write adapter with STM32 HAL
 */

#include "display.h"

#include "ssd1306_driver.h"
#include "ssd1306_commands.h"

#include "i2c.h"
#include "stm32f4xx_hal.h"

#include "string.h"

static void ssd1306_i2c_write_cmd(ssd1306_i2c_driver_t *self, uint8_t cmd)
{
    I2C_HandleTypeDef *hi2c = (I2C_HandleTypeDef *) self->i2c_handle;

    uint8_t cmd_buffer[2];

    cmd_buffer[0] = 0x00; // Control Byte
    cmd_buffer[1] = cmd;

    HAL_I2C_Master_Transmit(hi2c, self->i2c_addr, cmd_buffer, 2, HAL_MAX_DELAY);
}

static void ssd1306_i2c_write_data(ssd1306_i2c_driver_t *self, const uint8_t *data, size_t len)
{
    I2C_HandleTypeDef *hi2c = (I2C_HandleTypeDef *) self->i2c_handle;

    uint16_t buffer_size = len + 1;
    
    uint8_t buffer[buffer_size];
    buffer[0] = (uint8_t)SSD1306_START_LINE_BASE;   // Set page address

    memcpy(&buffer[1], data, len);

    HAL_I2C_Master_Transmit(hi2c, self->i2c_addr, buffer, buffer_size, HAL_MAX_DELAY);
}

display_t DISPLAY_Configure(void) {
    display_t display_template = {
    .driver.i2c_handle = &hi2c1,
    .driver.i2c_addr = (uint16_t)SSD1306_I2C_ADDRESS,
    .driver.i2c_write_cmd = ssd1306_i2c_write_cmd,
    .driver.i2c_write_data = ssd1306_i2c_write_data};

    memset(display_template.driver.frame_buffer, 0, sizeof(display_template.driver.frame_buffer));

    return display_template;
}