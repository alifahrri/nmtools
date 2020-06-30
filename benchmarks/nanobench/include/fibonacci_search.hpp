#ifndef FIBONACCI_SEARCH_HPP
#define FIBONACCI_SEARCH_HPP

#include "nanobench/nanobench.h"
#include "nmtools/optimization.hpp"

namespace nmt = nmtools;
namespace opt = nmtools::optimization;

template <typename T>
void fibonacci_search_benchmark(ankerl::nanobench::Bench *bench, char const* name) {
    /* define objective function */
    auto f = [](T x) {
        return x*x;
    };
    /* lower & upper limit */
    T x_l = -2.0;
    T x_u = 2.0;
    bench->run(name, [&](){
        auto x_opt = opt::fibonacci_search<10>(f,x_l,x_u);
        ankerl::nanobench::doNotOptimizeAway(x_opt);
    });
}

#endif