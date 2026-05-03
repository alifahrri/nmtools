#include "nmtools/tilekit/vector.hpp"
#include "nmtools/tilekit/tilekit.hpp"
#include "nmtools/array/ufuncs/minimum.hpp"
#include "nmtools/array/random.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/ndarray.hpp"

#include "kernels/minimum.hpp"

#include <nanobench.h>

namespace nm = nmtools;
using namespace nmtools::literals;

using ctx_t = tk::vector::context_t<512>;

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

#define V512_ST_MINIMUM_CASE(case_name, shape, tile_shape) \
TEST_CASE(#case_name * doctest::test_suite("tilekit")) \
{ \
    auto gen   = nm::random_engine(); \
    auto dtype = nm::float32; \
\
    auto a = nm::random(shape,dtype,gen); \
    auto b = nm::random(shape,dtype,gen); \
    auto c = nm::Array::zeros(shape,dtype); \
\
    auto ctx = ctx_t{}; \
\
    auto min_time = std::chrono::nanoseconds(50'000'000); \
    ankerl::nanobench::Bench() \
        .minEpochTime(min_time) \
        .run(#case_name,[&](){ \
            minimum_kernel(ctx,c,a,b,tile_shape); \
        }); \
\
    auto expected = nm::minimum(a,b); \
    NMTOOLS_ASSERT_CLOSE( c, expected ); \
}

// V512_ST_MINIMUM_CASE(v512_st.minimum.4_4.fp32.2x16, (make_shape(4,4)), (tuple{2_ct,16_ct}))
V512_ST_MINIMUM_CASE(v512_st.minimum.4_8.fp32.2x16, (make_shape(4,8)), (tuple{2_ct,16_ct}))
V512_ST_MINIMUM_CASE(v512_st.minimum.4_16.fp32.2x16, (make_shape(4,16)), (tuple{2_ct,16_ct}))
V512_ST_MINIMUM_CASE(v512_st.minimum.4_32.fp32.2x16, (make_shape(4,32)), (tuple{2_ct,16_ct}))
V512_ST_MINIMUM_CASE(v512_st.minimum.4_64.fp32.2x16, (make_shape(4,64)), (tuple{2_ct,16_ct}))
V512_ST_MINIMUM_CASE(v512_st.minimum.4_128.fp32.2x16, (make_shape(4,128)), (tuple{2_ct,16_ct}))
V512_ST_MINIMUM_CASE(v512_st.minimum.4_256.fp32.2x16, (make_shape(4,256)), (tuple{2_ct,16_ct}))
V512_ST_MINIMUM_CASE(v512_st.minimum.4_512.fp32.2x16, (make_shape(4,512)), (tuple{2_ct,16_ct}))
V512_ST_MINIMUM_CASE(v512_st.minimum.4_1024.fp32.2x16, (make_shape(4,1024)), (tuple{2_ct,16_ct}))
V512_ST_MINIMUM_CASE(v512_st.minimum.4_2048.fp32.2x16, (make_shape(4,2048)), (tuple{2_ct,16_ct}))

V512_ST_MINIMUM_CASE(v512_st.minimum.8_8.fp32.2x16, (make_shape(8,8)), (tuple{2_ct,16_ct}))
V512_ST_MINIMUM_CASE(v512_st.minimum.8_16.fp32.2x16, (make_shape(8,16)), (tuple{2_ct,16_ct}))
V512_ST_MINIMUM_CASE(v512_st.minimum.8_32.fp32.2x16, (make_shape(8,32)), (tuple{2_ct,16_ct}))
V512_ST_MINIMUM_CASE(v512_st.minimum.8_64.fp32.2x16, (make_shape(8,64)), (tuple{2_ct,16_ct}))
V512_ST_MINIMUM_CASE(v512_st.minimum.8_128.fp32.2x16, (make_shape(8,128)), (tuple{2_ct,16_ct}))
V512_ST_MINIMUM_CASE(v512_st.minimum.8_256.fp32.2x16, (make_shape(8,256)), (tuple{2_ct,16_ct}))
V512_ST_MINIMUM_CASE(v512_st.minimum.8_512.fp32.2x16, (make_shape(8,512)), (tuple{2_ct,16_ct}))
V512_ST_MINIMUM_CASE(v512_st.minimum.8_1024.fp32.2x16, (make_shape(8,1024)), (tuple{2_ct,16_ct}))
V512_ST_MINIMUM_CASE(v512_st.minimum.8_2048.fp32.2x16, (make_shape(8,2048)), (tuple{2_ct,16_ct}))

V512_ST_MINIMUM_CASE(v512_st.minimum.16_16.fp32.2x16, (make_shape(16,16)), (tuple{2_ct,16_ct}))
V512_ST_MINIMUM_CASE(v512_st.minimum.16_32.fp32.2x16, (make_shape(16,32)), (tuple{2_ct,16_ct}))
V512_ST_MINIMUM_CASE(v512_st.minimum.16_64.fp32.2x16, (make_shape(16,64)), (tuple{2_ct,16_ct}))
V512_ST_MINIMUM_CASE(v512_st.minimum.16_128.fp32.2x16, (make_shape(16,128)), (tuple{2_ct,16_ct}))
V512_ST_MINIMUM_CASE(v512_st.minimum.16_256.fp32.2x16, (make_shape(16,256)), (tuple{2_ct,16_ct}))
V512_ST_MINIMUM_CASE(v512_st.minimum.16_512.fp32.2x16, (make_shape(16,512)), (tuple{2_ct,16_ct}))
V512_ST_MINIMUM_CASE(v512_st.minimum.16_1024.fp32.2x16, (make_shape(16,1024)), (tuple{2_ct,16_ct}))
V512_ST_MINIMUM_CASE(v512_st.minimum.16_2048.fp32.2x16, (make_shape(16,2048)), (tuple{2_ct,16_ct}))

V512_ST_MINIMUM_CASE(v512_st.minimum.32_32.fp32.2x16, (make_shape(32,32)), (tuple{2_ct,16_ct}))
V512_ST_MINIMUM_CASE(v512_st.minimum.32_64.fp32.2x16, (make_shape(32,64)), (tuple{2_ct,16_ct}))
V512_ST_MINIMUM_CASE(v512_st.minimum.32_128.fp32.2x16, (make_shape(32,128)), (tuple{2_ct,16_ct}))
V512_ST_MINIMUM_CASE(v512_st.minimum.32_256.fp32.2x16, (make_shape(32,256)), (tuple{2_ct,16_ct}))
V512_ST_MINIMUM_CASE(v512_st.minimum.32_512.fp32.2x16, (make_shape(32,512)), (tuple{2_ct,16_ct}))
V512_ST_MINIMUM_CASE(v512_st.minimum.32_1024.fp32.2x16, (make_shape(32,1024)), (tuple{2_ct,16_ct}))
V512_ST_MINIMUM_CASE(v512_st.minimum.32_2048.fp32.2x16, (make_shape(32,2048)), (tuple{2_ct,16_ct}))

V512_ST_MINIMUM_CASE(v512_st.minimum.64_64.fp32.2x16, (make_shape(64,64)), (tuple{2_ct,16_ct}))
V512_ST_MINIMUM_CASE(v512_st.minimum.64_128.fp32.2x16, (make_shape(64,128)), (tuple{2_ct,16_ct}))
V512_ST_MINIMUM_CASE(v512_st.minimum.64_256.fp32.2x16, (make_shape(64,256)), (tuple{2_ct,16_ct}))
V512_ST_MINIMUM_CASE(v512_st.minimum.64_512.fp32.2x16, (make_shape(64,512)), (tuple{2_ct,16_ct}))
V512_ST_MINIMUM_CASE(v512_st.minimum.64_1024.fp32.2x16, (make_shape(64,1024)), (tuple{2_ct,16_ct}))
V512_ST_MINIMUM_CASE(v512_st.minimum.64_2048.fp32.2x16, (make_shape(64,2048)), (tuple{2_ct,16_ct}))

V512_ST_MINIMUM_CASE(v512_st.minimum.128_128.fp32.2x16, (make_shape(128,128)), (tuple{2_ct,16_ct}))
V512_ST_MINIMUM_CASE(v512_st.minimum.128_256.fp32.2x16, (make_shape(128,256)), (tuple{2_ct,16_ct}))
V512_ST_MINIMUM_CASE(v512_st.minimum.128_512.fp32.2x16, (make_shape(128,512)), (tuple{2_ct,16_ct}))
V512_ST_MINIMUM_CASE(v512_st.minimum.128_1024.fp32.2x16, (make_shape(128,1024)), (tuple{2_ct,16_ct}))
V512_ST_MINIMUM_CASE(v512_st.minimum.128_2048.fp32.2x16, (make_shape(128,2048)), (tuple{2_ct,16_ct}))
