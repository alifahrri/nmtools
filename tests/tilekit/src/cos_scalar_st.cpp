#include "nmtools/tilekit/vector.hpp"
#include "nmtools/tilekit/thread_pool.hpp"
#include "nmtools/tilekit/tilekit.hpp"
#include "nmtools/array/ufuncs/cos.hpp"
#include "nmtools/array/random.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/ndarray.hpp"

#include "kernels/cos.hpp"

#include <nanobench.h>

// TODO: fix precision!
#undef NMTOOLS_TESTING_PRECISION
#define NMTOOLS_TESTING_PRECISION (1e-1)

namespace nm = nmtools;
using namespace nmtools::literals;

using scalar_st = tk::scalar_t;

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

#define SCALAR_ST_COS_CASE(case_name, shape, tile_shape) \
TEST_CASE(#case_name * doctest::test_suite("tilekit")) \
{ \
    auto gen   = nm::random_engine(); \
    auto dtype = nm::float32; \
\
    auto inp = nm::random(shape,dtype,gen); \
    auto out = nm::Array::zeros(shape,dtype); \
\
    auto ctx = scalar_st(); \
\
    auto min_time = std::chrono::nanoseconds(50'000'000); \
    ankerl::nanobench::Bench() \
        .minEpochTime(min_time) \
        .run(#case_name,[&](){ \
            cos_kernel(ctx,out,inp,tile_shape); \
        }); \
\
    auto expected = nm::cos(inp); \
    NMTOOLS_ASSERT_CLOSE( out, expected ); \
}

#define SCALAR_ST_COS_UTL_CASE(case_name, shape, tile_shape) \
TEST_CASE(#case_name * doctest::test_suite("tilekit")) \
{ \
    auto gen   = nm::random_engine(); \
    auto dtype = nm::float32; \
\
    auto inp = nm::random(shape,dtype,gen); \
    auto out = nm::Array::zeros(shape,dtype); \
\
    auto ctx = scalar_st(); \
\
    auto min_time = std::chrono::nanoseconds(50'000'000); \
    ankerl::nanobench::Bench() \
        .minEpochTime(min_time) \
        .run(#case_name,[&](){ \
            cos_utl_kernel(ctx,out,inp,tile_shape); \
        }); \
\
    auto expected = nm::cos(inp); \
    NMTOOLS_ASSERT_CLOSE( out, expected ); \
}

SCALAR_ST_COS_CASE(scalar_st.cos.8.fp32.4,  make_shape(8), tuple{4_ct} );
SCALAR_ST_COS_UTL_CASE(scalar_st.cos_utl.8.fp32.4,  make_shape(8), tuple{4_ct} );

SCALAR_ST_COS_CASE(scalar_st.cos.64.fp32.4,  make_shape(64), tuple{4_ct} );
SCALAR_ST_COS_UTL_CASE(scalar_st.cos_utl.64.fp32.4,  make_shape(64), tuple{4_ct} );

SCALAR_ST_COS_CASE(scalar_st.cos.1024.fp32.4,  make_shape(1024), tuple{4_ct} );
SCALAR_ST_COS_UTL_CASE(scalar_st.cos_utl.1024.fp32.4,  make_shape(1024), tuple{4_ct} );

SCALAR_ST_COS_CASE(scalar_st.cos.4_256.fp32.2x4,  (make_shape(4,256)), (tuple{2_ct,4_ct}) );
SCALAR_ST_COS_UTL_CASE(scalar_st.cos_utl.4_256.fp32.2x4,  (make_shape(4,256)), (tuple{2_ct,4_ct}) );

SCALAR_ST_COS_CASE(scalar_st.cos.16_1024.fp32.2x4,  (make_shape(16,1024)), (tuple{2_ct,4_ct}) );
SCALAR_ST_COS_UTL_CASE(scalar_st.cos_utl.16_1024.fp32.2x4,  (make_shape(16,1024)), (tuple{2_ct,4_ct}) );

SCALAR_ST_COS_CASE(scalar_st.cos.64_1024.fp32.2x4,  (make_shape(64,1024)), (tuple{2_ct,4_ct}) );
SCALAR_ST_COS_UTL_CASE(scalar_st.cos_utl.64_1024.fp32.2x4,  (make_shape(64,1024)), (tuple{2_ct,4_ct}) );

SCALAR_ST_COS_CASE(scalar_st.cos.1024_1024.fp32.2x4,  (make_shape(1024,1024)), (tuple{2_ct,4_ct}) );
SCALAR_ST_COS_UTL_CASE(scalar_st.cos_utl.1024_1024.fp32.2x4,  (make_shape(1024,1024)), (tuple{2_ct,4_ct}) );