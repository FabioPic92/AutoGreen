add_executable(publisher Publisher.cpp)
target_link_libraries(publisher common_utils)

add_executable(subscriber Subscriber.cpp)
target_link_libraries(subscriber common_utils)