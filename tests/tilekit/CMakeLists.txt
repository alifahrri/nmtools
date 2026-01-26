cmake_minimum_required(VERSION 3.13)
project(numeric-tests-tilekit)

if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    find_package(nmtools REQUIRED CONFIG)
    set(${NMTOOLS_INCLUDE_DIR} ${nmtools_INCLUDE_DIRS})
    set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../cmake)
endif()

include(nmtools)

# TODO: cleanup
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

include(FetchContent)

FetchContent_Declare(
    nanobench
    GIT_REPOSITORY https://github.com/martinus/nanobench.git
    GIT_TAG v4.1.0
    GIT_SHALLOW TRUE)
FetchContent_MakeAvailable(nanobench)

enable_testing()

# TODO: remove, trye to detect constexpr math from stdlib
## defer static check to runtime for clang
## since constexpr math not supported
if ((CMAKE_CXX_COMPILER_ID STREQUAL "Clang") OR EMSCRIPTEN OR ANDROID OR MSYS)
    add_definitions(-DDEFER_STATIC_CHECK)
endif ()

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

option(NMTOOLS_TESTS_TILEKIT_ENABLE_TRACY "build tilekit tests with tracy profiling" OFF)

function(remove_target_compile_option TARGET_NAME OPTION_TO_REMOVE)
    # Get the current compile options property as a list
    get_target_property(_options ${TARGET_NAME} COMPILE_OPTIONS)

    if(_options)
        # Iterate over the list and remove the specific option
        list(REMOVE_ITEM _options ${OPTION_TO_REMOVE})

        # Set the modified list back to the property
        set_target_properties(${TARGET_NAME} PROPERTIES
            COMPILE_OPTIONS "${_options}"
        )
    endif()
endfunction()


set(NMTOOLS_TESTS_TILEKIT_SRCS
    src/tilekit.cpp
    src/vector.cpp

    src/add_v128_st.cpp
    src/multiply_v128_st.cpp
    src/subtract_v128_st.cpp
    src/divide_v128_st.cpp

    src/add_v128_mt.cpp
    src/multiply_v128_mt.cpp
    src/subtract_v128_mt.cpp
    src/divide_v128_mt.cpp

    src/add_padding_v128_st.cpp
    src/multiply_padding_v128_st.cpp
    src/subtract_padding_v128_st.cpp
    src/divide_padding_v128_st.cpp

    src/add_padding_v128_mt.cpp
    src/multiply_padding_v128_mt.cpp
    src/subtract_padding_v128_mt.cpp
    src/divide_padding_v128_mt.cpp

    src/add_v256_mt.cpp
    src/multiply_v256_mt.cpp

    src/add_v512_mt.cpp
    src/multiply_v512_mt.cpp
)
if (NMTOOLS_TESTS_TILEKIT_ENABLE_TRACY)
    add_executable(${PROJECT_NAME}-doctest tests.cpp 
        ${NMTOOLS_TESTS_TILEKIT_SRCS}
        /opt/tracy/public/TracyClient.cpp
    )
    target_compile_definitions(${PROJECT_NAME}-doctest PRIVATE -DTRACY_ENABLE)
    ## TODO: configurable tracy directory
    target_include_directories(${PROJECT_NAME}-doctest PRIVATE /opt/tracy/public/)
    remove_target_compile_option(${PROJECT_NAME}-doctest "-Werror")
else ()
    add_executable(${PROJECT_NAME}-doctest tests.cpp 
        ${NMTOOLS_TESTS_TILEKIT_SRCS}
    )
endif()

add_test(
    NAME ${PROJECT_NAME}-doctest
    COMMAND ${PROJECT_NAME}-doctest
)
set(NMTOOLS_TEST_TILEKIT_ARCH "native" CACHE STRING "manually set tilekit arch")
option(NMTOOLS_TESTS_TILEKIT_ENABLE_TSAN "build tilekit tests with thread sanitizer enabled" OFF)

if (NMTOOLS_TESTS_TILEKIT_ENABLE_TSAN)
    set(NMTOOLS_TEST_TILEKIT_OPT -g -O3 -fsanitize=thread)
else ()
    # set(NMTOOLS_TEST_TILEKIT_OPT -g -O2)
    set(NMTOOLS_TEST_TILEKIT_OPT -g -O3)
endif ()
target_compile_options(${PROJECT_NAME}-doctest
    PRIVATE
    ${NMTOOLS_TEST_TILEKIT_OPT} -march=${NMTOOLS_TEST_TILEKIT_ARCH}
)
target_link_libraries(${PROJECT_NAME}-doctest PRIVATE nanobench)
if (NMTOOLS_TESTS_TILEKIT_ENABLE_TSAN)
    target_link_options(${PROJECT_NAME}-doctest PRIVATE -fsanitize=thread)
endif ()

target_compile_options(${PROJECT_NAME}-doctest PRIVATE -std=c++17)
if (doctest_FOUND)
    target_link_libraries(${PROJECT_NAME}-doctest PRIVATE doctest::doctest)
endif()

apply_nmtools(
    TARGET ${PROJECT_NAME}-doctest
    COMPILE_OPTIONS -g
)
target_include_directories(
    ${PROJECT_NAME}-doctest PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if (NMTOOLS_CODE_COVERAGE)
    target_link_libraries(${PROJECT_NAME}-doctest PUBLIC coverage_config)
endif (NMTOOLS_CODE_COVERAGE)