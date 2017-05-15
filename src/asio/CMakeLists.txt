include_directories(protobuf_comm_asio
        ${CMAKE_SOURCE_DIR}/src/asio
        ${Boost_INCLUDE_DIRS}
        ${PROTOBUF_INCLUDE_DIRS}
        ${OPENSSL_INCLUDE_DIR})

add_library(protobuf_comm_asio SHARED
        client.cpp
        crypto.cpp
        peer.cpp
        server.cpp
        )

link_directories(protobuf_comm_asio
        ${Boost_LIBRARY_DIRS})

target_link_libraries(
        protobuf_comm_asio
        ${Boost_LIBARIES}
        ${PROTOBUF_LIBRARIES}
        ${OPENSSL_LIBRARIES}
        protobuf_comm_message
)
