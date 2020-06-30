cmake_minimum_required(VERSION 3.10)

find_package(benchmark REQUIRED)

add_executable(
    bm_benchmark
    src/benchmark.cpp
)

target_link_libraries(bm_benchmark benchmark::benchmark)

target_compile_options(
    bm_benchmark PRIVATE
    -O3 -march=native
)