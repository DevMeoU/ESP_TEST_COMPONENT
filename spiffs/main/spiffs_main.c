#include <stdio.h>
#include <string.h>
#include <sys/unistd.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"
#include <sys/stat.h>
#include "esp_err.h"
#include "esp_log.h"
#include "../component/app_spiffs/inc/app_spiffs.h"

#define DATA_FILE_SIZE (12203U)

TaskHandle_t xDelayHandle = NULL;
static const char *TAG = "FileSystem";

long long int Timer1;
long long int Timer2;
long long int diff;
char buff[DATA_FILE_SIZE];
char fileName[] = "/storage/myfile.txt";
long fileSize;

void delay_ms(int ms)
{
	vTaskDelay(ms/portTICK_PERIOD_MS);
}

void task_delay(void *pvParameter) {
    while(1) {
        Timer1 = esp_timer_get_time();
        printf("Timer: %lld μs\n", Timer1);
        vTaskDelay(1);
        Timer2 = esp_timer_get_time();
        printf("Timer: %lld μs\n", Timer2);  
        diff = Timer2 - Timer1;
        printf("Difference: %lld μs\n", diff);
        delay_ms(1000);
    }
}

void app_main(void)
{
    ESP_LOGW(TAG, "Hi! I am Deesol Reven.");
    // xTaskCreate(&task_delay,"task_delay",2048, NULL, 3, &xDelayHandle);

    app_spiffs_init();

    fileSize = app_spiffs_check_file_size(fileName);
    if (fileSize != 0) {
        printf("File size:%ld\n", fileSize);
    }
    else {
        ESP_LOGE(TAG, "File exist!");
    }
    
    /*
     * *************************************************************************
     *  /storage |
     *           |-----> myfile.txt (read file)
     * *************************************************************************
     */

    app_spiffs_read_file(fileName, buff, DATA_FILE_SIZE);
    printf("buff: %s\n", buff);

    /*
     * *************************************************************************
     *  /storage |
     *           |-----> myfile.txt
     *           |-----> hello.txt (create file hello.txt)
     * *************************************************************************
     */

    char * hello = "Hello World!";
    app_spiffs_write_file("/storage/hello.txt", hello);

    /*
     * *************************************************************************
     *  /storage |
     *           |-----> myfile.txt
     *           |-----> hello.txt (read file hello.txt)
     * *************************************************************************
     */

    char readHello[15];
    app_spiffs_read_file("/storage/hello.txt", readHello, 15);
    printf("buff: %s\n", readHello);

    /*
     * *************************************************************************
     *  /storage |
     *           |-----> myfile.txt
     *           |-----> hello.txt
     *           |-----> myfolder |
     *                            |-----> readme.txt (create file readme.txt)
     * *************************************************************************
     */

    char * readme = "This is read my produce more info about myself!";
    app_spiffs_write_file("/storage/myfolder/readme.txt", readme);

    /*
     * *************************************************************************
     *  /storage |
     *           |-----> myfile.txt
     *           |-----> hello.txt
     *           |-----> myfolder |
     *                            |-----> readme.txt (read file readme.txt)
     * *************************************************************************
     */

    char readReadme[50];
    app_spiffs_read_file("/storage/myfolder/readme.txt", readReadme, 50);
    printf("buff: %s\n", readReadme);

    /*
     * *************************************************************************
     *  /storage |
     *           |-----> myfile.txt
     *           |-----> hello.txt
     *           |-----> myfolder |
     *                            |-----> foo.txt (rename file readme.txt to foo.txt)
     * *************************************************************************
     */

    app_spiffs_rename_file("/storage/myfolder/readme.txt", "/storage/myfolder/foo.txt");

    /*
     * *************************************************************************
     *  /storage |
     *           |-----> myfile.txt
     *           |-----> hello.txt
     *           |-----> myfolder |
     *                            |-----> foo.txt (read file foo.txt)
     * *************************************************************************
     */

    char readFoo[50];
    app_spiffs_read_file("/storage/myfolder/foo.txt", readFoo, 50);

    printf("buff: %s\n", readFoo);

    /*
     * *************************************************************************
     *  /storage |
     *           |-----> myfile.txt
     *           |-----> hello.txt (X delete file hello.txt)
     *           |-----> myfolder |
     *                            |-----> foo.txt
     * 
     *                           |
     *                           V
     * 
     *  /storage |
     *           |-----> myfile.txt
     *           |-----> myfolder |
     *                            |-----> foo.txt
     * *************************************************************************
     */

    if(app_spiffs_delete_file("/storage/hello.txt") == ESP_OK)
        printf("Success to delete file!\n");
    else
        printf("Fail to delete file!\n");

    /*
     * *************************************************************************
     *  /storage |
     *           |-----> myfile.txt
     *           |-----> myfolder |
     *                            |-----> foo.txt
     * 
     * Try to read file hello.txt this is delete.
     * *************************************************************************
     */

    app_spiffs_read_file("/storage/hello.txt", readHello, 15);
    printf("buff: %s\n", readHello);

    /* All done, unmount partition and disable SPIFFS */
    app_spiffs_deinit();
}
