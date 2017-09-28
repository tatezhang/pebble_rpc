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
make install

release_name=`date +%Y%m%d%H%M%S`
tar zcf pebble_rpc_$release_name.tgz pebble_rpc
