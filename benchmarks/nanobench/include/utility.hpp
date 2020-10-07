#ifndef NMTOOLS_BENCHMARK_NANOBENCH_UTILITY_HPP
#define NMTOOLS_BENCHMARK_NANOBENCH_UTILITY_HPP

#include "nmtools/array/utility.hpp"
// TODO: rename to nmtools/bench/common/ or something
#include "common.hpp"

namespace nmtools::bench::nanobench
{
    NMTOOLS_BENCH_WRAPPER_TYPEID(::nmtools,at);
    NMTOOLS_BENCH_WRAPPER_TYPEID(::nmtools,row);
    NMTOOLS_BENCH_WRAPPER_TYPEID(::nmtools,column);
    NMTOOLS_BENCH_WRAPPER_TYPEID(::nmtools,slice);
    NMTOOLS_BENCH_WRAPPER_TYPEID(::nmtools,squeeze);
} // namespace nmtools::bench::nanobench

#endif // NMTOOLS_BENCHMARK_NANOBENCH_UTILITY_HPP