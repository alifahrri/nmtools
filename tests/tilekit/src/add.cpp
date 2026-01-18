#include "nmtools/tilekit/vector.hpp"
#include "nmtools/tilekit/tilekit.hpp"
#include "nmtools/array/ufuncs/add.hpp"
#include "nmtools/array/random.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/ndarray.hpp"

#include "kernels/add.hpp"

#include <nanobench.h>

namespace nm = nmtools;

TEST_CASE("add.case1" * doctest::test_suite("tilekit"))
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
        .run("add.case1",[&](){
            add_kernel(ctx,c,a,b);
        });

    auto expected = nm::add(a,b);
    NMTOOLS_ASSERT_CLOSE( c, expected );
}

TEST_CASE("add.case1b" * doctest::test_suite("tilekit"))
{
    auto gen   = nm::random_engine();
    auto dtype = nm::float32;

    auto M = 1024_ct;
    auto N = 8_ct;
    auto a_shape = tuple{M,N};
    auto b_shape = tuple{M,N};

    auto a = nm::random(a_shape,dtype,gen);
    auto b = nm::random(b_shape,dtype,gen);
    auto c = nm::Array::zeros(tuple{M,N},dtype);

    auto ctx = tk::vector::Context;

    auto min_time = std::chrono::nanoseconds(10'000'000);
    ankerl::nanobench::Bench()
        .minEpochTime(min_time)
        .run("add.case1b",[&](){
            add_kernel(ctx,c,a,b);
        });

    auto expected = nm::add(a,b);
    NMTOOLS_ASSERT_CLOSE( c, expected );
}

TEST_CASE("add.case1c" * doctest::test_suite("tilekit"))
{
    auto gen   = nm::random_engine();
    auto dtype = nm::float32;

    auto M = 1024;
    auto N = 8_ct;
    auto a_shape = tuple{M,N};
    auto b_shape = tuple{M,N};

    auto a = nm::random(a_shape,dtype,gen);
    auto b = nm::random(b_shape,dtype,gen);
    auto c = nm::Array::zeros(tuple{M,N},dtype);

    auto ctx = tk::vector::Context;

    auto min_time = std::chrono::nanoseconds(10'000'000);
    ankerl::nanobench::Bench()
        .minEpochTime(min_time)
        .run("add.case1c",[&](){
            add_kernel(ctx,c,a,b);
        });

    auto expected = nm::add(a,b);
    NMTOOLS_ASSERT_CLOSE( c, expected );
}

TEST_CASE("add.case2" * doctest::test_suite("tilekit"))
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
        .run("add.case2",[&](){
            add_kernel(ctx,c,a,b);
        });

    auto expected = nm::add(a,b);
    NMTOOLS_ASSERT_CLOSE( c, expected );
}

TEST_CASE("add.case2b" * doctest::test_suite("tilekit"))
{
    auto gen   = nm::random_engine();
    auto dtype = nm::float32;

    auto M = 8_ct;
    auto N = 1024_ct;
    auto a_shape = tuple{M,N};
    auto b_shape = tuple{M,N};

    auto a = nm::random(a_shape,dtype,gen);
    auto b = nm::random(b_shape,dtype,gen);
    auto c = nm::Array::zeros(tuple{M,N},dtype);

    auto ctx = tk::vector::Context;

    auto min_time = std::chrono::nanoseconds(10'000'000);
    ankerl::nanobench::Bench()
        .minEpochTime(min_time)
        .run("add.case2b",[&](){
            add_kernel(ctx,c,a,b);
        });

    auto expected = nm::add(a,b);
    NMTOOLS_ASSERT_CLOSE( c, expected );
}

TEST_CASE("add.case3" * doctest::test_suite("tilekit"))
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
        .run("add.case3",[&](){
            add_kernel(ctx,c,a,b);
        });

    auto expected = nm::add(a,b);
    NMTOOLS_ASSERT_CLOSE( c, expected );
}

TEST_CASE("add.case3b" * doctest::test_suite("tilekit"))
{
    auto gen   = nm::random_engine();
    auto dtype = nm::float32;

    auto M = 128_ct;
    auto N = 64_ct;
    auto a_shape = tuple{M,N};
    auto b_shape = tuple{M,N};

    auto a = nm::random(a_shape,dtype,gen);
    auto b = nm::random(b_shape,dtype,gen);
    auto c = nm::Array::zeros(tuple{M,N},dtype);

    auto ctx = tk::vector::Context;

    auto min_time = std::chrono::nanoseconds(10'000'000);
    ankerl::nanobench::Bench()
        .minEpochTime(min_time)
        .run("add.case3b",[&](){
            add_kernel(ctx,c,a,b);
        });

    auto expected = nm::add(a,b);
    NMTOOLS_ASSERT_CLOSE( c, expected );
}

TEST_CASE("add.case4" * doctest::test_suite("tilekit"))
{
    auto gen   = nm::random_engine();
    auto dtype = nm::float32;

    auto M = 16;
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
        .run("add.case4",[&](){
            add_kernel(ctx,c,a,b);
        });

    auto expected = nm::add(a,b);
    NMTOOLS_ASSERT_CLOSE( c, expected );
}

TEST_CASE("add.case4b" * doctest::test_suite("tilekit"))
{
    auto gen   = nm::random_engine();
    auto dtype = nm::float32;

    auto M = 16_ct;
    auto N = 8_ct;
    auto a_shape = tuple{M,N};
    auto b_shape = tuple{M,N};

    auto a = nm::random(a_shape,dtype,gen);
    auto b = nm::random(b_shape,dtype,gen);
    auto c = nm::Array::zeros(tuple{M,N},dtype);

    auto ctx = tk::vector::Context;

    auto min_time = std::chrono::nanoseconds(10'000'000);
    ankerl::nanobench::Bench()
        .minEpochTime(min_time)
        .run("add.case4b",[&](){
            add_kernel(ctx,c,a,b);
        });

    auto expected = nm::add(a,b);
    NMTOOLS_ASSERT_CLOSE( c, expected );
}

TEST_CASE("add.case5" * doctest::test_suite("tilekit"))
{
    auto gen   = nm::random_engine();
    auto dtype = nm::float32;

    auto N = 128;
    auto a_shape = array{N};
    auto b_shape = array{N};

    auto a = nm::random(a_shape,dtype,gen);
    auto b = nm::random(b_shape,dtype,gen);
    auto c = nm::Array::zeros(array{N},dtype);

    auto tile_shape = tuple{4_ct};
    auto ctx = tk::vector::Context;

    auto min_time = std::chrono::nanoseconds(10'000'000);
    ankerl::nanobench::Bench()
        .minEpochTime(min_time)
        .run("add.case5",[&](){
            add_kernel(ctx,c,a,b,tile_shape);
        });

    auto expected = nm::add(a,b);
    NMTOOLS_ASSERT_CLOSE( c, expected );
}

TEST_CASE("add.case5b" * doctest::test_suite("tilekit"))
{
    auto gen   = nm::random_engine();
    auto dtype = nm::float32;

    auto N = 128_ct;
    auto a_shape = tuple{N};
    auto b_shape = tuple{N};

    auto a = nm::random(a_shape,dtype,gen);
    auto b = nm::random(b_shape,dtype,gen);
    auto c = nm::Array::zeros(tuple{N},dtype);

    auto tile_shape = tuple{4_ct};
    auto ctx = tk::vector::Context;

    auto min_time = std::chrono::nanoseconds(10'000'000);
    ankerl::nanobench::Bench()
        .minEpochTime(min_time)
        .run("add.case5b",[&](){
            add_kernel(ctx,c,a,b,tile_shape);
        });

    auto expected = nm::add(a,b);
    NMTOOLS_ASSERT_CLOSE( c, expected );
}

TEST_CASE("add.case6" * doctest::test_suite("tilekit"))
{
    auto gen   = nm::random_engine();
    auto dtype = nm::float32;

    auto B = 4;
    auto M = 1024;
    auto N = 8;
    auto a_shape = array{B,M,N};
    auto b_shape = array{B,M,N};
    auto tile_shape = tuple{1_ct,2_ct,4_ct};

    auto a = nm::random(a_shape,dtype,gen);
    auto b = nm::random(b_shape,dtype,gen);
    auto c = nm::Array::zeros(array{B,M,N},dtype);

    auto ctx = tk::vector::Context;

    auto min_time = std::chrono::nanoseconds(10'000'000);
    ankerl::nanobench::Bench()
        .minEpochTime(min_time)
        .run("add.case6",[&](){
            add_kernel(ctx,c,a,b,tile_shape);
        });

    auto expected = nm::add(a,b);
    NMTOOLS_ASSERT_CLOSE( c, expected );
}

TEST_CASE("add.case6b" * doctest::test_suite("tilekit"))
{
    auto gen   = nm::random_engine();
    auto dtype = nm::float32;

    auto B = 4_ct;
    auto M = 1024_ct;
    auto N = 8_ct;
    auto a_shape = tuple{B,M,N};
    auto b_shape = tuple{B,M,N};
    auto tile_shape = tuple{1_ct,2_ct,4_ct};

    auto a = nm::random(a_shape,dtype,gen);
    auto b = nm::random(b_shape,dtype,gen);
    auto c = nm::Array::zeros(tuple{B,M,N},dtype);

    auto ctx = tk::vector::Context;

    auto min_time = std::chrono::nanoseconds(10'000'000);
    ankerl::nanobench::Bench()
        .minEpochTime(min_time)
        .run("add.case6b",[&](){
            add_kernel(ctx,c,a,b,tile_shape);
        });

    auto expected = nm::add(a,b);
    NMTOOLS_ASSERT_CLOSE( c, expected );
}

TEST_CASE("add.case6c" * doctest::test_suite("tilekit"))
{
    auto gen   = nm::random_engine();
    auto dtype = nm::float32;

    auto B = 4_ct;
    auto M = 1024_ct;
    auto N = 8_ct;
    auto a_shape = tuple{B,M,N};
    auto b_shape = tuple{B,M,N};
    auto tile_shape = tuple{1_ct,1_ct,8_ct};

    auto a = nm::random(a_shape,dtype,gen);
    auto b = nm::random(b_shape,dtype,gen);
    auto c = nm::Array::zeros(tuple{B,M,N},dtype);

    auto ctx = tk::vector::Context;

    auto min_time = std::chrono::nanoseconds(10'000'000);
    ankerl::nanobench::Bench()
        .minEpochTime(min_time)
        .run("add.case6c",[&](){
            add_kernel(ctx,c,a,b,tile_shape);
        });

    auto expected = nm::add(a,b);
    NMTOOLS_ASSERT_CLOSE( c, expected );
}

TEST_CASE("add.case6d" * doctest::test_suite("tilekit"))
{
    auto gen   = nm::random_engine();
    auto dtype = nm::float32;

    auto B = 4_ct;
    auto M = 1024_ct;
    auto N = 8_ct;
    auto a_shape = tuple{B,M,N};
    auto b_shape = tuple{B,M,N};
    auto tile_shape = tuple{1_ct,2_ct,8_ct};

    auto a = nm::random(a_shape,dtype,gen);
    auto b = nm::random(b_shape,dtype,gen);
    auto c = nm::Array::zeros(tuple{B,M,N},dtype);

    auto ctx = tk::vector::Context;

    auto min_time = std::chrono::nanoseconds(10'000'000);
    ankerl::nanobench::Bench()
        .minEpochTime(min_time)
        .run("add.case6d",[&](){
            add_kernel(ctx,c,a,b,tile_shape);
        });

    auto expected = nm::add(a,b);
    NMTOOLS_ASSERT_CLOSE( c, expected );
}