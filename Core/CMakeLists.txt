cmake_minimum_required(VERSION 3.30)
project(AutoGreen)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON) 

set(CMAKE_PREFIX_PATH "/usr/lib/qt6/" CACHE PATH "Path to Qt6 installation")

find_package(Qt6 COMPONENTS Widgets REQUIRED)

find_package(OpenCV REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/include)

set(OpenCV_INCLUDE_DIRS ${OpenCV_INCLUDE_DIRS} CACHE INTERNAL "")
set(OpenCV_LIBS ${OpenCV_LIBS} CACHE INTERNAL "")

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
