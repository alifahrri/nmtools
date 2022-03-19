cmake_minimum_required(VERSION 3.10.2)
project(numeric-tests-bench)

add_executable(${PROJECT_NAME}
    src/mnist.cpp
    src/tests.cpp
)
add_library(${PROJECT_NAME}-nanobench src/nanobench.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}-nanobench)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_compile_options(${PROJECT_NAME} PRIVATE -g -march=native)
target_include_directories(${PROJECT_NAME} PRIVATE include)