set(BOOST_ROOT ${CMAKE_SOURCE_DIR}/external/boost)
set(BOOST_INCLUDEDIR ${BOOST_ROOT}/include)
set(BOOST_LIBRARYDIR ${BOOST_ROOT}/lib)

include_directories(${BOOST_INCLUDEDIR})

link_directories(${BOOST_LIBRARYDIR})

add_executable(publisher Publisher.cpp)
target_include_directories(publisher PRIVATE ${BOOST_INCLUDEDIR})
target_link_libraries(publisher boost_system boost_thread pthread common_utils)

add_executable(subscriber Subscriber.cpp)
target_include_directories(subscriber PRIVATE ${BOOST_INCLUDEDIR})
target_link_libraries(subscriber boost_system boost_thread pthread common_utils)