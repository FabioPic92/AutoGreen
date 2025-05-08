file(GLOB COMMON_SOURCES "common/*.cpp")
add_library(common_utils ${COMMON_SOURCES})
target_include_directories(common_utils PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_subdirectory(Camera)