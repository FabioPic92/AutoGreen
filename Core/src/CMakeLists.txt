file(GLOB COMMON_SOURCES "common_utils/*.cpp")

if(COMMON_SOURCES)
    add_library(common_utils ${COMMON_SOURCES})
    target_include_directories(common_utils PUBLIC ${CMAKE_SOURCE_DIR}/include)
else()
    message(WARNING "common_utils: nessun file .cpp trovato!")
endif()

add_subdirectory(Camera)