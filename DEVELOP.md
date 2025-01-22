# Development Guide

Cheatsheet for development build and tests.

1. [Basic Building & Testing (CPU)](#basic-testing-cpu)
1. [Build & Test `web-wasm`](#build--test-web-wasm)
1. [Build & Test `sycl` OpenMP](#build--test-sycl-openmp)
1. [Build & Test `sycl` OpenCL](#build--test-sycl-opencl)
1. [Build & Test `cuda`](#build--test-cuda)
1. [Build & Test `hip`](#build--test-hip)
1. [Build & Test (Ubuntu20.04)](#build--test-ubuntu2004)
1. [Run Interactive Notebook](#run-interactive-notebook)

## Basic Building & Testing (CPU)

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

## Build & Test `web-wasm`

You can use [dockcross](https://github.com/dockcross/dockcross) wasm image to build and test easily:
```
export IMAGE=web-wasm
docker run --rm dockcross/${IMAGE}:latest > ./dockcross-${IMAGE}; chmod +x ./dockcross-${IMAGE}
./dockcross-${IMAGE} bash -c "emcc -v"
./dockcross-${IMAGE} bash -c "mkdir -p build/${IMAGE} && cd build/${IMAGE} && cmake -DNMTOOLS_TEST_ALL=OFF -DNMTOOLS_TEST_ARRAY_EVAL=ON -DNMTOOLS_TEST_ARRAY_NN_EVAL=ON ../.. && make -j16 VERBOSE=1"
./dockcross-${IMAGE} node build/${IMAGE}/tests/array/numeric-tests-doctest.js
```

## Build & Test `sycl` OpenMP

Targeting OpenMP backend, build dev image and run container:
```
docker build . --tag nmtools:sycl-clang14-omp --target build --file docker/sycl.dockerfile
docker run -it --name sycl-omp-dev --volume ${PWD}:/workspace/nmtools --entrypoint zsh nmtools:sycl-clang14-omp
```
Inside the container, build the tests:
```
mkdir -p build/${TOOLCHAIN} && cd build/${TOOLCHAIN} \
    && cmake -DCMAKE_TOOLCHAIN_FILE=cmake/toolchains/${TOOLCHAIN}.cmake \
        -DNMTOOLS_BUILD_META_TESTS=OFF -DNMTOOLS_BUILD_UTL_TESTS=OFF -DNMTOOLS_TEST_ALL=OFF \
        -DNMTOOLS_BUILD_SYCL_TESTS=ON \
        ../.. \
    && make -j`nproc` VERBOSE=1 numeric-tests-sycl-doctest
```
Then run the test:
```
ctest
```

## Build & Test `sycl` OpenCL

Targeting HIP backend on sycl, build dev image and run container:
```
docker build . --tag nmtools:sycl-clang14-opencl --build-arg opencl_backend=ON --build-arg toolchain=sycl-clang14-generic --target build --file docker/sycl.dockerfile
docker run -it --name sycl-opencl-dev --volume ${PWD}:/workspace/nmtools --entrypoint zsh nmtools:sycl-clang14-opencl
```
Inside the container, build the tests:
```
mkdir -p build/${TOOLCHAIN} && cd build/${TOOLCHAIN} \
    && cmake -DCMAKE_TOOLCHAIN_FILE=cmake/toolchains/${TOOLCHAIN}.cmake \
        -DNMTOOLS_BUILD_META_TESTS=OFF -DNMTOOLS_BUILD_UTL_TESTS=OFF -DNMTOOLS_TEST_ALL=OFF \
        -DNMTOOLS_BUILD_SYCL_TESTS=ON \
        ../.. \
    && make -j`nproc` VERBOSE=1 numeric-tests-sycl-doctest
```
Then run the test:
```
NMTOOLS_SYCL_DEFAULT_PLATFORM=opencl ./tests/sycl/numeric-tests-sycl-doctest
```

## Build & Test (Ubuntu20.04)

Use ubuntu 20.04 for gcc-9 and clang-10:
```
docker build . --tag nmtools:focal --target build --file docker/focal.dockerfile
docker run -it --name focal-dev --volume ${PWD}:/workspace/nmtools --entrypoint zsh nmtools:focal
```
Inside the container, build the tests:
```
export TOOLCHAIN=clang10-werror
mkdir -p build/${TOOLCHAIN} && cd build/${TOOLCHAIN} \
    && cmake -DCMAKE_TOOLCHAIN_FILE=cmake/toolchains/${TOOLCHAIN}.cmake -DNMTOOLS_TEST_ALL=ON \
        ../.. \
    && make -j`nproc` VERBOSE=1
```
Then run the test:
```
ctest
```

## Build & Test `cuda`

Build the image and run docker container:
```
docker build . --tag nmtools:cuda --target dev --file docker/cuda.dockerfile
docker run -it --name cuda-dev --volume ${PWD}:/workspace/nmtools --entrypoint zsh nmtools:cuda
```
Inside the container, build the tests:
```
mkdir -p build/cuda && cd build/cuda \
    && cmake -DCMAKE_TOOLCHAIN_FILE=cmake/toolchains/clang.cmake \
        -DNMTOOLS_BUILD_META_TESTS=OFF -DNMTOOLS_BUILD_UTL_TESTS=OFF -DNMTOOLS_TEST_ALL=OFF \
        -DNMTOOLS_BUILD_CUDA_TESTS=ON \
        -DNMTOOLS_TEST_CUDA_PATH=/usr/local/cuda \
        -DNMTOOLS_TEST_CUDA_ARCH=sm_80 \
        ../.. \
    && make -j`nproc` VERBOSE=1
```
To restart:
```
docker start cuda-dev
docker exec -it cuda-dev zsh
```

## Build & Test `hip`

Build the image and run docker container:
```
docker build . --tag nmtools:hip --target dev --file docker/hip.dockerfile
docker run -it --device /dev/kfd --device /dev/dri --name hip-dev --volume ${PWD}:/workspace/nmtools --entrypoint zsh nmtools:hip
```
Inside the container, build the tests:
```
mkdir -p build/hip && cd build/hip && cmake -DCMAKE_TOOLCHAIN_FILE=../../cmake/toolchains/hip.cmake -DNMTOOLS_BUILD_HIP_TESTS=ON ../.. && make -j`nproc` VERBOSE=1
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