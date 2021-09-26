FROM alifahrri/nmtools-emscripten-ubuntu:latest

WORKDIR /app/numeric_tools/

COPY examples examples
COPY include include
COPY scripts scripts
COPY tests tests
COPY cmake cmake
COPY CMakeLists.txt CMakeLists.txt 
COPY nmtools.pc.in nmtools.pc.in
COPY nmtoolsConfig.cmake.in nmtoolsConfig.cmake.in

# for emscripten use from include
RUN bash scripts/download_doctest_header.sh -d include

RUN /opt/emsdk/emsdk activate latest \
    && PATH=$PATH:/opt/emsdk:/opt/emsdk/node/12.18.1_64bit/bin:/opt/emsdk/upstream/emscripten \
    && mkdir build && cd build \
    && emcmake cmake -DNMTOOLS_BUILD_EXAMPLES=ON -DNMTOOLS_CODE_COVERAGE=OFF .. \
    && make -j4 VERBOSE=1 && make install

CMD ["/opt/emsdk/node/12.18.1_64bit/bin/node","/app/numeric_tools/build/tests/numeric-tests-doctest.wasm.js"]