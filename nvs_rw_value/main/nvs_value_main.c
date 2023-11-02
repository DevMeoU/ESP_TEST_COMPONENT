/* Non-Volatile Storage (NVS) Read and Write a Value - Example

   For other examples please check:
   https://github.com/espressif/esp-idf/tree/master/examples

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "../component/app_nvs_value/inc/app_nvs_value.h"

#define STRING_LENGTH_MAX   (100U)

nvs_handle_t my_handle;
char user_ssid[STRING_LENGTH_MAX] = "my_ssid";
char user_password[STRING_LENGTH_MAX] = "oldPassword";

void app_main(void)
{
    esp_err_t err = ESP_OK;
    app_nvs_value_init();

    /* Reading to NVS partitions */
    printf("Reading string from NVS ... ");
    err = app_nvs_get_str("nvs", "User", "SSID", user_ssid, STRING_LENGTH_MAX);
    err = app_nvs_get_str("nvs", "User", "PASS", user_password, STRING_LENGTH_MAX);

    switch (err) {
        case ESP_OK:
            printf("Done\n");
            printf("ssid: %s\n", user_ssid);
            printf("Pass: %s\n", user_password);
            break;
        case ESP_ERR_NVS_NOT_FOUND:
            printf("The value is not initialized yet!\n");
            break;
        default :
            printf("Error (%s) reading!\n", esp_err_to_name(err));
    }

        /* Writing to NVS partitions */
        printf("Writing string from NVS ... ");
        strncpy(user_ssid, "Cortex-M7", sizeof(user_ssid));
        strncpy(user_password, "038736402*", sizeof(user_password));
        err = app_nvs_set_str("nvs", "User", "SSID", user_ssid);
        err = app_nvs_set_str("nvs", "User", "PASS", user_password);
        printf((err != ESP_OK) ? "Failed!\n" : "Done\n");

#if 0
    err = app_nvs_value_open(NVS_READWRITE, &my_handle);

    if (err == ESP_OK) {
        // Read
        printf("Reading restart counter from NVS ... ");
        uint32_t restart_counter = 0; // value will default to 0, if not set yet in NVS
        err = nvs_get_u32(my_handle, "restart_counter", &restart_counter);

        // err = app_nvs_get_u32("nvs", "User", "Pass", &restart_counter);
        switch (err) {
            case ESP_OK:
                printf("Done\n");
                printf("Restart counter = %d\n", restart_counter);
                break;
            case ESP_ERR_NVS_NOT_FOUND:
                printf("The value is not initialized yet!\n");
                break;
            default :
                printf("Error (%s) reading!\n", esp_err_to_name(err));
        }

        // Write
        printf("Updating restart counter in NVS ... ");
        restart_counter++;
        err = nvs_set_u32(my_handle, "restart_counter", restart_counter);
        // err = app_nvs_set_u32("nvs", "User", "Pass", restart_counter);
        printf((err != ESP_OK) ? "Failed!\n" : "Done\n");

    }
#endif

    app_nvs_value_commit(&my_handle);
    app_nvs_value_close(&my_handle);

    printf("\n");

    // Restart module
    for (int i = 10; i >= 0; i--) {
        printf("Restarting in %d seconds...\n", i);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    printf("Restarting now.\n");
    fflush(stdout);
    esp_restart();
}
