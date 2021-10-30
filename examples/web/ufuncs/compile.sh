#!/usr/bin/bash

# this script compiles c++ file to javascript using emscripten

set -e
set -x

# use dockcross for simple install & compile
if [ ! -f ./dockcross-web-wasm ]; then
    docker run --rm dockcross/web-wasm > ./dockcross-web-wasm
    chmod +x ./dockcross-web-wasm
fi

# nmtools requires c++17, hence "-std=c++17"
# using "-s SINGLE_FILE" to embed wasm directly to js instead of separate .wasm file
# also mount nmtools to make it available to the container
compile () {
    ./dockcross-web-wasm --args --volume=${PWD}/../../../include/nmtools:/usr/local/include/nmtools bash -c \
        "emcc --bind -std=c++17 -s SINGLE_FILE -o $1.js $1.cpp -I/usr/local/include"
}

compile "ufuncs"