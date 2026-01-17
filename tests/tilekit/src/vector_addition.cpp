#include "nmtools/tilekit/vector.hpp"
#include "nmtools/tilekit/tilekit.hpp"
#include "nmtools/array/ufuncs/add.hpp"
#include "nmtools/array/random.hpp"
#include "nmtools/testing/doctest.hpp"

#include "kernels/vector_addition.hpp"

#include <nanobench.h>

namespace nm = nmtools;

TEST_CASE("vector_addition_kernel(f32x4)" * doctest::test_suite("tilekit"))
{
    auto gen   = nm::random_engine();
    auto dtype = nm::float32;

    constexpr auto DIM = 4;
    auto a_shape = array{DIM};
    auto b_shape = array{DIM};

    auto a = nm::random(a_shape,dtype,gen);
    auto b = nm::random(b_shape,dtype,gen);
    auto c = nmtools_array<float,DIM>{};

    auto ctx = nm::None;

    auto min_time = std::chrono::nanoseconds(10'000'000);
    ankerl::nanobench::Bench()
        .minEpochTime(min_time)
        .run("vector_addition_kernel(f32x4)",[&](){
            vector_addition(ctx,c,a,b);
        });

    auto expected = nm::add(a,b);
    NMTOOLS_ASSERT_CLOSE( c, expected );
}

TEST_CASE("vector_addition(f32x4)" * doctest::test_suite("tilekit"))
{
    auto gen   = nm::random_engine();
    auto dtype = nm::float32;

    constexpr auto DIM = 4;
    auto a_shape = array{DIM};
    auto b_shape = array{DIM};

    auto a = nm::random(a_shape,dtype,gen);
    auto b = nm::random(b_shape,dtype,gen);
    auto c = nmtools_array<float,DIM>{};

    auto min_time = std::chrono::nanoseconds(10'000'000);
    ankerl::nanobench::Bench()
        .minEpochTime(min_time)
        .run("vector_addition(f32x4)",[&](){
            for (nm_size_t i=0; i<DIM; i++) {
                at(c,i) = at(a,i) + at(b,i);
            }
        });

    auto expected = nm::add(a,b);
    NMTOOLS_ASSERT_CLOSE( c, expected );
}

TEST_CASE("vector_addition_kernel(f32x64)" * doctest::test_suite("tilekit"))
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
        .run("vector_addition_kernel(f32x64)",[&](){
            vector_addition(ctx,c,a,b);
        });

    auto expected = nm::add(a,b);
    NMTOOLS_ASSERT_CLOSE( c, expected );
}

TEST_CASE("vector_addition(f32x64)" * doctest::test_suite("tilekit"))
{
    auto gen   = nm::random_engine();
    auto dtype = nm::float32;

    constexpr auto DIM = 64;
    auto a_shape = array{DIM};
    auto b_shape = array{DIM};

    auto a = nm::random(a_shape,dtype,gen);
    auto b = nm::random(b_shape,dtype,gen);
    auto c = nmtools_array<float,DIM>{};

    auto min_time = std::chrono::nanoseconds(10'000'000);
    ankerl::nanobench::Bench()
        .minEpochTime(min_time)
        .run("vector_addition(f32x64)",[&](){
            for (nm_size_t i=0; i<DIM; i++) {
                at(c,i) = at(a,i) + at(b,i);
            }
        });

    auto expected = nm::add(a,b);
    NMTOOLS_ASSERT_CLOSE( c, expected );
}

TEST_CASE("vector_addition_kernel(f32x128)" * doctest::test_suite("tilekit"))
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
        .run("vector_addition_kernel(f32x128)",[&](){
            vector_addition(ctx,c,a,b);
        });

    auto expected = nm::add(a,b);
    NMTOOLS_ASSERT_CLOSE( c, expected );
}

TEST_CASE("vector_addition(f32x128)" * doctest::test_suite("tilekit"))
{
    auto gen   = nm::random_engine();
    auto dtype = nm::float32;

    constexpr auto DIM = 128;
    auto a_shape = array{DIM};
    auto b_shape = array{DIM};

    auto a = nm::random(a_shape,dtype,gen);
    auto b = nm::random(b_shape,dtype,gen);
    auto c = nmtools_array<float,DIM>{};

    auto min_time = std::chrono::nanoseconds(10'000'000);
    ankerl::nanobench::Bench()
        .minEpochTime(min_time)
        .run("vector_addition(f32x128)",[&](){
            for (nm_size_t i=0; i<DIM; i++) {
                at(c,i) = at(a,i) + at(b,i);
            }
        });

    auto expected = nm::add(a,b);
    NMTOOLS_ASSERT_CLOSE( c, expected );
}

TEST_CASE("vector_addition_simd(f32x128)" * doctest::test_suite("tilekit"))
{
    auto gen   = nm::random_engine();
    auto dtype = nm::float32;

    constexpr auto DIM = 128;
    auto a_shape = array{DIM};
    auto b_shape = array{DIM};

    auto a = nm::random(a_shape,dtype,gen);
    auto b = nm::random(b_shape,dtype,gen);
    auto c = nmtools_array<float,DIM>{};
    auto ctx = tk::vector::Context;

    auto min_time = std::chrono::nanoseconds(10'000'000);
    ankerl::nanobench::Bench()
        .minEpochTime(min_time)
        .run("vector_addition_simd(f32x128)",[&](){
            vector_addition(ctx,c,a,b);
        });

    auto expected = nm::add(a,b);
    NMTOOLS_ASSERT_CLOSE( c, expected );
}