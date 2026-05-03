cmake_minimum_required(VERSION 3.13)
project(tilekit-softmax)

set(NMTOOLS_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../include)
message(NMTOOLS_INCLUDE_DIR: ${NMTOOLS_INCLUDE_DIR})

include(FetchContent)
FetchContent_Declare(
    nanobench
    GIT_REPOSITORY https://github.com/martinus/nanobench.git
    GIT_TAG v4.1.0
    GIT_SHALLOW TRUE)
FetchContent_MakeAvailable(nanobench)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${NMTOOLS_INCLUDE_DIR})
add_executable(${PROJECT_NAME}
    softmax.cpp
)
target_compile_options(${PROJECT_NAME} PRIVATE -std=c++17 -O3)
target_link_libraries(${PROJECT_NAME} PRIVATE nanobench)