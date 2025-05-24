add_executable(publisher_motor Publisher.cpp)
add_executable(subscriber_motor Subscriber.cpp)

target_include_directories(publisher_motor PRIVATE ${OpenCV_INCLUDE_DIRS})
target_include_directories(subscriber_motor PRIVATE ${OpenCV_INCLUDE_DIRS})

target_link_libraries(publisher_motor
    ${OpenCV_LIBS}
    ${PahoMqttC_SHARED_LIBRARY}
    ${PahoMqttCpp_SHARED_LIBRARY}
    pthread
)

target_link_libraries(subscriber_motor
    ${OpenCV_LIBS}
    ${PahoMqttC_SHARED_LIBRARY}
    ${PahoMqttCpp_SHARED_LIBRARY}
    pthread
)