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