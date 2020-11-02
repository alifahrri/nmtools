FROM alifahrri/nmtools-clang-ubuntu:latest

WORKDIR /app/numeric_tools/

COPY benchmarks benchmarks
COPY examples examples
COPY include include
COPY scripts scripts
COPY tests tests
COPY cmake cmake
COPY CMakeLists.txt CMakeLists.txt 
COPY nmtools.pc.in nmtools.pc.in
COPY nmtoolsConfig.cmake.in nmtoolsConfig.cmake.in

RUN mkdir build && cd build \
    && CC=clang CXX=clang++ cmake -DBUILD_BENCHMARKS=OFF .. && make -j4 VERBOSE=1 && make install

CMD ["bash","scripts/run_unit_tests.sh"]