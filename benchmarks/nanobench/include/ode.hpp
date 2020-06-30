#ifndef ODE_HPP
#define ODE_HPP

#include "nanobench/nanobench.h"
#include "nmtools/ode.hpp"

namespace nmt = nmtools;
namespace ode = nmtools::ode;

template <typename T>
void ode_benchmark(ankerl::nanobench::Bench *bench, char const* name) {
    /* define differential equation */
    auto dy = [](T x, T y) {
        return -2*(x*x*x) + 12*(x*x) - 20*x + 8.5;
    };
    /* initial state and step */
    T h = 0.001;
    T xi = 0.0;
    T xf = 0.5;
    T yi = 1.0;
    bench->run(name, [&](){
        auto yn = ode::rk4(dy,xi,xf,yi,h);
        ankerl::nanobench::doNotOptimizeAway(yn);
    });
}

#endif