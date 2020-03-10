cmake_minimum_required(VERSION 3.10)

#-------------------------------------------------------------------------------
# BASIC SETUP
#-------------------------------------------------------------------------------

set(prog_name    fu540-fsbl)
set(src_dir      ${CMAKE_CURRENT_LIST_DIR})
set(scripts_dir  ${src_dir}/scripts)
set(lds_dir      ${src_dir}/lds)

#-------------------------------------------------------------------------------
# Program and flags
#-------------------------------------------------------------------------------

include(macros.cmake)
include(config.cmake)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE    "Debug")
else()
    if ((NOT CMAKE_BUILD_TYPE STREQUAL "Debug") AND (NOT CMAKE_BUILD_TYPE STREQUAL "Release"))
    message(FATAL_ERROR "CMAKE_BUILD_TYPE must either be Denug or Release instead of ${CMAKE_BUILD_TYPE}")
    endif()
endif()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDEBUG=1)
endif()

execute_process(
    COMMAND which riscv64-unknown-elf-gcc
    OUTPUT_VARIABLE CROSSCOMPILE
    RESULT_VARIABLE ERROR)
    
if (NOT "${ERROR}" STREQUAL 0)
    message(FATAL_ERROR "RISCV Toochain is not found")
endif()

string(STRIP ${CROSSCOMPILE} CROSSCOMPILE)
string(REPLACE "gcc" "" CROSSCOMPILE ${CROSSCOMPILE})

message(STATUS "Tagret tripplet: ${CROSSCOMPILE}")

set(CC              ${CROSSCOMPILE}gcc)
set(CXX             ${CROSSCOMPILE}g++)
set(LD              ${CROSSCOMPILE}ld)
set(AR              ${CROSSCOMPILE}ar)
set(OBJCOPY         ${CROSSCOMPILE}objcopy)
set(OBJDUMP         ${CROSSCOMPILE}objdump)
set(CFLAGS          "-I. -Ilib/ -O2 -ggdb -march=rv64imafdc -mabi=lp64d -Wall -mcmodel=medany -mexplicit-relocs ${FPGA_FLAGS}")
set(ASMFLAGS        "-I. -mcmodel=medany -mexplicit-relocs")
set(LDFLAGS         "-nostdlib -nostartfiles")

if (WIN32)
    set(EXT  ".exe")
else()
    set(EXT  "")
endif()

global_set(CMAKE_C_COMPILER        ${CC}${EXT})
global_set(CMAKE_CXX_COMPILER      ${CXX}${EXT})
global_set(CMAKE_LINKER            ${LD}${EXT})
global_set(CMAKE_AR                ${AR}${EXT})
global_set(CMAKE_OBJCOPY           ${OBJCOPY}${EXT})
global_set(CMAKE_OBJDUMP           ${OBJDUMP}${EXT})
global_set(CMAKE_C_FLAGS           ${CMAKE_C_FLAGS} ${CFLAGS})
global_set(CMAKE_ASM_FLAGS         ${CMAKE_ASM_FLAGS} ${ASMFLAGS})
global_set(CMAKE_EXE_LINKER_FLAGS  ${CMAKE_EXE_LINKER_FLAGS} ${LDFLAGS})

check_compiler(${CMAKE_C_COMPILER})
check_compiler(${CMAKE_CXX_COMPILER})

global_set(CMAKE_C_COMPILER_WORKS      1)
global_set(CMAKE_CXX_COMPILER_WORKS    1)

global_set(CMAKE_SYSTEM_NAME    "Generic")

################################################################################
# BUILD PROJECTS
################################################################################

project(${prog_name} C ASM)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T${src_dir}/lds/memory.lds -T${src_dir}/lds/ux00_fsbl.lds")

include_directories(${src_dir})

add_subdirectory(drivers)
add_subdirectory(keycore_driver)
add_subdirectory(ux00boot)

set(DTB_INPUT_PATH   ${CMAKE_SOURCE_DIR}/fsbl/ux00_fsbl.dts)
set(DTB_OUTPUT_PATH  ${CMAKE_BINARY_DIR}/ux00_fsbl.dtb)
        
execute_process(
    COMMAND dtc ${DTB_INPUT_PATH} -o ${DTB_OUTPUT_PATH}
    OUTPUT_FILE OUTPUT 
    RESULT_VARIABLE ERROR)
    
execute_process(
    COMMAND git describe --always --dirty
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
    OUTPUT_VARIABLE GIT_ID
    RESULT_VARIABLE ERROR)
string(STRIP ${GIT_ID} GIT_ID)
    
execute_process(
    COMMAND git log -n 1 --date=short --format=format:"%ad.%h" HEAD
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
    OUTPUT_VARIABLE GIT_DATE
    RESULT_VARIABLE ERROR)
string(STRIP ${GIT_DATE} GIT_DATE)
    
execute_process(
    COMMAND git log -n 1 --date=short --format=format:"%ad.%h" HEAD
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
    OUTPUT_VARIABLE GIT_VERSION
    RESULT_VARIABLE ERROR)
string(STRIP ${GIT_VERSION} GIT_VERSION)
    
configure_file(
    ${CMAKE_SOURCE_DIR}/fsbl/dtb.S.in
    ${CMAKE_SOURCE_DIR}/fsbl/dtb.S)
    
configure_file(
    ${CMAKE_SOURCE_DIR}/fsbl/version.c.in
    ${CMAKE_CURRENT_SOURCE_DIR}/fsbl/version.c)
    
set(SOURCE_FILES
        fsbl/version.c
        fsbl/dtb.S
        fsbl/start.S
        fsbl/main.c
        lib/memcpy.c
        lib/memset.S
        lib/strcmp.S
        lib/strcpy.c
        lib/strlen.c)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} fu540_drivers keycore_driver ux00boot)

add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${OBJCOPY} -O binary ${PROJECT_NAME} ${PROJECT_NAME}.bin
)






