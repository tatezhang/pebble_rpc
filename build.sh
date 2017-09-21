#!/bin/sh

cd src/
../tools/pebble --gen cpp_client -out ./ exception.pebble
../tools/pebble --gen cpp_client -out ./ protobuf_rpc_head.pebble

cd ../
mkdir build -p
rm build/* -rf

cd build
cmake ../
make

