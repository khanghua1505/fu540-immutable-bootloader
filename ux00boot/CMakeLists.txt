cmake_minimum_required(VERSION 3.10)

project(ux00boot C ASM)

set(UX00BOOT_BOOT_STATE_FLAG  "-DUX00BOOT_BOOT_STAGE=1")

set(SOURCE_FILES    ux00boot.c)

add_definitions(${UX00BOOT_BOOT_STATE_FLAG})

add_library(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} fu540_drivers)

