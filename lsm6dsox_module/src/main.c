/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#include "bsp.h"
#include "bsp_lsm6dsox.h"


static const char *TAG = "MAIN";

static void test_task(void *pvparameters)
{
  ESP_LOGI(TAG, "test_task() started!");
  bsp_lsm6dsox_init();

  while(1)
  {
    bsp_lsm6dsox_get_steps();
    bsp_lsm6dsox_tapping_handler();
  }
}


void app_main(void)
{
  ESP_LOGI(TAG, "app_main() started!");
  bsp_hw_init();          // Bsp init

  xTaskCreate(&test_task, "test_task", 8192, NULL, 5, NULL);

  while(1);
}

