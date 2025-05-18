file(GLOB COMMON_SOURCES "utils/*.cpp")

if(COMMON_SOURCES)
    add_library(utils ${COMMON_SOURCES})
    target_include_directories(utils PUBLIC ${CMAKE_SOURCE_DIR}/include)
else()
    message(WARNING "utils: no file .cpp found!")
endif()

add_subdirectory(Camera)

add_executable(core Core.cpp)

target_link_libraries(core
    utils
    ${OpenCV_LIBS}
    ${PahoMqttCpp_SHARED_LIBRARY}
    ${PahoMqttC_SHARED_LIBRARY}
    pthread
)