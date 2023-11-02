/**
* @copyright 2023
* @file app_spiffs.h
* @brief produce functions for access to flash spiffs.
* @{
*/

#ifndef __APP_SPIFFS_H
#define __APP_SPIFFS_H
 
#ifdef __cplusplus
extern "C"{
#endif
 
/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include <string.h>
#include <stdint.h>
#include <sys/unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

#include "esp_err.h"
#include "esp_log.h"
#include "esp_spiffs.h"

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
 
 
/*==================================================================================================
*                                             ENUMS
==================================================================================================*/
 
 
/*==================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
 
 
/*==================================================================================================
*                                GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/
 
/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/
esp_err_t app_spiffs_init();

esp_err_t app_spiffs_deinit();

esp_err_t app_spiffs_read_file(const char * fileName, char * buffer, int maximumLen);

esp_err_t app_spiffs_write_file(const char * fileName, const char * buffer);

esp_err_t app_spiffs_delete_file(const char * fileName);

esp_err_t app_spiffs_rename_file(const char * fileOldName, const char * fileNewName);

long app_spiffs_check_file_size(const char *fileName);
 
#ifdef __cplusplus
}
#endif
 
#endif /* __APP_SPIFFS_H */
 
/** @} */


