PROJECT(pebble_rpc)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)


SET(PEBBLE_RPC_SRC
    dr/protocol/base64_utils.cpp
    dr/protocol/json_protocol.cpp
    dr/transport/buffer_transport.cpp
    dr/transport/transport_exception.cpp
    error.cpp
    exception.cpp
    pebble_rpc.cpp
    processor.cpp
    protobuf_rpc_head.cpp
    rpc.cpp
    rpc_plugin.cpp
    timer.cpp
    time_utility.cpp
)

SET(PEBBLE_RPC_DR_COMMON_H
    dr/common/common.h
    dr/common/dr_define.h
    dr/common/to_string.h
)
SET(PEBBLE_RPC_PROTOCOL_H
    dr/protocol/base64_utils.h
    dr/protocol/binary_protocol.h
    dr/protocol/binary_protocol.tcc
    dr/protocol/json_protocol.h
    dr/protocol/protocol_exception.h
    dr/protocol/protocol.h
    dr/protocol/virtual_protocol.h
)
SET(PEBBLE_RPC_TRANSPORT_H
    dr/transport/buffer_transport.h
    dr/transport/transport_exception.h
    dr/transport/transport.h
    dr/transport/virtual_transport.h
)
SET(PEBBLE_RPC_H
    error.h
    log.h
    pebble_rpc.h
    platform.h
    processor.h
    rpc.h
    timer.h
    time_utility.h
)

add_library(pebble_rpc STATIC ${PEBBLE_RPC_SRC})

INSTALL(FILES ${PEBBLE_RPC_DR_COMMON_H} DESTINATION pebble_rpc/include/dr/common)
INSTALL(FILES ${PEBBLE_RPC_PROTOCOL_H} DESTINATION pebble_rpc/include/dr/protocol)
INSTALL(FILES ${PEBBLE_RPC_TRANSPORT_H} DESTINATION pebble_rpc/include/dr/transport)
INSTALL(FILES ${PEBBLE_RPC_H} DESTINATION pebble_rpc/include)
