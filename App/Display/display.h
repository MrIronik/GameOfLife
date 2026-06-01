#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "ssd1306_driver.h"
#include "ssd1306_commands.h"

typedef struct 
{
    ssd1306_i2c_driver_t driver;
} display_t;

extern struct Display display_0;

// void ssd1306_i2c_write_cmd(uint8_t cmd);
display_t DISPLAY_Configure(void);

#endif /* DISPLAY_H_ */