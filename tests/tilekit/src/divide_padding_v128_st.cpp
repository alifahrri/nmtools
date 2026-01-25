#include "nmtools/tilekit/vector.hpp"
#include "nmtools/tilekit/thread_pool.hpp"
#include "nmtools/tilekit/tilekit.hpp"
#include "nmtools/array/ufuncs/divide.hpp"
#include "nmtools/array/random.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/ndarray.hpp"

#include "kernels/divide.hpp"

#include <nanobench.h>

namespace nm = nmtools;
using namespace nmtools::literals;

using v128_st = tk::vector::context_t<128>;

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

#define V128_ST_DIVIDE_CASE(case_name, M, N, tile_m, tile_n) \
TEST_CASE(#case_name * doctest::test_suite("tilekit")) \
{ \
    auto gen   = nm::random_engine(); \
    auto dtype = nm::float32; \
\
    auto a_shape = make_shape(M,N); \
    auto b_shape = make_shape(M,N); \
\
    auto a = nm::random(a_shape,dtype,gen); \
    auto b = nm::random(b_shape,dtype,gen); \
    auto c = nm::Array::zeros(make_shape(M,N),dtype); \
\
    auto tile_shape = tuple{tile_m,tile_n}; \
    auto ctx = v128_st(); \
\
    auto min_time = std::chrono::nanoseconds(50'000'000); \
    ankerl::nanobench::Bench() \
        .minEpochTime(min_time) \
        .run(#case_name,[&](){ \
            divide_padding_kernel(ctx,c,a,b,tile_shape); \
        }); \
\
    auto expected = nm::divide(a,b); \
    NMTOOLS_ASSERT_CLOSE( c, expected ); \
}

V128_ST_DIVIDE_CASE(v128_st.divide_padding.1024_1024.fp32.2x4,  1024, 1024, 2_ct, 4_ct)

V128_ST_DIVIDE_CASE(v128_st.divide_padding.1024_1025.fp32.2x4,  1024, 1025, 2_ct, 4_ct)

V128_ST_DIVIDE_CASE(v128_st.divide_padding.1024_1026.fp32.2x4,  1024, 1026, 2_ct, 4_ct)

V128_ST_DIVIDE_CASE(v128_st.divide_padding.1024_1027.fp32.2x4,  1024, 1027, 2_ct, 4_ct)

V128_ST_DIVIDE_CASE(v128_st.divide_padding.1024_1028.fp32.2x4,  1024, 1028, 2_ct, 4_ct)

V128_ST_DIVIDE_CASE(v128_st.divide_padding.1024_1024_ct.fp32.2x4,  1024, 1024_ct, 2_ct, 4_ct)

V128_ST_DIVIDE_CASE(v128_st.divide_padding.1024_ct_1024_ct.fp32.2x4,  1024_ct, 1024_ct, 2_ct, 4_ct)

V128_ST_DIVIDE_CASE(v128_st.divide_padding.1024_1024.fp32.2x8,  1024, 1024, 2_ct, 8_ct)

V128_ST_DIVIDE_CASE(v128_st.divide_padding.1024_1025.fp32.2x8,  1024, 1025, 2_ct, 8_ct)

V128_ST_DIVIDE_CASE(v128_st.divide_padding.1024_1026.fp32.2x8,  1024, 1026, 2_ct, 8_ct)

V128_ST_DIVIDE_CASE(v128_st.divide_padding.1024_1027.fp32.2x8,  1024, 1024, 2_ct, 8_ct)

V128_ST_DIVIDE_CASE(v128_st.divide_padding.1024_1024_ct.fp32.2x8,  1024, 1024_ct, 2_ct, 8_ct)

V128_ST_DIVIDE_CASE(v128_st.divide_padding.1024_ct_1024_ct.fp32.2x8,  1024_ct, 1024_ct, 2_ct, 8_ct)

V128_ST_DIVIDE_CASE(v128_st.divide_padding.1024_1024.fp32.1x16,  1024, 1024, 1_ct, 16_ct)

V128_ST_DIVIDE_CASE(v128_st.divide_padding.1024_1024_ct.fp32.1x16,  1024, 1024_ct, 1_ct, 16_ct)

V128_ST_DIVIDE_CASE(v128_st.divide_padding.1024_ct_1024_ct.fp32.1x16,  1024_ct, 1024_ct, 1_ct, 16_ct)

V128_ST_DIVIDE_CASE(v128_st.divide_padding.1024_1024.fp32.1x32,  1024, 1024, 1_ct, 32_ct)

V128_ST_DIVIDE_CASE(v128_st.divide_padding.1024_1024_ct.fp32.1x32,  1024, 1024_ct, 1_ct, 32_ct)

V128_ST_DIVIDE_CASE(v128_st.divide_padding.1024_ct_1024_ct.fp32.1x32,  1024_ct, 1024_ct, 1_ct, 32_ct)

V128_ST_DIVIDE_CASE(v128_st.divide_padding.4096_1024.fp32.2x4,  4096, 1024, 2_ct, 4_ct)

V128_ST_DIVIDE_CASE(v128_st.divide_padding.4096_1024_ct.fp32.2x4,  4096, 1024_ct, 2_ct, 4_ct)

V128_ST_DIVIDE_CASE(v128_st.divide_padding.4096_ct_1024_ct.fp32.2x4,  4096_ct, 1024_ct, 2_ct, 4_ct)

V128_ST_DIVIDE_CASE(v128_st.divide_padding.4096_1024.fp32.2x8,  4096, 1024, 2_ct, 8_ct)

V128_ST_DIVIDE_CASE(v128_st.divide_padding.4096_1024_ct.fp32.2x8,  4096, 1024_ct, 2_ct, 8_ct)

V128_ST_DIVIDE_CASE(v128_st.divide_padding.4096_ct_1024_ct.fp32.2x8,  4096_ct, 1024_ct, 2_ct, 8_ct)

V128_ST_DIVIDE_CASE(v128_st.divide_padding.4096_1024.fp32.1x16,  4096, 1024, 1_ct, 16_ct)

V128_ST_DIVIDE_CASE(v128_st.divide_padding.4096_1024_ct.fp32.1x16,  4096, 1024_ct, 1_ct, 16_ct)

V128_ST_DIVIDE_CASE(v128_st.divide_padding.4096_ct_1024_ct.fp32.1x16,  4096_ct, 1024_ct, 1_ct, 16_ct)

V128_ST_DIVIDE_CASE(v128_st.divide_padding.4096_1024.fp32.1x32,  4096, 1024, 1_ct, 32_ct)

V128_ST_DIVIDE_CASE(v128_st.divide_padding.4096_1024_ct.fp32.1x32,  4096, 1024_ct, 1_ct, 32_ct)

V128_ST_DIVIDE_CASE(v128_st.divide_padding.4096_ct_1024_ct.fp32.1x32,  4096_ct, 1024_ct, 1_ct, 32_ct)