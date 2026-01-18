#include "nmtools/tilekit/vector.hpp"
#include "nmtools/tilekit/tilekit.hpp"
#include "nmtools/array/ufuncs/multiply.hpp"
#include "nmtools/array/random.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/ndarray.hpp"

#include "kernels/multiply.hpp"

#include <nanobench.h>

namespace nm = nmtools;

TEST_CASE("multiply.case1" * doctest::test_suite("tilekit"))
{
    auto gen   = nm::random_engine();
    auto dtype = nm::float32;

    auto M = 1024;
    auto N = 8;
    auto a_shape = array{M,N};
    auto b_shape = array{M,N};

    auto a = nm::random(a_shape,dtype,gen);
    auto b = nm::random(b_shape,dtype,gen);
    auto c = nm::Array::zeros(array{M,N},dtype);

    auto ctx = tk::vector::Context;

    auto min_time = std::chrono::nanoseconds(10'000'000);
    ankerl::nanobench::Bench()
        .minEpochTime(min_time)
        .run("multiply.case1",[&](){
            multiply_kernel(ctx,c,a,b);
        });

    auto expected = nm::multiply(a,b);
    NMTOOLS_ASSERT_CLOSE( c, expected );
}

TEST_CASE("multiply.case2" * doctest::test_suite("tilekit"))
{
    auto gen   = nm::random_engine();
    auto dtype = nm::float32;

    auto M = 8;
    auto N = 1024;
    auto a_shape = array{M,N};
    auto b_shape = array{M,N};

    auto a = nm::random(a_shape,dtype,gen);
    auto b = nm::random(b_shape,dtype,gen);
    auto c = nm::Array::zeros(array{M,N},dtype);

    auto ctx = tk::vector::Context;

    auto min_time = std::chrono::nanoseconds(10'000'000);
    ankerl::nanobench::Bench()
        .minEpochTime(min_time)
        .run("multiply.case2",[&](){
            multiply_kernel(ctx,c,a,b);
        });

    auto expected = nm::multiply(a,b);
    NMTOOLS_ASSERT_CLOSE( c, expected );
}

TEST_CASE("multiply.case3" * doctest::test_suite("tilekit"))
{
    auto gen   = nm::random_engine();
    auto dtype = nm::float32;

    auto M = 128;
    auto N = 64;
    auto a_shape = array{M,N};
    auto b_shape = array{M,N};

    auto a = nm::random(a_shape,dtype,gen);
    auto b = nm::random(b_shape,dtype,gen);
    auto c = nm::Array::zeros(array{M,N},dtype);

    auto ctx = tk::vector::Context;

    auto min_time = std::chrono::nanoseconds(10'000'000);
    ankerl::nanobench::Bench()
        .minEpochTime(min_time)
        .run("multiply.case3",[&](){
            multiply_kernel(ctx,c,a,b);
        });

    auto expected = nm::multiply(a,b);
    NMTOOLS_ASSERT_CLOSE( c, expected );
}