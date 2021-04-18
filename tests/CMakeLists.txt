cmake_minimum_required(VERSION 3.10.2)
project(numeric-tests)
# note cxx_std_20 for target_compile_features doesnt seem to work properly on 3.10.2

if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    find_package(nmtools REQUIRED CONFIG)
    set(${NMTOOLS_INCLUDE_DIR} ${nmtools_INCLUDE_DIRS})
    set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../cmake)
endif()

include(nmtools)

# handle emscripten
if(CMAKE_CXX_COMPILER MATCHES "/em\\+\\+(-[a-zA-Z0-9.])?$")
    set (EMSCRIPTEN)
endif()
if (${CMAKE_SYSTEM_PROCESSOR} MATCHES "arm")
    set (ARM)
endif()

# optionally use boost (esp. for type_id)
find_package(Boost)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

enable_testing()

## defer static check to runtime for clang
## since constexpr math not supported
if ((CMAKE_CXX_COMPILER_ID STREQUAL "Clang") OR EMSCRIPTEN OR ANDROID OR MSYS)
    add_definitions(-DDEFER_STATIC_CHECK)
endif ()

## disable benchmarks
add_definitions(-DNMTOOLS_TESTING_DOCTEST_DISABLE_BENCH)

option(TEST_ALL             "test all modules"              ON)
option(TEST_ARRAY_DETAIL    "test array detail modules"     OFF)
option(TEST_ARRAY_UTILITY   "test array utility modules"    OFF)
option(TEST_UTILS           "test utils modules"            OFF)
option(TEST_NDARRAY         "test ndarray modules"          OFF)
option(TEST_ARRAY_VIEW      "test array view modules"       OFF)
option(TEST_ARRAY_UFUNCS    "test array ufuncs modules"     OFF)
option(TEST_ARRAY_EVAL      "test array evaluation"         OFF)
option(TEST_MISC            "test other modules"            OFF)

if (TEST_ALL)
    SET(TEST_ARRAY_DETAIL   ON CACHE BOOL "test array detail modules"   FORCE)
    SET(TEST_ARRAY_UTILITY  ON CACHE BOOL "test array utility modules"  FORCE)
    SET(TEST_UTILS          ON CACHE BOOL "test utils modules"          FORCE)
    SET(TEST_NDARRAY        ON CACHE BOOL "test ndarray modules"        FORCE)
    SET(TEST_ARRAY_VIEW     ON CACHE BOOL "test array view modules"     FORCE)
    SET(TEST_ARRAY_UFUNCS   ON CACHE BOOL "test array ufuncs modules"   FORCE)
    SET(TEST_ARRAY_EVAL     ON CACHE BOOL "test array evaluation"       FORCE)
    SET(TEST_MISC           ON CACHE BOOL "test other modules"          FORCE)
endif (TEST_ALL)

set(ARRAY_DETAIL_TEST_SOURCES
    src/doctest/array/index/argfilter.cpp
    src/doctest/array/index/broadcast_shape.cpp
    src/doctest/array/index/broadcast_to.cpp
    src/doctest/array/index/choose.cpp
    src/doctest/array/index/compress.cpp
    src/doctest/array/index/concatenate.cpp
    src/doctest/array/index/compute_indices.cpp
    src/doctest/array/index/compute_offset.cpp
    src/doctest/array/index/compute_strides.cpp
    src/doctest/array/index/expand_dims.cpp
    src/doctest/array/index/filter.cpp
    src/doctest/array/index/free_axes.cpp
    src/doctest/array/index/gather.cpp
    src/doctest/array/index/logical_not.cpp
    src/doctest/array/index/ndenumerate.cpp
    src/doctest/array/index/ndindex.cpp
    src/doctest/array/index/nonzero.cpp
    src/doctest/array/index/outer.cpp
    src/doctest/array/index/remove_dims.cpp
    src/doctest/array/index/remove_single_dims.cpp
    src/doctest/array/index/repeat.cpp
    src/doctest/array/index/reverse.cpp
    src/doctest/array/index/scatter.cpp
    src/doctest/array/index/shape_concatenate.cpp
    src/doctest/array/index/shape_repeat.cpp
    src/doctest/array/index/shape_tile.cpp
    src/doctest/array/index/slice.cpp
    src/doctest/array/index/tile.cpp
    src/doctest/array/index/take.cpp
)
if (NOT TEST_ARRAY_DETAIL)
    set(ARRAY_DETAIL_TEST_SOURCES "")
endif ()

set(UTILS_TEST_SOURCES
    src/doctest/utils/isequal.cpp
    src/doctest/utils/isclose.cpp
    src/doctest/utils/to_string.cpp
)
if (NOT TEST_UTILS)
    set(UTILS_TEST_SOURCES "")
endif ()

set(ARRAY_UTILITY_TEST_SOURCES
    src/doctest/array/utility/at.cpp
    src/doctest/array/utility/apply_at.cpp
    src/doctest/array/utility/cast.cpp
)
if (NOT TEST_ARRAY_UTILITY)
    set (ARRAY_UTILITY_TEST_SOURCES "")
endif ()

set(NDARRAY_TEST_SOURCES
    src/doctest/array/fixed/vector.cpp
    src/doctest/array/fixed/matrix.cpp
    src/doctest/array/dynamic/matrix.cpp
    src/doctest/array/fixed/ndarray.cpp
    src/doctest/array/hybrid/ndarray.cpp
    src/doctest/array/dynamic/ndarray.cpp
)
if (NOT TEST_NDARRAY)
    set(NDARRAY_TEST_SOURCES "")
endif ()

set(ARRAY_VIEW_TEST_SOURCES
    src/doctest/array/view/broadcast_to.cpp
    src/doctest/array/view/broadcast_arrays.cpp
    src/doctest/array/view/concatenate.cpp
    src/doctest/array/view/compress.cpp
    src/doctest/array/view/expand_dims.cpp
    src/doctest/array/view/flatten.cpp
    src/doctest/array/view/flip.cpp
    src/doctest/array/view/mutable_flatten.cpp
    src/doctest/array/view/mutable_ref.cpp
    src/doctest/array/view/ref.cpp
    src/doctest/array/view/ref/initializer_list.cpp
    src/doctest/array/view/repeat.cpp
    src/doctest/array/view/reshape.cpp
    src/doctest/array/view/slice.cpp
    src/doctest/array/view/squeeze.cpp
    src/doctest/array/view/take.cpp
    src/doctest/array/view/tile.cpp
    src/doctest/array/view/transpose.cpp
    src/doctest/array/view/where.cpp
)
if (NOT TEST_ARRAY_VIEW)
    set (ARRAY_VIEW_TEST_SOURCES "")
endif ()

set(ARRAY_UFUNCS_TEST_SOURCES
    src/doctest/array/view/ufuncs/add.cpp
    src/doctest/array/view/ufuncs/arccos.cpp
    src/doctest/array/view/ufuncs/arccosh.cpp
    src/doctest/array/view/ufuncs/arcsin.cpp
    src/doctest/array/view/ufuncs/arcsinh.cpp
    src/doctest/array/view/ufuncs/arctan.cpp
    src/doctest/array/view/ufuncs/arctanh.cpp
    src/doctest/array/view/ufuncs/arctan2.cpp
    src/doctest/array/view/ufuncs/bitwise_and.cpp
    src/doctest/array/view/ufuncs/bitwise_or.cpp
    src/doctest/array/view/ufuncs/bitwise_xor.cpp
    src/doctest/array/view/ufuncs/cbrt.cpp
    src/doctest/array/view/ufuncs/ceil.cpp
    src/doctest/array/view/ufuncs/clip.cpp
    src/doctest/array/view/ufuncs/cos.cpp
    src/doctest/array/view/ufuncs/cosh.cpp
    src/doctest/array/view/ufuncs/divide.cpp
    src/doctest/array/view/ufuncs/equal.cpp
    src/doctest/array/view/ufuncs/exp.cpp
    src/doctest/array/view/ufuncs/exp2.cpp
    src/doctest/array/view/ufuncs/expm1.cpp
    src/doctest/array/view/ufuncs/fabs.cpp
    src/doctest/array/view/ufuncs/floor.cpp
    src/doctest/array/view/ufuncs/fmax.cpp
    src/doctest/array/view/ufuncs/fmin.cpp
    src/doctest/array/view/ufuncs/fmod.cpp
    src/doctest/array/view/ufuncs/greater.cpp
    src/doctest/array/view/ufuncs/greater_equal.cpp
    src/doctest/array/view/ufuncs/hypot.cpp
    src/doctest/array/view/ufuncs/invert.cpp
    src/doctest/array/view/ufuncs/isfinite.cpp
    src/doctest/array/view/ufuncs/isinf.cpp
    src/doctest/array/view/ufuncs/isnan.cpp
    src/doctest/array/view/ufuncs/ldexp.cpp
    src/doctest/array/view/ufuncs/left_shift.cpp
    src/doctest/array/view/ufuncs/less.cpp
    src/doctest/array/view/ufuncs/less_equal.cpp
    src/doctest/array/view/ufuncs/log.cpp
    src/doctest/array/view/ufuncs/log1p.cpp
    src/doctest/array/view/ufuncs/log2.cpp
    src/doctest/array/view/ufuncs/log10.cpp
    src/doctest/array/view/ufuncs/logical_and.cpp
    src/doctest/array/view/ufuncs/logical_not.cpp
    src/doctest/array/view/ufuncs/logical_or.cpp
    src/doctest/array/view/ufuncs/logical_xor.cpp
    src/doctest/array/view/ufuncs/maximum.cpp
    src/doctest/array/view/ufuncs/minimum.cpp
    src/doctest/array/view/ufuncs/multiply.cpp
    src/doctest/array/view/ufuncs/negative.cpp
    src/doctest/array/view/ufuncs/not_equal.cpp
    src/doctest/array/view/ufuncs/positive.cpp
    src/doctest/array/view/ufuncs/power.cpp
    src/doctest/array/view/ufuncs/reciprocal.cpp
    src/doctest/array/view/ufuncs/right_shift.cpp
    src/doctest/array/view/ufuncs/rint.cpp
    src/doctest/array/view/ufuncs/signbit.cpp
    src/doctest/array/view/ufuncs/sin.cpp
    src/doctest/array/view/ufuncs/sinh.cpp
    src/doctest/array/view/ufuncs/sqrt.cpp
    src/doctest/array/view/ufuncs/square.cpp
    src/doctest/array/view/ufuncs/subtract.cpp
    src/doctest/array/view/ufuncs/tan.cpp
    src/doctest/array/view/ufuncs/tanh.cpp
    src/doctest/array/view/ufuncs/trunc.cpp
)
if (NOT TEST_ARRAY_UFUNCS)
    set (ARRAY_UFUNCS_TEST_SOURCES "")
endif ()

set(ARRAY_EVAL_TEST_SOURCES
    src/doctest/array/array/broadcast_to.cpp
    src/doctest/array/array/flip.cpp
    src/doctest/array/array/ufuncs/add.cpp
    src/doctest/array/array/ufuncs/arccos.cpp
    src/doctest/array/array/ufuncs/arccosh.cpp
    src/doctest/array/array/ufuncs/arcsin.cpp
    src/doctest/array/array/ufuncs/arcsinh.cpp
    src/doctest/array/array/ufuncs/arctan.cpp
    src/doctest/array/array/ufuncs/arctan2.cpp
    src/doctest/array/array/ufuncs/arctanh.cpp
    src/doctest/array/array/ufuncs/bitwise_and.cpp
    src/doctest/array/array/ufuncs/bitwise_or.cpp
    src/doctest/array/array/ufuncs/bitwise_xor.cpp
    src/doctest/array/array/ufuncs/ceil.cpp
    src/doctest/array/array/ufuncs/clip.cpp
    src/doctest/array/array/ufuncs/cos.cpp
    src/doctest/array/array/ufuncs/cosh.cpp
    src/doctest/array/array/ufuncs/divide.cpp
    src/doctest/array/array/ufuncs/equal.cpp
    src/doctest/array/array/ufuncs/exp.cpp
    src/doctest/array/array/ufuncs/exp2.cpp
    src/doctest/array/array/ufuncs/expm1.cpp
    src/doctest/array/array/ufuncs/fabs.cpp
    src/doctest/array/array/ufuncs/floor.cpp
    src/doctest/array/array/ufuncs/fmax.cpp
    src/doctest/array/array/ufuncs/fmin.cpp
    src/doctest/array/array/ufuncs/fmod.cpp
    src/doctest/array/array/ufuncs/greater_equal.cpp
    src/doctest/array/array/ufuncs/greater.cpp
    src/doctest/array/array/ufuncs/hypot.cpp
    src/doctest/array/array/ufuncs/invert.cpp
    src/doctest/array/array/ufuncs/isfinite.cpp
    src/doctest/array/array/ufuncs/isinf.cpp
    src/doctest/array/array/ufuncs/isnan.cpp
    src/doctest/array/array/ufuncs/ldexp.cpp
    src/doctest/array/array/ufuncs/left_shift.cpp
    src/doctest/array/array/ufuncs/less_equal.cpp
    src/doctest/array/array/ufuncs/less.cpp
    src/doctest/array/array/ufuncs/log.cpp
    src/doctest/array/array/ufuncs/log1p.cpp
    src/doctest/array/array/ufuncs/log2.cpp
    src/doctest/array/array/ufuncs/log10.cpp
    src/doctest/array/array/ufuncs/logical_and.cpp
    src/doctest/array/array/ufuncs/logical_not.cpp
    src/doctest/array/array/ufuncs/logical_or.cpp
    src/doctest/array/array/ufuncs/logical_xor.cpp
    src/doctest/array/array/ufuncs/maximum.cpp
    src/doctest/array/array/ufuncs/minimum.cpp
    src/doctest/array/array/ufuncs/multiply.cpp
    src/doctest/array/array/ufuncs/negative.cpp
    src/doctest/array/array/ufuncs/not_equal.cpp
    src/doctest/array/array/ufuncs/positive.cpp
    src/doctest/array/array/ufuncs/power.cpp
    src/doctest/array/array/ufuncs/reciprocal.cpp
    src/doctest/array/array/ufuncs/right_shift.cpp
    src/doctest/array/array/ufuncs/rint.cpp
    src/doctest/array/array/ufuncs/signbit.cpp
    src/doctest/array/array/ufuncs/sin.cpp
    src/doctest/array/array/ufuncs/sinh.cpp
    src/doctest/array/array/ufuncs/sqrt.cpp
    src/doctest/array/array/ufuncs/square.cpp
    src/doctest/array/array/ufuncs/subtract.cpp
    src/doctest/array/array/ufuncs/tan.cpp
    src/doctest/array/array/ufuncs/tanh.cpp
    src/doctest/array/array/ufuncs/trunc.cpp
)
if (NOT TEST_ARRAY_EVAL)
    set (ARRAY_EVAL_TEST_SOURCES "")
endif ()

set(MISC_TEST_SOURCES
    src/doctest/misc/constants.cpp
)
if (NOT TEST_MISC)
    set (MISC_TEST_SOURCES "")
endif()

add_executable(${PROJECT_NAME}-doctest src/doctest/tests.cpp 
    ## array detail
    ${ARRAY_DETAIL_TEST_SOURCES}
    ## utility function
    ${UTILS_TEST_SOURCES}
    ## array utility
    ${ARRAY_UTILITY_TEST_SOURCES}
    ## ndarray
    ${NDARRAY_TEST_SOURCES}
    ## view
    ${ARRAY_VIEW_TEST_SOURCES}
    ## ufuncs
    ${ARRAY_UFUNCS_TEST_SOURCES}
    ## array evaluation
    ${ARRAY_EVAL_TEST_SOURCES}
    ## misc
    ${MISC_TEST_SOURCES}
)

target_compile_features(${PROJECT_NAME}-doctest PRIVATE cxx_std_17)
if (doctest_FOUND)
    target_link_libraries(${PROJECT_NAME}-doctest PRIVATE doctest::doctest)
endif()

option(ENABLE_TEST_BENCHMARKS "build benchmark programs" OFF)
if (ENABLE_TEST_BENCHMARKS)
    add_definitions(-DNMTOOLS_TESTING_ENABLE_BENCHMARKS)
    add_library(nanobench src/nanobench.cpp)
    target_link_libraries(${PROJECT_NAME}-doctest PRIVATE nanobench)
endif()

add_executable(${PROJECT_NAME}-doctest-meta src/doctest/tests.cpp 
    ## metafunctions
    src/doctest/meta.cpp
    src/doctest/meta/loop.cpp
    src/doctest/meta/array/index/argfilter.cpp
    src/doctest/meta/array/index/broadcast_shape.cpp
    src/doctest/meta/array/index/choose.cpp
    src/doctest/meta/array/index/concatenate.cpp
    src/doctest/meta/array/index/expand_dims.cpp
    src/doctest/meta/array/index/gather.cpp
    src/doctest/meta/array/index/nonzero.cpp
    src/doctest/meta/traits/apply_conjunction.cpp
    src/doctest/meta/traits/apply_disjunction.cpp
    src/doctest/meta/traits/compose_logical_and.cpp
    src/doctest/meta/traits/compose_logical_or.cpp
    src/doctest/meta/traits/ndarray.cpp
    src/doctest/meta/traits/has_template_get.cpp
    src/doctest/meta/traits/has_type.cpp
    src/doctest/meta/traits/has_square_bracket.cpp
    src/doctest/meta/traits/is_index.cpp
    src/doctest/meta/traits/is_index_array.cpp
    src/doctest/meta/transform/accumulate.cpp
    src/doctest/meta/transform/apply.cpp
    src/doctest/meta/transform/constant.cpp
    src/doctest/meta/transform/constant_to_sequence.cpp
    src/doctest/meta/transform/gather.cpp
    src/doctest/meta/transform/get_element_type.cpp
    src/doctest/meta/transform/insert_type.cpp
    src/doctest/meta/transform/replace_element_type.cpp
    src/doctest/meta/transform/nested_array_dim.cpp
    src/doctest/meta/transform/reduce.cpp
    src/doctest/meta/transform/remove_nested_array_extents.cpp
    src/doctest/meta/transform/replace_at.cpp
    src/doctest/meta/transform/select_array.cpp
    src/doctest/meta/transform/sequence.cpp
    src/doctest/meta/transform/split_at.cpp
    src/doctest/meta/transform/scatter.cpp
    src/doctest/meta/get_container_value_type.cpp
)
# omg
if ((NOT EMSCRIPTEN) AND (NOT ANDROID))
    target_compile_features(${PROJECT_NAME}-doctest-meta PRIVATE cxx_std_17)
    if (doctest_FOUND)
        target_link_libraries(${PROJECT_NAME}-doctest-meta PRIVATE doctest::doctest)
    endif()
endif()

apply_nmtools(
    TARGET ${PROJECT_NAME}-doctest
    COMPILE_OPTIONS -g
)
target_include_directories(
    ${PROJECT_NAME}-doctest PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

apply_nmtools(
    TARGET ${PROJECT_NAME}-doctest-meta
    COMPILE_OPTIONS -g
)
target_include_directories(
    ${PROJECT_NAME}-doctest-meta PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
# for now, force metafunctions test to defer static check
target_compile_definitions(
    ${PROJECT_NAME}-doctest-meta PRIVATE
    DEFER_STATIC_CHECK
)

option(DEFER_STATIC_CHECK "defer static check to runtime for testing purpose" OFF)
if (DEFER_STATIC_CHECK)
    add_definitions(-DDEFER_STATIC_CHECK)
endif ()


option(ADDRESS_SANITIZER "build with -fsanitize=address" OFF)
message(STATUS "ADDRESS_SANITIZER ${ADDRESS_SANITIZER}")

# from https://gist.github.com/jlblancoc/44be9d4d466f0a973b1f3808a8e56782
# TODO: findout if can be used for private target instead
# TODO: find out if can be used with other compiler
# TODO: provide option to disable/enable
if (ADDRESS_SANITIZER)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fsanitize=leak")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address -fsanitize=leak")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address -fsanitize=leak")
    set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -fsanitize=address -fsanitize=leak")
endif (ADDRESS_SANITIZER)

option(CODE_COVERAGE "build with code coverage reporting" OFF)
message(STATUS "CODE_COVERAGE ${CODE_COVERAGE}")
if (CODE_COVERAGE)
    include(CodeCoverage)
    append_coverage_compiler_flags()
    setup_target_for_coverage_gcovr_html(
        NAME ${PROJECT_NAME}-coverage 
        EXECUTABLE ${PROJECT_NAME}
        EXCLUDE "${PROJECT_SOURCE_DIR}/examples/*" "${PROJECT_SOURCE_DIR}/tests/*" "/usr/*"
    )
    setup_target_for_coverage_gcovr_html(
        NAME ${PROJECT_NAME}-doctest-coverage 
        EXECUTABLE ${PROJECT_NAME}-doctest
        EXCLUDE "${PROJECT_SOURCE_DIR}/examples/*" "${PROJECT_SOURCE_DIR}/tests/*" "/usr/*"
    )
endif (CODE_COVERAGE)

# for emscripten generate js
if(CMAKE_CXX_COMPILER MATCHES "/em\\+\\+(-[a-zA-Z0-9.])?$")
    message(" * C++ compiler: Emscripten")
    message(STATUS "Emscripten detected")
    option(JS_ONLY "build javascript only for emscripten" OFF)
    if(JS_ONLY)
        message(STATUS "Setting compilation target to native JavaScript")
        set(CMAKE_EXECUTABLE_SUFFIX ".js")
        set_target_properties(
            ${PROJECT_NAME}-doctest
            ${PROJECT_NAME}-doctest-meta
            PROPERTIES LINK_FLAGS "--emrun -s EXPORTED_FUNCTIONS='[_main]'"
        )
    else(JS_ONLY)
        message(STATUS "Setting compilation target to WASM")
        set(CMAKE_EXECUTABLE_SUFFIX ".wasm.js")
        set_target_properties(
            ${PROJECT_NAME}-doctest
            ${PROJECT_NAME}-doctest-meta
            PROPERTIES LINK_FLAGS "--emrun -s WASM=1 -s BINARYEN_METHOD='native-wasm' -s EXPORTED_FUNCTIONS='[_main]' -s NO_EXIT_RUNTIME=1 -s EXTRA_EXPORTED_RUNTIME_METHODS=['ccall']"
        )
    endif(JS_ONLY)
endif()