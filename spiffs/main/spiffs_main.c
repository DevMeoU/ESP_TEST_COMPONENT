/* SPIFFS filesystem example.
   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include <stdio.h>
#include <string.h>
#include <sys/unistd.h>
#include <sys/stat.h>
#include "esp_err.h"
#include "esp_log.h"
#include "esp_spiffs.h"
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"

static const char *TAG = "FileSystem";

void app_main(void)
{
    ESP_LOGI(TAG, "Initializing SPIFFS");
    
    esp_vfs_spiffs_conf_t conf = {
      .base_path = "/storage",
      .partition_label = NULL,
      .max_files = 5,
      .format_if_mount_failed = true
    };
    
    // Use settings defined above to initialize and mount SPIFFS filesystem.
    // Note: esp_vfs_spiffs_register is an all-in-one convenience function.
    esp_err_t ret = esp_vfs_spiffs_register(&conf);

    if (ret != ESP_OK) {
        if (ret == ESP_FAIL) {
            ESP_LOGE(TAG, "Failed to mount or format filesystem");
        } else if (ret == ESP_ERR_NOT_FOUND) {
            ESP_LOGE(TAG, "Failed to find SPIFFS partition");
        } else {
            ESP_LOGE(TAG, "Failed to initialize SPIFFS (%s)", esp_err_to_name(ret));
        }
        return;
    }
    
    size_t total = 0, used = 0;
    ret = esp_spiffs_info(conf.partition_label, &total, &used);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to get SPIFFS partition information (%s)", esp_err_to_name(ret));
    } else {
        ESP_LOGI(TAG, "Partition size: total: %d, used: %d", total, used);
    }

    // Use POSIX and C standard library functions to work with files.
    // First create a file.
    ESP_LOGI(TAG, "Opening file");
    FILE* f = fopen("/storage/myfile.txt", "r");
    if (f == NULL) {
        ESP_LOGE(TAG, "Failed to open file for writing");
        return;
    }

    long long int Timer1 = esp_timer_get_time();
    printf("Timer: %lld μs\n", Timer1);  
    vTaskDelay(1);
    long long int Timer2 = esp_timer_get_time();
    printf("Timer: %lld μs\n", Timer2);  
    long long int diff = Timer2 - Timer1;
    printf("Difference: %lld μs\n", diff); 

    int c;
    while ((c = fgetc(f)) != EOF)
    {
        printf("%c", c);
        // vTaskDelay(1);
    }
    // printf("Break: %d\n", c);
    // c = fgetc(f);
    fclose(f);
    // printf("Character: %c\n", c);

    // fprintf(f, "Hello World!\n");
    // fclose(f);
    // ESP_LOGI(TAG, "File written");

    // // Check if destination file exists before renaming
    // struct stat st;
    // if (stat("/storage/foo.txt", &st) == 0) {
    //     // Delete it if it exists
    //     unlink("/storage/foo.txt");
    // }

    // // Rename original file
    // ESP_LOGI(TAG, "Renaming file");
    // if (rename("/storage/hello.txt", "/storage/foo.txt") != 0) {
    //     ESP_LOGE(TAG, "Rename failed");
    //     return;
    // }

    // // Open renamed file for reading
    // ESP_LOGI(TAG, "Reading file");
    // f = fopen("/storage/foo.txt", "r");
    // if (f == NULL) {
    //     ESP_LOGE(TAG, "Failed to open file for reading");
    //     return;
    // }
    // char line[64];
    // fgets(line, sizeof(line), f);
    // fclose(f);
    // // strip newline
    // char* pos = strchr(line, '\n');
    // if (pos) {
    //     *pos = '\0';
    // }
    // ESP_LOGI(TAG, "Read from file: '%s'", line);

    // // All done, unmount partition and disable SPIFFS
    // esp_vfs_spiffs_unregister(conf.partition_label);
    // ESP_LOGI(TAG, "SPIFFS unmounted");
}
