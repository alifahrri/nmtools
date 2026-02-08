#include "nmtools/tilekit/vector.hpp"
#include "nmtools/tilekit/tilekit.hpp"
#include "nmtools/array/random.hpp"
#include "nmtools/testing/doctest.hpp"

#include "kernels/load_store.hpp"

#include <nanobench.h>

namespace nm = nmtools;
using namespace nmtools::literals;

using v128_st = tk::vector::context_t<128>;
using nmtools_tuple;

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

#define V128_ST_LOAD_STORE_CASE(case_name, shape, tile_shape) \
TEST_CASE(#case_name * doctest::test_suite("tilekit")) \
{ \
    auto gen   = nm::random_engine(); \
    auto dtype = nm::float32; \
\
    auto inp = nm::random(shape,dtype,gen); \
    auto out = nm::Array::zeros(shape,dtype); \
\
    auto ctx = v128_st(); \
\
    auto min_time = std::chrono::nanoseconds(50'000'000); \
    ankerl::nanobench::Bench() \
        .minEpochTime(min_time) \
        .run(#case_name,[&](){ \
            load_store_kernel(ctx,out,inp,tile_shape); \
        }); \
\
    auto expected = inp; \
    NMTOOLS_ASSERT_CLOSE( out, expected ); \
}

#define V128_ST_LOAD_STORE_CASE1(case_name, M, N, tile_m, tile_n) \
TEST_CASE(#case_name * doctest::test_suite("tilekit")) \
{ \
    auto gen   = nm::random_engine(); \
    auto dtype = nm::float32; \
\
    auto inp_shape = make_shape(M,N); \
    auto out_shape = make_shape(M,N); \
\
    auto inp = nm::random(inp_shape,dtype,gen); \
    auto out = nm::Array::zeros(out_shape,dtype); \
\
    auto tile_shape = tuple{tile_m,tile_n}; \
    auto ctx = v128_st(); \
\
    auto min_time = std::chrono::nanoseconds(50'000'000); \
    ankerl::nanobench::Bench() \
        .minEpochTime(min_time) \
        .run(#case_name,[&](){ \
            load_store_kernel(ctx,out,inp,tile_shape); \
        }); \
\
    auto expected = inp; \
    NMTOOLS_ASSERT_CLOSE( out, expected ); \
}

#define V128_ST_LOAD_STORE_CASE2(case_name, M, N, O, tile_m, tile_n, tile_o) \
TEST_CASE(#case_name * doctest::test_suite("tilekit")) \
{ \
    auto gen   = nm::random_engine(); \
    auto dtype = nm::float32; \
\
    auto inp_shape = make_shape(M,N,O); \
    auto out_shape = make_shape(M,N,O); \
\
    auto inp = nm::random(inp_shape,dtype,gen); \
    auto out = nm::Array::zeros(out_shape,dtype); \
\
    auto tile_shape = tuple{tile_m,tile_n,tile_o}; \
    auto ctx = v128_st(); \
\
    auto min_time = std::chrono::nanoseconds(50'000'000); \
    ankerl::nanobench::Bench() \
        .minEpochTime(min_time) \
        .run(#case_name,[&](){ \
            load_store_kernel(ctx,out,inp,tile_shape); \
        }); \
\
    auto expected = inp; \
    NMTOOLS_ASSERT_CLOSE( out, expected ); \
}

V128_ST_LOAD_STORE_CASE(v128_st.load_store.8.fp32.4, (make_shape(8)), (tuple{4_ct}))

V128_ST_LOAD_STORE_CASE(v128_st.load_store.4_8.fp32.2x4, (make_shape(4,8)), (tuple{2_ct,4_ct}))

V128_ST_LOAD_STORE_CASE(v128_st.load_store.8_16.fp32.2x4, (make_shape(8,16)), (tuple{2_ct,4_ct}))

V128_ST_LOAD_STORE_CASE(v128_st.load_store.1024_1024.fp32.2x4, (make_shape(1024,1024)), (tuple{2_ct, 4_ct}))
V128_ST_LOAD_STORE_CASE(v128_st.load_store.1024_1024_ct.fp32.2x4, (make_shape(1024,1024_ct)), (tuple{2_ct, 4_ct}))
// TODO: make zeros to fallback to dynamic buffer if size > some threshold
// V128_ST_LOAD_STORE_CASE(v128_st.load_store.1024_ct_1024_ct.fp32.2x4, (make_shape(1024_ct,1024_ct)), (tuple{2_ct, 4_ct}))
V128_ST_LOAD_STORE_CASE(v128_st.load_store.1024_ct_1024.fp32.2x4, (make_shape(1024_ct,1024)), (tuple{2_ct, 4_ct}))

V128_ST_LOAD_STORE_CASE(v128_st.load_store.4_2_8.fp32.2x4, (make_shape(4,2,8)), (tuple{1_ct,2_ct,4_ct}))
V128_ST_LOAD_STORE_CASE(v128_st.load_store.4_2_8_ct.fp32.2x4, (make_shape(4,2,8_ct)), (tuple{1_ct,2_ct,4_ct}))
V128_ST_LOAD_STORE_CASE(v128_st.load_store.4_2_ct_8_ct.fp32.2x4, (make_shape(4,2_ct,8_ct)), (tuple{1_ct,2_ct,4_ct}))
V128_ST_LOAD_STORE_CASE(v128_st.load_store.4_ct_2_ct_8_ct.fp32.2x4, (make_shape(4_ct,2_ct,8_ct)), (tuple{1_ct,2_ct,4_ct}))
V128_ST_LOAD_STORE_CASE(v128_st.load_store.4_ct_2_ct_8.fp32.2x4, (make_shape(4_ct,2_ct,8)), (tuple{1_ct,2_ct,4_ct}))
V128_ST_LOAD_STORE_CASE(v128_st.load_store.4_ct_2_8.fp32.2x4, (make_shape(4_ct,2,8)), (tuple{1_ct,2_ct,4_ct}))

V128_ST_LOAD_STORE_CASE(v128_st.load_store.4_1_8.fp32.2x4, (make_shape(4,1,8)), (tuple{2_ct,1_ct,4_ct}))
V128_ST_LOAD_STORE_CASE(v128_st.load_store.4_1_8_ct.fp32.2x4, (make_shape(4,1,8_ct)), (tuple{2_ct,1_ct,4_ct}))
V128_ST_LOAD_STORE_CASE(v128_st.load_store.4_1_ct_8_ct.fp32.2x4, (make_shape(4,1_ct,8_ct)), (tuple{2_ct,1_ct,4_ct}))
V128_ST_LOAD_STORE_CASE(v128_st.load_store.4_ct_1_ct_8_ct.fp32.2x4, (make_shape(4_ct,1_ct,8_ct)), (tuple{2_ct,1_ct,4_ct}))
V128_ST_LOAD_STORE_CASE(v128_st.load_store.4_ct_1_ct_8.fp32.2x4, (make_shape(4_ct,1_ct,8)), (tuple{2_ct,1_ct,4_ct}))
V128_ST_LOAD_STORE_CASE(v128_st.load_store.4_ct_1_8.fp32.2x4, (make_shape(4_ct,1,8)), (tuple{2_ct,1_ct,4_ct}))