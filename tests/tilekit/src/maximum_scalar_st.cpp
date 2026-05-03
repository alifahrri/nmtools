#include "nmtools/tilekit/scalar.hpp"
#include "nmtools/tilekit/tilekit.hpp"
#include "nmtools/array/ufuncs/maximum.hpp"
#include "nmtools/array/random.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/ndarray.hpp"

#include "kernels/maximum.hpp"

#include <nanobench.h>

namespace nm = nmtools;
using namespace nmtools::literals;

template <typename shape_m_t, typename shape_n_t>
constexpr auto make_shape(shape_m_t shape_m, shape_n_t shape_n)
{
    if constexpr (nm::is_constant_index_v<shape_m_t>
        || nm::is_constant_index_v<shape_n_t>
    ) {
        return nmtools_tuple{shape_m,shape_n};
    } else {
        return nmtools_array{shape_m,shape_n};
    }
}

#define SCALAR_ST_MAXIMUM_CASE(case_name, shape, tile_shape) \
TEST_CASE(#case_name * doctest::test_suite("tilekit")) \
{ \
    auto gen   = nm::random_engine(); \
    auto dtype = nm::float32; \
\
    auto a = nm::random(shape,dtype,gen); \
    auto b = nm::random(shape,dtype,gen); \
    auto c = nm::Array::zeros(shape,dtype); \
\
    auto ctx = tk::Scalar; \
\
    auto min_time = std::chrono::nanoseconds(50'000'000); \
    ankerl::nanobench::Bench() \
        .minEpochTime(min_time) \
        .run(#case_name,[&](){ \
            maximum_kernel(ctx,c,a,b,tile_shape); \
        }); \
\
    auto expected = nm::maximum(a,b); \
    NMTOOLS_ASSERT_CLOSE( c, expected ); \
}

SCALAR_ST_MAXIMUM_CASE(scalar_st.maximum.4_4.fp32.2x4,       (make_shape(4,4)), (tuple{2_ct,4_ct}))
SCALAR_ST_MAXIMUM_CASE(scalar_st.maximum.8_8.fp32.2x4,       (make_shape(8,8)), (tuple{2_ct,4_ct}))
SCALAR_ST_MAXIMUM_CASE(scalar_st.maximum.16_16.fp32.2x4,     (make_shape(16,16)), (tuple{2_ct,4_ct}))
SCALAR_ST_MAXIMUM_CASE(scalar_st.maximum.32_32.fp32.2x4,     (make_shape(32,32)), (tuple{2_ct,4_ct}))
SCALAR_ST_MAXIMUM_CASE(scalar_st.maximum.64_64.fp32.2x4,     (make_shape(64,64)), (tuple{2_ct,4_ct}))
SCALAR_ST_MAXIMUM_CASE(scalar_st.maximum.128_128.fp32.2x4,   (make_shape(128,128)), (tuple{2_ct,4_ct}))
SCALAR_ST_MAXIMUM_CASE(scalar_st.maximum.256_256.fp32.2x4,   (make_shape(256,256)), (tuple{2_ct,4_ct}))
SCALAR_ST_MAXIMUM_CASE(scalar_st.maximum.512_512.fp32.2x4,   (make_shape(512,512)), (tuple{2_ct,4_ct}))
SCALAR_ST_MAXIMUM_CASE(scalar_st.maximum.1024_1024.fp32.2x4, (make_shape(1024,1024)), (tuple{2_ct,4_ct}))

SCALAR_ST_MAXIMUM_CASE(scalar_st.maximum.4_ct_4_ct.fp32.2x4,       (make_shape(4_ct,4_ct)), (tuple{2_ct,4_ct}))
SCALAR_ST_MAXIMUM_CASE(scalar_st.maximum.8_ct_8_ct.fp32.2x4,       (make_shape(8_ct,8_ct)), (tuple{2_ct,4_ct}))
SCALAR_ST_MAXIMUM_CASE(scalar_st.maximum.16_ct_16_ct.fp32.2x4,     (make_shape(16_ct,16_ct)), (tuple{2_ct,4_ct}))
SCALAR_ST_MAXIMUM_CASE(scalar_st.maximum.32_ct_32_ct.fp32.2x4,     (make_shape(32_ct,32_ct)), (tuple{2_ct,4_ct}))
SCALAR_ST_MAXIMUM_CASE(scalar_st.maximum.64_ct_64_ct.fp32.2x4,     (make_shape(64_ct,64_ct)), (tuple{2_ct,4_ct}))
SCALAR_ST_MAXIMUM_CASE(scalar_st.maximum.128_ct_128_ct.fp32.2x4,   (make_shape(128_ct,128_ct)), (tuple{2_ct,4_ct}))
SCALAR_ST_MAXIMUM_CASE(scalar_st.maximum.256_ct_256_ct.fp32.2x4,   (make_shape(256_ct,256_ct)), (tuple{2_ct,4_ct}))
SCALAR_ST_MAXIMUM_CASE(scalar_st.maximum.512_ct_512_ct.fp32.2x4,   (make_shape(512_ct,512_ct)), (tuple{2_ct,4_ct}))
SCALAR_ST_MAXIMUM_CASE(scalar_st.maximum.1024_ct_1024_ct.fp32.2x4, (make_shape(1024_ct,1024_ct)), (tuple{2_ct,4_ct}))