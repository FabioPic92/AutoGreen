add_executable(publisher Publisher.cpp)
add_executable(subscriber Subscriber.cpp)

# Collega le librerie condivise
target_link_libraries(publisher
    ${PahoMqttC_SHARED_LIBRARY}
    ${PahoMqttCpp_SHARED_LIBRARY}
    pthread
)

target_link_libraries(subscriber
    ${PahoMqttC_SHARED_LIBRARY}
    ${PahoMqttCpp_SHARED_LIBRARY}
    pthread
)