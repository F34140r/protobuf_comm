find_package (Mosquittopp REQUIRED)

include_directories(protobuf_comm_mqtt
        ${CMAKE_SOURCE_DIR}/src/mqtt
        ${Boost_INCLUDE_DIRS}
        ${PROTOBUF_INCLUDE_DIRS}
        ${MOSQUITTO_INCLUDE_DIR}
        )

add_library(protobuf_comm_mqtt SHARED
        mqtt_client.cpp
        mqtt_publisher.cpp
        mqtt_subscriber.cpp
        )

link_directories(protobuf_comm_mqtt
        ${Boost_LIBRARY_DIRS}
        )


target_link_libraries(protobuf_comm_mqtt
        ${Boost_LIBARIES}
        ${PROTOBUF_LIBRARIES}
        ${MOSQUITTO_LIBRARIES}
        protobuf_comm_message
        )