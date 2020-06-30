#ifndef SPLINE_HPP
#define SPLINE_HPP

#include "nanobench/nanobench.h"
#include "nmtools/curvefit.hpp"

#include <vector>
#include <array>

namespace nmt = nmtools;
namespace cvt = nmt::curvefit;

template <typename Container>
void spline_benchmark(ankerl::nanobench::Bench *bench, char const* name) {
    Container t_data{
        0.0, 0.1, 0.2, 0.35, 0.5, 0.65, 0.8, 0.9, 1.0
    };
    Container x_data{
        0.0, 0.125, 0.25, 0.4375, 0.625, 0.8125, 1.0, 1.0, 1.0
    };
    bench->run(name, [&](){
        auto results = cvt::cubic_spline(t_data, x_data, t_data);
        ankerl::nanobench::doNotOptimizeAway(results);
    });
}

template <>
void spline_benchmark<std::array<double,9>>(ankerl::nanobench::Bench *bench, char const* name) {
    std::array<double,9> t_data{
        0.0, 0.1, 0.2, 0.35, 0.5, 0.65, 0.8, 0.9, 1.0
    };
    std::array<double,9> x_data{
        0.0, 0.125, 0.25, 0.4375, 0.625, 0.8125, 1.0, 1.0, 1.0
    };
    bench->run(name, [&](){
        auto results = cvt::cubic_spline(t_data, x_data, t_data);
        ankerl::nanobench::doNotOptimizeAway(results);
    });
}

template <>
void spline_benchmark<std::array<float,9>>(ankerl::nanobench::Bench *bench, char const* name) {
    std::array<float,9> t_data{
        0.0, 0.1, 0.2, 0.35, 0.5, 0.65, 0.8, 0.9, 1.0
    };
    std::array<float,9> x_data{
        0.0, 0.125, 0.25, 0.4375, 0.625, 0.8125, 1.0, 1.0, 1.0
    };
    bench->run(name, [&](){
        auto results = cvt::cubic_spline(t_data, x_data, t_data);
        ankerl::nanobench::doNotOptimizeAway(results);
    });
}

#endif