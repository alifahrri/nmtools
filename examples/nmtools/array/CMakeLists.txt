cmake_minimum_required(VERSION 3.10)
project(nmtools-array-example)

include_directories(
    ${NMTOOLS_INCLUDE_DIR}
)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_compile_options(-frelaxed-template-template-args)
endif()

set(CMAKE_CXX_STANDARD 17)

add_executable(
    ${PROJECT_NAME}-tile
    src/tile.cpp
)

add_executable(
    ${PROJECT_NAME}-repeat
    src/repeat.cpp
)

add_executable(
    ${PROJECT_NAME}-reshape
    src/reshape.cpp
)

add_executable(
    ${PROJECT_NAME}-transpose
    src/transpose.cpp
)

add_executable(
    ${PROJECT_NAME}-broadcast_to
    src/broadcast_to.cpp
)

add_executable(
    ${PROJECT_NAME}-expand_dims
    src/expand_dims.cpp
)

add_executable(
    ${PROJECT_NAME}-squeeze
    src/squeeze.cpp
)

add_executable(
    ${PROJECT_NAME}-flatten
    src/flatten.cpp
)

if(CMAKE_CXX_COMPILER MATCHES "/em\\+\\+(-[a-zA-Z0-9.])?$")
    # message(" * C++ compiler: Emscripten")
    # message(STATUS "Emscripten detected")
    option(JS_ONLY "build javascript only for emscripten" OFF)
    if(JS_ONLY)
        message(STATUS "Setting compilation target to native JavaScript")
        set(CMAKE_EXECUTABLE_SUFFIX ".js")
        set_target_properties(
            ${PROJECT_NAME}-transpose
            ${PROJECT_NAME}-tile
            ${PROJECT_NAME}-repeat
            ${PROJECT_NAME}-reshape
            ${PROJECT_NAME}-broadcast_to
            ${PROJECT_NAME}-expand_dims
            ${PROJECT_NAME}-squeeze
            ${PROJECT_NAME}-flatten
            PROPERTIES LINK_FLAGS "--emrun -s EXPORTED_FUNCTIONS='[_main]'"
        )
    else(JS_ONLY)
        message(STATUS "Setting compilation target to WASM")
        set(CMAKE_EXECUTABLE_SUFFIX ".wasm.js")
        set_target_properties(
            ${PROJECT_NAME}-transpose
            ${PROJECT_NAME}-tile
            ${PROJECT_NAME}-repeat
            ${PROJECT_NAME}-reshape
            ${PROJECT_NAME}-broadcast_to
            ${PROJECT_NAME}-expand_dims
            ${PROJECT_NAME}-squeeze
            ${PROJECT_NAME}-flatten
            PROPERTIES LINK_FLAGS "--emrun -s WASM=1 -s BINARYEN_METHOD='native-wasm' -s EXPORTED_FUNCTIONS='[_main]' -s NO_EXIT_RUNTIME=1 -s EXTRA_EXPORTED_RUNTIME_METHODS=['ccall']"
        )
    endif(JS_ONLY)
endif()