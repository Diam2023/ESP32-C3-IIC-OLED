# For more information about build system see
# https://docs.espressif.com/projects/esp-idf/en/latest/api-guides/build-system.html
# The following five lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.5)

# Build target is esp32c3
set(IDF_TARGET esp32c3)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(ESP32-C3-IIC-OLED)
