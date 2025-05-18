add_executable(publisher_camera Publisher.cpp)
add_executable(subscriber_camera Subscriber.cpp)

target_include_directories(publisher_camera PRIVATE ${OpenCV_INCLUDE_DIRS})
target_include_directories(subscriber_camera PRIVATE ${OpenCV_INCLUDE_DIRS})

target_link_libraries(publisher_camera
    ${OpenCV_LIBS}
    ${PahoMqttC_SHARED_LIBRARY}
    ${PahoMqttCpp_SHARED_LIBRARY}
    pthread
)

target_link_libraries(subscriber_camera
    ${OpenCV_LIBS}
    ${PahoMqttC_SHARED_LIBRARY}
    ${PahoMqttCpp_SHARED_LIBRARY}
    pthread
)