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

using mt_vector = tk::thread_pool<tk::vector::context_t>;

TEST_CASE("thread_pool.add.case7" * doctest::test_suite("tilekit"))
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
    auto ctx = mt_vector(num_threads);
    auto worker_size = num_threads;

    auto min_time = std::chrono::nanoseconds(50'000'000);
    ankerl::nanobench::Bench()
        .minEpochTime(min_time)
        .run("thread_pool.add.case7",[&](){
            ctx.launch(worker_size,add_kernel,c,a,b,tile_shape);
        });

    auto expected = nm::add(a,b);
    NMTOOLS_ASSERT_CLOSE( c, expected );
}

TEST_CASE("thread_pool.add.case7b" * doctest::test_suite("tilekit"))
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
    auto ctx = mt_vector(num_threads);
    auto worker_size = num_threads;

    auto min_time = std::chrono::nanoseconds(50'000'000);
    ankerl::nanobench::Bench()
        .minEpochTime(min_time)
        .run("thread_pool.add.case7b",[&](){
            ctx.launch(worker_size,add_kernel,c,a,b,tile_shape);
        });

    auto expected = nm::add(a,b);
    NMTOOLS_ASSERT_CLOSE( c, expected );
}

TEST_CASE("thread_pool.add.case7c" * doctest::test_suite("tilekit"))
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
    auto ctx = mt_vector(num_threads);
    auto worker_size = num_threads;

    auto min_time = std::chrono::nanoseconds(50'000'000);
    ankerl::nanobench::Bench()
        .minEpochTime(min_time)
        .run("thread_pool.add.case7c",[&](){
            ctx.launch(worker_size,add_kernel,c,a,b,tile_shape);
        });

    auto expected = nm::add(a,b);
    NMTOOLS_ASSERT_CLOSE( c, expected );
}

TEST_CASE("thread_pool.add.case7d" * doctest::test_suite("tilekit"))
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
    auto ctx = mt_vector(num_threads);
    auto worker_size = num_threads;

    auto min_time = std::chrono::nanoseconds(50'000'000);
    ankerl::nanobench::Bench()
        .minEpochTime(min_time)
        .run("thread_pool.add.case7d",[&](){
            ctx.launch(worker_size,add_kernel,c,a,b,tile_shape);
        });

    auto expected = nm::add(a,b);
    NMTOOLS_ASSERT_CLOSE( c, expected );
}

/*********************************************************************************** */
// no thread affinity

TEST_CASE("thread_pool.add.case7e" * doctest::test_suite("tilekit"))
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
    auto ctx = mt_vector(num_threads,false);
    auto worker_size = num_threads;

    auto min_time = std::chrono::nanoseconds(50'000'000);
    ankerl::nanobench::Bench()
        .minEpochTime(min_time)
        .run("thread_pool.add.case7e",[&](){
            ctx.launch(worker_size,add_kernel,c,a,b,tile_shape);
        });

    auto expected = nm::add(a,b);
    NMTOOLS_ASSERT_CLOSE( c, expected );
}

TEST_CASE("thread_pool.add.case7f" * doctest::test_suite("tilekit"))
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
    auto ctx = mt_vector(num_threads,false);
    auto worker_size = num_threads;

    auto min_time = std::chrono::nanoseconds(50'000'000);
    ankerl::nanobench::Bench()
        .minEpochTime(min_time)
        .run("thread_pool.add.case7f",[&](){
            ctx.launch(worker_size,add_kernel,c,a,b,tile_shape);
        });

    auto expected = nm::add(a,b);
    NMTOOLS_ASSERT_CLOSE( c, expected );
}

TEST_CASE("thread_pool.add.case7g" * doctest::test_suite("tilekit"))
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
    auto ctx = mt_vector(num_threads,false);
    auto worker_size = num_threads;

    auto min_time = std::chrono::nanoseconds(50'000'000);
    ankerl::nanobench::Bench()
        .minEpochTime(min_time)
        .run("thread_pool.add.case7g",[&](){
            ctx.launch(worker_size,add_kernel,c,a,b,tile_shape);
        });

    auto expected = nm::add(a,b);
    NMTOOLS_ASSERT_CLOSE( c, expected );
}

TEST_CASE("thread_pool.add.case7h" * doctest::test_suite("tilekit"))
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
    auto ctx = mt_vector(num_threads,false);
    auto worker_size = num_threads;

    auto min_time = std::chrono::nanoseconds(50'000'000);
    ankerl::nanobench::Bench()
        .minEpochTime(min_time)
        .run("thread_pool.add.case7h",[&](){
            ctx.launch(worker_size,add_kernel,c,a,b,tile_shape);
        });

    auto expected = nm::add(a,b);
    NMTOOLS_ASSERT_CLOSE( c, expected );
}

/*********************************************************************************** */
// mixed shape
TEST_CASE("thread_pool.add.case7i" * doctest::test_suite("tilekit") * doctest::skip())
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
    auto ctx = mt_vector(num_threads);
    auto worker_size = num_threads;

    auto min_time = std::chrono::nanoseconds(50'000'000);
    ankerl::nanobench::Bench()
        .minEpochTime(min_time)
        .run("thread_pool.add.case7i",[&](){
            ctx.launch(worker_size,add_kernel,c,a,b,tile_shape);
        });

    auto expected = nm::add(a,b);
    NMTOOLS_ASSERT_CLOSE( c, expected );
}

TEST_CASE("thread_pool.add.case7j" * doctest::test_suite("tilekit"))
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
    auto ctx = mt_vector(num_threads);
    auto worker_size = num_threads;

    auto min_time = std::chrono::nanoseconds(50'000'000);
    ankerl::nanobench::Bench()
        .minEpochTime(min_time)
        .run("thread_pool.add.case7j",[&](){
            ctx.launch(worker_size,add_kernel,c,a,b,tile_shape);
        });

    auto expected = nm::add(a,b);
    NMTOOLS_ASSERT_CLOSE( c, expected );
}

TEST_CASE("thread_pool.add.case7k" * doctest::test_suite("tilekit"))
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
    auto ctx = mt_vector(num_threads);
    auto worker_size = num_threads;

    auto min_time = std::chrono::nanoseconds(50'000'000);
    ankerl::nanobench::Bench()
        .minEpochTime(min_time)
        .run("thread_pool.add.case7k",[&](){
            ctx.launch(worker_size,add_kernel,c,a,b,tile_shape);
        });

    auto expected = nm::add(a,b);
    NMTOOLS_ASSERT_CLOSE( c, expected );
}

TEST_CASE("thread_pool.add.case7l" * doctest::test_suite("tilekit"))
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
    auto ctx = mt_vector(num_threads);
    auto worker_size = num_threads;

    auto min_time = std::chrono::nanoseconds(50'000'000);
    ankerl::nanobench::Bench()
        .minEpochTime(min_time)
        .run("thread_pool.add.case7l",[&](){
            ctx.launch(worker_size,add_kernel,c,a,b,tile_shape);
        });

    auto expected = nm::add(a,b);
    NMTOOLS_ASSERT_CLOSE( c, expected );
}

// TODO: fix segfault
#if 0
TEST_CASE("thread_pool.add.case7e" * doctest::test_suite("tilekit"))
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
    auto ctx = mt_vector(num_threads);
    auto worker_size = num_threads;

    auto min_time = std::chrono::nanoseconds(50'000'000);
    ankerl::nanobench::Bench()
        .minEpochTime(min_time)
        .run("thread_pool.add.case7e",[&](){
            ctx.launch(worker_size,add_kernel,c,a,b,tile_shape);
        });

    auto expected = nm::add(a,b);
    NMTOOLS_ASSERT_CLOSE( c, expected );
}

TEST_CASE("thread_pool.add.case7f" * doctest::test_suite("tilekit"))
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
    auto ctx = mt_vector(num_threads);
    auto worker_size = num_threads;

    auto min_time = std::chrono::nanoseconds(50'000'000);
    ankerl::nanobench::Bench()
        .minEpochTime(min_time)
        .run("thread_pool.add.case7f",[&](){
            ctx.launch(worker_size,add_kernel,c,a,b,tile_shape);
        });

    auto expected = nm::add(a,b);
    NMTOOLS_ASSERT_CLOSE( c, expected );
}
#endif

TEST_CASE("thread_pool.add.case9" * doctest::test_suite("tilekit"))
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
    auto ctx = mt_vector(num_threads);
    auto worker_size = num_threads;

    auto min_time = std::chrono::nanoseconds(50'000'000);
    ankerl::nanobench::Bench()
        .minEpochTime(min_time)
        .run("thread_pool.add.case9",[&](){
            ctx.launch(worker_size,add_kernel,c,a,b,tile_shape);
        });

    auto expected = nm::add(a,b);
    NMTOOLS_ASSERT_CLOSE( c, expected );
}

TEST_CASE("thread_pool.add.case9b" * doctest::test_suite("tilekit"))
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
    auto ctx = mt_vector(num_threads);
    auto worker_size = num_threads;

    auto min_time = std::chrono::nanoseconds(50'000'000);
    ankerl::nanobench::Bench()
        .minEpochTime(min_time)
        .run("thread_pool.add.case9b",[&](){
            ctx.launch(worker_size,add_kernel,c,a,b,tile_shape);
        });

    auto expected = nm::add(a,b);
    NMTOOLS_ASSERT_CLOSE( c, expected );
}

TEST_CASE("thread_pool.add.case9c" * doctest::test_suite("tilekit"))
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
    auto ctx = mt_vector(num_threads);
    auto worker_size = num_threads;

    auto min_time = std::chrono::nanoseconds(50'000'000);
    ankerl::nanobench::Bench()
        .minEpochTime(min_time)
        .run("thread_pool.add.case9c",[&](){
            ctx.launch(worker_size,add_kernel,c,a,b,tile_shape);
        });

    auto expected = nm::add(a,b);
    NMTOOLS_ASSERT_CLOSE( c, expected );
}

TEST_CASE("thread_pool.add.case9d" * doctest::test_suite("tilekit"))
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
    auto ctx = mt_vector(num_threads);
    auto worker_size = num_threads;

    auto min_time = std::chrono::nanoseconds(50'000'000);
    ankerl::nanobench::Bench()
        .minEpochTime(min_time)
        .run("thread_pool.add.case9d",[&](){
            ctx.launch(worker_size,add_kernel,c,a,b,tile_shape);
        });

    auto expected = nm::add(a,b);
    NMTOOLS_ASSERT_CLOSE( c, expected );
}

TEST_CASE("thread_pool.add.case9e" * doctest::test_suite("tilekit"))
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
    auto ctx = mt_vector(num_threads);
    auto worker_size = num_threads;

    auto min_time = std::chrono::nanoseconds(50'000'000);
    ankerl::nanobench::Bench()
        .minEpochTime(min_time)
        .run("thread_pool.add.case9e",[&](){
            ctx.launch(worker_size,add_kernel,c,a,b,tile_shape);
        });

    auto expected = nm::add(a,b);
    NMTOOLS_ASSERT_CLOSE( c, expected );
}