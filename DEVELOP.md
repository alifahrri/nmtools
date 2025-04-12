# Development Guide

Cheatsheet for development build and tests.

1. [Basic Building & Testing (CPU)](#basic-testing-cpu)
1. [Build & Test `web-wasm`](#build--test-web-wasm)
1. [Build & Test `sycl` OpenMP](#build--test-sycl-openmp)
1. [Build & Test `sycl` OpenCL](#build--test-sycl-opencl)
1. [Build & Test `sycl` `cuda`](#build--test-sycl-cuda)
1. [Build & Test `cuda`](#build--test-cuda)
1. [Build & Test `hip`](#build--test-hip)
1. [Build & Test (Ubuntu20.04)](#build--test-ubuntu2004)
1. [Run Interactive Notebook](#run-interactive-notebook)
1. [Run clang-repl](#run-clang-repl)
1. [Build with ditstcc](#setup-distcc)

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
If there is existing container with name sycl-cuda-dev, you can remove it before build/run:
```
docker rm sycl-omp-dev
```
Or to re-run (after stopping)
```
docker start sycl-omp-dev
docker exec -it sycl-omp-dev zsh
```

## Build & Test `sycl` OpenCL

Targeting OpenCL backend on sycl, build dev image and run container:
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
NMTOOLS_SYCL_DEFAULT_DEVICE=opencl ./tests/sycl/numeric-tests-sycl-doctest
```
The env `NMTOOLS_SYCL_DEFAULT_DEVICE` above can be used to select the default device.
If you know the index of the platform you want to use:
```
NMTOOLS_SYCL_DEFAULT_DEVICE_IDX=1 ./tests/sycl/numeric-tests-sycl-doctest
```

If there is existing container with name sycl-cuda-dev, you can remove it before build/run:
```
docker rm sycl-opencl-dev
```
Or to re-run (after stopping)
```
docker start sycl-opencl-dev
docker exec -it sycl-opencl-dev zsh
```
Latest know working version configuration is:
```docker
ENV LLVM_VERSION="18"
ENV LLVM_SPV_VERSION="v18.1.8"
ENV POCL_VERSION="v6.0"
ENV ADAPTIVE_CPP_VERSION="v24.10.0"
```
LLVM version 14 and AdaptiveCPP v23.10.0 is know to be broken, other version not tested.

## Build & Test `sycl` `cuda`
Targeting cuda backend on sycl, build dev image and run container:
```
docker build . --tag nmtools:sycl-cuda-dev --target build --build-arg BASE=nvidia/cuda:11.8.0-devel-ubuntu22.04 --build-arg cuda_backend=ON --build-arg toolchain=sycl-clang14-cuda --file docker/sycl.dockerfile
docker run -it --runtime=nvidia --name sycl-cuda-dev --volume ${PWD}:/workspace/nmtools --entrypoint zsh nmtools:sycl-cuda-dev
```
If there is existing container with name sycl-cuda-dev, you can remove it before build/run:
```
docker rm sycl-cuda-dev
```
Or to re-run (after stopping)
```
docker start sycl-cuda-dev
docker exec -it sycl-cuda-dev zsh
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
docker run -it --runtime=nvidia --name cuda-dev --volume ${PWD}:/workspace/nmtools --entrypoint zsh nmtools:cuda
```

Inside the container, build the tests:
```
# using cuda-clang (`clang -x cuda`)
export TOOLCHAIN=clang
mkdir -p build/cuda-${TOOLCHAIN} && cd build/cuda-${TOOLCHAIN} \
    && cmake -DCMAKE_TOOLCHAIN_FILE=cmake/toolchains/${TOOLCHAIN}.cmake \
        -DNMTOOLS_BUILD_META_TESTS=OFF \
        -DNMTOOLS_BUILD_UTL_TESTS=OFF \
        -DNMTOOLS_TEST_ALL=OFF \
        -DNMTOOLS_BUILD_CUDA_TESTS=ON \
        -DNMTOOLS_TEST_CUDA_PATH=/usr/local/cuda \
        -DNMTOOLS_TEST_CUDA_ARCH=sm_80 \
        ../.. \
    && make -j`nproc` VERBOSE=1
```
```
docker run -it --runtime=nvidia --device /dev/nvidia0 \
  --device /dev/nvidiactl \
  --device /dev/nvidia-uvm \
  --device /dev/nvidia-uvm-tools --name cuda-dev --volume ${PWD}:/workspace/nmtools --entrypoint zsh nmtools:cuda
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
By default, the test use gfx1103 (Ryzen 8700G) as target, you can specify target arch by adding cmake args `-DNMTOOLS_TEST_HIP_ARCH` as follows:
```
mkdir -p build/hip && cd build/hip && cmake -DCMAKE_TOOLCHAIN_FILE=../../cmake/toolchains/hip.cmake -DNMTOOLS_BUILD_HIP_TESTS=ON -DNMTOOLS_TEST_HIP_ARCH="gfx1036,gfx1100,gfx1103" ../.. && make -j`nproc` VERBOSE=1
```
where `gfx1036` is iGPU in ryzen 7000/9000 series and `gfx1100` is for Radeon 7900 XTX.

After successful build, then you can run the hip-test:
```
./tests/hip/numeric-tests-hip-doctest
```
![docs/image/hip-test.png](docs/image/hip-test.png)

If there is container naming conflict you can remove then re-run, or just restart.
```
docker rm hip-dev
docker run -it --device /dev/kfd --device /dev/dri --name hip-dev --volume ${PWD}:/workspace/nmtools --entrypoint zsh nmtools:hip
```
To restart:
```
docker start hip-dev
docker exec -it hip-dev zsh
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

## Run Clang-Repl

Sometimes when you try to build the xeus-cling env it's broken, use clang-repl to run interactively.

Build the image:
```
docker build -t clang-repl -f ./docker/clang-repl.dockerfile .
```
Run
```
docker run -it --name clang-repl -v ${PWD}:/workspace/ clang-repl zsh
```
Then, inside the container, run clang-repl:
```
/opt/llvm-project/build/bin/clang-repl --Xcc="-I/workspace/include/" -Xcc="-Wno-gnu-string-literal-operator-template"
```
![clang-repl.png](docs/image/clang-repl.png)
To re-run stopped container
```
docker start clang-repl
docker exec -it clang-repl zsh
```

## Setup `distcc`
Build distcc server:
```
docker build --build-arg ubuntu_base=22.04 -t distcc-server -f docker/distcc.dockerfile .
```
Run distcc server (from your build server):
```
docker run -d -p 3632:3632 -p 5201:5201 --name distcc-server1 distcc-server --jobs 24
```
From client machine:
```
mkdir -p build/distcc-clang
cd build/distcc-clang
cmake -DCMAKE_TOOLCHAIN_FILE=cmake/toolchains/distcc-clang.cmake ../..
ccmake ../.. # optional to select which tests to be built
```
build:
```
export DISTCC_VERBOSE=0
export DISTCC_PAUSE_TIME_MSEC=10
export DISTCC_HOSTS="192.168.1.11/24,lzo localhost/32,lzo"
clear && make -j56 VERBOSE=1 all
```