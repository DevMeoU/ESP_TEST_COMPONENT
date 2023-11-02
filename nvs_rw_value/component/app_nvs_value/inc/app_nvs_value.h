/**
* @copyright 2023
* @file app_spiffs.h
* @brief produce functions for access to flash spiffs.
* @{
*/

#ifndef __APP_NVS_H
#define __APP_NVS_H
 
#ifdef __cplusplus
extern "C"{
#endif
 
/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "nvs_flash.h"
#include "nvs.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
 
 
/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
 
 
/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/
 
 
/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/
/*debug*/
#define DEBUG
#ifdef DEBUG
#define LREP(tag, format, ...) 				ESP_LOGI(tag, format, ##__VA_ARGS__)
#define LREP_WARNING(tag, format, ...)		ESP_LOGW(tag, format, ##__VA_ARGS__)
#define LREP_ERROR(tag, format, ...)		ESP_LOGE(tag, format, ##__VA_ARGS__)
#define LREP_RAW(format, ...)				printf(format, ##__VA_ARGS__)
#else
#define LREP(tag, format, ...)				{}
#define LREP_WARNING(tag, format, ...)		{}
#define LREP_ERROR(tag, format, ...)		{}
#define LREP_RAW(format, ...)				{}
#endif
/*==================================================================================================
*                                             ENUMS
==================================================================================================*/

 
/*==================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
typedef struct {
    nvs_type_t type;
    const char *str;
} type_str_pair_t;

typedef const char cchar;
 
/*==================================================================================================
*                                GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/
void app_nvs_value_init();
esp_err_t app_nvs_value_open (nvs_open_mode_t open_mode, nvs_handle_t * nvs_handle);
esp_err_t app_nvs_value_commit(nvs_handle_t * nvs_handle);
void app_nvs_value_close(nvs_handle_t * nvs_handle);

nvs_type_t nvs_str_to_type(cchar* type);
cchar* nvs_type_to_str(nvs_type_t type);

void app_nvs_print_blob(const uint8_t *blob, size_t len);

esp_err_t app_nvs_erase_namespace(cchar *partition ,cchar *name_space);
esp_err_t app_nvs_erase(cchar *partition, cchar *name_space, cchar *key);

esp_err_t app_nvs_get_u8(cchar *partition, cchar *name_space, cchar *key, uint8_t *u8);
esp_err_t app_nvs_set_u8(cchar *partition, cchar *name_space, cchar *key, uint8_t u8);
esp_err_t app_nvs_get_i8(cchar *partition, cchar *name_space, cchar *key, int8_t *i8);
esp_err_t app_nvs_set_i8(cchar *partition, cchar *name_space, cchar *key, int8_t i8);
esp_err_t app_nvs_get_u16(cchar *partition, cchar *name_space, cchar *key, uint16_t *u16);
esp_err_t app_nvs_set_u16(cchar *partition, cchar *name_space, cchar *key, uint16_t u16);
esp_err_t app_nvs_get_i16(cchar *partition, cchar *name_space, cchar *key, int16_t *i16);
esp_err_t app_nvs_set_i16(cchar *partition, cchar *name_space, cchar *key, int16_t i16);
esp_err_t app_nvs_get_u32(cchar *partition, cchar *name_space, cchar *key, uint32_t *u32);
esp_err_t app_nvs_set_u32(cchar *partition, cchar *name_space, cchar *key, uint32_t u32);
esp_err_t app_nvs_get_i32(cchar *partition, cchar *name_space, cchar *key, int32_t *i32);
esp_err_t app_nvs_set_i32(cchar *partition, cchar *name_space, cchar *key, int32_t i32);
esp_err_t app_nvs_get_u64(cchar *partition, cchar *name_space, cchar *key, uint64_t *u64);
esp_err_t app_nvs_set_u64(cchar *partition, cchar *name_space, cchar *key, uint64_t u64);
esp_err_t app_nvs_get_i64(cchar *partition, cchar *name_space, cchar *key, int64_t *i64);
esp_err_t app_nvs_set_i64(cchar *partition, cchar *name_space, cchar *key, int64_t i64);
esp_err_t app_nvs_get_str_length(cchar *partition, cchar *name_space, cchar *key, int *length);
esp_err_t app_nvs_get_str(cchar *partition, cchar *name_space, cchar *key, char *str, int length);
esp_err_t app_nvs_set_str(cchar *partition, cchar *name_space, cchar *key, cchar *str);
esp_err_t app_nvs_get_blob_length(cchar *partition, cchar *name_space, cchar *key, int *length);
esp_err_t app_nvs_get_blob(cchar *partition, cchar *name_space, cchar *key, void *blob, int length);
esp_err_t app_nvs_set_blob(cchar *partition, cchar *name_space, cchar *key, const void *blob, int length);
esp_err_t app_nvs_set_blob_str(cchar *partition, cchar *name_space, cchar *key, cchar *str_values);

esp_err_t app_nvs_copy_u8(cchar *partition, cchar *src_name, cchar *src_key, cchar *des_name, cchar *des_key);
esp_err_t app_nvs_copy_i8(cchar *partition, cchar *src_name, cchar *src_key, cchar *des_name, cchar *des_key);
esp_err_t app_nvs_copy_u16(cchar *partition, cchar *src_name, cchar *src_key, cchar *des_name, cchar *des_key);
esp_err_t app_nvs_copy_i16(cchar *partition, cchar *src_name, cchar *src_key, cchar *des_name, cchar *des_key);
esp_err_t app_nvs_copy_u32(cchar *partition, cchar *src_name, cchar *src_key, cchar *des_name, cchar *des_key);
esp_err_t app_nvs_copy_i32(cchar *partition, cchar *src_name, cchar *src_key, cchar *des_name, cchar *des_key);
esp_err_t app_nvs_copy_u64(cchar *partition, cchar *src_name, cchar *src_key, cchar *des_name, cchar *des_key);
esp_err_t app_nvs_copy_i64(cchar *partition, cchar *src_name, cchar *src_key, cchar *des_name, cchar *des_key);
esp_err_t app_nvs_copy_str(cchar *partition, cchar *src_name, cchar *src_key, cchar *des_name, cchar *des_key);
esp_err_t app_nvs_copy_blob(cchar *partition, cchar *src_name, cchar *src_key, cchar *des_name, cchar *des_key);

esp_err_t app_nvs_copy_namespace(cchar *partition, cchar *src, cchar *des);
bool app_nvs_check_namespace(cchar *partition, cchar *name_space);
 
#ifdef __cplusplus
}
#endif
 
#endif /* __APP_NVS_H */
 
/** @} */


