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

add_subdirectory(src/asio)
add_subdirectory(src/mqtt)
add_subdirectory(src/message)









 
