/*
 * bsp_lsm6dsox.h
 *
 *  Created on: Sep 23, 2021
 *      Author: Thi Han
 */

/* Includes ----------------------------------------------------------- */
#include <string.h>
#include "bsp_lsm6dsox.h"
#include "lsm_driver.h"
#include "lsm_configuration.h"
#include "esp_log.h"

/* Private defines ---------------------------------------------------- */
#define SENSOR_BUS  LSM6DSOX_I2C_ADD_L

/* Private enumerate/structure ---------------------------------------- */
/* Private macros ----------------------------------------------------- */
/* Public variables --------------------------------------------------- */
/* Private variables -------------------------------------------------- */
static const char* TAG = "LSM6DSOX BSP";

static stmdev_ctx_t m_lsm6dsox_t;
static lsm6dsox_all_sources_t status;
static uint16_t steps;
static uint8_t whoamI;
static uint8_t tx_buffer[1000];

/* Private function prototypes ---------------------------------------- */
/* Function definitions ----------------------------------------------- */

base_status_t bsp_lsm6dsox_init(void)
{
  ESP_LOGI(TAG, "bsp_lsm6dsox_init()");

  m_lsm6dsox_t.device_address = SENSOR_BUS;
  m_lsm6dsox_t.read_reg       = bsp_i2c_read;
  m_lsm6dsox_t.write_reg      = bsp_i2c_write;

  //Identify i2c bus
  lsm6dsox_device_id_get(&m_lsm6dsox_t, &whoamI);
  if (whoamI == LSM6DSOX_ID)
  {
    ESP_LOGI(TAG, "pedometer_init() I2C bus establish successfully!");
  }
  else
  {
    ESP_LOGI(TAG, "pedometer_init() I2C address mismatch!");
    while (1);
  }

  lsm_config_configuration(&m_lsm6dsox_t);

  return BS_OK;
}


void bsp_lsm6dsox_get_steps()
{
  ESP_LOGI(TAG,"bsp_lsm6dsox_get_steps() called. ");

  /* Read interrupt source registers in polling mode (no int) */
  lsm6dsox_all_sources_get(&m_lsm6dsox_t, &status);

  if (status.step_detector)
  {
    ESP_LOGI(TAG,"bsp_lsm6dsox_get_steps() step detected! ");
    lsm6dsox_number_of_steps_get(&m_lsm6dsox_t, &steps);
  }

  ESP_LOGI(TAG,"bsp_lsm6dsox_get_steps() steps: %d! ", steps);
//  return steps;
}

void bsp_lsm6dsox_tapping_handler()
{
  ESP_LOGI(TAG,"bsp_lsm6dsox_tapping_handler() Called");

  lsm6dsox_all_sources_t all_source;
  /* Check if Tap events */
  lsm6dsox_all_sources_get(&m_lsm6dsox_t, &all_source);

  if (all_source.double_tap)
  {
    ESP_LOGI(TAG,"bsp_lsm6dsox_tapping_handler() Double Tap:");

    if (all_source.tap_x)
    {
      strcat((char *)tx_buffer, "x-axis");
    }
    else if (all_source.tap_x)
    {
      strcat((char *)tx_buffer, "y-axis");
    }
    else
    {
      strcat((char *)tx_buffer, "z-axis");
    }

    if (all_source.tap_sign)
    {
      strcat((char *)tx_buffer, " negative");
    }
    else
    {
      strcat((char *)tx_buffer, " positive");
    }

    strcat((char *)tx_buffer, " sign\r\n");
//    tx_com(tx_buffer, strlen((char const *)tx_buffer));
    ESP_LOGI(TAG,"bsp_lsm6dsox_tapping_handler() \t:%s", tx_buffer);
  }

  if (all_source.single_tap)
  {
    ESP_LOGI(TAG,"bsp_lsm6dsox_tapping_handler() Double Tap:");

    if (all_source.tap_x)
    {
      strcat((char *)tx_buffer, "x-axis");
    }

    else if (all_source.tap_y)
    {
      strcat((char *)tx_buffer, "y-axis");
    }

    else
    {
      strcat((char *)tx_buffer, "z-axis");
    }

    if (all_source.tap_sign)
    {
      strcat((char *)tx_buffer, " negative");
    }

    else
    {
      strcat((char *)tx_buffer, " positive");
    }

    strcat((char *)tx_buffer, " sign\r\n");
//    tx_com(tx_buffer, strlen((char const *)tx_buffer));
    ESP_LOGI(TAG,"bsp_lsm6dsox_tapping_handler() \t:%s", tx_buffer);
  }
}

/* Private function definitions ---------------------------------------- */


/* End of file -------------------------------------------------------- */
