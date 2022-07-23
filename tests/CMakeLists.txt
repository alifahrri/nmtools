cmake_minimum_required(VERSION 3.10.2)
project(numeric-tests)

option(NMTOOLS_DEFER_STATIC_CHECK "defer static check to runtime for testing purpose" OFF)
if (NMTOOLS_DEFER_STATIC_CHECK)
    add_definitions(-DDEFER_STATIC_CHECK)
endif ()

# Code Coverage Configuration
add_library(coverage_config INTERFACE)

# Add required flags (GCC & LLVM/Clang)
target_compile_options(coverage_config INTERFACE
    -O0        # no optimization
    -g         # generate debug info
    --coverage # sets all required flags
)
target_link_options(coverage_config INTERFACE --coverage)

option(NMTOOLS_CODE_COVERAGE "build with code coverage reporting" OFF)
message(STATUS "CODE_COVERAGE ${NMTOOLS_CODE_COVERAGE}")

option(NMTOOLS_TESTING_GENERIC_NDARRAY "build test with generic ndarray" OFF)
if (NMTOOLS_TESTING_GENERIC_NDARRAY)
    add_compile_definitions(NMTOOLS_TESTING_GENERIC_NDARRAY)
endif(NMTOOLS_TESTING_GENERIC_NDARRAY)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(array)

option(NMTOOLS_ADDRESS_SANITIZER "build with -fsanitize=address" OFF)
message(STATUS "NMTOOLS_ADDRESS_SANITIZER ${ADDRESS_SANITIZER}")

# TODO: remove, use toolchain instead
# from https://gist.github.com/jlblancoc/44be9d4d466f0a973b1f3808a8e56782
# TODO: findout if can be used for private target instead
# TODO: find out if can be used with other compiler
# TODO: provide option to disable/enable
if (NMTOOLS_ADDRESS_SANITIZER)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fsanitize=leak")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address -fsanitize=leak")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address -fsanitize=leak")
    set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -fsanitize=address -fsanitize=leak")
endif (NMTOOLS_ADDRESS_SANITIZER)

option(NMTOOLS_UNDEFINED_SANITIZER "build with -fsanitize=undefined" OFF)
message(STATUS "NMTOOLS_UNDEFINED_SANITIZER ${NMTOOLS_UNDEFINED_SANITIZER}")

if (NMTOOLS_UNDEFINED_SANITIZER)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=undefined")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=undefined")
    set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -fsanitize=undefined")
endif (NMTOOLS_UNDEFINED_SANITIZER)

# for emscripten, generate js main
if(CMAKE_CXX_COMPILER MATCHES "/em\\+\\+(-[a-zA-Z0-9.])?$")
    message(" * C++ compiler: Emscripten")
    message(STATUS "Emscripten detected")
    option(JS_ONLY "build javascript only for emscripten" OFF)
    if(JS_ONLY)
        message(STATUS "Setting compilation target to native JavaScript")
        set(CMAKE_EXECUTABLE_SUFFIX ".js")
        set_target_properties(
            ${PROJECT_NAME}-doctest
            PROPERTIES LINK_FLAGS "--emrun -s EXPORTED_FUNCTIONS='[_main]'"
        )
    else(JS_ONLY)
        message(STATUS "Setting compilation target to WASM")
        set(CMAKE_EXECUTABLE_SUFFIX ".wasm.js")
        # note triggers error on newer version: em++: error: --emrun is only compatible with html output
        # set_target_properties(
        #     ${PROJECT_NAME}-doctest
        #     PROPERTIES LINK_FLAGS "--emrun -s WASM=1 -s BINARYEN_METHOD='native-wasm' -s EXPORTED_FUNCTIONS='[_main]' -s NO_EXIT_RUNTIME=1 -s EXTRA_EXPORTED_RUNTIME_METHODS=['ccall']"
        # )
    endif(JS_ONLY)
endif()

option(NMTOOLS_BUILD_META_TESTS "build metafunctions test programs" ON)
if (NMTOOLS_BUILD_META_TESTS)
    add_subdirectory(meta)
endif (NMTOOLS_BUILD_META_TESTS)

option(NMTOOLS_BUILD_UTL_TESTS "build utl tests programs" ON)
if (NMTOOLS_BUILD_UTL_TESTS)
    add_subdirectory(utl/utl)
    add_subdirectory(utl/meta)
    add_subdirectory(utl/array)
endif (NMTOOLS_BUILD_UTL_TESTS)

option(NMTOOLS_BUILD_TESTBENCH "build testbench programs" OFF)
if (NMTOOLS_BUILD_TESTBENCH)
    add_subdirectory(testbench)
endif (NMTOOLS_BUILD_TESTBENCH)