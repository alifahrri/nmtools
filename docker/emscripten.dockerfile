FROM alifahrri/nmtools-emscripten-ubuntu:latest

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

RUN /opt/emsdk/emsdk activate && source "/opt/emsdk/emsdk_env.sh" && \
    mkdir build && cd build \
    && emcmake cmake -DBUILD_BENCHMARKS=OFF -DBUILD_EXAMPLES=ON -DCODE_COVERAGE=OFF .. \
    && make -j4 VERBOSE=1 && make install

CMD ["node","/app/numeric_tools/build/tests/numeric-tests-doctest.wasm.js"]