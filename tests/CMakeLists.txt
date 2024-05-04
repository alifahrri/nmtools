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

option(NMTOOLS_TESTING_NO_BACKTRACE_LIMIT "add -ftemplate-backtrace-limit=0" OFF)
if (NMTOOLS_TESTING_NO_BACKTRACE_LIMIT)
    add_compile_options(-ftemplate-backtrace-limit=0)
endif ()

option(NMTOOLS_CODE_COVERAGE "build with code coverage reporting" OFF)
message(STATUS "CODE_COVERAGE ${NMTOOLS_CODE_COVERAGE}")

option(NMTOOLS_TESTING_GENERIC_NDARRAY "build test with generic ndarray" OFF)
if (NMTOOLS_TESTING_GENERIC_NDARRAY)
    add_compile_definitions(NMTOOLS_TESTING_GENERIC_NDARRAY)
endif(NMTOOLS_TESTING_GENERIC_NDARRAY)

option(NMTOOLS_TESTING_NOSTL "build tests without stl dependencies" OFF)
if (NMTOOLS_TESTING_NOSTL)
    add_compile_definitions(NMTOOLS_DISABLE_STL)
endif (NMTOOLS_TESTING_NOSTL)

option(NMTOOLS_TESTING_CONSTEXPR "constexpr tests only" OFF)
if (NMTOOLS_TESTING_CONSTEXPR)
    add_compile_definitions(NMTOOLS_TESTING_CONSTEXPR)
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        add_compile_options(-fconstexpr-ops-limit=100000000)
    endif ()
endif (NMTOOLS_TESTING_CONSTEXPR)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

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

add_subdirectory(array)

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
            PROPERTIES LINK_FLAGS "--emrun -s  EXPORTED_FUNCTIONS='[_main]'"
        )
        target_compile_options(
            ${PROJECT_NAME}-doctest PUBLIC
            "-sALLOW_MEMORY_GROWTH=1"
        )
    else(JS_ONLY)
        message(STATUS "Setting compilation target to WASM")
        set(CMAKE_EXECUTABLE_SUFFIX ".wasm.js")
        target_compile_options(
            ${PROJECT_NAME}-doctest PUBLIC
            "-sSTACK_SIZE=131072"
        )
        # note triggers error on newer version: em++: error: --emrun is only compatible with html output
        # set_target_properties(
        #     ${PROJECT_NAME}-doctest
        #     PROPERTIES LINK_FLAGS "--emrun -s WASM=1 -s BINARYEN_METHOD='native-wasm' -s EXPORTED_FUNCTIONS='[_main]' -s NO_EXIT_RUNTIME=1 -s EXTRA_EXPORTED_RUNTIME_METHODS=['ccall']"
        # )
    endif(JS_ONLY)
endif()

option(NMTOOLS_BUILD_SIMD_TESTS "build simd test programs" OFF)
if (NMTOOLS_BUILD_SIMD_TESTS)
    add_subdirectory(simd)
endif (NMTOOLS_BUILD_SIMD_TESTS)

option(NMTOOLS_BUILD_VECTOR_TESTS "build vector extension test programs" OFF)
if (NMTOOLS_BUILD_VECTOR_TESTS)
    add_subdirectory(vector)
endif (NMTOOLS_BUILD_VECTOR_TESTS)

option(NMTOOLS_BUILD_SIMDE_TESTS "build simde test programs" OFF)
if (NMTOOLS_BUILD_SIMDE_TESTS)
    add_subdirectory(simde)
endif (NMTOOLS_BUILD_SIMDE_TESTS)

option(NMTOOLS_BUILD_INDEX_TESTS "build index test programs" OFF)
if (NMTOOLS_BUILD_INDEX_TESTS)
    add_subdirectory(index)
endif (NMTOOLS_BUILD_INDEX_TESTS)

option(NMTOOLS_BUILD_FUNCTIONAL_TESTS "build functional test programs" OFF)
if (NMTOOLS_BUILD_FUNCTIONAL_TESTS)
    add_subdirectory(functional)
endif (NMTOOLS_BUILD_FUNCTIONAL_TESTS)

option(NMTOOLS_BUILD_VIEW_TESTS "build view test programs" OFF)
if (NMTOOLS_BUILD_VIEW_TESTS)
    add_subdirectory(view)
endif (NMTOOLS_BUILD_VIEW_TESTS)

option(NMTOOLS_BUILD_OPENCL_TESTS "build opencl test programs" OFF)
if (NMTOOLS_BUILD_OPENCL_TESTS)
    add_subdirectory(opencl)
endif (NMTOOLS_BUILD_OPENCL_TESTS)

option(NMTOOLS_BUILD_CUDA_TESTS "build cuda test programs" OFF)
if (NMTOOLS_BUILD_CUDA_TESTS)
    add_subdirectory(cuda)
endif (NMTOOLS_BUILD_CUDA_TESTS)

option(NMTOOLS_BUILD_SYCL_TESTS "build sycl test programs" OFF)
if (NMTOOLS_BUILD_SYCL_TESTS)
    add_subdirectory(sycl)
endif (NMTOOLS_BUILD_SYCL_TESTS)

option(NMTOOLS_BUILD_CIRCLE_TESTS "build circle test programs" OFF)
if (NMTOOLS_BUILD_CIRCLE_TESTS)
    add_subdirectory(circle)
endif (NMTOOLS_BUILD_CIRCLE_TESTS)

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