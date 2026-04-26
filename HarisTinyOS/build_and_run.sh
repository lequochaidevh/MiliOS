#!/bin/bash

PLATFORM_TARGET="x86_64"
APP_NAME="dummy_app"
CMAKE_TARGET_DIR="source/platform/${PLATFORM_TARGET}/${APP_NAME}/CMakeLists.txt"

# Copy CMake compatiable with platform
cp $CMAKE_TARGET_DIR source/

BUILD_DIR="${PLATFORM_TARGET}_build_${APP_NAME}"

# Clean sstate
rm -rf $BUILD_DIR
mkdir $BUILD_DIR

# BUILD
cd $BUILD_DIR
cmake ../source/ 
make

# Clean screen
clear

# Run app
./dummy_app
