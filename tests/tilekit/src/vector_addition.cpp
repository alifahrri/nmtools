#include "kernels/vector_addition.hpp"
#include "nmtools/tilekit/tilekit.hpp"
#include "nmtools/array/ufuncs/add.hpp"
#include "nmtools/array/random.hpp"
#include "nmtools/testing/doctest.hpp"

#include <nanobench.h>

namespace nm = nmtools;

TEST_CASE("vector_addition" * doctest::test_suite("tilekit"))
{
    auto a = nmtools_array{0,1,2,3};
    auto b = nmtools_array{4,5,6,7};
    auto c = nmtools_array<int,4>{};
    auto ctx = nm::None;

    vector_addition(ctx,c,a,b);

    auto expected = nm::add(a,b);
    NMTOOLS_ASSERT_EQUAL( c, expected );
}

TEST_CASE("vector_addition_f32x64" * doctest::test_suite("tilekit"))
{
    auto gen   = nm::random_engine();
    auto dtype = nm::float32;

    constexpr auto DIM = 64;
    auto a_shape = array{DIM};
    auto b_shape = array{DIM};

    auto a = nm::random(a_shape,dtype,gen);
    auto b = nm::random(b_shape,dtype,gen);
    auto c = nmtools_array<float,DIM>{};
    auto ctx = nm::None;

    
    auto min_time = std::chrono::nanoseconds(10'000'000);
    ankerl::nanobench::Bench()
        .minEpochTime(min_time)
        .run("vector_addition_f32x64",[&](){
            vector_addition(ctx,c,a,b);
        });

    auto expected = nm::add(a,b);
    NMTOOLS_ASSERT_CLOSE( c, expected );
}

TEST_CASE("vector_addition_f32x128" * doctest::test_suite("tilekit"))
{
    auto gen   = nm::random_engine();
    auto dtype = nm::float32;

    constexpr auto DIM = 128;
    auto a_shape = array{DIM};
    auto b_shape = array{DIM};

    auto a = nm::random(a_shape,dtype,gen);
    auto b = nm::random(b_shape,dtype,gen);
    auto c = nmtools_array<float,DIM>{};
    auto ctx = nm::None;

    auto min_time = std::chrono::nanoseconds(10'000'000);
    ankerl::nanobench::Bench()
        .minEpochTime(min_time)
        .run("vector_addition_f32x128",[&](){
            vector_addition(ctx,c,a,b);
        });

    auto expected = nm::add(a,b);
    NMTOOLS_ASSERT_CLOSE( c, expected );
}