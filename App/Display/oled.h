#ifndef OLED_H_
#define OLED_H_

#include "ssd1306_driver.h"
#include "ssd1306_commands.h"

#include <stdbool.h>

typedef struct
{
    uint8_t screen[SSD1306_PAGE_SIZE][SSD1306_SCREEN_WIDTH];
    ssd1306_i2c_driver_t driver;
} display_t;

void DISPLAY_Init(void);
void DISPLAY_GameOfLife_Title(bool q);

#endif /* OLED_H_ */