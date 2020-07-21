#ifndef LINALG_HPP
#define LINALG_HPP

#include "nanobench/nanobench.h"
#include "nmtools/linalg.hpp"
#include <array>

namespace nmt = nmtools;
namespace nla = nmt::linalg;
using std::array;

template <typename T>
void gauss_elimination_benchmark(ankerl::nanobench::Bench *bench, char const *name) 
{
    /** TODO: benchmark other container **/
    auto A = array<array<T,3>,3>{
        array<T,3>{3.0, -0.1, -0.2},
        array<T,3>{0.1,  7.0, -0.3},
        array<T,3>{0.3, -0.2, 10.0},
    };
    auto b = array<T,3>{7.85, -19.3, 71.4};
    bench->run(name, [&](){
        auto x = nla::gauss_elimination(A,b);
    });
}

template <typename Array>
void lu_decomposition_benchmark(ankerl::nanobench::Bench *bench, char const *name, const Array& A) 
{
    bench->run(name, [&](){
        auto [L,U] = nla::lu_decomposition(A);
        ankerl::nanobench::doNotOptimizeAway(L);
        ankerl::nanobench::doNotOptimizeAway(U);
    });
}

template <typename Array>
void inverse_benchmark(ankerl::nanobench::Bench *bench, char const *name, const Array& A) 
{
    bench->run(name, [&](){
        auto inv = nla::inverse(A);
        ankerl::nanobench::doNotOptimizeAway(inv);
    });
}

template <typename Array>
void cholesky_decomposition_benchmark(ankerl::nanobench::Bench *bench, char const *name, const Array& A) 
{
    bench->run(name, [&](){
        auto L = nla::cholesky_decomposition(A);
        ankerl::nanobench::doNotOptimizeAway(L);
    });
}

template <typename E, typename F, typename G, typename B>
void tridiagonal_elimination_benchmark(ankerl::nanobench::Bench *bench, char const *name, const E& e, const F& f, const G& g, const B& b)
{
    using tag_t = nmt::tag::no_assert_t;
    bench->run(name, [&](){
        auto x = nla::tridiagonal_elimination<tag_t>(e,f,g,b);
        ankerl::nanobench::doNotOptimizeAway(x);
    });
}

#endif