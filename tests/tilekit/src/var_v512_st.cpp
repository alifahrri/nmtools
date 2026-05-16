#include "nmtools/tilekit/vector.hpp"
#include "nmtools/tilekit/thread_pool.hpp"
#include "nmtools/tilekit/tilekit.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/ndarray.hpp"

#include "kernels/var.hpp"

#include <nanobench.h>

#undef NMTOOLS_TESTING_PRECISION
#define NMTOOLS_TESTING_PRECISION (1e-2)

namespace nm = nmtools;
using namespace nmtools::literals;
using nmtools_tuple;

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

#define V512_ST_VAR_CASE( case_name, shape, out_shape, tile_shape, axis ) \
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
            var_kernel(ctx,out,inp,tk::index(tile_shape),axis); \
        }); \
    auto expected = nm::var(inp,axis); \
    NMTOOLS_ASSERT_CLOSE( out, expected ); \
}

V512_ST_VAR_CASE(v512_st.var.16_32.16.fp32.16x16,   (make_shape(16,32)),   make_shape(16), (tuple{16_ct,16_ct}), nm::ct_v<-1> );
V512_ST_VAR_CASE(v512_st.var.16_64.16.fp32.16x16,   (make_shape(16,64)),   make_shape(16), (tuple{16_ct,16_ct}), nm::ct_v<-1> );
V512_ST_VAR_CASE(v512_st.var.16_128.16.fp32.16x16,  (make_shape(16,128)),  make_shape(16), (tuple{16_ct,16_ct}), nm::ct_v<-1> );
V512_ST_VAR_CASE(v512_st.var.16_256.16.fp32.16x16,  (make_shape(16,256)),  make_shape(16), (tuple{16_ct,16_ct}), nm::ct_v<-1> );
V512_ST_VAR_CASE(v512_st.var.16_512.16.fp32.16x16,  (make_shape(16,512)),  make_shape(16), (tuple{16_ct,16_ct}), nm::ct_v<-1> );
V512_ST_VAR_CASE(v512_st.var.16_1024.16.fp32.16x16, (make_shape(16,1024)), make_shape(16), (tuple{16_ct,16_ct}), nm::ct_v<-1> );
V512_ST_VAR_CASE(v512_st.var.16_2048.16.fp32.16x16, (make_shape(16,2048)), make_shape(16), (tuple{16_ct,16_ct}), nm::ct_v<-1> );

V512_ST_VAR_CASE(v512_st.var.16_ct_32_ct.16_ct.fp32.16x16,   (make_shape(16_ct,32_ct)),   make_shape(16_ct), (tuple{16_ct,16_ct}), nm::ct_v<-1> );
V512_ST_VAR_CASE(v512_st.var.16_ct_64_ct.16_ct.fp32.16x16,   (make_shape(16_ct,64_ct)),   make_shape(16_ct), (tuple{16_ct,16_ct}), nm::ct_v<-1> );
V512_ST_VAR_CASE(v512_st.var.16_ct_128_ct.16_ct.fp32.16x16,  (make_shape(16_ct,128_ct)),  make_shape(16_ct), (tuple{16_ct,16_ct}), nm::ct_v<-1> );
V512_ST_VAR_CASE(v512_st.var.16_ct_256_ct.16_ct.fp32.16x16,  (make_shape(16_ct,256_ct)),  make_shape(16_ct), (tuple{16_ct,16_ct}), nm::ct_v<-1> );
V512_ST_VAR_CASE(v512_st.var.16_ct_512_ct.16_ct.fp32.16x16,  (make_shape(16_ct,512_ct)),  make_shape(16_ct), (tuple{16_ct,16_ct}), nm::ct_v<-1> );
V512_ST_VAR_CASE(v512_st.var.16_ct_1024_ct.16_ct.fp32.16x16, (make_shape(16_ct,1024_ct)), make_shape(16_ct), (tuple{16_ct,16_ct}), nm::ct_v<-1> );
V512_ST_VAR_CASE(v512_st.var.16_ct_2048_ct.16_ct.fp32.16x16, (make_shape(16_ct,2048_ct)), make_shape(16_ct), (tuple{16_ct,16_ct}), nm::ct_v<-1> );

V512_ST_VAR_CASE(v512_st.var.16_32.32.fp32.16x16,   (make_shape(16,32)),   make_shape(32),   (tuple{16_ct,16_ct}), nm::ct_v<0> );
V512_ST_VAR_CASE(v512_st.var.16_64.64.fp32.16x16,   (make_shape(16,64)),   make_shape(64),   (tuple{16_ct,16_ct}), nm::ct_v<0> );
V512_ST_VAR_CASE(v512_st.var.16_128.128.fp32.16x16, (make_shape(16,128)),  make_shape(128),  (tuple{16_ct,16_ct}), nm::ct_v<0> );
V512_ST_VAR_CASE(v512_st.var.16_256.256.fp32.16x16, (make_shape(16,256)),  make_shape(256),  (tuple{16_ct,16_ct}), nm::ct_v<0> );
V512_ST_VAR_CASE(v512_st.var.16_512.512.fp32.16x16, (make_shape(16,512)),  make_shape(512),  (tuple{16_ct,16_ct}), nm::ct_v<0> );
V512_ST_VAR_CASE(v512_st.var.16_1024.1024.fp32.16x16, (make_shape(16,1024)), make_shape(1024), (tuple{16_ct,16_ct}), nm::ct_v<0> );
V512_ST_VAR_CASE(v512_st.var.16_2048.2048.fp32.16x16, (make_shape(16,2048)), make_shape(2048), (tuple{16_ct,16_ct}), nm::ct_v<0> );

V512_ST_VAR_CASE(v512_st.var.16_ct_32_ct.32_ct.fp32.16x16,   (make_shape(16_ct,32_ct)),   make_shape(32_ct),   (tuple{16_ct,16_ct}), nm::ct_v<0> );
V512_ST_VAR_CASE(v512_st.var.16_ct_64_ct.64_ct.fp32.16x16,   (make_shape(16_ct,64_ct)),   make_shape(64_ct),   (tuple{16_ct,16_ct}), nm::ct_v<0> );
V512_ST_VAR_CASE(v512_st.var.16_ct_128_ct.128_ct.fp32.16x16, (make_shape(16_ct,128_ct)),  make_shape(128_ct),  (tuple{16_ct,16_ct}), nm::ct_v<0> );
V512_ST_VAR_CASE(v512_st.var.16_ct_256_ct.256_ct.fp32.16x16, (make_shape(16_ct,256_ct)),  make_shape(256_ct),  (tuple{16_ct,16_ct}), nm::ct_v<0> );
V512_ST_VAR_CASE(v512_st.var.16_ct_512_ct.512_ct.fp32.16x16, (make_shape(16_ct,512_ct)),  make_shape(512_ct),  (tuple{16_ct,16_ct}), nm::ct_v<0> );
V512_ST_VAR_CASE(v512_st.var.16_ct_1024_ct.1024_ct.fp32.16x16, (make_shape(16_ct,1024_ct)), make_shape(1024_ct), (tuple{16_ct,16_ct}), nm::ct_v<0> );
V512_ST_VAR_CASE(v512_st.var.16_ct_2048_ct.2048_ct.fp32.16x16, (make_shape(16_ct,2048_ct)), make_shape(2048_ct), (tuple{16_ct,16_ct}), nm::ct_v<0> );
