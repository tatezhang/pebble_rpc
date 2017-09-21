PROJECT(pebble_rpc)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)


SET(PEBBLE_RPC_SOURCE
    dr/common/common.h
    dr/common/dr_define.h
    dr/common/to_string.h
    dr/protocol/base64_utils.cpp
    dr/protocol/base64_utils.h
    dr/protocol/binary_protocol.h
    dr/protocol/binary_protocol.tcc
    dr/protocol/json_protocol.cpp
    dr/protocol/json_protocol.h
    dr/protocol/protocol_exception.h
    dr/protocol/protocol.h
    dr/protocol/virtual_protocol.h
    dr/transport/buffer_transport.cpp
    dr/transport/buffer_transport.h
    dr/transport/transport_exception.cpp
    dr/transport/transport_exception.h
    dr/transport/transport.h
    dr/transport/virtual_transport.h
    error.cpp
    error.h
    exception.cpp
    exception.h
    log.h
    pebble_rpc.cpp
    pebble_rpc.h
    platform.h
    processor.cpp
    processor.h
    protobuf_rpc_head.cpp
    protobuf_rpc_head.h
    rpc.cpp
    rpc.h
    rpc_plugin.cpp
    rpc_plugin.inh
    string_utility.cpp
    string_utility.h
    timer.cpp
    timer.h
    time_utility.cpp
    time_utility.h
    version.inh
)

add_library(libpebble_rpc STATIC ${PEBBLE_RPC_SOURCE})

