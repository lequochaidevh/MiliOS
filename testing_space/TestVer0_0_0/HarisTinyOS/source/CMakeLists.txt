cmake_minimum_required(VERSION 3.10)
project(dummy_app CXX C)
set(CMAKE_BUILD_TYPE Debug)
include_directories(
    application
    common/command
    common/container
    common/io_xput
    common/pch
    common/util
    core/inc
    test/x86_64/v001/
    test/x86_64/v001/fake_sys_inc
)

file(GLOB_RECURSE COMMON_SOURCES "common/*.c")
file(GLOB_RECURSE CORE_SOURCES "core/src/*.c")
file(GLOB_RECURSE APP_SOURCES "application/*.cpp")
file(GLOB_RECURSE TEST_SOURCES "test/x86_64/v001/*.cpp")
file(GLOB_RECURSE TEST_C_SOURCES "test/x86_64/v001/*.c")

add_executable(${PROJECT_NAME} ${COMMON_SOURCES} ${CORE_SOURCES} ${APP_SOURCES} ${TEST_SOURCES} ${TEST_C_SOURCES})

# add_library(${PROJECT_NAME} STATIC ${SOURCES})

set(CMAKE_C_STANDARD 99)
add_definitions(-DHARIS_KERNEL_VERSION="0.0.1")