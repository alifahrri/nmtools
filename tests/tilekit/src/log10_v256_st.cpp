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

using v256_st = tk::vector::context_t<256>;

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

#define V256_ST_LOG10_CASE(case_name, shape, tile_shape) \
TEST_CASE(#case_name * doctest::test_suite("tilekit")) \
{ \
    auto gen   = nm::random_engine(); \
    auto dtype = nm::float32; \
\
    auto inp = nm::random(shape,dtype,gen); \
    auto out = nm::Array::zeros(shape,dtype); \
\
    auto ctx = v256_st(); \
\
    auto min_time = std::chrono::nanoseconds(50'000'000); \
    ankerl::nanobench::Bench() \
        .minEpochTime(min_time) \
        .run(#case_name,[&](){ \
            log10_kernel(ctx,out,inp,tile_shape); \
        }); \
\
    auto expected = nm::log10(inp); \
    NMTOOLS_ASSERT_CLOSE( out, expected ); \
}

#define V256_ST_LOG10_UTL_CASE(case_name, shape, tile_shape) \
TEST_CASE(#case_name * doctest::test_suite("tilekit")) \
{ \
    auto gen   = nm::random_engine(); \
    auto dtype = nm::float32; \
\
    auto inp = nm::random(shape,dtype,gen); \
    auto out = nm::Array::zeros(shape,dtype); \
\
    auto ctx = v256_st(); \
\
    auto min_time = std::chrono::nanoseconds(50'000'000); \
    ankerl::nanobench::Bench() \
        .minEpochTime(min_time) \
        .run(#case_name,[&](){ \
            log10_utl_kernel(ctx,out,inp,tile_shape); \
        }); \
\
    auto expected = nm::log10(inp); \
    NMTOOLS_ASSERT_CLOSE( out, expected ); \
}

V256_ST_LOG10_CASE(v256_st.log10.8.fp32.4,  make_shape(8), tuple{8_ct} );
V256_ST_LOG10_UTL_CASE(v256_st.log10_utl.8.fp32.4,  make_shape(8), tuple{8_ct} );

V256_ST_LOG10_CASE(v256_st.log10.64.fp32.4,  make_shape(64), tuple{8_ct} );
V256_ST_LOG10_UTL_CASE(v256_st.log10_utl.64.fp32.4,  make_shape(64), tuple{8_ct} );

V256_ST_LOG10_CASE(v256_st.log10.1024.fp32.4,  make_shape(1024), tuple{8_ct} );
V256_ST_LOG10_UTL_CASE(v256_st.log10_utl.1024.fp32.4,  make_shape(1024), tuple{8_ct} );

V256_ST_LOG10_CASE(v256_st.log10.4_256.fp32.2x4,  (make_shape(4,256)), (tuple{2_ct,8_ct}) );
V256_ST_LOG10_UTL_CASE(v256_st.log10_utl.4_256.fp32.2x4,  (make_shape(4,256)), (tuple{2_ct,8_ct}) );

V256_ST_LOG10_CASE(v256_st.log10.16_1024.fp32.2x4,  (make_shape(16,1024)), (tuple{2_ct,8_ct}) );
V256_ST_LOG10_UTL_CASE(v256_st.log10_utl.16_1024.fp32.2x4,  (make_shape(16,1024)), (tuple{2_ct,8_ct}) );

V256_ST_LOG10_CASE(v256_st.log10.64_1024.fp32.2x4,  (make_shape(64,1024)), (tuple{2_ct,8_ct}) );
V256_ST_LOG10_UTL_CASE(v256_st.log10_utl.64_1024.fp32.2x4,  (make_shape(64,1024)), (tuple{2_ct,8_ct}) );

V256_ST_LOG10_CASE(v256_st.log10.1024_1024.fp32.2x4,  (make_shape(1024,1024)), (tuple{2_ct,8_ct}) );
V256_ST_LOG10_UTL_CASE(v256_st.log10_utl.1024_1024.fp32.2x4,  (make_shape(1024,1024)), (tuple{2_ct,8_ct}) );
