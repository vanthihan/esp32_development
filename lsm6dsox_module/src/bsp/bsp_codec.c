/**
 * @file       bsp_codec.c
 * @copyright  Copyright (C) 2020 Hydratech. All rights reserved.
 * @license    This project is released under the Hydratech License.
 * @version    1.0.0
 * @date       2021-03-24
 * @author     Thuan Le
 * @brief      Board support package for Audio Codec
 * @note       None
 * @example    None
 */

/* Includes ----------------------------------------------------------- */
#include "bsp_codec.h"

/* Private defines ---------------------------------------------------- */
/* Private enumerate/structure ---------------------------------------- */
/* Private macros ----------------------------------------------------- */
/* Public variables --------------------------------------------------- */
/* Private variables -------------------------------------------------- */
static max98089_t m_max98089;

/* Private function prototypes ---------------------------------------- */
/* Function definitions ----------------------------------------------- */
base_status_t bsp_codec_init(void)
{
  m_max98089.device_address = MAX89098_I2C_ADDR;
  m_max98089.i2c_read       = bsp_i2c_read;
  m_max98089.i2c_write      = bsp_i2c_write;

  CHECK_STATUS(max98089_init(&m_max98089));
}

/* Private function definitions ---------------------------------------- */
/* End of file -------------------------------------------------------- */
