include_directories(protobuf_comm_message
        ${CMAKE_SOURCE_DIR}/src/message
        ${Boost_INCLUDE_DIRS}
        ${PROTOBUF_INCLUDE_DIRS}
        )

add_library(protobuf_comm_message SHARED
            message_register.cpp
        )

link_directories(protobuf_comm_message
        ${Boost_LIBRARY_DIRS}
        )


target_link_libraries(protobuf_comm_message
        ${Boost_LIBARIES}
        )