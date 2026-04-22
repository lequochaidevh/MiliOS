cmake_minimum_required(VERSION 3.10)
project(harisV001 C)

include_directories(
    common
    common/data
    core/inc
)

file(GLOB_RECURSE COMMON_SOURCES "common/*.c")
file(GLOB_RECURSE CORE_SOURCES "core/src/*.c")
file(GLOB_RECURSE APP_SOURCES "app/*.c")

add_executable(${PROJECT_NAME} ${COMMON_SOURCES} ${CORE_SOURCES} ${APP_SOURCES})

# add_library(${PROJECT_NAME} STATIC ${SOURCES})

set(CMAKE_C_STANDARD 99)
add_definitions(-DHARIS_KERNEL_VERSION="0.0.1")