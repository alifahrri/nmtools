#include "nmtools/tilekit/vector.hpp"
#include "nmtools/tilekit/tilekit.hpp"
#include "nmtools/array/ufuncs/add.hpp"
#include "nmtools/array/random.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/ndarray.hpp"

#include "kernels/add.hpp"

#include <nanobench.h>

namespace nm = nmtools;
using nmtools_array, nmtools_tuple;
using namespace nmtools::literals;

TEST_CASE("add_padding.1024_8.fp32.2x4" * doctest::test_suite("tilekit"))
{
    auto gen   = nm::random_engine();
    auto dtype = nm::float32;

    auto M = 1024;
    auto N = 8;
    auto a_shape = array{M,N};
    auto b_shape = array{M,N};
    auto t_shape = tuple{2_ct,4_ct};

    auto a = nm::random(a_shape,dtype,gen);
    auto b = nm::random(b_shape,dtype,gen);
    auto c = nm::Array::zeros(array{M,N},dtype);

    auto ctx = tk::vector::Context;

    auto min_time = std::chrono::nanoseconds(10'000'000);
    ankerl::nanobench::Bench()
        .minEpochTime(min_time)
        .run("add_padding.1024_8.fp32.2x4",[&](){
            add_padding_kernel(ctx,c,a,b,t_shape);
        });

    auto expected = nm::add(a,b);
    NMTOOLS_ASSERT_CLOSE( c, expected );
}

TEST_CASE("add_padding.1024_8ct.fp32.2x4" * doctest::test_suite("tilekit"))
{
    auto gen   = nm::random_engine();
    auto dtype = nm::float32;

    auto M = 1024;
    auto N = 8_ct;
    auto a_shape = tuple{M,N};
    auto b_shape = tuple{M,N};
    auto t_shape = tuple{2_ct,4_ct};

    auto a = nm::random(a_shape,dtype,gen);
    auto b = nm::random(b_shape,dtype,gen);
    auto c = nm::Array::zeros(tuple{M,N},dtype);

    auto ctx = tk::vector::Context;

    auto min_time = std::chrono::nanoseconds(10'000'000);
    ankerl::nanobench::Bench()
        .minEpochTime(min_time)
        .run("add_padding.1024_8ct.fp32.2x4",[&](){
            add_padding_kernel(ctx,c,a,b,t_shape);
        });

    auto expected = nm::add(a,b);
    NMTOOLS_ASSERT_CLOSE( c, expected );
}

TEST_CASE("add_padding.1024ct_8ct.fp32.2x4" * doctest::test_suite("tilekit"))
{
    auto gen   = nm::random_engine();
    auto dtype = nm::float32;

    auto M = 1024_ct;
    auto N = 8_ct;
    auto a_shape = tuple{M,N};
    auto b_shape = tuple{M,N};
    auto t_shape = tuple{2_ct,4_ct};

    auto a = nm::random(a_shape,dtype,gen);
    auto b = nm::random(b_shape,dtype,gen);
    auto c = nm::Array::zeros(tuple{M,N},dtype);

    auto ctx = tk::vector::Context;

    auto min_time = std::chrono::nanoseconds(10'000'000);
    ankerl::nanobench::Bench()
        .minEpochTime(min_time)
        .run("add_padding.1024ct_8ct.fp32.2x4",[&](){
            add_padding_kernel(ctx,c,a,b,t_shape);
        });

    auto expected = nm::add(a,b);
    NMTOOLS_ASSERT_CLOSE( c, expected );
}

TEST_CASE("add_padding.1024_10.fp32.2x4" * doctest::test_suite("tilekit"))
{
    auto gen   = nm::random_engine();
    auto dtype = nm::float32;

    auto M = 1024;
    auto N = 10;
    auto a_shape = array{M,N};
    auto b_shape = array{M,N};
    auto t_shape = tuple{2_ct,4_ct};

    auto a = nm::random(a_shape,dtype,gen);
    auto b = nm::random(b_shape,dtype,gen);
    auto c = nm::Array::zeros(array{M,N},dtype);

    auto ctx = tk::vector::Context;

    auto min_time = std::chrono::nanoseconds(10'000'000);
    ankerl::nanobench::Bench()
        .minEpochTime(min_time)
        .run("add_padding.1024_10.fp32.2x4",[&](){
            add_padding_kernel(ctx,c,a,b,t_shape);
        });

    auto expected = nm::add(a,b);
    NMTOOLS_ASSERT_CLOSE( c, expected );
}

TEST_CASE("add_padding.1024_10ct.fp32.2x4" * doctest::test_suite("tilekit"))
{
    auto gen   = nm::random_engine();
    auto dtype = nm::float32;

    auto M = 1024;
    auto N = 10_ct;
    auto a_shape = tuple{M,N};
    auto b_shape = tuple{M,N};
    auto t_shape = tuple{2_ct,4_ct};

    auto a = nm::random(a_shape,dtype,gen);
    auto b = nm::random(b_shape,dtype,gen);
    auto c = nm::Array::zeros(tuple{M,N},dtype);

    auto ctx = tk::vector::Context;

    auto min_time = std::chrono::nanoseconds(10'000'000);
    ankerl::nanobench::Bench()
        .minEpochTime(min_time)
        .run("add_padding.1024_10ct.fp32.2x4",[&](){
            add_padding_kernel(ctx,c,a,b,t_shape);
        });

    auto expected = nm::add(a,b);
    NMTOOLS_ASSERT_CLOSE( c, expected );
}

TEST_CASE("add_padding.1024ct_10ct.fp32.2x4" * doctest::test_suite("tilekit"))
{
    auto gen   = nm::random_engine();
    auto dtype = nm::float32;

    auto M = 1024_ct;
    auto N = 10_ct;
    auto a_shape = tuple{M,N};
    auto b_shape = tuple{M,N};
    auto t_shape = tuple{2_ct,4_ct};

    auto a = nm::random(a_shape,dtype,gen);
    auto b = nm::random(b_shape,dtype,gen);
    auto c = nm::Array::zeros(tuple{M,N},dtype);

    auto ctx = tk::vector::Context;

    auto min_time = std::chrono::nanoseconds(10'000'000);
    ankerl::nanobench::Bench()
        .minEpochTime(min_time)
        .run("add_padding.1024ct_10ct.fp32.2x4",[&](){
            add_padding_kernel(ctx,c,a,b,t_shape);
        });

    auto expected = nm::add(a,b);
    NMTOOLS_ASSERT_CLOSE( c, expected );
}