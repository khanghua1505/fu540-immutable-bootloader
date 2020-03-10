cmake_minimum_required(VERSION 3.10)

project(fu540_drivers C ASM)

include(${CMAKE_SOURCE_DIR}/macros.cmake)

set(SOURCE_FILES    "")
set(INCLUDE_DIRS    "")
set(DEFINES         "")

list(APPEND INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR})

subdirs_list(subdirs ${CMAKE_CURRENT_SOURCE_DIR})

foreach(subdir ${subdirs})
    include(${CMAKE_CURRENT_SOURCE_DIR}/${subdir}/${subdir}.cmake)  
    list(APPEND DEFINES ${${subdir}_DEFINES})
    add_files(SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/${subdir} ${${subdir}_SOURCE_FILES})
    add_files(INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/${subdir} ${${subdir}_INCLUDE_DIRS})
endforeach()

add_library(${PROJECT_NAME} ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIRS})


