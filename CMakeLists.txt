cmake_minimum_required(VERSION 3.5)
project(protobuf_comm)

set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")

if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-std=gnu++0x)
endif()

find_package(Protobuf REQUIRED) 
find_package(Boost 1.48 REQUIRED COMPONENTS system filesystem)
find_package(OpenSSL REQUIRED)
find_package (Mosquitto REQUIRED)

message("INclude: " ${MOSQUITTO_INCLUDE_DIR} )

include_directories(protobuf_comm_asio
        src/
        src/asio
        ${Boost_INCLUDE_DIRS}
        ${PROTOBUF_INCLUDE_DIRS}
        ${OPENSSL_INCLUDE_DIR})

add_library(protobuf_comm_asio SHARED
        src/asio/client.cpp
        src/asio/crypto.cpp
        src/message_register.cpp
        src/asio/peer.cpp
        src/asio/server.cpp
        )

link_directories(protobuf_comm_asio
            ${Boost_LIBRARY_DIRS})


target_link_libraries(
              protobuf_comm_asio
              ${Boost_LIBARIES}
              ${PROTOBUF_LIBRARIES}
              ${OPENSSL_LIBRARIES}
              )


include_directories(protobuf_comm_mqtt
        src/
        src/mqtt ${Boost_INCLUDE_DIRS}
        ${PROTOBUF_INCLUDE_DIRS}
        ${MOSQUITTO_INCLUDE_DIR}
        )

add_library(protobuf_comm_mqtt SHARED
        src/mqtt/mqtt_client.cpp
        src/mqtt/mqtt_publisher.cpp
        src/mqtt/mqtt_subscriber.cpp
        src/message_register.cpp
        )

link_directories(protobuf_comm_mqtt
        ${Boost_LIBRARY_DIRS}
        )


target_link_libraries(protobuf_comm_mqtt
        ${Boost_LIBARIES}
        ${PROTOBUF_LIBRARIES}
        ${MOSQUITTO_LIBRARIES}
)




 
