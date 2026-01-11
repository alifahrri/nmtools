#include "kernels/copy.hpp"
#include "kernels/simd_copy.hpp"
#include "nmtools/nmtools.hpp"
#include "nmtools/tilekit/tilekit.hpp"
#include "nmtools/testing/doctest.hpp"

#include <nanobench.h>

namespace nm = nmtools;
using namespace nmtools::literals;

TEST_CASE("copy_kernel(4)" * doctest::test_suite("tilekit"))
{
    auto inp = nmtools_array{0,1,2,3};
    auto out = nmtools_array<nm_index_t,4>{};

    auto min_time = std::chrono::nanoseconds(10'000'000);

    {
        auto ctx = nm::None;
        ankerl::nanobench::Bench()
            .minEpochTime(min_time)
            .run("copy_kernel(4)",[&](){
                copy_kernel(ctx,out,inp);
            });

        NMTOOLS_ASSERT_EQUAL( out, inp );
    }
}

TEST_CASE("copy(4)" * doctest::test_suite("tilekit"))
{
    auto inp = nmtools_array{0,1,2,3};
    auto out = nmtools_array<nm_index_t,4>{};

    auto min_time = std::chrono::nanoseconds(10'000'000);
    {
        ankerl::nanobench::Bench()
            .minEpochTime(min_time)
            .run("copy(4)",[&](){
                for (nm_size_t i=0; i<4; i++) {
                    at(out,i) = at(inp,i);
                }
            });

        NMTOOLS_ASSERT_CLOSE( out, inp );
    }
}

TEST_CASE("copy_kernel(128)" * doctest::test_suite("tilekit"))
{
    auto gen   = nm::random_engine();
    auto dtype = nm::float32;

    auto inp = nm::random(array{128},dtype,gen);
    auto out = nmtools_array<float,128>{};

    auto min_time = std::chrono::nanoseconds(10'000'000);

    {
        auto ctx = nm::None;
        ankerl::nanobench::Bench()
            .minEpochTime(min_time)
            .run("copy_kernel(128)",[&](){
                copy_kernel(ctx,out,inp);
            });

        NMTOOLS_ASSERT_CLOSE( out, inp );
    }
}

TEST_CASE("simd_copy_kernel(128)" * doctest::test_suite("tilekit"))
{
    auto gen   = nm::random_engine();
    auto dtype = nm::float32;

    auto inp = nm::random(array{128},dtype,gen);
    auto out = nmtools_array<float,128>{};

    auto min_time = std::chrono::nanoseconds(10'000'000);

    {
        ankerl::nanobench::Bench()
            .minEpochTime(min_time)
            .run("simd_copy_kernel(128)",[&](){
                simd_copy_kernel(out,inp);
            });

        NMTOOLS_ASSERT_CLOSE( out, inp );
    }
}

TEST_CASE("copy(128)" * doctest::test_suite("tilekit"))
{
    auto gen   = nm::random_engine();
    auto dtype = nm::float32;

    auto inp = nm::random(array{128},dtype,gen);
    auto out = nmtools_array<float,128>{};

    auto min_time = std::chrono::nanoseconds(10'000'000);
    {
        ankerl::nanobench::Bench()
            .minEpochTime(min_time)
            .run("copy(128)",[&](){
                for (nm_size_t i=0; i<128; i++) {
                    at(out,i) = at(inp,i);
                }
            });

        NMTOOLS_ASSERT_CLOSE( out, inp );
    }
}