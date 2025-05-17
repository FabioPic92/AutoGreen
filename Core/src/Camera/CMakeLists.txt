add_executable(publisher Publisher.cpp)
add_executable(subscriber Subscriber.cpp)

target_include_directories(publisher PRIVATE ${OpenCV_INCLUDE_DIRS})
target_include_directories(subscriber PRIVATE ${OpenCV_INCLUDE_DIRS})

# Collega le librerie condivise
target_link_libraries(publisher
    ${OpenCV_LIBS}
    ${PahoMqttC_SHARED_LIBRARY}
    ${PahoMqttCpp_SHARED_LIBRARY}
    pthread
)

target_link_libraries(subscriber
    ${OpenCV_LIBS}
    ${PahoMqttC_SHARED_LIBRARY}
    ${PahoMqttCpp_SHARED_LIBRARY}
    pthread
)