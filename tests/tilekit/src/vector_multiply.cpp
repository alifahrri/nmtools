#include "nmtools/tilekit/tilekit.hpp"
#include "nmtools/tilekit/vector.hpp"
#include "nmtools/array/ufuncs/multiply.hpp"
#include "nmtools/array/random.hpp"
#include "nmtools/array/zeros.hpp"
#include "nmtools/testing/doctest.hpp"

#include "kernels/vector_multiply.hpp"

#include <nanobench.h>

namespace nm = nmtools;

using nmtools_tuple;
using nmtools_array;
using namespace nmtools::literals;

/******************************************************************************************************************/

TEST_CASE("vector_multiply_kernel(f32x4)" * doctest::test_suite("tilekit"))
{
    auto gen = nm::random_engine();
    auto dtype = nm::float32;

    constexpr auto DIM = 4;
    auto a_shape = array{DIM};
    auto b_shape = array{DIM};

    auto a = nm::random(a_shape,dtype,gen);
    auto b = nm::random(b_shape,dtype,gen);
    auto c = array<float,DIM>{};
    auto ctx = nm::None;

    auto min_time = std::chrono::nanoseconds(10'000'000);
    ankerl::nanobench::Bench()
        .minEpochTime(min_time)
        .run("vector_multiply_kernel(f32x4)",[&](){
            vector_multiply(ctx,c,a,b);
        });
    
    auto expected = nm::multiply(a,b);
    NMTOOLS_ASSERT_CLOSE( c, expected );
}

TEST_CASE("vector_multiply(f32x4)" * doctest::test_suite("tilekit"))
{
    auto gen = nm::random_engine();
    auto dtype = nm::float32;

    constexpr auto DIM = 4;
    auto a_shape = array{DIM};
    auto b_shape = array{DIM};

    auto a = nm::random(a_shape,dtype,gen);
    auto b = nm::random(b_shape,dtype,gen);
    auto c = array<float,DIM>{};

    auto min_time = std::chrono::nanoseconds(10'000'000);
    ankerl::nanobench::Bench()
        .minEpochTime(min_time)
        .run("vector_multiply(f32x4)",[&](){
            for (nm_size_t i=0; i<DIM; i++) {
                at(c,i) = at(a,i) * at(b,i);
            }
        });

    auto expected = nm::multiply(a,b);
    NMTOOLS_ASSERT_CLOSE( c, expected );
}

/******************************************************************************************************************/

TEST_CASE("vector_multiply_kernel(i32x4)" * doctest::test_suite("tilekit"))
{
    auto gen = nm::random_engine();
    auto dtype = nm::int32;

    constexpr auto DIM = 4;
    auto a_shape = array{DIM};
    auto b_shape = array{DIM};

    auto a = nm::random(a_shape,dtype,gen);
    auto b = nm::random(b_shape,dtype,gen);
    auto c = nm::zeros(a_shape,dtype);
    auto ctx = nm::None;

    auto min_time = std::chrono::nanoseconds(10'000'000);
    ankerl::nanobench::Bench()
        .minEpochTime(min_time)
        .run("vector_multiply_kernel(i32x4)",[&](){
            vector_multiply(ctx,c,a,b);
        });
    
    auto expected = nm::multiply(a,b);
    NMTOOLS_ASSERT_CLOSE( c, expected );
}

TEST_CASE("vector_multiply(i32x4)" * doctest::test_suite("tilekit"))
{
    auto gen = nm::random_engine();
    auto dtype = nm::int32;

    constexpr auto DIM = 4;
    auto a_shape = array{DIM};
    auto b_shape = array{DIM};

    auto a = nm::random(a_shape,dtype,gen);
    auto b = nm::random(b_shape,dtype,gen);
    auto c = nm::zeros(a_shape,dtype);

    auto min_time = std::chrono::nanoseconds(10'000'000);
    ankerl::nanobench::Bench()
        .minEpochTime(min_time)
        .run("vector_multiply(i32x4)",[&](){
            for (nm_size_t i=0; i<DIM; i++) {
                at(c,i) = at(a,i) * at(b,i);
            }
        });

    auto expected = nm::multiply(a,b);
    NMTOOLS_ASSERT_CLOSE( c, expected );
}

/******************************************************************************************************************/

TEST_CASE("vector_multiply_kernel(f32x128)" * doctest::test_suite("tilekit"))
{
    auto gen = nm::random_engine();
    auto dtype = nm::float32;

    constexpr auto DIM = 128;
    auto a_shape = array{DIM};
    auto b_shape = array{DIM};

    auto a = nm::random(a_shape,dtype,gen);
    auto b = nm::random(b_shape,dtype,gen);
    auto c = array<float,DIM>{};
    auto ctx = nm::None;

    auto min_time = std::chrono::nanoseconds(10'000'000);
    ankerl::nanobench::Bench()
        .minEpochTime(min_time)
        .run("vector_multiply_kernel(f32x128)",[&](){
            vector_multiply(ctx,c,a,b);
        });
    
    auto expected = nm::multiply(a,b);
    NMTOOLS_ASSERT_CLOSE( c, expected );
}

TEST_CASE("vector_multiply(f32x128)" * doctest::test_suite("tilekit"))
{
    auto gen = nm::random_engine();
    auto dtype = nm::float32;

    constexpr auto DIM = 128;
    auto a_shape = array{DIM};
    auto b_shape = array{DIM};

    auto a = nm::random(a_shape,dtype,gen);
    auto b = nm::random(b_shape,dtype,gen);
    auto c = array<float,DIM>{};

    auto min_time = std::chrono::nanoseconds(10'000'000);
    ankerl::nanobench::Bench()
        .minEpochTime(min_time)
        .run("vector_multiply(f32x128)",[&](){
            for (nm_size_t i=0; i<DIM; i++) {
                at(c,i) = at(a,i) * at(b,i);
            }
        });

    auto expected = nm::multiply(a,b);
    NMTOOLS_ASSERT_CLOSE( c, expected );
}

TEST_CASE("vector_multiply_simd(f32x128)" * doctest::test_suite("tilekit"))
{
    auto gen = nm::random_engine();
    auto dtype = nm::float32;

    constexpr auto DIM = 128;
    auto a_shape = array{DIM};
    auto b_shape = array{DIM};

    auto a = nm::random(a_shape,dtype,gen);
    auto b = nm::random(b_shape,dtype,gen);
    auto c = array<float,DIM>{};
    auto ctx = tk::vector::Context;

    auto min_time = std::chrono::nanoseconds(10'000'000);
    ankerl::nanobench::Bench()
        .minEpochTime(min_time)
        .run("vector_multiply_simd(f32x128)",[&](){
            vector_multiply(ctx,c,a,b);
        });
    
    auto expected = nm::multiply(a,b);
    NMTOOLS_ASSERT_CLOSE( c, expected );
}

/******************************************************************************************************************/