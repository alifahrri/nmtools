#ifndef NMTOOLS_BENCHMARK_BLAS_HPP
#define NMTOOLS_BENCHMARK_BLAS_HPP

#include "nmtools/blas/blas.hpp"
// TODO: rename to nmtools/bench/common/ or something
#include "common.hpp"

#include <boost/type_index.hpp>
#include <sstream>

/**
 * @brief wraps nmtools functions to nanobench
 * 
 */
namespace nmtools::bench::nanobench
{
    NMTOOLS_BENCH_WRAPPER_TYPEID(blas, zeros_like);
    NMTOOLS_BENCH_WRAPPER_TYPEID(blas, clone);
    NMTOOLS_BENCH_WRAPPER_TYPEID(blas, identity);

    template <typename array_t>
    auto zeros(ankerl::nanobench::Bench *bench, size_t m)
    {
        auto name = common::make_func_args<array_t,size_t>("zeros");
        bench->run(name, [&](){
            auto x = blas::zeros<array_t>(m);
            ankerl::nanobench::doNotOptimizeAway(x);
        });
        auto ret = blas::zeros<array_t>(m);
        return ret;
    }

    template <typename array_t>
    auto zeros(ankerl::nanobench::Bench *bench, size_t m, size_t n)
    {
        auto name = common::make_func_args<array_t,size_t,size_t>("zeros");
        bench->run(name, [&](){
            auto x = blas::zeros<array_t>(m,n);
            ankerl::nanobench::doNotOptimizeAway(x);
        });
        auto ret = blas::zeros<array_t>(m,n);
        return ret;
    }

    template <typename array_t, size_t...N>
    auto zeros(ankerl::nanobench::Bench *bench)
    {
        std::stringstream ss;
        ss << "zeros<";
        ss << boost::typeindex::type_id<array_t>() << ",";
        (ss << ... << N);
        ss << ">()";
        auto name = ss.str();
        bench->run(name, [&](){
            auto x = blas::zeros<array_t,N...>();
            ankerl::nanobench::doNotOptimizeAway(x);
        });
        auto ret = blas::zeros<array_t,N...>();
        return ret;
    }

    NMTOOLS_BENCH_WRAPPER_TYPEID(blas, transpose);
    NMTOOLS_BENCH_WRAPPER_TYPEID(blas, ones_like);
    NMTOOLS_BENCH_WRAPPER_TYPEID(blas, mmmul);
    NMTOOLS_BENCH_WRAPPER_TYPEID(blas, mvmul);
    NMTOOLS_BENCH_WRAPPER_TYPEID(blas, msmul);
    NMTOOLS_BENCH_WRAPPER_TYPEID(blas, vsmul);
    NMTOOLS_BENCH_WRAPPER_TYPEID(blas, vvadd);
    NMTOOLS_BENCH_WRAPPER_TYPEID(blas, mmadd);
    NMTOOLS_BENCH_WRAPPER_TYPEID(blas, saxpy);
    NMTOOLS_BENCH_WRAPPER_TYPEID(blas, gaxpy);
    NMTOOLS_BENCH_WRAPPER_TYPEID(blas, dot);
    NMTOOLS_BENCH_WRAPPER_TYPEID(blas, outer);

} // nmtools::bench::nanobench

#endif // NMTOOLS_BENCHMARK_BLAS_HPP