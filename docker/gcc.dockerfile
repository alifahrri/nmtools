FROM alifahrri/nmtools-gcc-ubuntu:latest

WORKDIR /app/numeric_tools/

COPY examples examples
COPY include include
COPY scripts scripts
COPY tests tests
COPY cmake cmake
COPY CMakeLists.txt CMakeLists.txt 
COPY nmtools.pc.in nmtools.pc.in
COPY nmtoolsConfig.cmake.in nmtoolsConfig.cmake.in

RUN mkdir build && cd build \
    && cmake -DCMAKE_TOOLCHAIN_FILE=cmake/toolchains/gcc-werror.cmake \
        -DNMTOOLS_BUILD_EXAMPLES=ON \
        -DNMTOOLS_CODE_COVERAGE=ON \
        -DNMTOOLS_ENABLE_TEST_BENCHMARKS=OFF \
        .. \
    && make VERBOSE=1 -j1 && make install

CMD ["bash","scripts/run_unit_tests.sh"]