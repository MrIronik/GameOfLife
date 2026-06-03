/*
 * @file ssd1306_config.h
 *
 * @description Configuration enums
 *
 * @author Mikołaj Majewski
 * @created 31.05.26r
 *
 */

#ifndef SSD1306_CONFIG_H
#define SSD1306_CONFIG_H

#include <stdint.h>
#include "ssd1306_commands.h"

typedef struct
{
    ssd1306_cmd_t cmd;
    ssd1306_memory_mode_t mode;
} ssd1306_conf_mem_mode_t;

typedef struct
{
    ssd1306_cmd_t cmd;
    uint8_t contrast;
} ssd1306_conf_contrast_t;

typedef struct
{
    ssd1306_inverse_disp_t cmd;
} ssd1306_conf_inverse_disp_t;

typedef struct
{
    ssd1306_cmd_t cmd;
    uint8_t multiplex;
} ssd1306_conf_multiplex_t;

typedef struct
{
    ssd1306_cmd_t cmd;
    uint8_t freq_ratio; // Use SSD1306_VAL_CLK_DRATIO_FREQ(frequency, divide_ratio) to set this value
} ssd1306_conf_clock_t;

typedef struct
{
    ssd1306_conf_mem_mode_t mem_mode;

} ssd1306_config_t;

#endif /* SSD1306_CONFIG_H */