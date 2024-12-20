# Development Guide

## Testing

### Build Unit Tests

To build unit tests using gcc:
```
mkdir -p build/gcc
cd build/gcc
cmake ../..
clear && cmake -j16
```

To build unit tests using clang:
```
mkdir -p build/clang
cd build/clang
cmake -DCMAKE_TOOLCHAIN_FILE=cmake/toolchains/clang-werror.cmake ../..
clear && cmake -j16
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