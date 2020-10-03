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
namespace nmtools::bench::nanobench::blas
{
    NMTOOLS_BENCH_WRAPPER_TYPEID(::nmtools::blas, zeros_like);
    NMTOOLS_BENCH_WRAPPER_TYPEID(::nmtools::blas, clone);
    NMTOOLS_BENCH_WRAPPER_TYPEID(::nmtools::blas, identity);

    template <typename array_t>
    auto zeros(ankerl::nanobench::Bench *bench, size_t m)
    {
        auto name = common::make_func_args<array_t,size_t>("zeros");
        bench->run(name, [&](){
            auto x = ::nmtools::blas::zeros<array_t>(m);
            ankerl::nanobench::doNotOptimizeAway(x);
        });
        auto ret = ::nmtools::blas::zeros<array_t>(m);
        return ret;
    }

    template <typename array_t>
    auto zeros(ankerl::nanobench::Bench *bench, size_t m, size_t n)
    {
        auto name = common::make_func_args<array_t,size_t,size_t>("zeros");
        bench->run(name, [&](){
            auto x = ::nmtools::blas::zeros<array_t>(m,n);
            ankerl::nanobench::doNotOptimizeAway(x);
        });
        auto ret = ::nmtools::blas::zeros<array_t>(m,n);
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
            auto x = ::nmtools::blas::zeros<array_t,N...>();
            ankerl::nanobench::doNotOptimizeAway(x);
        });
        auto ret = ::nmtools::blas::zeros<array_t,N...>();
        return ret;
    }

    NMTOOLS_BENCH_WRAPPER_TYPEID(::nmtools::blas, transpose);
    NMTOOLS_BENCH_WRAPPER_TYPEID(::nmtools::blas, ones_like);
    NMTOOLS_BENCH_WRAPPER_TYPEID(::nmtools::blas, mmmul);
    NMTOOLS_BENCH_WRAPPER_TYPEID(::nmtools::blas, mvmul);
    NMTOOLS_BENCH_WRAPPER_TYPEID(::nmtools::blas, msmul);
    NMTOOLS_BENCH_WRAPPER_TYPEID(::nmtools::blas, vsmul);
    NMTOOLS_BENCH_WRAPPER_TYPEID(::nmtools::blas, vvadd);
    NMTOOLS_BENCH_WRAPPER_TYPEID(::nmtools::blas, mmadd);
    NMTOOLS_BENCH_WRAPPER_TYPEID(::nmtools::blas, saxpy);
    NMTOOLS_BENCH_WRAPPER_TYPEID(::nmtools::blas, gaxpy);
    NMTOOLS_BENCH_WRAPPER_TYPEID(::nmtools::blas, dot);
    NMTOOLS_BENCH_WRAPPER_TYPEID(::nmtools::blas, outer);
    NMTOOLS_BENCH_WRAPPER_TYPEID(::nmtools::blas, row_sum);
    NMTOOLS_BENCH_WRAPPER_TYPEID(::nmtools::blas, col_sum);
    NMTOOLS_BENCH_WRAPPER_TYPEID(::nmtools::blas, sum);
    NMTOOLS_BENCH_WRAPPER_TYPEID(::nmtools::blas, norm);
    NMTOOLS_BENCH_WRAPPER_TYPEID(::nmtools::blas, vector_norm);
    NMTOOLS_BENCH_WRAPPER_TYPEID(::nmtools::blas, matrix_norm);

} // nmtools::bench::nanobench

#endif // NMTOOLS_BENCHMARK_BLAS_HPP