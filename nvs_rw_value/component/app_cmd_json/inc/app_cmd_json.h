/**
* @copyright 2023
* @file app_spiffs.h
* @brief produce functions for access to flash spiffs.
* @{
*/

#ifndef __APP_CMD_JSON_H
#define __APP_CMD_JSON_H
 
#ifdef __cplusplus
extern "C"{
#endif
 
/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "cJSON.h"
#include <string.h>

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
#define PARAM_INT_VALUE_ADD(__JS_ARRAY, __PARAM, __VALUE) \
	do{\
		cJSON* pX = cJSON_CreateObject();\
		cJSON_AddStringToObject(pX, "param", __PARAM);\
		cJSON_AddNumberToObject(pX, "value", __VALUE);\
		cJSON_AddItemToArray(__JS_ARRAY, pX);\
	}while(0)

#define ROUND_FLOAT_NUMBER(__VALUE) (roundf(__VALUE * 100) / 100)

#define PARAM_FLOAT_ADD(__JS_ARRAY, __PARAM, __VALUE) \
	do{\
		char strBuff[64] = {0};\
		sprintf(strBuff, "%0.2f", __VALUE);\
		cJSON* pX = cJSON_CreateObject();\
		cJSON_AddStringToObject(pX, "param", __PARAM);\
		cJSON_AddRawToObject(pX, "value", strBuff);\
		cJSON_AddItemToArray(__JS_ARRAY, pX);\
	}while(0)

#define VALUE_FLOAT_ADD(__P_VALUE, __PARAM, __VALUE) \
	do{\
		char strBuff[20] = {0};\
		sprintf(strBuff, "%0.2f", __VALUE);\
		cJSON_AddRawToObject(__P_VALUE, __PARAM, strBuff);\
	}while(0)

#define json_check_object(__JSON) 		(__JSON != NULL && cJSON_IsObject(__JSON))
#define json_check_array(__JSON) 		(__JSON != NULL && cJSON_IsArray(__JSON))
#define json_check_string(__JSON)		(__JSON != NULL && cJSON_IsString(__JSON))
#define json_check_number(__JSON)		(__JSON != NULL && cJSON_IsNumber(__JSON))

#define json_cmp_str(__JSON_STR, __STR) strcmp(__JSON_STR->valuestring, __STR) == 0
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

 
#ifdef __cplusplus
}
#endif
 
#endif /* __APP_CMD_JSON_H */
 
/** @} */


