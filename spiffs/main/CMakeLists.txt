set(APP_SRC
    "spiffs_main.c"
    "../component/app_spiffs/src/app_spiffs.c"
)

message(STATUS "APP_SRC: ${APP_SRC}")

set(COMPONENTS_REQ
        nvs_flash
        spiffs
)

message(STATUS "COMPONENTS_REQ: ${COMPONENTS_REQ}")

set(APP_INCLUDES
        "."
        "../component/app_spiffs/inc"
)

message(STATUS "APP_INCLUDES: ${APP_INCLUDES}")

idf_component_register(
        SRCS ${APP_SRC}
        INCLUDE_DIRS ${APP_INCLUDES}
        REQUIRES ${COMPONENTS_REQ}
)

spiffs_create_partition_image(storage ../spiffs_data FLASH_IN_PROJECT)