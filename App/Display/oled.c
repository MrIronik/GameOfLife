/*
 * Example of how to write adapter with STM32 HAL
 */

#include "oled.h"

#include "ssd1306_driver.h"
#include "ssd1306_commands.h"

#include "i2c.h"
#include "stm32f4xx_hal.h"

#include "string.h"

#include "font.h"

#include <stdbool.h>

static display_t oled;

static void ssd1306_write_cmd(ssd1306_driver_t *self, uint8_t cmd)
{
    I2C_HandleTypeDef *hi2c = (I2C_HandleTypeDef *)self->protocol_handle;

    uint8_t cmd_buffer[2];

    cmd_buffer[0] = 0x00; // Control Byte
    cmd_buffer[1] = cmd;

    HAL_I2C_Master_Transmit(hi2c, self->i2c_addr, cmd_buffer, 2, HAL_MAX_DELAY);
}

static void ssd1306_write_data(ssd1306_driver_t *self, const uint8_t *data, size_t len)
{
    I2C_HandleTypeDef *hi2c = (I2C_HandleTypeDef *)self->protocol_handle;

    uint16_t buffer_size = len + 1;

    uint8_t buffer[buffer_size];
    buffer[0] = (uint8_t)SSD1306_START_LINE_BASE; // Set page address

    memcpy(&buffer[1], data, len);

    HAL_I2C_Master_Transmit(hi2c, self->i2c_addr, buffer, buffer_size, HAL_MAX_DELAY);
}

display_t DISPLAY_Configure(void)
{
    display_t display_template = {
        .driver.protocol_handle = &hi2c1,
        .driver.i2c_addr = (uint16_t)SSD1306_I2C_ADDRESS,
        .driver.write_cmd = ssd1306_write_cmd,
        .driver.write_data = ssd1306_write_data};

    memset(display_template.screen, 0, sizeof(display_template.screen));
    memset(display_template.driver.frame_buffer, 0, sizeof(display_template.driver.frame_buffer));

    return display_template;
}

void DISPLAY_Init(void)
{
    oled = DISPLAY_Configure();
    SSD1306_BasicInit(&oled.driver);
}

void DISPLAY_Write(uint8_t *screen)
{
    memcpy(oled.screen, screen, sizeof(oled.screen));
}

void DISPLAY_Clear(void)
{
    SSD1306_Clear_Display(&oled.driver);
}

void DISPLAY_Update(void)
{
    memcpy(oled.driver.frame_buffer, oled.screen, sizeof(oled.driver.frame_buffer));

    SSD1306_Write_Display(&oled.driver);
}

/* Title Screen Draw Functions */
// TODO: Add GFX

static const font_char_t *FONT_Get(char c)
{
    static const uint32_t font_size = sizeof(font) / sizeof(font[0]);

    for (uint32_t i = 0; i < font_size; i++)
    {
        if (font[i].c == c)
        {
            return &font[i];
        }
    }

    return 0; // znak nieobsługiwany
}

static void DISPLAY_DrawChar(ssd1306_driver_t *d,
                             char c,
                             uint8_t x,
                             uint8_t y)
{
    const font_char_t *ch = FONT_Get(c);
    if (!ch)
        return;

    for (uint8_t row = 0; row < FONT_HEIGHT; row++)
    {
        for (uint8_t col = 0; col < FONT_WIDTH; col++)
        {
            // FIX: MSB -> LSB mapping
            if (ch->data[row] & (1 << (FONT_WIDTH - 1 - col)))
            {
                SSD1306_Draw_Pixel(d, x + col, y + row);
            }
        }
    }
}

void DISPLAY_TitleScreen(void)
{
    const char *title = "GAME OF LIFE";
    // const char *subtitle = "PRESS BUTTON TO START";

    // -------------------------
    // TITLE
    // -------------------------
    uint8_t x = 10;
    uint8_t y = 20;

    for (uint8_t i = 0; title[i] != '\0'; i++)
    {
        if (title[i] != ' ')
            DISPLAY_DrawChar(&oled.driver, title[i], x, y);

        x += FONT_WIDTH + 1;
    }

    // -------------------------
    // SUBTITLE
    // -------------------------
    x = 0;
    y = 40;

    // for (uint8_t i = 0; subtitle[i] != '\0'; i++)
    // {
    //     if (subtitle[i] != ' ')
    //         DISPLAY_DrawChar(&oled.driver, subtitle[i], x, y);

    //     x += FONT_WIDTH + 1;
    // }

    SSD1306_Write_Display(&oled.driver);
}