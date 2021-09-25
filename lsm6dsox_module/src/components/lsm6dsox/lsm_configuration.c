/*
 * lsm_configuration.c
 *
 *  Created on: Sep 23, 2021
 *      Author: sai
 */

/* Includes ----------------------------------------------------------- */
#include "lsm_configuration.h"
#include "esp_log.h"

/* Private defines ---------------------------------------------------- */
#define SENSOR_BUS  LSM6DSOX_I2C_ADD_L

/* Private enumerate/structure ---------------------------------------- */
/* Private macros ----------------------------------------------------- */
/* Public variables --------------------------------------------------- */
/* Private variables -------------------------------------------------- */
static const char* TAG = "lsm_configuration";
stmdev_ctx_t lsm6dsox_t;

/* Private function prototypes ---------------------------------------- */
/* Function definitions ----------------------------------------------- */

void lsm_config_configuration(stmdev_ctx_t *instance)
{
  ESP_LOGI(TAG, "lsm_config_configuration()");
  lsm6dsox_t = *instance;

  /* Variable declaration */
  lsm6dsox_pin_int1_route_t pin_int1_route;
  lsm6dsox_pin_int2_route_t int2_route;
  lsm6dsox_emb_sens_t emb_sens;
  uint8_t rst;

  /* Restore default configuration */
  lsm6dsox_reset_set(&lsm6dsox_t, PROPERTY_ENABLE);

  do {
    lsm6dsox_reset_get(&lsm6dsox_t, &rst);
    ESP_LOGI(TAG, "lsm_config_configuration() rst: %d", rst);
  } while (rst);

  /* Disable I3C interface */
  lsm6dsox_i3c_disable_set(&lsm6dsox_t, LSM6DSOX_I3C_DISABLE);

  /* Enable Block Data Update */
  lsm6dsox_block_data_update_set(&lsm6dsox_t, PROPERTY_ENABLE);

  /* Set full scale */
  lsm6dsox_xl_full_scale_set(&lsm6dsox_t, LSM6DSOX_4g);
  lsm6dsox_gy_full_scale_set(&lsm6dsox_t, LSM6DSOX_2000dps);

  /* ========================Enable pedometer config========================*/
  lsm6dsox_pedo_sens_set(&lsm6dsox_t, LSM6DSOX_FALSE_STEP_REJ_ADV_MODE);
  emb_sens.step = PROPERTY_ENABLE;
  emb_sens.mlc = PROPERTY_ENABLE;
  lsm6dsox_embedded_sens_set(&lsm6dsox_t, &emb_sens);
  /* ========================End of pedometer config========================*/

  /* ========================Tapping config===============================*/
  /* Enable Tap detection on X, Y, Z */
  lsm6dsox_tap_detection_on_z_set(&lsm6dsox_t, PROPERTY_ENABLE);
  lsm6dsox_tap_detection_on_y_set(&lsm6dsox_t, PROPERTY_ENABLE);
  lsm6dsox_tap_detection_on_x_set(&lsm6dsox_t, PROPERTY_ENABLE);
  /* Set Tap threshold to 01000b, therefore the tap threshold
   * is 500 mg (= 12 * FS_XL / 32 )
   */
  lsm6dsox_tap_threshold_x_set(&lsm6dsox_t, 0x08);
  lsm6dsox_tap_threshold_y_set(&lsm6dsox_t, 0x08);
  lsm6dsox_tap_threshold_z_set(&lsm6dsox_t, 0x08);
  /* Configure Single and Double Tap parameter
   *
   * For the maximum time between two consecutive detected taps, the DUR
   * field of the INT_DUR2 register is set to 0111b, therefore the Duration
   * time is 538.5 ms (= 7 * 32 * ODR_XL)
   *
   * The SHOCK field of the INT_DUR2 register is set to 11b, therefore
   * the Shock time is 57.36 ms (= 3 * 8 * ODR_XL)
   *
   * The QUIET field of the INT_DUR2 register is set to 11b, therefore
   * the Quiet time is 28.68 ms (= 3 * 4 * ODR_XL)
   */
  lsm6dsox_tap_dur_set(&lsm6dsox_t, 0x07);
  lsm6dsox_tap_quiet_set(&lsm6dsox_t, 0x03);
  lsm6dsox_tap_shock_set(&lsm6dsox_t, 0x03);
  /* Enable Single and Double Tap detection. */
  lsm6dsox_tap_mode_set(&lsm6dsox_t, LSM6DSOX_BOTH_SINGLE_DOUBLE);
  /* ========================End of Tapping config========================*/


  /* Route signals on interrupt pin 1 */
  lsm6dsox_pin_int1_route_get(&lsm6dsox_t, &pin_int1_route);
  pin_int1_route.step_detector = PROPERTY_ENABLE;
  lsm6dsox_pin_int1_route_set(&lsm6dsox_t, pin_int1_route);

  /* Uncomment if interrupt generation on Single and Double Tap INT2 pin */
  lsm6dsox_pin_int2_route_get(&lsm6dsox_t, NULL, &int2_route);
  /* For single tap only comment next function */
  int2_route.double_tap = PROPERTY_ENABLE;
  int2_route.single_tap = PROPERTY_ENABLE;
  lsm6dsox_pin_int2_route_set(&lsm6dsox_t, NULL, int2_route);

  /* Configure interrupt pin mode notification */
  lsm6dsox_int_notification_set(&lsm6dsox_t,
                                LSM6DSOX_BASE_PULSED_EMB_LATCHED);

  /* Set Output Data Rate.
   * Selected data rate have to be equal or greater with respect
   * with MLC data rate.
   */
  lsm6dsox_xl_data_rate_set(&lsm6dsox_t, LSM6DSOX_XL_ODR_417Hz);
  lsm6dsox_gy_data_rate_set(&lsm6dsox_t, LSM6DSOX_GY_ODR_OFF);

  /* Reset steps of pedometer */
  lsm6dsox_steps_reset(&lsm6dsox_t);
}

