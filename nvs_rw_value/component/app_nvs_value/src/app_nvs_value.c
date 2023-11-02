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
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "esp_err.h"
#include "esp_log.h"
#include "../inc/app_nvs_value.h"

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/
#define TYPE_STR_PAIR_SIZE 11
static const type_str_pair_t type_str_pair[TYPE_STR_PAIR_SIZE] = {
    { NVS_TYPE_I8, "i8" },
    { NVS_TYPE_U8, "u8" },
    { NVS_TYPE_U16, "u16" },
    { NVS_TYPE_I16, "i16" },
    { NVS_TYPE_U32, "u32" },
    { NVS_TYPE_I32, "i32" },
    { NVS_TYPE_U64, "u64" },
    { NVS_TYPE_I64, "i64" },
    { NVS_TYPE_STR, "str" },
    { NVS_TYPE_BLOB, "blob" },
    { NVS_TYPE_ANY, "any" },
};

#define APP_NVS_GET(__part, __name, __key, __value, __func) \
	nvs_handle_t nvs;\
	esp_err_t err = ESP_OK;\
	if (__part == NULL) err = nvs_open(__name, NVS_READONLY, &nvs);\
	else err =  nvs_open_from_partition(__part, __name, NVS_READONLY, &nvs);\
	if (err != ESP_OK) return err;\
	err = __func(nvs, __key, __value);\
	nvs_close(nvs);\
	return err;

#define APP_NVS_SET(__part, __name, __key, __value, __func) \
	nvs_handle_t nvs;\
	esp_err_t err = ESP_OK;\
	if (__part == NULL) err = nvs_open(__name, NVS_READWRITE, &nvs);\
	else err = nvs_open_from_partition(__part, __name, NVS_READWRITE, &nvs);\
	if (err != ESP_OK) return err;\
	err = __func(nvs, __key, __value);\
	nvs_commit(nvs);\
	nvs_close(nvs);\
	return err;

#define APP_NVS_SET_PART(__part, __key, __value, __func) \
	nvs_handle_t nvs;\
	esp_err_t err = nvs_open_from_partition(__part, __name, NVS_READWRITE, &nvs);\
	if (err != ESP_OK) return err;\
	err = __func(nvs, __key, __value);\
	nvs_commit(nvs);\
	nvs_close(nvs);\
	return err;

#define APP_NVS_GET(__part, __name, __key, __value, __func) \
	nvs_handle_t nvs;\
	esp_err_t err = ESP_OK;\
	if (__part == NULL) err = nvs_open(__name, NVS_READONLY, &nvs);\
	else err =  nvs_open_from_partition(__part, __name, NVS_READONLY, &nvs);\
	if (err != ESP_OK) return err;\
	err = __func(nvs, __key, __value);\
	nvs_close(nvs);\
	return err;

#define APP_NVS_SET(__part, __name, __key, __value, __func) \
	nvs_handle_t nvs;\
	esp_err_t err = ESP_OK;\
	if (__part == NULL) err = nvs_open(__name, NVS_READWRITE, &nvs);\
	else err = nvs_open_from_partition(__part, __name, NVS_READWRITE, &nvs);\
	if (err != ESP_OK) return err;\
	err = __func(nvs, __key, __value);\
	nvs_commit(nvs);\
	nvs_close(nvs);\
	return err;

#define APP_NVS_SET_PART(__part, __key, __value, __func) \
	nvs_handle_t nvs;\
	esp_err_t err = nvs_open_from_partition(__part, __name, NVS_READWRITE, &nvs);\
	if (err != ESP_OK) return err;\
	err = __func(nvs, __key, __value);\
	nvs_commit(nvs);\
	nvs_close(nvs);\
	return err;

/*==================================================================================================
*                                      LOCAL CONSTANTS
==================================================================================================*/

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
void app_nvs_value_init() {
    /* Initialize NVS */
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        // NVS partition was truncated and needs to be erased
        // Retry nvs_flash_init
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK( err );
}

esp_err_t app_nvs_value_open (nvs_open_mode_t open_mode, nvs_handle_t * nvs_handle) {
    /* Open NVS */
    printf("\n");
    printf("Opening Non-Volatile Storage (NVS) handle... ");
    esp_err_t err = nvs_open("storage", open_mode, nvs_handle);
    if (err != ESP_OK) {
        printf("Error (%s) opening NVS handle!\n", esp_err_to_name(err));
    } else {
        printf("Success to open NVS\n");
    }
    return err;
}

esp_err_t app_nvs_value_commit(nvs_handle_t * nvs_handle) {
	/* 
	 * Commit written value.
	 * After setting any values, nvs_commit() must be called to ensure changes are written
	 * to flash storage. Implementations may write to storage at other times,
	 * but this is not guaranteed. 
	 */
	printf("Committing updates in NVS ... ");
	esp_err_t err = nvs_commit((*nvs_handle));
	printf((err != ESP_OK) ? "Failed!\n" : "Done\n");
	
	return err;
}

void app_nvs_value_close(nvs_handle_t * nvs_handle) {
	// Close
	printf("Closing Non-Volatile Storage (NVS) handle... ");
	nvs_close((*nvs_handle));
}

nvs_type_t nvs_str_to_type(cchar* type) {
	if (type == NULL) return NVS_TYPE_ANY;
	for (int i=0; i < TYPE_STR_PAIR_SIZE; ++i) {
        const type_str_pair_t *p = &type_str_pair[i];
        if (strcmp(type, p->str) == 0) {
            return  p->type;
        }
	}
	return NVS_TYPE_ANY;
}
cchar* nvs_type_to_str(nvs_type_t type) {
	for (int i=0; i < TYPE_STR_PAIR_SIZE; ++i) {
        const type_str_pair_t *p = &type_str_pair[i];
        if (p->type == type) {
            return  p->str;
        }
	}
	return "Unknown";
}

void app_nvs_print_blob(const uint8_t *blob, size_t len) {
    for (int i = 0; i < len; i++) {
    	LREP_RAW("%02x", blob[i]);
    }
    LREP_RAW("\n");
}

esp_err_t app_nvs_erase_namespace(cchar *partition, cchar *name_space) {
	nvs_handle_t nvs;
	esp_err_t err = ESP_OK;
	if (partition == NULL) err = nvs_open(name_space, NVS_READWRITE, &nvs);
	else err = nvs_open_from_partition(partition, name_space, NVS_READWRITE, &nvs);
    if (err != ESP_OK) return err;
    do {
    	err = nvs_erase_all(nvs);
    	if (err != ESP_OK) break;

    	err = nvs_commit(nvs);
    	 if (err != ESP_OK) break;
    } while (0);

    LREP(__func__, "Namespace '%s' was %s erased", name_space, (err == ESP_OK) ? "" : "not");
    nvs_close(nvs);
    return err;
}

esp_err_t app_nvs_erase(cchar *partition, cchar *name_space, cchar *key) {
    nvs_handle_t nvs;
    esp_err_t err = ESP_OK;
    if (partition == NULL) err = nvs_open(name_space, NVS_READWRITE, &nvs);
    else err = nvs_open_from_partition(partition, name_space, NVS_READWRITE, &nvs);
    if (err != ESP_OK) return err;
	do {
		err = nvs_erase_key(nvs, key);
		if (err != ESP_OK) break;

		err = nvs_commit(nvs);
		if (err != ESP_OK) break;
	} while (0);

	if (err == ESP_OK) LREP(__func__, "Value with key '%s' erased", key);
	else LREP_WARNING(__func__, "err %s", esp_err_to_name(err));

	nvs_close(nvs);
    return err;
}

esp_err_t app_nvs_get_u8(cchar *partition, cchar *name_space, cchar *key, uint8_t *u8) {
	APP_NVS_GET(partition, name_space, key, u8, nvs_get_u8);
}

esp_err_t app_nvs_set_u8(cchar *partition, cchar *name_space, cchar *key, uint8_t u8) {
	APP_NVS_SET(partition, name_space, key, u8, nvs_set_u8);
}

esp_err_t app_nvs_get_i8(cchar *partition, cchar *name_space, cchar *key, int8_t *i8) {
	APP_NVS_GET(partition, name_space, key, i8, nvs_get_i8);
}

esp_err_t app_nvs_set_i8(cchar *partition, cchar *name_space, cchar *key, int8_t i8) {
	APP_NVS_SET(partition, name_space, key, i8, nvs_set_i8);
}

esp_err_t app_nvs_get_u16(cchar *partition, cchar *name_space, cchar *key, uint16_t *u16) {
	APP_NVS_GET(partition, name_space, key, u16, nvs_get_u16);
}

esp_err_t app_nvs_set_u16(cchar *partition, cchar *name_space, cchar *key, uint16_t u16) {
	APP_NVS_SET(partition, name_space, key, u16, nvs_set_u16);
}

esp_err_t app_nvs_get_i16(cchar *partition, cchar *name_space, cchar *key, int16_t *i16) {
	APP_NVS_GET(partition, name_space, key, i16, nvs_get_i16);
}

esp_err_t app_nvs_set_i16(cchar *partition, cchar *name_space, cchar *key, int16_t i16) {
	APP_NVS_SET(partition, name_space, key, i16, nvs_set_i16);
}

esp_err_t app_nvs_get_u32(cchar *partition, cchar *name_space, cchar *key, uint32_t *u32) {
	APP_NVS_GET(partition, name_space, key, u32, nvs_get_u32);
}

esp_err_t app_nvs_set_u32(cchar *partition, cchar *name_space, cchar *key, uint32_t u32) {
	APP_NVS_SET(partition, name_space, key, u32, nvs_set_u32);
}

esp_err_t app_nvs_get_i32(cchar *partition, cchar *name_space, cchar *key, int32_t *i32) {
	APP_NVS_GET(partition, name_space, key, i32, nvs_get_i32);
}

esp_err_t app_nvs_set_i32(cchar *partition, cchar *name_space, cchar *key, int32_t i32) {
	APP_NVS_SET(partition, name_space, key, i32, nvs_set_i32);
}

esp_err_t app_nvs_get_u64(cchar *partition, cchar *name_space, cchar *key, uint64_t *u64) {
	APP_NVS_GET(partition, name_space, key, u64, nvs_get_u64);
}

esp_err_t app_nvs_set_u64(cchar *partition, cchar *name_space, cchar *key, uint64_t u64) {
	APP_NVS_SET(partition, name_space, key, u64, nvs_set_u64);
}

esp_err_t app_nvs_get_i64(cchar *partition, cchar *name_space, cchar *key, int64_t *i64) {
	APP_NVS_GET(partition, name_space, key, i64, nvs_get_i64);
}

esp_err_t app_nvs_set_i64(cchar *partition, cchar *name_space, cchar *key, int64_t i64) {
	APP_NVS_SET(partition, name_space, key, i64, nvs_set_i64);
}

esp_err_t app_nvs_get_str_length(cchar *partition, cchar *name_space, cchar *key, int *length) {
	nvs_handle_t nvs;
	esp_err_t err = ESP_OK;
	if (partition == NULL) err = nvs_open(name_space, NVS_READONLY, &nvs);
	else err = nvs_open_from_partition(partition, name_space, NVS_READONLY, &nvs);
	if (err != ESP_OK) return err;
	err = nvs_get_str(nvs, key, NULL, (size_t *)length);
	nvs_close(nvs);
	return err;
}

esp_err_t app_nvs_get_str(cchar *partition, cchar *name_space, cchar *key, char *str, int length) {
	nvs_handle_t nvs;
	esp_err_t err = ESP_OK;
	if (partition == NULL) err = nvs_open(name_space, NVS_READONLY, &nvs);
	else err = nvs_open_from_partition(partition, name_space, NVS_READONLY, &nvs);
	if (err != ESP_OK) return err;
	err = nvs_get_str(nvs, key, str, (size_t *)&length);
	nvs_close(nvs);
	return err;
}

esp_err_t app_nvs_set_str(cchar *partition, cchar *name_space, cchar *key, cchar *str) {
	nvs_handle_t nvs;
	esp_err_t err = ESP_OK;
	if (partition == NULL) err = nvs_open(name_space, NVS_READWRITE, &nvs);
	else err = nvs_open_from_partition(partition, name_space, NVS_READWRITE, &nvs);
	if (err != ESP_OK) return err;
	do {
		err = nvs_set_str(nvs, key, str);
		if (err != ESP_OK) break;

		err = nvs_commit(nvs);
		if (err != ESP_OK) break;
	} while(0);

	nvs_close(nvs);
	return err;
}

esp_err_t app_nvs_get_blob_length(cchar *partition, cchar *name_space, cchar *key, int *length) {
	nvs_handle_t nvs;
	esp_err_t err = ESP_OK;
	if (partition == NULL) err = nvs_open(name_space, NVS_READONLY, &nvs);
	else err = nvs_open_from_partition(partition, name_space, NVS_READONLY, &nvs);
	if (err != ESP_OK) return err;
	err = nvs_get_blob(nvs, key, NULL, (size_t *)length);
	nvs_close(nvs);
	return err;
}

esp_err_t app_nvs_get_blob(cchar *partition, cchar *name_space, cchar *key, void *blob, int length) {
	nvs_handle_t nvs;
	esp_err_t err = ESP_OK;
	if(partition == NULL) err = nvs_open(name_space, NVS_READONLY, &nvs);
	else err = nvs_open_from_partition(partition, name_space, NVS_READONLY, &nvs);
	if (err != ESP_OK) return err;
	err = nvs_get_blob(nvs, key, blob, (size_t *)&length);
	nvs_close(nvs);
	return err;
}

esp_err_t app_nvs_set_blob(cchar *partition, cchar *name_space, cchar *key, const void *blob, int length) {
	nvs_handle_t nvs;
	esp_err_t err = ESP_OK;
	if(partition == NULL) err = nvs_open(name_space, NVS_READWRITE, &nvs);
	else err = nvs_open_from_partition(partition, name_space, NVS_READWRITE, &nvs);
	if (err != ESP_OK) return err;
	do {
		err = nvs_set_blob(nvs, key, blob, length);
		if (err != ESP_OK) break;

		err = nvs_commit(nvs);
		if (err != ESP_OK) break;
	} while (0);
	nvs_close(nvs);
	return err;
}

esp_err_t app_nvs_set_blob_str(cchar *partition, cchar *name_space, cchar *key, cchar *str_values) {
    uint8_t value;
    size_t str_len = strlen(str_values);
    size_t blob_len = str_len / 2;

    if (str_len % 2) {
    	LREP_ERROR(__func__, "Blob data must contain even number of characters");
        return ESP_ERR_NVS_TYPE_MISMATCH;
    }

    char *blob = (char *)malloc(blob_len);
    if (blob == NULL) {
        return ESP_ERR_NO_MEM;
    }

    for (int i = 0, j = 0; i < str_len; i++) {
        char ch = str_values[i];
        if (ch >= '0' && ch <= '9') {
            value = ch - '0';
        } else if (ch >= 'A' && ch <= 'F') {
            value = ch - 'A' + 10;
        } else if (ch >= 'a' && ch <= 'f') {
            value = ch - 'a' + 10;
        } else {
        	LREP_ERROR(__func__, "Blob data contain invalid character");
            free(blob);
            return ESP_ERR_NVS_TYPE_MISMATCH;
        }

        if (i & 1) {
            blob[j++] += value;
        } else {
            blob[j] = value << 4;
        }
    }

    esp_err_t err = app_nvs_set_blob(partition, name_space, key, blob, blob_len);
    free(blob);
    return err;
}

esp_err_t app_nvs_copy_u8(cchar *partition, cchar *src_name, cchar *src_key, cchar *des_name, cchar *des_key) {
	esp_err_t err = ESP_OK;
	uint8_t value;
	if ((err = app_nvs_get_u8(partition, src_name, src_key, &value)) != ESP_OK) return err;
	if ((err = app_nvs_set_u8(partition, des_name, des_key, value)) != ESP_OK) return err;
	return err;
}

esp_err_t app_nvs_copy_i8(cchar *partition, cchar *src_name, cchar *src_key, cchar *des_name, cchar *des_key) {
	esp_err_t err = ESP_OK;
	int8_t value;
	if ((err = app_nvs_get_i8(partition, src_name, src_key, &value)) != ESP_OK) return err;
	if ((err = app_nvs_set_i8(partition, des_name, des_key, value)) != ESP_OK) return err;
	return err;
}

esp_err_t app_nvs_copy_u16(cchar *partition, cchar *src_name, cchar *src_key, cchar *des_name, cchar *des_key) {
	esp_err_t err = ESP_OK;
	uint16_t value;
	if ((err = app_nvs_get_u16(partition, src_name, src_key, &value)) != ESP_OK) return err;
	if ((err = app_nvs_set_u16(partition, des_name, des_key, value)) != ESP_OK) return err;
	return err;
}

esp_err_t app_nvs_copy_i16(cchar *partition, cchar *src_name, cchar *src_key, cchar *des_name, cchar *des_key) {
	esp_err_t err = ESP_OK;
	int16_t value;
	if ((err = app_nvs_get_i16(partition, src_name, src_key, &value)) != ESP_OK) return err;
	if ((err = app_nvs_set_i16(partition, des_name, des_key, value)) != ESP_OK) return err;
	return err;
}

esp_err_t app_nvs_copy_u32(cchar *partition, cchar *src_name, cchar *src_key, cchar *des_name, cchar *des_key) {
	esp_err_t err = ESP_OK;
	uint32_t value;
	if ((err = app_nvs_get_u32(partition, src_name, src_key, &value)) != ESP_OK) return err;
	if ((err = app_nvs_set_u32(partition, des_name, des_key, value)) != ESP_OK) return err;
	return err;
}

esp_err_t app_nvs_copy_i32(cchar *partition, cchar *src_name, cchar *src_key, cchar *des_name, cchar *des_key) {
	esp_err_t err = ESP_OK;
	int32_t value;
	if ((err = app_nvs_get_i32(partition, src_name, src_key, &value)) != ESP_OK) return err;
	if ((err = app_nvs_set_i32(partition, des_name, des_key, value)) != ESP_OK) return err;
	return err;
}

esp_err_t app_nvs_copy_u64(cchar *partition, cchar *src_name, cchar *src_key, cchar *des_name, cchar *des_key) {
	esp_err_t err = ESP_OK;
	uint64_t value;
	if ((err = app_nvs_get_u64(partition, src_name, src_key, &value)) != ESP_OK) return err;
	if ((err = app_nvs_set_u64(partition, des_name, des_key, value)) != ESP_OK) return err;
	return err;
}

esp_err_t app_nvs_copy_i64(cchar *partition, cchar *src_name, cchar *src_key, cchar *des_name, cchar *des_key) {
	esp_err_t err = ESP_OK;
	int64_t value;
	if ((err = app_nvs_get_i64(partition, src_name, src_key, &value)) != ESP_OK) return err;
	if ((err = app_nvs_set_i64(partition, des_name, des_key, value)) != ESP_OK) return err;
	return err;
}

esp_err_t app_nvs_copy_str(cchar *partition, cchar *src_name, cchar *src_key, cchar *des_name, cchar *des_key) {
	esp_err_t err = ESP_OK;
	int length = 0;
	if ((err = app_nvs_get_str_length(partition, src_name, src_key, &length)) != ESP_OK) return err;

	char *str = (char *)calloc(length + 1, sizeof(char));
	if (str == NULL) {LREP_ERROR(__func__, "calloc failed"); return ESP_ERR_NO_MEM;}

	do {
		if ((err == app_nvs_get_str(partition, src_name, src_key, str, length)) != ESP_OK) break;
		if ((err == app_nvs_set_str(partition, des_name, des_key, str)) != ESP_OK) break;
	} while(0);

	free(str);
	return err;
}

esp_err_t app_nvs_copy_blob(cchar *partition, cchar *src_name, cchar *src_key, cchar *des_name, cchar *des_key) {
	esp_err_t err = ESP_OK;
	int length = 0;
	if ((err = app_nvs_get_blob_length(partition, src_name, src_key, &length)) != ESP_OK) return err;

	uint8_t *blob = (uint8_t *)malloc(length);
	if (blob == NULL) {LREP_ERROR(__func__, "malloc failed"); return ESP_ERR_NO_MEM;}

	do {
		if ((err = app_nvs_get_blob(partition, src_name, src_key, blob, length)) != ESP_OK) break;
		if ((err = app_nvs_set_blob(partition, des_name, des_key, blob, length)) != ESP_OK) break;
	} while (0);

	free(blob);

	return err;
}

esp_err_t app_nvs_copy_namespace(cchar *partition, cchar *src, cchar *des) {
	esp_err_t err = ESP_OK;
	nvs_iterator_t it = nvs_entry_find((partition==NULL) ? NVS_DEFAULT_PART_NAME : partition, src, NVS_TYPE_ANY);
	if (it == NULL) {
		LREP_ERROR(__func__, "Src namespace was not found");
		return ESP_ERR_NVS_NOT_FOUND;
	}
	int xcount = 0;
	do {
		nvs_entry_info_t info;
		nvs_entry_info(it, &info);
		LREP(__func__, "copy %s", info.key);
		if (info.type == NVS_TYPE_U8)
			err = app_nvs_copy_u8(partition, src, info.key, des, info.key);
		else if (info.type == NVS_TYPE_I8)
			err = app_nvs_copy_i8(partition, src, info.key, des, info.key);
		else if (info.type == NVS_TYPE_U16)
			err = app_nvs_copy_u16(partition, src, info.key, des, info.key);
		else if (info.type == NVS_TYPE_I16)
			err = app_nvs_copy_i16(partition, src, info.key, des, info.key);
		else if (info.type == NVS_TYPE_U32)
			err = app_nvs_copy_u32(partition, src, info.key, des, info.key);
		else if (info.type == NVS_TYPE_I32)
			err = app_nvs_copy_i32(partition, src, info.key, des, info.key);
		else if (info.type == NVS_TYPE_U64)
			err = app_nvs_copy_u64(partition, src, info.key, des, info.key);
		else if (info.type == NVS_TYPE_I64)
			err = app_nvs_copy_i64(partition, src, info.key, des, info.key);
		else if (info.type == NVS_TYPE_STR)
			err = app_nvs_copy_str(partition, src, info.key, des, info.key);
		else if (info.type == NVS_TYPE_BLOB)
			err = app_nvs_copy_blob(partition, src, info.key, des, info.key);
		else {
			LREP_WARNING(__func__, "nvs type is not implemented");
		}
		if (err != ESP_OK) {
			LREP_ERROR(__func__, "%s", esp_err_to_name(err));
		}
		it = nvs_entry_next(it);
		xcount++;
	} while (it != NULL);
	LREP_WARNING(__func__, "xcount %d", xcount);
	return err;
}

bool app_nvs_check_namespace(cchar *partition, cchar *name_space) {
	nvs_iterator_t it = nvs_entry_find((partition == NULL) ? NVS_DEFAULT_PART_NAME : partition, name_space, NVS_TYPE_ANY);
	if (it == NULL) return false;
	int xcount = 0;
	do {
        nvs_entry_info_t info;
        nvs_entry_info(it, &info);
        it = nvs_entry_next(it);
        cchar* info_str_type = nvs_type_to_str(info.type);
        LREP(__func__, "namespace '%s', key '%s', type '%s'", info.namespace_name, info.key, info_str_type);
        xcount++;
	} while (it != NULL);
	LREP_WARNING(__func__, "xcount %d", xcount);
	return true;
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