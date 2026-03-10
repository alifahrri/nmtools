#include "nmtools/tilekit/vector.hpp"
#include "nmtools/tilekit/thread_pool.hpp"
#include "nmtools/tilekit/tilekit.hpp"
#include "nmtools/array/ufuncs/log10.hpp"
#include "nmtools/array/random.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/ndarray.hpp"

#include "kernels/log10.hpp"

#include <nanobench.h>

#undef NMTOOLS_TESTING_PRECISION
#define NMTOOLS_TESTING_PRECISION (1e-3)

namespace nm = nmtools;
using namespace nmtools::literals;

using scalar_mt = tk::thread_pool<tk::scalar_t>;

template <typename shape_0_t, typename...shape_n_t>
constexpr auto make_shape(shape_0_t shape_0, shape_n_t...shape_n)
{
    if constexpr (nm::is_constant_index_v<shape_0_t>
        || (nm::is_constant_index_v<shape_n_t> || ...)
    ) {
        return nmtools_tuple{shape_0,shape_n...};
    } else {
        return nmtools_array{shape_0,shape_n...};
    }
}

#define SCALAR_MT_LOG10_CASE(case_name, shape, tile_shape, num_threads) \
TEST_CASE(#case_name * doctest::test_suite("tilekit")) \
{ \
    auto gen   = nm::random_engine(); \
    auto dtype = nm::float32; \
\
    auto inp = nm::random(shape,dtype,gen); \
    auto out = nm::Array::zeros(shape,dtype); \
\
    auto ctx = scalar_mt(num_threads); \
    auto worker_size = num_threads; \
\
    auto min_time = std::chrono::nanoseconds(50'000'000); \
    ankerl::nanobench::Bench() \
        .minEpochTime(min_time) \
        .run(#case_name,[&](){ \
            ctx.eval(worker_size,log10_kernel,out,inp,tile_shape); \
        }); \
\
    auto expected = nm::log10(inp); \
    NMTOOLS_ASSERT_CLOSE( out, expected ); \
}

#define SCALAR_MT_LOG10_UTL_CASE(case_name, shape, tile_shape, num_threads) \
TEST_CASE(#case_name * doctest::test_suite("tilekit")) \
{ \
    auto gen   = nm::random_engine(); \
    auto dtype = nm::float32; \
\
    auto inp = nm::random(shape,dtype,gen); \
    auto out = nm::Array::zeros(shape,dtype); \
\
    auto ctx = scalar_mt(num_threads); \
    auto worker_size = num_threads; \
\
    auto min_time = std::chrono::nanoseconds(50'000'000); \
    ankerl::nanobench::Bench() \
        .minEpochTime(min_time) \
        .run(#case_name,[&](){ \
            ctx.eval(worker_size,log10_utl_kernel,out,inp,tile_shape); \
        }); \
\
    auto expected = nm::log10(inp); \
    NMTOOLS_ASSERT_CLOSE( out, expected ); \
}

SCALAR_MT_LOG10_CASE(scalar_mt.log10.8.fp32.4.2,  make_shape(8), tuple{4_ct}, 2 );
SCALAR_MT_LOG10_CASE(scalar_mt.log10.8.fp32.4.4,  make_shape(8), tuple{4_ct}, 4 );
SCALAR_MT_LOG10_CASE(scalar_mt.log10.8.fp32.4.8,  make_shape(8), tuple{4_ct}, 8 );
SCALAR_MT_LOG10_CASE(scalar_mt.log10.8.fp32.4.16,  make_shape(8), tuple{4_ct}, 16 );

SCALAR_MT_LOG10_UTL_CASE(scalar_mt.log10_utl.8.fp32.4.2,  make_shape(8), tuple{4_ct}, 2 );
SCALAR_MT_LOG10_UTL_CASE(scalar_mt.log10_utl.8.fp32.4.4,  make_shape(8), tuple{4_ct}, 4 );
SCALAR_MT_LOG10_UTL_CASE(scalar_mt.log10_utl.8.fp32.4.8,  make_shape(8), tuple{4_ct}, 8 );
SCALAR_MT_LOG10_UTL_CASE(scalar_mt.log10_utl.8.fp32.4.16,  make_shape(8), tuple{4_ct}, 16 );

SCALAR_MT_LOG10_CASE(scalar_mt.log10.64.fp32.4.2,  make_shape(64), tuple{4_ct}, 2 );
SCALAR_MT_LOG10_CASE(scalar_mt.log10.64.fp32.4.4,  make_shape(64), tuple{4_ct}, 4 );
SCALAR_MT_LOG10_CASE(scalar_mt.log10.64.fp32.4.8,  make_shape(64), tuple{4_ct}, 8 );
SCALAR_MT_LOG10_CASE(scalar_mt.log10.64.fp32.4.16,  make_shape(64), tuple{4_ct}, 16 );

SCALAR_MT_LOG10_UTL_CASE(scalar_mt.log10_utl.64.fp32.4.2,  make_shape(64), tuple{4_ct}, 2 );
SCALAR_MT_LOG10_UTL_CASE(scalar_mt.log10_utl.64.fp32.4.4,  make_shape(64), tuple{4_ct}, 4 );
SCALAR_MT_LOG10_UTL_CASE(scalar_mt.log10_utl.64.fp32.4.8,  make_shape(64), tuple{4_ct}, 8 );
SCALAR_MT_LOG10_UTL_CASE(scalar_mt.log10_utl.64.fp32.4.16,  make_shape(64), tuple{4_ct}, 16 );

SCALAR_MT_LOG10_CASE(scalar_mt.log10.1024.fp32.4.2,  make_shape(1024), tuple{4_ct}, 2 );
SCALAR_MT_LOG10_CASE(scalar_mt.log10.1024.fp32.4.4,  make_shape(1024), tuple{4_ct}, 4 );
SCALAR_MT_LOG10_CASE(scalar_mt.log10.1024.fp32.4.8,  make_shape(1024), tuple{4_ct}, 8 );
SCALAR_MT_LOG10_CASE(scalar_mt.log10.1024.fp32.4.16,  make_shape(1024), tuple{4_ct}, 16 );

SCALAR_MT_LOG10_UTL_CASE(scalar_mt.log10_utl.1024.fp32.4.2,  make_shape(1024), tuple{4_ct}, 2 );
SCALAR_MT_LOG10_UTL_CASE(scalar_mt.log10_utl.1024.fp32.4.4,  make_shape(1024), tuple{4_ct}, 4 );
SCALAR_MT_LOG10_UTL_CASE(scalar_mt.log10_utl.1024.fp32.4.8,  make_shape(1024), tuple{4_ct}, 8 );
SCALAR_MT_LOG10_UTL_CASE(scalar_mt.log10_utl.1024.fp32.4.16,  make_shape(1024), tuple{4_ct}, 16 );

SCALAR_MT_LOG10_CASE(scalar_mt.log10.4_256.fp32.2x4.2,  (make_shape(4,256)), (tuple{2_ct,4_ct}), 2 );
SCALAR_MT_LOG10_CASE(scalar_mt.log10.4_256.fp32.2x4.4,  (make_shape(4,256)), (tuple{2_ct,4_ct}), 4 );
SCALAR_MT_LOG10_CASE(scalar_mt.log10.4_256.fp32.2x4.8,  (make_shape(4,256)), (tuple{2_ct,4_ct}), 8 );
SCALAR_MT_LOG10_CASE(scalar_mt.log10.4_256.fp32.2x4.16,  (make_shape(4,256)), (tuple{2_ct,4_ct}), 16 );

SCALAR_MT_LOG10_UTL_CASE(scalar_mt.log10_utl.4_256.fp32.2x4.2,  (make_shape(4,256)), (tuple{2_ct,4_ct}), 2 );
SCALAR_MT_LOG10_UTL_CASE(scalar_mt.log10_utl.4_256.fp32.2x4.4,  (make_shape(4,256)), (tuple{2_ct,4_ct}), 4 );
SCALAR_MT_LOG10_UTL_CASE(scalar_mt.log10_utl.4_256.fp32.2x4.8,  (make_shape(4,256)), (tuple{2_ct,4_ct}), 8 );
SCALAR_MT_LOG10_UTL_CASE(scalar_mt.log10_utl.4_256.fp32.2x4.16,  (make_shape(4,256)), (tuple{2_ct,4_ct}), 16 );

SCALAR_MT_LOG10_CASE(scalar_mt.log10.16_1024.fp32.2x4.2,  (make_shape(16,1024)), (tuple{2_ct,4_ct}), 2 );
SCALAR_MT_LOG10_CASE(scalar_mt.log10.16_1024.fp32.2x4.4,  (make_shape(16,1024)), (tuple{2_ct,4_ct}), 4 );
SCALAR_MT_LOG10_CASE(scalar_mt.log10.16_1024.fp32.2x4.8,  (make_shape(16,1024)), (tuple{2_ct,4_ct}), 8 );
SCALAR_MT_LOG10_CASE(scalar_mt.log10.16_1024.fp32.2x4.16,  (make_shape(16,1024)), (tuple{2_ct,4_ct}), 16 );

SCALAR_MT_LOG10_UTL_CASE(scalar_mt.log10_utl.16_1024.fp32.2x4.2,  (make_shape(16,1024)), (tuple{2_ct,4_ct}), 2 );
SCALAR_MT_LOG10_UTL_CASE(scalar_mt.log10_utl.16_1024.fp32.2x4.4,  (make_shape(16,1024)), (tuple{2_ct,4_ct}), 4 );
SCALAR_MT_LOG10_UTL_CASE(scalar_mt.log10_utl.16_1024.fp32.2x4.8,  (make_shape(16,1024)), (tuple{2_ct,4_ct}), 8 );
SCALAR_MT_LOG10_UTL_CASE(scalar_mt.log10_utl.16_1024.fp32.2x4.16,  (make_shape(16,1024)), (tuple{2_ct,4_ct}), 16 );

SCALAR_MT_LOG10_CASE(scalar_mt.log10.64_1024.fp32.2x4.2,  (make_shape(64,1024)), (tuple{2_ct,4_ct}), 2 );
SCALAR_MT_LOG10_CASE(scalar_mt.log10.64_1024.fp32.2x4.4,  (make_shape(64,1024)), (tuple{2_ct,4_ct}), 4 );
SCALAR_MT_LOG10_CASE(scalar_mt.log10.64_1024.fp32.2x4.8,  (make_shape(64,1024)), (tuple{2_ct,4_ct}), 8 );
SCALAR_MT_LOG10_CASE(scalar_mt.log10.64_1024.fp32.2x4.16,  (make_shape(64,1024)), (tuple{2_ct,4_ct}), 16 );

SCALAR_MT_LOG10_UTL_CASE(scalar_mt.log10_utl.64_1024.fp32.2x4.2,  (make_shape(64,1024)), (tuple{2_ct,4_ct}), 2 );
SCALAR_MT_LOG10_UTL_CASE(scalar_mt.log10_utl.64_1024.fp32.2x4.4,  (make_shape(64,1024)), (tuple{2_ct,4_ct}), 4 );
SCALAR_MT_LOG10_UTL_CASE(scalar_mt.log10_utl.64_1024.fp32.2x4.8,  (make_shape(64,1024)), (tuple{2_ct,4_ct}), 8 );
SCALAR_MT_LOG10_UTL_CASE(scalar_mt.log10_utl.64_1024.fp32.2x4.16,  (make_shape(64,1024)), (tuple{2_ct,4_ct}), 16 );

SCALAR_MT_LOG10_CASE(scalar_mt.log10.1024_1024.fp32.2x4.2,  (make_shape(1024,1024)), (tuple{2_ct,4_ct}), 2 );
SCALAR_MT_LOG10_CASE(scalar_mt.log10.1024_1024.fp32.2x4.4,  (make_shape(1024,1024)), (tuple{2_ct,4_ct}), 4 );
SCALAR_MT_LOG10_CASE(scalar_mt.log10.1024_1024.fp32.2x4.8,  (make_shape(1024,1024)), (tuple{2_ct,4_ct}), 8 );
SCALAR_MT_LOG10_CASE(scalar_mt.log10.1024_1024.fp32.2x4.16,  (make_shape(1024,1024)), (tuple{2_ct,4_ct}), 16 );

SCALAR_MT_LOG10_UTL_CASE(scalar_mt.log10_utl.1024_1024.fp32.2x4.2,  (make_shape(1024,1024)), (tuple{2_ct,4_ct}), 2 );
SCALAR_MT_LOG10_UTL_CASE(scalar_mt.log10_utl.1024_1024.fp32.2x4.4,  (make_shape(1024,1024)), (tuple{2_ct,4_ct}), 4 );
SCALAR_MT_LOG10_UTL_CASE(scalar_mt.log10_utl.1024_1024.fp32.2x4.8,  (make_shape(1024,1024)), (tuple{2_ct,4_ct}), 8 );
SCALAR_MT_LOG10_UTL_CASE(scalar_mt.log10_utl.1024_1024.fp32.2x4.16,  (make_shape(1024,1024)), (tuple{2_ct,4_ct}), 16 );