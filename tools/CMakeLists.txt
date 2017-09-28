PROJECT(pebble_rpc)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)


SET(PEBBLE_RPC_TOOL
    pebble
    protobuf_rpc
    protobuf_rpc_client
    protoc
)


INSTALL(FILES ${PEBBLE_RPC_TOOL} DESTINATION pebble_rpc/tools)
