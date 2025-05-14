cmake_minimum_required(VERSION 3.14)
project(AutoGreen)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/include)

set(PahoMqttCpp_LIBRARY_PATH "${CMAKE_SOURCE_DIR}/external/paho/paho.mqtt.cpp/build/src")
set(PahoMqttC_LIBRARY_PATH "${CMAKE_SOURCE_DIR}/external/paho/paho.mqtt.c/build/src")

find_library(PahoMqttCpp_SHARED_LIBRARY NAMES libpaho-mqttpp3.so PATHS ${PahoMqttCpp_LIBRARY_PATH})
find_library(PahoMqttC_SHARED_LIBRARY NAMES libpaho-mqtt3c.a PATHS ${PahoMqttC_LIBRARY_PATH})

include_directories(
    "${CMAKE_SOURCE_DIR}/external/paho/paho.mqtt.c/src"
    "${CMAKE_SOURCE_DIR}/external/paho/paho.mqtt.cpp/include/mqtt"
)

include_directories(external/json/single_include)

add_subdirectory(src)
