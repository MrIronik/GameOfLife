/*
 * @file ssd1306_commands.h
 *
 * @description All commands to handle SSD1306 oled screen
 *
 * @author Mikołaj Majewski
 * @created 31.05.26r
 *
 */

#ifndef SSD1306_COMMANDS_H_
#define SSD1306_COMMANDS_H_

// TODO: Make Pages Handle Macros

// Only if SSD1306_CMD_SET_MEMORY_MODE is set to page
#define SSD1306_CMD_SET_PAGE_START_ADDR(page) (0xB0 | ((page) & 0x07))

// SSD1306_CMD_SET_CLOCK_DIVIDE_RATIO Value
#define SSD1306_VAL_CLK_DRATIO_FREQ(divide_ratio, frequency)                   \
  ((divide_ratio & 0x0F) | ((frequency & 0x0F) << 4))

#define SSD1306_START_LINE_BASE 0x40

#define SSD1306_COLUMN_LOWER_BASE 0x00
#define SSD1306_COLUMN_HIGHER_BASE 0x10

// SSD1306 COMMANDS
typedef enum {
  SSD1306_CMD_SET_MEMORY_MODE = 0x20,
  SSD1306_CMD_SET_COLUMN_ADDRESS = 0x21,
  SSD1306_CMD_SET_PAGE_ADDRESS = 0x22,
  SSD1306_CMD_SET_CONTRAST = 0x81,           // Value 0-255
  SSD1306_CMD_ENTIRE_ON = 0xA5,              // Entire screen printed
  SSD1306_CMD_ENTIRE_OFF = 0xA4,             // Entire screen cleared
  SSD1306_CMD_NORMAL_DISPLAY = 0xA6,         // Normal colors
  SSD1306_CMD_INVERSE_DISPLAY = 0xA7,        // Negative colors
  SSD1306_CMD_SET_MULTIPLEX = 0xA8,          // Value 16-63
  SSD1306_CMD_DISPLAY_OFF = 0xAE,            // Sleep
  SSD1306_CMD_DISPLAY_ON = 0xAF,             // Normal mode
  SSD1306_CMD_SET_DISPLAY_OFFSET = 0xD3,     // Check Table 10-1 in DOCs
  SSD1306_CMD_SET_CLOCK_DIVIDE_RATIO = 0xD5, // Could help with refreshing bugs
  SSD1306_CMD_SET_PRECHARGE_PERIOD = 0xD9,
  SSD1306_CMD_SET_CON_PIN_HW_CONF = 0xDA, // Check Table 10-3 in DOCs
  SSD1306_CMD_SET_V_COMH_DESELECT_LVL = 0xDB,
  SSD1306_CMD_NOP = 0xE3,
  SSD1306_CMD_SET_HORIZONTAL_SCROLL_RIGHT = 0x26,
  SSD1306_CMD_SET_HORIZONTAL_SCROLL_LEFT = 0x27,
  SSD1306_CMD_SET_HORIZONTAL_SCROLL_OFF = 0x2E,
  SSD1306_CMD_SET_HORIZONTAL_SCROLL_ON = 0x2F,
  // TODO: Split to separate enums, add continous scroll
  SSD1306_CMD_SET_CHARGE_PUMP = 0x8D // Init charge pump
} ssd1306_cmd_t;

typedef enum {
  SSD1306_SEGMENT_NORMAL = 0xA0,
  SSD1306_SEGMENT_REMAP = 0xA1
} ssd1306_mapping_t;

typedef enum {
  SSD1306_COM_SCAN_NORMAL = 0xC0,
  SSD1306_COM_SCAN_REMAPPED = 0xC8
} ssd1306_com_scan_t;

// SSD1306_CMD_SET_MEMORY_MODE values
typedef enum {
  SSD1306_ADDR_MODE_HORIZONTAL = 0x00,
  SSD1306_ADDR_MODE_VERTICAL = 0x01,
  SSD1306_ADDR_MODE_PAGE = 0x02
} ssd1306_address_mode_t;

// SSD1306_CMD_SET_CHARGE_PUMP values
typedef enum {
  SSD1306_CHARGE_PUMP_OFF = 0x10, // Enable charge pump
  SSD1306_CHARGE_PUMP_ON = 0x14   // Enable charge pump
} ssd1306_charge_pump_mode_t;

#endif /* SSD1306_COMMANDS_H_ */
