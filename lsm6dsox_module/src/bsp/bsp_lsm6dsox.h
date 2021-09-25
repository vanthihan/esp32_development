/*
 * bsp_lsm6dsox.h
 *
 *  Created on: Sep 23, 2021
 *      Author: Thi Han
 */


#ifndef MAIN_BSP_BSP_LSM6DSOX_H_
#define MAIN_BSP_BSP_LSM6DSOX_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------- */
#include "bsp.h"

/* Public defines ----------------------------------------------------- */
/* Public enumerate/structure ----------------------------------------- */
/* Public macros ------------------------------------------------------ */
/* Public variables --------------------------------------------------- */
/* Public function prototypes ----------------------------------------- */
/**
 * @brief         BSP LSM6DSOX init
 *
 * @param[in]     None
 *
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */

base_status_t bsp_lsm6dsox_init(void);
void bsp_lsm6dsox_get_steps();
void bsp_lsm6dsox_tapping_handler();

#endif /* MAIN_BSP_BSP_LSM6DSOX_H_ */
