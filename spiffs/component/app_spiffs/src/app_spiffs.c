/*
 * *************************************************************************************
 * Author: Deesol.
 * Date of time: 11/02/2023 12:12 AM
 * @copyright: Deesol.
 * *************************************************************************************
 * {@
 */

#ifdef __cplusplus
extern "C"
{
#endif

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/

#include "../inc/app_spiffs.h"

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/

/*==================================================================================================
*                                      LOCAL CONSTANTS
==================================================================================================*/
static esp_vfs_spiffs_conf_t conf = {
    .base_path = "/storage",
    .partition_label = NULL,
    .max_files = 5,
    .format_if_mount_failed = true};

/*==================================================================================================
*                                      LOCAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                      GLOBAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      GLOBAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/
esp_err_t app_spiffs_init()
{
    ESP_LOGI(__func__, "Initializing SPIFFS");
    esp_err_t ret = esp_vfs_spiffs_register(&conf);
    if (ret != ESP_OK)
    {
        if (ret == ESP_FAIL)
        {
            ESP_LOGE(__func__, "Failed to mount or format filesystem");
        }
        else if (ret == ESP_ERR_NOT_FOUND)
        {
            ESP_LOGE(__func__, "Failed to find SPIFFS partition");
        }
        else
        {
            ESP_LOGE(__func__, "Failed to initialize SPIFFS (%s)", esp_err_to_name(ret));
        }
    }
    else
    {
        ESP_LOGI(__func__, "Initialize SPIFFS OK");
    }
    ESP_ERROR_CHECK(ret);
    if (esp_spiffs_mounted("storage") == ESP_OK)
    {
        ESP_LOGI(__func__, "So far so good");
    }

    size_t total = 0, used = 0;
    ret = esp_spiffs_info(conf.partition_label, &total, &used);
    if (ret != ESP_OK)
    {
        ESP_LOGE(__func__, "Failed to get SPIFFS partition information (%s)", esp_err_to_name(ret));
    }
    else
    {
        ESP_LOGI(__func__, "Partition size: total: %d, used: %d", total, used);
    }
    return ret;
}

esp_err_t app_spiffs_deinit()
{
    ESP_LOGI(__func__, "DeInitializing SPIFFS");
    esp_err_t ret = esp_vfs_spiffs_unregister(conf.partition_label);
    if (ret != ESP_OK)
    {
        return ret;
    }
    ESP_LOGI(__func__, "SPIFFS unmounted");
    return ESP_OK;
}

esp_err_t app_spiffs_read_file(const char *fileName, char *buffer, int maximumLen)
{
    int index = 0;
    int c;

    ESP_LOGI(__func__, "Opening file");

    FILE *fptr = fopen(fileName, "r");
    if (fptr == NULL)
    {
        ESP_LOGE(__func__, "Failed to open file for reading");
        return ESP_FAIL;
    }

    while ((c = fgetc(fptr)) != EOF)
    {
        buffer[index] = (char)c;
        if (index++ >= maximumLen)
            break;
    }
    fclose(fptr);
    return ESP_OK;
}

esp_err_t app_spiffs_write_file(const char *fileName, const char *buffer)
{
    ESP_LOGI(__func__, "Opening file");
    FILE *fPtr = fopen(fileName, "w");
    if (fPtr == NULL)
    {
        ESP_LOGE(__func__, "Failed to open file for reading");
        return ESP_FAIL;
    }

    fputs(buffer, fPtr);
    fclose(fPtr);
    return ESP_OK;
}

esp_err_t app_spiffs_delete_file(const char *fileName)
{
    if (remove(fileName) == 0)
        return ESP_OK;
    return ESP_FAIL;
}

esp_err_t app_spiffs_rename_file(const char *fileOldName, const char *fileNewName)
{
    ESP_LOGI(__func__, "Renaming file");
    if (rename(fileOldName, fileNewName) != 0)
    {
        ESP_LOGE(__func__, "Rename failed");
        return ESP_FAIL;
    }
    return ESP_OK;
}

long app_spiffs_check_file_size(const char *fileName)
{
    struct stat st;
    if (stat(fileName, &st) == 0)
    {
        return st.st_size;
    }
    return 0;
}

/*================================================================================================*/
/*================================================================================================*/

/**
 * @brief
 * @details
 */

#ifdef __cplusplus
}
#endif

/** @} */