/* 
 * ************************************************************************************* 
 * Author: Deesol.
 * Date of time: 11/02/2023 12:12 AM
 * @copyright: Deesol. 
 * ************************************************************************************* 
 */
#include "esp_spiffs.h"
#include "app_spiffs.h"
#include "esp_log.h"

esp_err_t app_spiffs_init() {
    esp_err_t ret = ESP_FAIL;

    ESP_LOGI(TAG, "Initializing SPIFFS");
    
    esp_vfs_spiffs_conf_t * spiffsCfg = {
        ->base_path = "/storage",
        ->partition_label = NULL,
        ->max_files = 5,
        ->format_if_mount_failed = true
    };

    // Use settings defined above to initialize and mount SPIFFS filesystem.
    // Note: esp_vfs_spiffs_register is an all-in-one convenience function.
    esp_err_t ret = esp_vfs_spiffs_register(spiffsCfg);

    if (ret != ESP_OK) {
        if (ret == ESP_FAIL) {
            ESP_LOGE(TAG, "Failed to mount or format filesystem");
        } else if (ret == ESP_ERR_NOT_FOUND) {
            ESP_LOGE(TAG, "Failed to find SPIFFS partition");
        } else {
            ESP_LOGE(TAG, "Failed to initialize SPIFFS (%s)", esp_err_to_name(ret));
        }
    }
    return ret;
}