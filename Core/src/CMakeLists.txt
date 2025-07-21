file(GLOB COMMON_SOURCES 
    "utils/*.cpp")

if(COMMON_SOURCES)
    add_library(utils ${COMMON_SOURCES})
    target_include_directories(utils PUBLIC ${CMAKE_SOURCE_DIR}/include)
    target_link_libraries(utils PUBLIC Qt6::Widgets)
else()
    message(WARNING "utils: no file .cpp found!")
endif()

add_executable(core 
                Core.cpp 
                UI/MainWindow.cpp
                ${CMAKE_SOURCE_DIR}/include/UI/MainWindow.hpp
                UI/Pages/MainPage.cpp
                ${CMAKE_SOURCE_DIR}/include/UI/Pages/MainPage.hpp
                UI/Pages/PageAbstract.cpp
                ${CMAKE_SOURCE_DIR}/include/UI/Pages/PageAbstract.hpp
                utils/PageManager.cpp              
                ${CMAKE_SOURCE_DIR}/include/PageManager.hpp)

target_compile_features(core PRIVATE cxx_std_20)

target_link_libraries(core PRIVATE
    Qt6::Core
    Qt6::Widgets
    utils
    # ${OpenCV_LIBS}
    ${PahoMqttCpp_SHARED_LIBRARY}
    ${PahoMqttC_SHARED_LIBRARY}
    pthread
)

target_include_directories(core PRIVATE
    ${CMAKE_SOURCE_DIR}/include 
    #${OpenCV_INCLUDE_DIRS}
    "${CMAKE_SOURCE_DIR}/external/paho/paho.mqtt.c/src"
    "${CMAKE_SOURCE_DIR}/external/paho/paho.mqtt.cpp/include/mqtt"
    #"${CMAKE_SOURCE_DIR}/external/json/single_include"
)

add_subdirectory(Motor)

