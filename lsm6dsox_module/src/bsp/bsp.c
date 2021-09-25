/**
 * @file       bsp.c
 * @copyright  Copyright (C) 2020 Hydratech. All rights reserved.
 * @license    This project is released under the ThuanLe License.
 * @version    1.0.0
 * @date       2021-01-23
 * @author     Thuan Le
 * @brief      Board Support Package (BSP)
 * 
 * @note       None
 * @example    None
 */

/* Includes ----------------------------------------------------------- */
#include "bsp.h"
#include "i2c_bus.h"
#include "esp_log.h"

/* Private defines ---------------------------------------------------- */
static const char *TAG = "BSP";

/* Private enumerate/structure ---------------------------------------- */
/* Private macros ----------------------------------------------------- */
/* Public variables --------------------------------------------------- */
/* Private variables -------------------------------------------------- */
static i2c_bus_handle_t m_i2c_0_hdl;

/* Private function prototypes ---------------------------------------- */
static void m_bsp_i2c_init(void);

/* Function definitions ----------------------------------------------- */
void bsp_hw_init(void)
{
  m_bsp_i2c_init();
}

int bsp_i2c_write(uint8_t slave_addr, uint8_t reg_addr, uint8_t *p_data, uint32_t len)
{
  int ret;

  ret = i2c_bus_write_bytes(m_i2c_0_hdl, slave_addr, &reg_addr, sizeof(reg_addr), p_data, len);
  if (ret != 0)
  {
    ESP_LOGE(TAG, "I2C 0 error: %d. Restart I2C.", ret);
    i2c_bus_delete(m_i2c_0_hdl);
    m_bsp_i2c_init();
    ret = i2c_bus_write_bytes(m_i2c_0_hdl, slave_addr, &reg_addr, sizeof(reg_addr), p_data, len);
  }

  return ret;
}

int bsp_i2c_read(uint8_t slave_addr, uint8_t reg_addr, uint8_t *p_data, uint32_t len)
{
  int ret;

  ret = i2c_bus_read_bytes(m_i2c_0_hdl, slave_addr, &reg_addr, sizeof(reg_addr), p_data, len);

  if (ret != 0)
  {
    ESP_LOGE(TAG, "I2C 0 error: %d. Restart I2C.", ret);
    i2c_bus_delete(m_i2c_0_hdl);
    m_bsp_i2c_init();
    ret = i2c_bus_read_bytes(m_i2c_0_hdl, slave_addr, &reg_addr, sizeof(reg_addr), p_data, len);
  }

  return ret;
}

void bsp_delay_ms(uint32_t ms)
{
}

void bsp_gpio_write(uint8_t pin , uint8_t state)
{
}

/* Private function definitions ---------------------------------------- */
/**
 * @brief         I2C init
 *
 * @param[in]     None
 *
 * @attention     None
 *
 * @return        None
 */
void m_bsp_i2c_init(void)
{
  i2c_config_t es_i2c_cfg =
  {
    .mode             = I2C_MODE_MASTER,
    .sda_io_num       = 21,
    .scl_io_num       = 22,
    .sda_pullup_en    = GPIO_PULLUP_ENABLE,
    .scl_pullup_en    = GPIO_PULLUP_ENABLE,
    .master.clk_speed = 400000
  };

  m_i2c_0_hdl = i2c_bus_create(I2C_NUM_0, &es_i2c_cfg);
  i2c_set_timeout(I2C_NUM_0, 0xfffff);
}

/* End of file -------------------------------------------------------- */
