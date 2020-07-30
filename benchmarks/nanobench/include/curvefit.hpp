#ifndef SPLINE_HPP
#define SPLINE_HPP

#include "nanobench/nanobench.h"
#include "nmtools/curvefit.hpp"

#include <vector>
#include <array>

namespace nmt = nmtools;
namespace cvt = nmt::curvefit;

template <typename X, typename Y>
void cubic_spline_construct_benchmark(ankerl::nanobench::Bench *bench, char const* name, const X& x, const Y& y)
{
    bench->run(name, [&](){
        auto result = cvt::cubic_spline(x,y);
        ankerl::nanobench::doNotOptimizeAway(result);
    });
}

template <typename F, typename T>
void cubic_spline_eval_benchmark(ankerl::nanobench::Bench *bench, char const* name, const F& f, const T& t)
{
    bench->run(name, [&](){
        auto result = f(t);
        ankerl::nanobench::doNotOptimizeAway(result);
    });
}

template <typename X, typename Y>
void linear_spline_construct_benchmark(ankerl::nanobench::Bench *bench, char const* name, const X& x, const Y& y)
{
    bench->run(name, [&](){
        auto result = cvt::linear_spline(x,y);
        ankerl::nanobench::doNotOptimizeAway(result);
    });
}

template <typename F, typename T>
void linear_spline_eval_benchmark(ankerl::nanobench::Bench *bench, char const* name, const F& f, const T& t)
{
    bench->run(name, [&](){
        auto result = f(t);
        ankerl::nanobench::doNotOptimizeAway(result);
    });
}

template <typename X, typename Y>
void linear_regression_benchmark(ankerl::nanobench::Bench *bench, char const* name, const X& x, const Y& y)
{
    bench->run(name, [&](){
        auto results = cvt::linear_regression(x,y);
        ankerl::nanobench::doNotOptimizeAway(results);
    });
}

template <typename X, typename Y, typename ...Vector>
void least_square_regression_benchmark(ankerl::nanobench::Bench *bench, char const* name, const Y& y, const X& x, const Vector&...xs)
{
    bench->run(name, [&](){
        auto results = cvt::least_square_regression(y,x,xs...);
        ankerl::nanobench::doNotOptimizeAway(results);
    });
}

#endif