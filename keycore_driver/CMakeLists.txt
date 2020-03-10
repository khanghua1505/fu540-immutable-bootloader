cmake_minimum_required(VERSION 3.10)

project(keycore_driver C ASM)

include(interfaces/interfaces.cmake)

set(SOURCE_FILES    "")
set(INCLUDE_DIRS    "")

add_files(SOURCE_FILES interfaces ${INTERFACES_SOURCE_FILES})
add_files(INCLUDE_DIRS interfaces ${INTERFACES_INCLUDE_DIRS})

list(APPEND INCLUDE_DIRS include)
list(APPEND SOURCE_FILES src/keycore.c)

include_directories(${INCLUDE_DIRS} include/keycore_driver)

add_library(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} fu540_drivers)

target_include_directories(${PROJECT_NAME} PUBLIC include)








