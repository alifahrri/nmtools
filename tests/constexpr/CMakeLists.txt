cmake_minimum_required(VERSION 3.10.2)
project(numeric-tests-constexpr)

find_package(Boost)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

enable_testing()

set(NMTOOLS_CONSTEXPR_TEST_SOURCES
    src/atleast_1d.cpp
    src/atleast_2d.cpp
    src/atleast_3d.cpp
)

add_executable(${PROJECT_NAME}-doctest tests.cpp
    ${NMTOOLS_CONSTEXPR_TEST_SOURCES}
)

target_compile_options(${PROJECT_NAME}-doctest PRIVATE --std=c++17)

if (doctest_FOUND)
    target_link_libraries(${PROJECT_NAME}-doctest PRIVATE doctest::doctest)
endif ()