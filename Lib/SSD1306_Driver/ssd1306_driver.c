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

#include <math.h>

static ssd1306_config_clock_error_t SSD1306_Configure_Clock(ssd1306_i2c_driver_t *driver,
                                                            uint8_t clock_config);
static ssd1306_config_multiplexer_error_t SSD1306_Configure_Multiplex(ssd1306_i2c_driver_t *driver);
static ssd1306_config_offset_error_t SSD1306_Configure_Offset(ssd1306_i2c_driver_t *driver, uint8_t offset);
static ssd1306_config_chargepump_error_t SSD1306_Configure_ChargePump(ssd1306_i2c_driver_t *driver,
                                                                      ssd1306_charge_pump_mode_t mode);
static ssd1306_config_mem_mode_error_t SSD1306_Configure_MemoryMode(ssd1306_i2c_driver_t *driver,
                                                                    ssd1306_memory_mode_t mode);
static ssd1306_config_mapping_error_t SSD1306_Config_Mapping(ssd1306_i2c_driver_t *driver,
                                                             ssd1306_mapping_t mode);
static ssd1306_config_com_scan_error_t SSD1306_Config_ComScanDec(ssd1306_i2c_driver_t *driver,
                                                                 ssd1306_com_scan_t mode);
static ssd1306_config_com_pins_error_t SSD1306_Config_ComPins(ssd1306_i2c_driver_t *driver,
                                                              uint8_t pins);
static ssd1306_config_contrast_error_t SSD1306_Config_Contrast(ssd1306_i2c_driver_t *driver,
                                                               uint8_t contrast);
static ssd1306_config_precharge_error_t SSD1306_Config_Precharge(ssd1306_i2c_driver_t *driver);
static ssd1306_config_voltage_error_t SSD1306_Config_Voltage(ssd1306_i2c_driver_t *driver);
static ssd1306_config_inverse_error_t SSD1306_Config_Inverse(ssd1306_i2c_driver_t *driver,
                                                             uint8_t mode);

ssd1306_error_t SSD1306_BasicInit(ssd1306_i2c_driver_t *driver)
{
  SSD1306_Display_OnOff(driver, SSD1306_DISPLAY_DISABLE);

  SSD1306_Configure_Clock(driver, SSD1306_VAL_CLK_DRATIO_FREQ(0x0, 0xF));

  SSD1306_Configure_Multiplex(driver);

  SSD1306_Configure_Offset(driver, 0);

  driver->i2c_write_cmd(driver, 0x40); // start line = 0

  SSD1306_Configure_ChargePump(driver, SSD1306_CHARGE_PUMP_ON);

  SSD1306_Configure_MemoryMode(driver, SSD1306_MEM_MODE_HORIZONTAL);

  SSD1306_Config_Mapping(driver, SSD1306_SEGMENT_REMAP);

  SSD1306_Config_ComScanDec(driver, SSD1306_COM_SCAN_REMAPPED);

  SSD1306_Config_ComPins(driver, 0x12); // TODO: Handle Number correctly

  SSD1306_Config_Contrast(driver, 127);

  SSD1306_Config_Precharge(driver);

  SSD1306_Config_Voltage(driver);

  SSD1306_Clear_Display(driver);   // Clear BUFFOR

  driver->i2c_write_cmd(driver, 0xA4); // resume RAM

  SSD1306_Config_Inverse(driver, SSD1306_INVERSE_DISABLE);

  SSD1306_Display_OnOff(driver, SSD1306_DISPLAY_ENABLE);

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

  driver->frame_buffer[page_number][xpos] |= bit_y;
}

void SSD1306_Write_Display(ssd1306_i2c_driver_t *driver)
{
  // TODO: Make this normal lol struct with config etc
  // uint8_t cmd[3];

  // cmd[0] = (uint8_t)SSD1306_CMD_SET_PAGE_ADDRESS;
  // cmd[1] = 0x00;  // First Page Addr
  // cmd[2] = 0x07;  // Last Page Addr

  // for (size_t i = 0; i < sizeof(cmd); i++) {
  //   driver->i2c_write_cmd(driver, cmd[i]);
  // }

  driver->i2c_write_data(driver,
                         (const uint8_t *)driver->frame_buffer,
                         sizeof(driver->frame_buffer));
}

void SSD1306_Write_Page(ssd1306_i2c_driver_t *driver)
{
  // TODO: Implement this
}

void SSD1306_Clear_Display(ssd1306_i2c_driver_t *driver)
{
  memset(driver->frame_buffer, 0, sizeof(driver->frame_buffer));

  SSD1306_Write_Display(driver);
}

/*
 * @brief Function for clock configuration, should be called in Init func
 *
 * @param clock_config value, should be passed for SSD1306_VAL_CLK_DRATIO_FREQ macro
 */
static ssd1306_config_clock_error_t SSD1306_Configure_Clock(ssd1306_i2c_driver_t *driver,
                                                            uint8_t clock_config)
{
  uint8_t cmd[2];

  cmd[0] = (uint8_t)SSD1306_CMD_SET_CLOCK_DIVIDE_RATIO; // Get to clock config
  cmd[1] = clock_config;                                // Pass clock config value

  for (size_t i = 0; i < sizeof(cmd); i++)
  {
    driver->i2c_write_cmd(driver, cmd[i]);
  }

  return SSD1306_CLOCK_OK;
}

static ssd1306_config_multiplexer_error_t SSD1306_Configure_Multiplex(ssd1306_i2c_driver_t *driver)
{
  uint8_t cmd[2];

  cmd[0] = (uint8_t)SSD1306_CMD_SET_MULTIPLEX;
  cmd[1] = (uint8_t)SSD1306_SCREEN_HIGHT - 1;

  for (size_t i = 0; i < sizeof(cmd); i++)
  {
    driver->i2c_write_cmd(driver, cmd[i]);
  }

  return SSD1306_MULTIPLEXER_OK;
}

static ssd1306_config_offset_error_t SSD1306_Configure_Offset(ssd1306_i2c_driver_t *driver, uint8_t offset)
{
  if (offset > 254)
    return SSD1306_OFFSET_FAIL; // Set correct max value

  uint8_t cmd[2];

  cmd[0] = (uint8_t)SSD1306_CMD_SET_DISPLAY_OFFSET;
  cmd[1] = offset;

  for (size_t i = 0; i < sizeof(cmd); i++)
  {
    driver->i2c_write_cmd(driver, cmd[i]);
  }

  return SSD1306_OFFSET_OK;
}

//   TODO: Make driver set start page addr func driver->i2c_write_cmd(driver, 0x40); // start line = 0

static ssd1306_config_chargepump_error_t SSD1306_Configure_ChargePump(ssd1306_i2c_driver_t *driver,
                                                                      ssd1306_charge_pump_mode_t mode)
{
  uint8_t cmd[2];

  cmd[0] = (uint8_t)SSD1306_CMD_SET_CHARGE_PUMP;
  cmd[1] = (uint8_t)mode;

  for (size_t i = 0; i < sizeof(cmd); i++)
  {
    driver->i2c_write_cmd(driver, cmd[i]);
  }

  return SSD1306_CHARGEPUMP_OK;
}

static ssd1306_config_mem_mode_error_t SSD1306_Configure_MemoryMode(ssd1306_i2c_driver_t *driver,
                                                                    ssd1306_memory_mode_t mode)
{
  uint8_t cmd[2];

  cmd[0] = (uint8_t)SSD1306_CMD_SET_MEMORY_MODE;
  cmd[1] = (uint8_t)mode;

  for (size_t i = 0; i < sizeof(cmd); i++)
  {
    driver->i2c_write_cmd(driver, cmd[i]);
  }

  return SSD1306_MEMORYMODE_OK;
}

static ssd1306_config_mapping_error_t SSD1306_Config_Mapping(ssd1306_i2c_driver_t *driver,
                                                             ssd1306_mapping_t mode)
{
  //   driver->i2c_write_cmd(driver, 0xA1); // segment remap
  uint8_t cmd = (uint8_t)mode;
  driver->i2c_write_cmd(driver, cmd);

  return SSD1306_MAPPING_OK;
}

static ssd1306_config_com_scan_error_t SSD1306_Config_ComScanDec(ssd1306_i2c_driver_t *driver,
                                                                 ssd1306_com_scan_t mode)
{
  uint8_t cmd = (uint8_t)mode;
  driver->i2c_write_cmd(driver, cmd);

  return SSD1306_COM_SCAN_OK;
}

static ssd1306_config_com_pins_error_t SSD1306_Config_ComPins(ssd1306_i2c_driver_t *driver,
                                                              uint8_t pins)
{
  if (pins > 254)
    return SSD1306_COM_PINS_FAIL;

  uint8_t cmd[2];

  cmd[0] = (uint8_t)SSD1306_CMD_SET_CON_PIN_HW_CONF;
  cmd[1] = pins;

  for (size_t i = 0; i < sizeof(cmd); i++)
  {
    driver->i2c_write_cmd(driver, cmd[i]);
  }

  return SSD1306_COM_PINS_OK;
}

static ssd1306_config_contrast_error_t SSD1306_Config_Contrast(ssd1306_i2c_driver_t *driver,
                                                               uint8_t contrast)
{
  uint8_t cmd[2];

  cmd[0] = (uint8_t)SSD1306_CMD_SET_CONTRAST;
  cmd[1] = contrast;

  for (size_t i = 0; i < sizeof(cmd); i++)
  {
    driver->i2c_write_cmd(driver, cmd[i]);
  }

  return SSD1306_CONTRAST_OK;
}

static ssd1306_config_precharge_error_t SSD1306_Config_Precharge(ssd1306_i2c_driver_t *driver)
{
  //   driver->i2c_write_cmd(driver, 0xD9); // precharge
  //   driver->i2c_write_cmd(driver, 0xF1);
  // TODO: Change it to handle proper config, hardcoded default valuse for charge pump enable!
  uint8_t cmd[2];

  cmd[0] = (uint8_t)SSD1306_CMD_SET_PRECHARGE_PERIOD;
  cmd[1] = 0xF1;

  for (size_t i = 0; i < sizeof(cmd); i++)
  {
    driver->i2c_write_cmd(driver, cmd[i]);
  }

  return SSD1306_PRECHARGE_OK;
}

static ssd1306_config_voltage_error_t SSD1306_Config_Voltage(ssd1306_i2c_driver_t *driver)
{
  //   driver->i2c_write_cmd(driver, 0xDB); // VCOMH
  //   driver->i2c_write_cmd(driver, 0x40);
  // TODO: Add vcc values handle, hardcoded default
  uint8_t cmd[2];

  cmd[0] = (uint8_t)SSD1306_CMD_SET_V_COMH_DESELECT_LVL;
  cmd[1] = 0x40;

  for (size_t i = 0; i < sizeof(cmd); i++)
  {
    driver->i2c_write_cmd(driver, cmd[i]);
  }

  return SSD1306_VOLTAGE_OK;
}

static ssd1306_config_inverse_error_t SSD1306_Config_Inverse(ssd1306_i2c_driver_t *driver,
                                                             uint8_t mode)
{
  // TODO: Refactor it ugly thing
  //   driver->i2c_write_cmd(driver, 0xA6); // normal display
  uint8_t cmd = (uint8_t)SSD1306_CMD_NORMAL_DISPLAY;

  if (mode == SSD1306_INVERSE_ENABLE) cmd = (uint8_t)SSD1306_CMD_INVERSE_DISPLAY;

  driver->i2c_write_cmd(driver, cmd);

  return SSD1306_INVERSE_OK;
}
//   driver->i2c_write_cmd(driver, 0xA4); // resume RAM

void SSD1306_Display_OnOff(ssd1306_i2c_driver_t *driver, uint8_t state)
{  
  // TODO: Refactor it ugly thing
  //   driver->i2c_write_cmd(driver, 0xAF); // display ON
  //   driver->i2c_write_cmd(driver, 0xAF); // display OFF
  uint8_t cmd = (uint8_t)SSD1306_CMD_DISPLAY_ON;

  if (state == SSD1306_DISPLAY_DISABLE)
    cmd = (uint8_t)SSD1306_CMD_DISPLAY_OFF;

  driver->i2c_write_cmd(driver, cmd);
}
