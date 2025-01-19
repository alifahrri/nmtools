# Development Guide

## Testing

### Build Unit Tests

To build unit tests using gcc:
```
mkdir -p build/gcc
cd build/gcc
cmake ../..
clear && make -j16
```

To build unit tests using clang:
```
mkdir -p build/clang
cd build/clang
cmake -DCMAKE_TOOLCHAIN_FILE=cmake/toolchains/clang-werror.cmake ../..
clear && make -j16
```

### Configuring the tests

To configure the tests interactively:
```
mkdir -p build/gcc
cd build/gcc
ccmake ../..
```
or
```
mkdir -p build/clang
cd build/clang
ccmake -DCMAKE_TOOLCHAIN_FILE=cmake/toolchains/clang-werror.cmake ../..
```

> Tip: install ccmake using `sudo apt install cmake-curses-gui`

A TUI will show up with options available:

![ccmake-options](docs/image/ccmake-options.png)

After generating, compile the test using:
```
clear && cmake -j16
```

> Warning: Building all the test may takes time and consume huge amount of memory especially on gcc

### Run Unit Tests

After building the tests, run unit tests:
```
ctest
```

## Run Interactive Notebook

This is useful to add/update notebook examples. The notebook is using xeus-cling jupyter kernel to run C++ interactively.

Build the image:
```
docker build -t cling -f ./docker/cling.dockerfile .
```
(Optional) Remove existing if any:
```
docker rm cling
```
Run the image, do not automatically remove since the xeus-cling installation is done in the container not the image.
Starting the container for the first time will install xeus-cling and launch jupyter-lab automatically.
```
docker run -it --network=host -v ${PWD}:/workspace/ --name cling cling
```
If the container is stopped, then you can start it again.
```
docker start cling
docker exec -it cling zsh
```
Inside the docker container, run jupyter-lab:
```
jupyter-lab --allow-root
```

## Build & Test web-wasm

You can use [dockcross](https://github.com/dockcross/dockcross) wasm image to build and test easily:
```
export IMAGE=web-wasm
docker run --rm dockcross/${IMAGE}:latest > ./dockcross-${IMAGE}; chmod +x ./dockcross-${IMAGE}
./dockcross-${IMAGE} bash -c "emcc -v"
./dockcross-${IMAGE} bash -c "mkdir -p build/${IMAGE} && cd build/${IMAGE} && cmake -DNMTOOLS_TEST_ALL=OFF -DNMTOOLS_TEST_ARRAY_EVAL=ON -DNMTOOLS_TEST_ARRAY_NN_EVAL=ON ../.. && make -j16 VERBOSE=1"
./dockcross-${IMAGE} node build/${IMAGE}/tests/array/numeric-tests-doctest.js
```