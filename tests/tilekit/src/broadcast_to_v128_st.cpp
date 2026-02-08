#include "nmtools/tilekit/vector.hpp"
#include "nmtools/tilekit/tilekit.hpp"
#include "nmtools/array/ufuncs/add.hpp"
#include "nmtools/array/random.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/ndarray.hpp"
#include "nmtools/nmtools.hpp"

#include "kernels/broadcast_to.hpp"

#include <nanobench.h>

namespace nm = nmtools;
using namespace nmtools::literals;

using v128_st = tk::vector::context_t<128>;

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

#define V128_ST_BROADCAST_TO_CASE(case_name, inp_shape, out_shape, src_tile, dst_tile) \
TEST_CASE(#case_name * doctest::test_suite("tilekit")) \
{ \
    auto gen   = nm::random_engine(); \
    auto dtype = nm::float32; \
\
    auto inp = nm::random(inp_shape,dtype,gen); \
    auto out = nm::Array::zeros(out_shape,dtype); \
\
    auto ctx = v128_st(); \
\
    auto min_time = std::chrono::nanoseconds(50'000'000); \
    ankerl::nanobench::Bench() \
        .minEpochTime(min_time) \
        .run(#case_name,[&](){ \
            broadcast_to_kernel(ctx,out,inp,dst_tile,src_tile); \
        }); \
\
    auto expected = nm::broadcast_to(inp,out_shape); \
    NMTOOLS_ASSERT_CLOSE( out, expected ); \
}

V128_ST_BROADCAST_TO_CASE(v128_st.broadcast_to.8.4_8.4.4x4,          make_shape(8),    (make_shape(4,8)),       tuple{4_ct}, (tuple{4_ct,4_ct}) );
V128_ST_BROADCAST_TO_CASE(v128_st.broadcast_to.8_ct.4_8_ct.4.4x4,    make_shape(8_ct), (make_shape(4,8_ct)),    tuple{4_ct}, (tuple{4_ct,4_ct}) );
V128_ST_BROADCAST_TO_CASE(v128_st.broadcast_to.8_ct.4_ct_8_ct.4.4x4, make_shape(8_ct), (make_shape(4_ct,8_ct)), tuple{4_ct}, (tuple{4_ct,4_ct}) );

V128_ST_BROADCAST_TO_CASE(v128_st.broadcast_to.12.4_12.4.4x4,          make_shape(12),    (make_shape(4,12)),       tuple{4_ct}, (tuple{4_ct,4_ct}) );
V128_ST_BROADCAST_TO_CASE(v128_st.broadcast_to.12_ct.4_12_ct.4.4x4,    make_shape(12_ct), (make_shape(4,12_ct)),    tuple{4_ct}, (tuple{4_ct,4_ct}) );
V128_ST_BROADCAST_TO_CASE(v128_st.broadcast_to.12_ct.4_ct_12_ct.4.4x4, make_shape(12_ct), (make_shape(4_ct,12_ct)), tuple{4_ct}, (tuple{4_ct,4_ct}) );

V128_ST_BROADCAST_TO_CASE(v128_st.broadcast_to.12.5_12.4.5x4,          make_shape(12),    (make_shape(5,12)),       tuple{4_ct}, (tuple{5_ct,4_ct}) );
V128_ST_BROADCAST_TO_CASE(v128_st.broadcast_to.12_ct.5_12_ct.4.5x4,    make_shape(12_ct), (make_shape(5,12_ct)),    tuple{4_ct}, (tuple{5_ct,4_ct}) );
V128_ST_BROADCAST_TO_CASE(v128_st.broadcast_to.12_ct.5_ct_12_ct.4.5x4, make_shape(12_ct), (make_shape(5_ct,12_ct)), tuple{4_ct}, (tuple{5_ct,4_ct}) );

V128_ST_BROADCAST_TO_CASE(v128_st.broadcast_to.12.4_12.4.2x4,          make_shape(12),    (make_shape(4,12)),       tuple{4_ct}, (tuple{2_ct,4_ct}) );
V128_ST_BROADCAST_TO_CASE(v128_st.broadcast_to.12_ct.4_12_ct.4.2x4,    make_shape(12_ct), (make_shape(4,12_ct)),    tuple{4_ct}, (tuple{2_ct,4_ct}) );
V128_ST_BROADCAST_TO_CASE(v128_st.broadcast_to.12_ct.4_ct_12_ct.4.2x4, make_shape(12_ct), (make_shape(4_ct,12_ct)), tuple{4_ct}, (tuple{2_ct,4_ct}) );

V128_ST_BROADCAST_TO_CASE(v128_st.broadcast_to.64.5_64.4.4x4,          make_shape(64),    (make_shape(4,64)),       tuple{4_ct}, (tuple{4_ct,4_ct}) );
V128_ST_BROADCAST_TO_CASE(v128_st.broadcast_to.64_ct.5_64_ct.4.4x4,    make_shape(64_ct), (make_shape(4,64_ct)),    tuple{4_ct}, (tuple{4_ct,4_ct}) );
V128_ST_BROADCAST_TO_CASE(v128_st.broadcast_to.64_ct.5_ct_64_ct.4.4x4, make_shape(64_ct), (make_shape(4_ct,64_ct)), tuple{4_ct}, (tuple{4_ct,4_ct}) );

V128_ST_BROADCAST_TO_CASE(v128_st.broadcast_to.64.4_64.4.2x4,          make_shape(64),    (make_shape(4,64)),       tuple{4_ct}, (tuple{2_ct,4_ct}) );
V128_ST_BROADCAST_TO_CASE(v128_st.broadcast_to.64_ct.4_64_ct.4.2x4,    make_shape(64_ct), (make_shape(4,64_ct)),    tuple{4_ct}, (tuple{2_ct,4_ct}) );
V128_ST_BROADCAST_TO_CASE(v128_st.broadcast_to.64_ct.4_ct_64_ct.4.2x4, make_shape(64_ct), (make_shape(4_ct,64_ct)), tuple{4_ct}, (tuple{2_ct,4_ct}) );


V128_ST_BROADCAST_TO_CASE(v128_st.broadcast_to.4_8.2_4_8.4.4x4,             (make_shape(4,8)),       (make_shape(2,4,8)),       (tuple{2_ct,4_ct}), (tuple{2_ct,2_ct,4_ct}) );
V128_ST_BROADCAST_TO_CASE(v128_st.broadcast_to.4_8_ct.2_4_8_ct.4.4x4,       (make_shape(4,8_ct)),    (make_shape(2,4,8_ct)),    (tuple{2_ct,4_ct}), (tuple{2_ct,2_ct,4_ct}) );
V128_ST_BROADCAST_TO_CASE(v128_st.broadcast_to.4_ct_8_ct.2_4_ct_8_ct.4.4x4, (make_shape(4_ct,8_ct)), (make_shape(2,4_ct,8_ct)), (tuple{2_ct,4_ct}), (tuple{2_ct,2_ct,4_ct}) );

// TODO: fix
// V128_ST_BROADCAST_TO_CASE(v128_st.broadcast_to.4_1_8.4_4_8.4.4x4x4, (make_shape(4,1,8)), (make_shape(4,4,8)), (tuple{4_ct,1_ct,8_ct}), (tuple{4_ct,4_ct,8_ct}) );