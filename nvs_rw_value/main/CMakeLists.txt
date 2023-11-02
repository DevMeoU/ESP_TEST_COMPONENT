set(APP_SRC
    "nvs_value_main.c"
    "../component/app_nvs_value/src/app_nvs_value.c"
    "../component/app_cmd_json/src/app_cmd_json.c"
)

message(STATUS "APP_SRC: ${APP_SRC}")

set(COMPONENTS_REQ
        nvs_flash
        spiffs
        json
)

message(STATUS "COMPONENTS_REQ: ${COMPONENTS_REQ}")

set(APP_INCLUDES
        "."
        "../component/app_nvs_value/inc"
        "../component/app_cmd_json/inc"
)

message(STATUS "APP_INCLUDES: ${APP_INCLUDES}")

idf_component_register(
        SRCS ${APP_SRC}
        INCLUDE_DIRS ${APP_INCLUDES}
        REQUIRES ${COMPONENTS_REQ}
)