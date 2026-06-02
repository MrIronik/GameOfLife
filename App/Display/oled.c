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

static void ssd1306_i2c_write_cmd(ssd1306_i2c_driver_t *self, uint8_t cmd)
{
    I2C_HandleTypeDef *hi2c = (I2C_HandleTypeDef *)self->i2c_handle;

    uint8_t cmd_buffer[2];

    cmd_buffer[0] = 0x00; // Control Byte
    cmd_buffer[1] = cmd;

    HAL_I2C_Master_Transmit(hi2c, self->i2c_addr, cmd_buffer, 2, HAL_MAX_DELAY);
}

static void ssd1306_i2c_write_data(ssd1306_i2c_driver_t *self, const uint8_t *data, size_t len)
{
    I2C_HandleTypeDef *hi2c = (I2C_HandleTypeDef *)self->i2c_handle;

    uint16_t buffer_size = len + 1;

    uint8_t buffer[buffer_size];
    buffer[0] = (uint8_t)SSD1306_START_LINE_BASE; // Set page address

    memcpy(&buffer[1], data, len);

    HAL_I2C_Master_Transmit(hi2c, self->i2c_addr, buffer, buffer_size, HAL_MAX_DELAY);
}

display_t DISPLAY_Configure(void)
{
    display_t display_template = {
        .driver.i2c_handle = &hi2c1,
        .driver.i2c_addr = (uint16_t)SSD1306_I2C_ADDRESS,
        .driver.i2c_write_cmd = ssd1306_i2c_write_cmd,
        .driver.i2c_write_data = ssd1306_i2c_write_data};

    memset(display_template.screen, 0, sizeof(display_template.screen));
    memset(display_template.driver.frame_buffer, 0, sizeof(display_template.driver.frame_buffer));

    return display_template;
}

void DISPLAY_Init(void)
{
    oled = DISPLAY_Configure();
    SSD1306_BasicInit(&oled.driver);
}

void DISPLAY_Write(void)
{
}

void DISPLAY_Update(void)
{
    memcpy(oled.driver.frame_buffer, oled.screen, sizeof(oled.driver.frame_buffer));

    SSD1306_Write_Display(&oled.driver);
}

static const font_char_t *FONT_Get(char c)
{
    for (uint32_t i = 0; i < sizeof(font) / sizeof(font[0]); i++)
    {
        if (font[i].c == c)
            return &font[i];
    }
    return 0;
}

static void DISPLAY_DrawChar(ssd1306_i2c_driver_t *d,
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
            if (ch->data[row] & (1 << (4 - col)))
            {
                SSD1306_Draw_Pixel(d, x + col, y + row);
            }
        }
    }
}

// void DISPLAY_Draw_GameOfLife_Title(void)
// {
//     SSD1306_Clear_Display(&oled.driver);

//     const char *text = "GAME OF LIFE";

//     uint8_t x = 10;
//     uint8_t y = 10;

//     for (uint8_t i = 0; text[i] != '\0'; i++)
//     {
//         if (text[i] == ' ')
//         {
//             x += FONT_WIDTH; // spacing
//             continue;
//         }

//         DISPLAY_DrawChar(&oled.driver, text[i], x, y);
//         x += FONT_WIDTH + 1;
//     }

//     SSD1306_Write_Display(&oled.driver);
// }

static uint8_t DISPLAY_TextWidth(const char *text)
{
    uint8_t width = 0;

    for (uint8_t i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == ' ')
            width += FONT_WIDTH; // space
        else
            width += FONT_WIDTH + 1; // char + spacing
    }

    if (width > 0)
        width -= 1; // usuń ostatni spacing

    return width;
}

static void DISPLAY_Draw_GameOfLife_Title(uint16_t frame)
{
    SSD1306_Clear_Display(&oled.driver);

    const char *text = "GAME OF LIFE";

    uint8_t text_width = DISPLAY_TextWidth(text);

    uint8_t base_x = (SSD1306_SCREEN_WIDTH - text_width) / 2;
    uint8_t base_y = (SSD1306_SCREEN_HIGHT - FONT_HEIGHT) / 2;

    for (uint8_t i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == ' ')
        {
            base_x += FONT_WIDTH;
            continue;
        }

        // -------------------------
        // 🌊 WAVE EFFECT (sin-like without float)
        // -------------------------
        int8_t wave = 0;
        {
            uint8_t t = frame + i * 6;

            // pseudo-sine using lookup trick
            static const int8_t sin_lut[16] =
                {0, 1, 2, 1, 0, -1, -2, -1, 0, 1, 2, 1, 0, -1, -2, -1};

            wave = sin_lut[t & 0x0F];
        }

        // -------------------------
        // ✨ FADE-IN EFFECT
        // -------------------------
        uint8_t appear_delay = i * 3;
        if (frame < appear_delay)
        {
            continue; // jeszcze się nie pojawił
        }

        uint8_t x = base_x;
        uint8_t y = base_y + wave;

        DISPLAY_DrawChar(&oled.driver, text[i], x, y);

        base_x += FONT_WIDTH + 1;
    }

    SSD1306_Write_Display(&oled.driver);
}

void DISPLAY_GameOfLife_Title(bool q)
{
    do {
        for (uint16_t f = 0; f < 200; f++) {

            DISPLAY_Draw_GameOfLife_Title(f);

            HAL_Delay(30);
        }
    } while (q);

    SSD1306_Clear_Display(&oled.driver);
}