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
    && cmake -DBUILD_EXAMPLES=ON -DCODE_COVERAGE=ON .. && make VERBOSE=1 -j4 && make install

CMD ["bash","scripts/run_unit_tests.sh"]