#include "nmtools/tilekit/vector.hpp"
#include "nmtools/tilekit/thread_pool.hpp"
#include "nmtools/tilekit/tilekit.hpp"
#include "nmtools/array/ufuncs/add.hpp"
#include "nmtools/array/random.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/ndarray.hpp"

#include "kernels/add.hpp"

#include <nanobench.h>

namespace nm = nmtools;
using namespace nmtools::literals;

using v128_mt = tk::thread_pool<tk::vector::context_t<>>;

TEST_CASE("v128_mt.add.case7" * doctest::test_suite("tilekit"))
{
    auto gen   = nm::random_engine();
    auto dtype = nm::float32;

    auto M = 1024;
    auto N = 1024;
    auto a_shape = array{M,N};
    auto b_shape = array{M,N};

    auto a = nm::random(a_shape,dtype,gen);
    auto b = nm::random(b_shape,dtype,gen);
    auto c = nm::Array::zeros(array{M,N},dtype);

    auto tile_shape = tuple{2_ct,4_ct};
    auto num_threads = 2;
    auto ctx = v128_mt(num_threads);
    auto worker_size = num_threads;

    auto min_time = std::chrono::nanoseconds(50'000'000);
    ankerl::nanobench::Bench()
        .minEpochTime(min_time)
        .run("v128_mt.add.case7",[&](){
            ctx.eval(worker_size,add_kernel,c,a,b,tile_shape);
        });

    auto expected = nm::add(a,b);
    NMTOOLS_ASSERT_CLOSE( c, expected );
}

TEST_CASE("v128_mt.add.case7b" * doctest::test_suite("tilekit"))
{
    auto gen   = nm::random_engine();
    auto dtype = nm::float32;

    auto M = 1024;
    auto N = 1024;
    auto a_shape = array{M,N};
    auto b_shape = array{M,N};

    auto a = nm::random(a_shape,dtype,gen);
    auto b = nm::random(b_shape,dtype,gen);
    auto c = nm::Array::zeros(array{M,N},dtype);

    auto tile_shape = tuple{2_ct,4_ct};
    auto num_threads = 4;
    auto ctx = v128_mt(num_threads);
    auto worker_size = num_threads;

    auto min_time = std::chrono::nanoseconds(50'000'000);
    ankerl::nanobench::Bench()
        .minEpochTime(min_time)
        .run("v128_mt.add.case7b",[&](){
            ctx.eval(worker_size,add_kernel,c,a,b,tile_shape);
        });

    auto expected = nm::add(a,b);
    NMTOOLS_ASSERT_CLOSE( c, expected );
}

TEST_CASE("v128_mt.add.case7c" * doctest::test_suite("tilekit"))
{
    auto gen   = nm::random_engine();
    auto dtype = nm::float32;

    auto M = 1024;
    auto N = 1024;
    auto a_shape = array{M,N};
    auto b_shape = array{M,N};

    auto a = nm::random(a_shape,dtype,gen);
    auto b = nm::random(b_shape,dtype,gen);
    auto c = nm::Array::zeros(array{M,N},dtype);

    auto tile_shape = tuple{2_ct,4_ct};
    auto num_threads = 8;
    auto ctx = v128_mt(num_threads);
    auto worker_size = num_threads;

    auto min_time = std::chrono::nanoseconds(50'000'000);
    ankerl::nanobench::Bench()
        .minEpochTime(min_time)
        .run("v128_mt.add.case7c",[&](){
            ctx.eval(worker_size,add_kernel,c,a,b,tile_shape);
        });

    auto expected = nm::add(a,b);
    NMTOOLS_ASSERT_CLOSE( c, expected );
}

TEST_CASE("v128_mt.add.case7d" * doctest::test_suite("tilekit"))
{
    auto gen   = nm::random_engine();
    auto dtype = nm::float32;

    auto M = 1024;
    auto N = 1024;
    auto a_shape = array{M,N};
    auto b_shape = array{M,N};

    auto a = nm::random(a_shape,dtype,gen);
    auto b = nm::random(b_shape,dtype,gen);
    auto c = nm::Array::zeros(array{M,N},dtype);

    auto tile_shape = tuple{2_ct,4_ct};
    auto num_threads = 16;
    auto ctx = v128_mt(num_threads);
    auto worker_size = num_threads;

    auto min_time = std::chrono::nanoseconds(50'000'000);
    ankerl::nanobench::Bench()
        .minEpochTime(min_time)
        .run("v128_mt.add.case7d",[&](){
            ctx.eval(worker_size,add_kernel,c,a,b,tile_shape);
        });

    auto expected = nm::add(a,b);
    NMTOOLS_ASSERT_CLOSE( c, expected );
}

/*********************************************************************************** */
// no thread affinity

TEST_CASE("v128_mt.add.case7e" * doctest::test_suite("tilekit"))
{
    auto gen   = nm::random_engine();
    auto dtype = nm::float32;

    auto M = 1024;
    auto N = 1024;
    auto a_shape = array{M,N};
    auto b_shape = array{M,N};

    auto a = nm::random(a_shape,dtype,gen);
    auto b = nm::random(b_shape,dtype,gen);
    auto c = nm::Array::zeros(array{M,N},dtype);

    auto tile_shape = tuple{2_ct,4_ct};
    auto num_threads = 2;
    auto ctx = v128_mt(num_threads,false);
    auto worker_size = num_threads;

    auto min_time = std::chrono::nanoseconds(50'000'000);
    ankerl::nanobench::Bench()
        .minEpochTime(min_time)
        .run("v128_mt.add.case7e",[&](){
            ctx.eval(worker_size,add_kernel,c,a,b,tile_shape);
        });

    auto expected = nm::add(a,b);
    NMTOOLS_ASSERT_CLOSE( c, expected );
}

TEST_CASE("v128_mt.add.case7f" * doctest::test_suite("tilekit"))
{
    auto gen   = nm::random_engine();
    auto dtype = nm::float32;

    auto M = 1024;
    auto N = 1024;
    auto a_shape = array{M,N};
    auto b_shape = array{M,N};

    auto a = nm::random(a_shape,dtype,gen);
    auto b = nm::random(b_shape,dtype,gen);
    auto c = nm::Array::zeros(array{M,N},dtype);

    auto tile_shape = tuple{2_ct,4_ct};
    auto num_threads = 4;
    auto ctx = v128_mt(num_threads,false);
    auto worker_size = num_threads;

    auto min_time = std::chrono::nanoseconds(50'000'000);
    ankerl::nanobench::Bench()
        .minEpochTime(min_time)
        .run("v128_mt.add.case7f",[&](){
            ctx.eval(worker_size,add_kernel,c,a,b,tile_shape);
        });

    auto expected = nm::add(a,b);
    NMTOOLS_ASSERT_CLOSE( c, expected );
}

TEST_CASE("v128_mt.add.case7g" * doctest::test_suite("tilekit"))
{
    auto gen   = nm::random_engine();
    auto dtype = nm::float32;

    auto M = 1024;
    auto N = 1024;
    auto a_shape = array{M,N};
    auto b_shape = array{M,N};

    auto a = nm::random(a_shape,dtype,gen);
    auto b = nm::random(b_shape,dtype,gen);
    auto c = nm::Array::zeros(array{M,N},dtype);

    auto tile_shape = tuple{2_ct,4_ct};
    auto num_threads = 8;
    auto ctx = v128_mt(num_threads,false);
    auto worker_size = num_threads;

    auto min_time = std::chrono::nanoseconds(50'000'000);
    ankerl::nanobench::Bench()
        .minEpochTime(min_time)
        .run("v128_mt.add.case7g",[&](){
            ctx.eval(worker_size,add_kernel,c,a,b,tile_shape);
        });

    auto expected = nm::add(a,b);
    NMTOOLS_ASSERT_CLOSE( c, expected );
}

TEST_CASE("v128_mt.add.case7h" * doctest::test_suite("tilekit"))
{
    auto gen   = nm::random_engine();
    auto dtype = nm::float32;

    auto M = 1024;
    auto N = 1024;
    auto a_shape = array{M,N};
    auto b_shape = array{M,N};

    auto a = nm::random(a_shape,dtype,gen);
    auto b = nm::random(b_shape,dtype,gen);
    auto c = nm::Array::zeros(array{M,N},dtype);

    auto tile_shape = tuple{2_ct,4_ct};
    auto num_threads = 16;
    auto ctx = v128_mt(num_threads,false);
    auto worker_size = num_threads;

    auto min_time = std::chrono::nanoseconds(50'000'000);
    ankerl::nanobench::Bench()
        .minEpochTime(min_time)
        .run("v128_mt.add.case7h",[&](){
            ctx.eval(worker_size,add_kernel,c,a,b,tile_shape);
        });

    auto expected = nm::add(a,b);
    NMTOOLS_ASSERT_CLOSE( c, expected );
}

/*********************************************************************************** */
// mixed shape
TEST_CASE("v128_mt.add.case7i" * doctest::test_suite("tilekit") * doctest::skip())
{
    auto gen   = nm::random_engine();
    auto dtype = nm::float32;

    auto M = 1024;
    auto N = 1024_ct;
    auto a_shape = tuple{M,N};
    auto b_shape = tuple{M,N};

    auto a = nm::random(a_shape,dtype,gen);
    auto b = nm::random(b_shape,dtype,gen);
    auto c = nm::Array::zeros(tuple{M,N},dtype);

    auto tile_shape = tuple{2_ct,4_ct};
    auto num_threads = 2;
    auto ctx = v128_mt(num_threads);
    auto worker_size = num_threads;

    auto min_time = std::chrono::nanoseconds(50'000'000);
    ankerl::nanobench::Bench()
        .minEpochTime(min_time)
        .run("v128_mt.add.case7i",[&](){
            ctx.eval(worker_size,add_kernel,c,a,b,tile_shape);
        });

    auto expected = nm::add(a,b);
    NMTOOLS_ASSERT_CLOSE( c, expected );
}

TEST_CASE("v128_mt.add.case7j" * doctest::test_suite("tilekit"))
{
    auto gen   = nm::random_engine();
    auto dtype = nm::float32;

    auto M = 1024;
    auto N = 1024_ct;
    auto a_shape = tuple{M,N};
    auto b_shape = tuple{M,N};

    auto a = nm::random(a_shape,dtype,gen);
    auto b = nm::random(b_shape,dtype,gen);
    auto c = nm::Array::zeros(tuple{M,N},dtype);

    auto tile_shape = tuple{2_ct,4_ct};
    auto num_threads = 4;
    auto ctx = v128_mt(num_threads);
    auto worker_size = num_threads;

    auto min_time = std::chrono::nanoseconds(50'000'000);
    ankerl::nanobench::Bench()
        .minEpochTime(min_time)
        .run("v128_mt.add.case7j",[&](){
            ctx.eval(worker_size,add_kernel,c,a,b,tile_shape);
        });

    auto expected = nm::add(a,b);
    NMTOOLS_ASSERT_CLOSE( c, expected );
}

TEST_CASE("v128_mt.add.case7k" * doctest::test_suite("tilekit"))
{
    auto gen   = nm::random_engine();
    auto dtype = nm::float32;

    auto M = 1024;
    auto N = 1024_ct;
    auto a_shape = tuple{M,N};
    auto b_shape = tuple{M,N};

    auto a = nm::random(a_shape,dtype,gen);
    auto b = nm::random(b_shape,dtype,gen);
    auto c = nm::Array::zeros(tuple{M,N},dtype);

    auto tile_shape = tuple{2_ct,4_ct};
    auto num_threads = 8;
    auto ctx = v128_mt(num_threads);
    auto worker_size = num_threads;

    auto min_time = std::chrono::nanoseconds(50'000'000);
    ankerl::nanobench::Bench()
        .minEpochTime(min_time)
        .run("v128_mt.add.case7k",[&](){
            ctx.eval(worker_size,add_kernel,c,a,b,tile_shape);
        });

    auto expected = nm::add(a,b);
    NMTOOLS_ASSERT_CLOSE( c, expected );
}

TEST_CASE("v128_mt.add.case7l" * doctest::test_suite("tilekit"))
{
    auto gen   = nm::random_engine();
    auto dtype = nm::float32;

    auto M = 1024;
    auto N = 1024_ct;
    auto a_shape = tuple{M,N};
    auto b_shape = tuple{M,N};

    auto a = nm::random(a_shape,dtype,gen);
    auto b = nm::random(b_shape,dtype,gen);
    auto c = nm::Array::zeros(tuple{M,N},dtype);

    auto tile_shape = tuple{2_ct,4_ct};
    auto num_threads = 16;
    auto ctx = v128_mt(num_threads);
    auto worker_size = num_threads;

    auto min_time = std::chrono::nanoseconds(50'000'000);
    ankerl::nanobench::Bench()
        .minEpochTime(min_time)
        .run("v128_mt.add.case7l",[&](){
            ctx.eval(worker_size,add_kernel,c,a,b,tile_shape);
        });

    auto expected = nm::add(a,b);
    NMTOOLS_ASSERT_CLOSE( c, expected );
}

/*********************************************************************************** */
// constant shape
#if 1
TEST_CASE("v128_mt.add.case7m" * doctest::test_suite("tilekit"))
{
    auto gen   = nm::random_engine();
    auto dtype = nm::float32;

    auto M = 1024_ct;
    auto N = 1024_ct;
    auto a_shape = tuple{M,N};
    auto b_shape = tuple{M,N};

    auto a = nm::random(a_shape,dtype,gen);
    auto b = nm::random(b_shape,dtype,gen);
    auto c = nm::Array::zeros(tuple{M,N},dtype);

    auto tile_shape = tuple{2_ct,4_ct};
    auto num_threads = 2;
    auto ctx = v128_mt(num_threads);
    auto worker_size = num_threads;

    auto min_time = std::chrono::nanoseconds(50'000'000);
    ankerl::nanobench::Bench()
        .minEpochTime(min_time)
        .run("v128_mt.add.case7m",[&](){
            ctx.eval(worker_size,add_kernel,c,a,b,tile_shape);
        });

    auto expected = nm::add(a,b);
    NMTOOLS_ASSERT_CLOSE( c, expected );
}

TEST_CASE("v128_mt.add.case7n" * doctest::test_suite("tilekit"))
{
    auto gen   = nm::random_engine();
    auto dtype = nm::float32;

    auto M = 1024_ct;
    auto N = 1024_ct;
    auto a_shape = tuple{M,N};
    auto b_shape = tuple{M,N};

    auto a = nm::random(a_shape,dtype,gen);
    auto b = nm::random(b_shape,dtype,gen);
    auto c = nm::Array::zeros(tuple{M,N},dtype);

    auto tile_shape = tuple{2_ct,4_ct};
    auto num_threads = 4;
    auto ctx = v128_mt(num_threads);
    auto worker_size = num_threads;

    auto min_time = std::chrono::nanoseconds(50'000'000);
    ankerl::nanobench::Bench()
        .minEpochTime(min_time)
        .run("v128_mt.add.case7n",[&](){
            ctx.eval(worker_size,add_kernel,c,a,b,tile_shape);
        });

    auto expected = nm::add(a,b);
    NMTOOLS_ASSERT_CLOSE( c, expected );
}
#endif

TEST_CASE("v128_mt.add.case9" * doctest::test_suite("tilekit"))
{
    auto gen   = nm::random_engine();
    auto dtype = nm::float32;

    auto M = 1024 * 4;
    auto N = 1024;
    auto a_shape = array{M,N};
    auto b_shape = array{M,N};

    auto a = nm::random(a_shape,dtype,gen);
    auto b = nm::random(b_shape,dtype,gen);
    auto c = nm::Array::zeros(array{M,N},dtype);

    auto tile_shape = tuple{2_ct,4_ct};
    auto num_threads = 2;
    auto ctx = v128_mt(num_threads);
    auto worker_size = num_threads;

    auto min_time = std::chrono::nanoseconds(50'000'000);
    ankerl::nanobench::Bench()
        .minEpochTime(min_time)
        .run("v128_mt.add.case9",[&](){
            ctx.eval(worker_size,add_kernel,c,a,b,tile_shape);
        });

    auto expected = nm::add(a,b);
    NMTOOLS_ASSERT_CLOSE( c, expected );
}

TEST_CASE("v128_mt.add.case9b" * doctest::test_suite("tilekit"))
{
    auto gen   = nm::random_engine();
    auto dtype = nm::float32;

    auto M = 1024 * 4;
    auto N = 1024;
    auto a_shape = array{M,N};
    auto b_shape = array{M,N};

    auto a = nm::random(a_shape,dtype,gen);
    auto b = nm::random(b_shape,dtype,gen);
    auto c = nm::Array::zeros(array{M,N},dtype);

    auto tile_shape = tuple{2_ct,4_ct};
    auto num_threads = 4;
    auto ctx = v128_mt(num_threads);
    auto worker_size = num_threads;

    auto min_time = std::chrono::nanoseconds(50'000'000);
    ankerl::nanobench::Bench()
        .minEpochTime(min_time)
        .run("v128_mt.add.case9b",[&](){
            ctx.eval(worker_size,add_kernel,c,a,b,tile_shape);
        });

    auto expected = nm::add(a,b);
    NMTOOLS_ASSERT_CLOSE( c, expected );
}

TEST_CASE("v128_mt.add.case9c" * doctest::test_suite("tilekit"))
{
    auto gen   = nm::random_engine();
    auto dtype = nm::float32;

    auto M = 1024 * 4;
    auto N = 1024;
    auto a_shape = array{M,N};
    auto b_shape = array{M,N};

    auto a = nm::random(a_shape,dtype,gen);
    auto b = nm::random(b_shape,dtype,gen);
    auto c = nm::Array::zeros(array{M,N},dtype);

    auto tile_shape = tuple{2_ct,16_ct};
    auto num_threads = 2;
    auto ctx = v128_mt(num_threads);
    auto worker_size = num_threads;

    auto min_time = std::chrono::nanoseconds(50'000'000);
    ankerl::nanobench::Bench()
        .minEpochTime(min_time)
        .run("v128_mt.add.case9c",[&](){
            ctx.eval(worker_size,add_kernel,c,a,b,tile_shape);
        });

    auto expected = nm::add(a,b);
    NMTOOLS_ASSERT_CLOSE( c, expected );
}

TEST_CASE("v128_mt.add.case9d" * doctest::test_suite("tilekit"))
{
    auto gen   = nm::random_engine();
    auto dtype = nm::float32;

    auto M = 1024 * 4;
    auto N = 1024;
    auto a_shape = array{M,N};
    auto b_shape = array{M,N};

    auto a = nm::random(a_shape,dtype,gen);
    auto b = nm::random(b_shape,dtype,gen);
    auto c = nm::Array::zeros(array{M,N},dtype);

    auto tile_shape = tuple{2_ct,16_ct};
    auto num_threads = 4;
    auto ctx = v128_mt(num_threads);
    auto worker_size = num_threads;

    auto min_time = std::chrono::nanoseconds(50'000'000);
    ankerl::nanobench::Bench()
        .minEpochTime(min_time)
        .run("v128_mt.add.case9d",[&](){
            ctx.eval(worker_size,add_kernel,c,a,b,tile_shape);
        });

    auto expected = nm::add(a,b);
    NMTOOLS_ASSERT_CLOSE( c, expected );
}

TEST_CASE("v128_mt.add.case9e" * doctest::test_suite("tilekit"))
{
    auto gen   = nm::random_engine();
    auto dtype = nm::float32;

    auto M = 1024 * 4;
    auto N = 1024;
    auto a_shape = array{M,N};
    auto b_shape = array{M,N};

    auto a = nm::random(a_shape,dtype,gen);
    auto b = nm::random(b_shape,dtype,gen);
    auto c = nm::Array::zeros(array{M,N},dtype);

    auto tile_shape = tuple{1_ct,32_ct};
    auto num_threads = 4;
    auto ctx = v128_mt(num_threads);
    auto worker_size = num_threads;

    auto min_time = std::chrono::nanoseconds(50'000'000);
    ankerl::nanobench::Bench()
        .minEpochTime(min_time)
        .run("v128_mt.add.case9e",[&](){
            ctx.eval(worker_size,add_kernel,c,a,b,tile_shape);
        });

    auto expected = nm::add(a,b);
    NMTOOLS_ASSERT_CLOSE( c, expected );
}