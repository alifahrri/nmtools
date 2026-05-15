#include "nmtools/tilekit/vector.hpp"
#include "nmtools/tilekit/thread_pool.hpp"
#include "nmtools/tilekit/tilekit.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/ndarray.hpp"

#include "kernels/std.hpp"

#include <nanobench.h>

#undef NMTOOLS_TESTING_PRECISION
#define NMTOOLS_TESTING_PRECISION (1e-2)

namespace nm = nmtools;
using namespace nmtools::literals;
using nmtools_tuple;

using ctx_t = tk::vector::context_t<256>;

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

#define V256_ST_STD_CASE( case_name, shape, out_shape, tile_shape, axis ) \
TEST_CASE(#case_name * doctest::test_suite("tilekit")) \
{ \
    auto gen   = nm::random_engine(); \
    auto dtype = nm::float32; \
\
    auto inp = nm::random(shape,dtype,gen); \
    auto out = nm::Array::zeros(out_shape,dtype); \
\
    auto ctx = ctx_t(); \
\
    auto min_time = std::chrono::nanoseconds(50'000'000); \
    ankerl::nanobench::Bench() \
        .minEpochTime(min_time) \
        .run(#case_name,[&](){ \
            std_kernel(ctx,out,inp,tk::index(tile_shape),axis); \
        }); \
    auto expected = nm::std(inp,axis); \
    NMTOOLS_ASSERT_CLOSE( out, expected ); \
}

V256_ST_STD_CASE(v256_st.std.8_16.8.fp32.8x8,   (make_shape(8,16)),   make_shape(8), (tuple{8_ct,8_ct}), nm::ct_v<-1> );
V256_ST_STD_CASE(v256_st.std.8_32.8.fp32.8x8,   (make_shape(8,32)),   make_shape(8), (tuple{8_ct,8_ct}), nm::ct_v<-1> );
V256_ST_STD_CASE(v256_st.std.8_64.8.fp32.8x8,   (make_shape(8,64)),   make_shape(8), (tuple{8_ct,8_ct}), nm::ct_v<-1> );
V256_ST_STD_CASE(v256_st.std.8_128.8.fp32.8x8,  (make_shape(8,128)),  make_shape(8), (tuple{8_ct,8_ct}), nm::ct_v<-1> );
V256_ST_STD_CASE(v256_st.std.8_256.8.fp32.8x8,  (make_shape(8,256)),  make_shape(8), (tuple{8_ct,8_ct}), nm::ct_v<-1> );
V256_ST_STD_CASE(v256_st.std.8_512.8.fp32.8x8,  (make_shape(8,512)),  make_shape(8), (tuple{8_ct,8_ct}), nm::ct_v<-1> );
V256_ST_STD_CASE(v256_st.std.8_1024.8.fp32.8x8, (make_shape(8,1024)), make_shape(8), (tuple{8_ct,8_ct}), nm::ct_v<-1> );
V256_ST_STD_CASE(v256_st.std.8_2048.8.fp32.8x8, (make_shape(8,2048)), make_shape(8), (tuple{8_ct,8_ct}), nm::ct_v<-1> );

V256_ST_STD_CASE(v256_st.std.8_ct_16_ct.8_ct.fp32.8x8,   (make_shape(8_ct,16_ct)),   make_shape(8_ct), (tuple{8_ct,8_ct}), nm::ct_v<-1> );
V256_ST_STD_CASE(v256_st.std.8_ct_32_ct.8_ct.fp32.8x8,   (make_shape(8_ct,32_ct)),   make_shape(8_ct), (tuple{8_ct,8_ct}), nm::ct_v<-1> );
V256_ST_STD_CASE(v256_st.std.8_ct_64_ct.8_ct.fp32.8x8,   (make_shape(8_ct,64_ct)),   make_shape(8_ct), (tuple{8_ct,8_ct}), nm::ct_v<-1> );
V256_ST_STD_CASE(v256_st.std.8_ct_128_ct.8_ct.fp32.8x8,  (make_shape(8_ct,128_ct)),  make_shape(8_ct), (tuple{8_ct,8_ct}), nm::ct_v<-1> );
V256_ST_STD_CASE(v256_st.std.8_ct_256_ct.8_ct.fp32.8x8,  (make_shape(8_ct,256_ct)),  make_shape(8_ct), (tuple{8_ct,8_ct}), nm::ct_v<-1> );
V256_ST_STD_CASE(v256_st.std.8_ct_512_ct.8_ct.fp32.8x8,  (make_shape(8_ct,512_ct)),  make_shape(8_ct), (tuple{8_ct,8_ct}), nm::ct_v<-1> );
V256_ST_STD_CASE(v256_st.std.8_ct_1024_ct.8_ct.fp32.8x8, (make_shape(8_ct,1024_ct)), make_shape(8_ct), (tuple{8_ct,8_ct}), nm::ct_v<-1> );
V256_ST_STD_CASE(v256_st.std.8_ct_2048_ct.8_ct.fp32.8x8, (make_shape(8_ct,2048_ct)), make_shape(8_ct), (tuple{8_ct,8_ct}), nm::ct_v<-1> );

V256_ST_STD_CASE(v256_st.std.8_16.16.fp32.8x8,   (make_shape(8,16)),   make_shape(16),   (tuple{8_ct,8_ct}), nm::ct_v<0> );
V256_ST_STD_CASE(v256_st.std.8_32.32.fp32.8x8,   (make_shape(8,32)),   make_shape(32),   (tuple{8_ct,8_ct}), nm::ct_v<0> );
V256_ST_STD_CASE(v256_st.std.8_64.64.fp32.8x8,   (make_shape(8,64)),   make_shape(64),   (tuple{8_ct,8_ct}), nm::ct_v<0> );
V256_ST_STD_CASE(v256_st.std.8_128.128.fp32.8x8, (make_shape(8,128)),  make_shape(128),  (tuple{8_ct,8_ct}), nm::ct_v<0> );
V256_ST_STD_CASE(v256_st.std.8_256.256.fp32.8x8, (make_shape(8,256)),  make_shape(256),  (tuple{8_ct,8_ct}), nm::ct_v<0> );
V256_ST_STD_CASE(v256_st.std.8_512.512.fp32.8x8, (make_shape(8,512)),  make_shape(512),  (tuple{8_ct,8_ct}), nm::ct_v<0> );
V256_ST_STD_CASE(v256_st.std.8_1024.1024.fp32.8x8, (make_shape(8,1024)), make_shape(1024), (tuple{8_ct,8_ct}), nm::ct_v<0> );
V256_ST_STD_CASE(v256_st.std.8_2048.2048.fp32.8x8, (make_shape(8,2048)), make_shape(2048), (tuple{8_ct,8_ct}), nm::ct_v<0> );

V256_ST_STD_CASE(v256_st.std.8_ct_16_ct.16_ct.fp32.8x8,   (make_shape(8_ct,16_ct)),   make_shape(16_ct),   (tuple{8_ct,8_ct}), nm::ct_v<0> );
V256_ST_STD_CASE(v256_st.std.8_ct_32_ct.32_ct.fp32.8x8,   (make_shape(8_ct,32_ct)),   make_shape(32_ct),   (tuple{8_ct,8_ct}), nm::ct_v<0> );
V256_ST_STD_CASE(v256_st.std.8_ct_64_ct.64_ct.fp32.8x8,   (make_shape(8_ct,64_ct)),   make_shape(64_ct),   (tuple{8_ct,8_ct}), nm::ct_v<0> );
V256_ST_STD_CASE(v256_st.std.8_ct_128_ct.128_ct.fp32.8x8, (make_shape(8_ct,128_ct)),  make_shape(128_ct),  (tuple{8_ct,8_ct}), nm::ct_v<0> );
V256_ST_STD_CASE(v256_st.std.8_ct_256_ct.256_ct.fp32.8x8, (make_shape(8_ct,256_ct)),  make_shape(256_ct),  (tuple{8_ct,8_ct}), nm::ct_v<0> );
V256_ST_STD_CASE(v256_st.std.8_ct_512_ct.512_ct.fp32.8x8, (make_shape(8_ct,512_ct)),  make_shape(512_ct),  (tuple{8_ct,8_ct}), nm::ct_v<0> );
V256_ST_STD_CASE(v256_st.std.8_ct_1024_ct.1024_ct.fp32.8x8, (make_shape(8_ct,1024_ct)), make_shape(1024_ct), (tuple{8_ct,8_ct}), nm::ct_v<0> );
V256_ST_STD_CASE(v256_st.std.8_ct_2048_ct.2048_ct.fp32.8x8, (make_shape(8_ct,2048_ct)), make_shape(2048_ct), (tuple{8_ct,8_ct}), nm::ct_v<0> );
