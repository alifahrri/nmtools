#include <benchmark/benchmark.h>
#include "nmtools/optimization.hpp"
#include "nmtools/ode.hpp"
#include "nmtools/curvefit.hpp"

#include <vector>
#include <array>

namespace nmt = nmtools;
namespace ode = nmtools::ode;
namespace cvt = nmt::curvefit;
namespace opt = nmtools::optimization;

template <typename T>
void fibonacci_search(benchmark::State& state) {
    /* define objective function */
    auto f = [](T x) {
        return x*x;
    };
    /* lower & upper limit */
    T x_l = -2.0;
    T x_u = 2.0;
    for (auto _ : state) {
        auto x_opt = opt::fibonacci_search<10>(f,x_l,x_u);
        benchmark::DoNotOptimize(x_opt);
    }
}
BENCHMARK_TEMPLATE(fibonacci_search, double);
BENCHMARK_TEMPLATE(fibonacci_search, float);

template <typename T>
void bm_ode(benchmark::State& state) {
    /* define differential equation */
    auto dy = [](T x, T y) {
        return -2*(x*x*x) + 12*(x*x) - 20*x + 8.5;
    };
    /* initial state and step */
    T h = 0.001;
    T xi = 0.0;
    T xf = 0.5;
    T yi = 1.0;
    for (auto _ : state) {
        auto yn = ode::rk4(dy,xi,xf,yi,h);
        benchmark::DoNotOptimize(yn);
    }
}
BENCHMARK_TEMPLATE(bm_ode, double);
BENCHMARK_TEMPLATE(bm_ode, float);

BENCHMARK_MAIN();