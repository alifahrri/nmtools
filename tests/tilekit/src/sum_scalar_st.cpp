#include "nmtools/tilekit/vector.hpp"
#include "nmtools/tilekit/thread_pool.hpp"
#include "nmtools/tilekit/tilekit.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/ndarray.hpp"

#include "kernels/sum.hpp"

#include <nanobench.h>

// due to different ordering of summation, the result may be different
// especially on big array
#undef NMTOOLS_TESTING_PRECISION
#define NMTOOLS_TESTING_PRECISION (1e-2)

namespace nm = nmtools;
using namespace nmtools::literals;
using nmtools_tuple;

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

#define SCALAR_SUM_CASE( case_name, shape, out_shape, tile_shape, axis ) \
TEST_CASE(#case_name * doctest::test_suite("tilekit")) \
{ \
    auto gen = nm::random_engine(); \
    auto dtype = nm::float32; \
\
    auto inp = nm::random(shape,dtype,gen); \
    auto out = nm::Array::zeros(out_shape,dtype); \
\
    auto ctx = scalar_st(); \
\
    auto min_time = std::chrono::nanoseconds(50'000'000); \
    ankerl::nanobench::Bench() \
        .minEpochTime(min_time) \
        .run(#case_name,[&](){ \
            sum_kernel(ctx,out,inp,tk::index(tile_shape),axis); \
        }); \
\
    auto expected = nm::sum(inp,axis); \
    NMTOOLS_ASSERT_CLOSE( out, expected ); \
}

SCALAR_SUM_CASE(scalar_st.sum.2_8.2.fp32.2x4,    (make_shape(2,8)),    make_shape(2), (tuple{2_ct,4_ct}), nm::ct_v<-1> );
SCALAR_SUM_CASE(scalar_st.sum.2_16.2.fp32.2x4,   (make_shape(2,16)),   make_shape(2), (tuple{2_ct,4_ct}), nm::ct_v<-1> );
SCALAR_SUM_CASE(scalar_st.sum.2_32.2.fp32.2x4,   (make_shape(2,32)),   make_shape(2), (tuple{2_ct,4_ct}), nm::ct_v<-1> );
SCALAR_SUM_CASE(scalar_st.sum.2_64.2.fp32.2x4,   (make_shape(2,64)),   make_shape(2), (tuple{2_ct,4_ct}), nm::ct_v<-1> );
SCALAR_SUM_CASE(scalar_st.sum.2_128.2.fp32.2x4,  (make_shape(2,128)),  make_shape(2), (tuple{2_ct,4_ct}), nm::ct_v<-1> );
SCALAR_SUM_CASE(scalar_st.sum.2_256.2.fp32.2x4,  (make_shape(2,256)),  make_shape(2), (tuple{2_ct,4_ct}), nm::ct_v<-1> );
SCALAR_SUM_CASE(scalar_st.sum.2_512.2.fp32.2x4,  (make_shape(2,512)),  make_shape(2), (tuple{2_ct,4_ct}), nm::ct_v<-1> );
SCALAR_SUM_CASE(scalar_st.sum.2_1024.2.fp32.2x4, (make_shape(2,1024)), make_shape(2), (tuple{2_ct,4_ct}), nm::ct_v<-1> );
SCALAR_SUM_CASE(scalar_st.sum.2_2048.2.fp32.2x4, (make_shape(2,2048)), make_shape(2), (tuple{2_ct,4_ct}), nm::ct_v<-1> );

SCALAR_SUM_CASE(scalar_st.sum.2_ct_8_ct.2_ct.fp32.2x4,    (make_shape(2_ct,8_ct)),    make_shape(2_ct), (tuple{2_ct,4_ct}), nm::ct_v<-1> );
SCALAR_SUM_CASE(scalar_st.sum.2_ct_16_ct.2_ct.fp32.2x4,   (make_shape(2_ct,16_ct)),   make_shape(2_ct), (tuple{2_ct,4_ct}), nm::ct_v<-1> );
SCALAR_SUM_CASE(scalar_st.sum.2_ct_32_ct.2_ct.fp32.2x4,   (make_shape(2_ct,32_ct)),   make_shape(2_ct), (tuple{2_ct,4_ct}), nm::ct_v<-1> );
SCALAR_SUM_CASE(scalar_st.sum.2_ct_64_ct.2_ct.fp32.2x4,   (make_shape(2_ct,64_ct)),   make_shape(2_ct), (tuple{2_ct,4_ct}), nm::ct_v<-1> );
SCALAR_SUM_CASE(scalar_st.sum.2_ct_128_ct.2_ct.fp32.2x4,  (make_shape(2_ct,128_ct)),  make_shape(2_ct), (tuple{2_ct,4_ct}), nm::ct_v<-1> );
SCALAR_SUM_CASE(scalar_st.sum.2_ct_256_ct.2_ct.fp32.2x4,  (make_shape(2_ct,256_ct)),  make_shape(2_ct), (tuple{2_ct,4_ct}), nm::ct_v<-1> );
SCALAR_SUM_CASE(scalar_st.sum.2_ct_512_ct.2_ct.fp32.2x4,  (make_shape(2_ct,512_ct)),  make_shape(2_ct), (tuple{2_ct,4_ct}), nm::ct_v<-1> );
SCALAR_SUM_CASE(scalar_st.sum.2_ct_1024_ct.2_ct.fp32.2x4, (make_shape(2_ct,1024_ct)), make_shape(2_ct), (tuple{2_ct,4_ct}), nm::ct_v<-1> );
SCALAR_SUM_CASE(scalar_st.sum.2_ct_2048_ct.2_ct.fp32.2x4, (make_shape(2_ct,2048_ct)), make_shape(2_ct), (tuple{2_ct,4_ct}), nm::ct_v<-1> );

SCALAR_SUM_CASE(scalar_st.sum.4_8.4.fp32.2x4,    (make_shape(4,8)),    make_shape(4), (tuple{2_ct,4_ct}), nm::ct_v<-1> );
SCALAR_SUM_CASE(scalar_st.sum.4_16.4.fp32.2x4,   (make_shape(4,16)),   make_shape(4), (tuple{2_ct,4_ct}), nm::ct_v<-1> );
SCALAR_SUM_CASE(scalar_st.sum.4_32.4.fp32.2x4,   (make_shape(4,32)),   make_shape(4), (tuple{2_ct,4_ct}), nm::ct_v<-1> );
SCALAR_SUM_CASE(scalar_st.sum.4_64.4.fp32.2x4,   (make_shape(4,64)),   make_shape(4), (tuple{2_ct,4_ct}), nm::ct_v<-1> );
SCALAR_SUM_CASE(scalar_st.sum.4_128.4.fp32.2x4,  (make_shape(4,128)),  make_shape(4), (tuple{2_ct,4_ct}), nm::ct_v<-1> );
SCALAR_SUM_CASE(scalar_st.sum.4_256.4.fp32.2x4,  (make_shape(4,256)),  make_shape(4), (tuple{2_ct,4_ct}), nm::ct_v<-1> );
SCALAR_SUM_CASE(scalar_st.sum.4_512.4.fp32.2x4,  (make_shape(4,512)),  make_shape(4), (tuple{2_ct,4_ct}), nm::ct_v<-1> );
SCALAR_SUM_CASE(scalar_st.sum.4_1024.4.fp32.2x4, (make_shape(4,1024)), make_shape(4), (tuple{2_ct,4_ct}), nm::ct_v<-1> );
SCALAR_SUM_CASE(scalar_st.sum.4_2048.4.fp32.2x4, (make_shape(4,2048)), make_shape(4), (tuple{2_ct,4_ct}), nm::ct_v<-1> );

SCALAR_SUM_CASE(scalar_st.sum.4_ct_8_ct.4_ct.fp32.2x4,    (make_shape(4_ct,8_ct)),    make_shape(4_ct), (tuple{2_ct,4_ct}), nm::ct_v<-1> );
SCALAR_SUM_CASE(scalar_st.sum.4_ct_16_ct.4_ct.fp32.2x4,   (make_shape(4_ct,16_ct)),   make_shape(4_ct), (tuple{2_ct,4_ct}), nm::ct_v<-1> );
SCALAR_SUM_CASE(scalar_st.sum.4_ct_32_ct.4_ct.fp32.2x4,   (make_shape(4_ct,32_ct)),   make_shape(4_ct), (tuple{2_ct,4_ct}), nm::ct_v<-1> );
SCALAR_SUM_CASE(scalar_st.sum.4_ct_64_ct.4_ct.fp32.2x4,   (make_shape(4_ct,64_ct)),   make_shape(4_ct), (tuple{2_ct,4_ct}), nm::ct_v<-1> );
SCALAR_SUM_CASE(scalar_st.sum.4_ct_128_ct.4_ct.fp32.2x4,  (make_shape(4_ct,128_ct)),  make_shape(4_ct), (tuple{2_ct,4_ct}), nm::ct_v<-1> );
SCALAR_SUM_CASE(scalar_st.sum.4_ct_256_ct.4_ct.fp32.2x4,  (make_shape(4_ct,256_ct)),  make_shape(4_ct), (tuple{2_ct,4_ct}), nm::ct_v<-1> );
SCALAR_SUM_CASE(scalar_st.sum.4_ct_512_ct.4_ct.fp32.2x4,  (make_shape(4_ct,512_ct)),  make_shape(4_ct), (tuple{2_ct,4_ct}), nm::ct_v<-1> );
SCALAR_SUM_CASE(scalar_st.sum.4_ct_1024_ct.4_ct.fp32.2x4, (make_shape(4_ct,1024_ct)), make_shape(4_ct), (tuple{2_ct,4_ct}), nm::ct_v<-1> );
SCALAR_SUM_CASE(scalar_st.sum.4_ct_2048_ct.4_ct.fp32.2x4, (make_shape(4_ct,2048_ct)), make_shape(4_ct), (tuple{2_ct,4_ct}), nm::ct_v<-1> );

SCALAR_SUM_CASE(scalar_st.sum.2_8.8.fp32.2x4,       (make_shape(2,8)),    make_shape(8),    (tuple{2_ct,4_ct}), nm::ct_v<0> );
SCALAR_SUM_CASE(scalar_st.sum.2_16.16.fp32.2x4,     (make_shape(2,16)),   make_shape(16),   (tuple{2_ct,4_ct}), nm::ct_v<0> );
SCALAR_SUM_CASE(scalar_st.sum.2_32.32.fp32.2x4,     (make_shape(2,32)),   make_shape(32),   (tuple{2_ct,4_ct}), nm::ct_v<0> );
SCALAR_SUM_CASE(scalar_st.sum.2_64.64.fp32.2x4,     (make_shape(2,64)),   make_shape(64),   (tuple{2_ct,4_ct}), nm::ct_v<0> );
SCALAR_SUM_CASE(scalar_st.sum.2_128.128.fp32.2x4,   (make_shape(2,128)),  make_shape(128),  (tuple{2_ct,4_ct}), nm::ct_v<0> );
SCALAR_SUM_CASE(scalar_st.sum.2_256.256.fp32.2x4,   (make_shape(2,256)),  make_shape(256),  (tuple{2_ct,4_ct}), nm::ct_v<0> );
SCALAR_SUM_CASE(scalar_st.sum.2_512.512.fp32.2x4,   (make_shape(2,512)),  make_shape(512),  (tuple{2_ct,4_ct}), nm::ct_v<0> );
SCALAR_SUM_CASE(scalar_st.sum.2_1024.1024.fp32.2x4, (make_shape(2,1024)), make_shape(1024), (tuple{2_ct,4_ct}), nm::ct_v<0> );
SCALAR_SUM_CASE(scalar_st.sum.2_2048.2048.fp32.2x4, (make_shape(2,2048)), make_shape(2048), (tuple{2_ct,4_ct}), nm::ct_v<0> );

SCALAR_SUM_CASE(scalar_st.sum.2_ct_8_ct.8_ct.fp32.2x4,       (make_shape(2_ct,8_ct)),    make_shape(8_ct),    (tuple{2_ct,4_ct}), nm::ct_v<0> );
SCALAR_SUM_CASE(scalar_st.sum.2_ct_16_ct.16_ct.fp32.2x4,     (make_shape(2_ct,16_ct)),   make_shape(16_ct),   (tuple{2_ct,4_ct}), nm::ct_v<0> );
SCALAR_SUM_CASE(scalar_st.sum.2_ct_32_ct.32_ct.fp32.2x4,     (make_shape(2_ct,32_ct)),   make_shape(32_ct),   (tuple{2_ct,4_ct}), nm::ct_v<0> );
SCALAR_SUM_CASE(scalar_st.sum.2_ct_64_ct.64_ct.fp32.2x4,     (make_shape(2_ct,64_ct)),   make_shape(64_ct),   (tuple{2_ct,4_ct}), nm::ct_v<0> );
SCALAR_SUM_CASE(scalar_st.sum.2_ct_128_ct.128_ct.fp32.2x4,   (make_shape(2_ct,128_ct)),  make_shape(128_ct),  (tuple{2_ct,4_ct}), nm::ct_v<0> );
SCALAR_SUM_CASE(scalar_st.sum.2_ct_256_ct.256_ct.fp32.2x4,   (make_shape(2_ct,256_ct)),  make_shape(256_ct),  (tuple{2_ct,4_ct}), nm::ct_v<0> );
SCALAR_SUM_CASE(scalar_st.sum.2_ct_512_ct.512_ct.fp32.2x4,   (make_shape(2_ct,512_ct)),  make_shape(512_ct),  (tuple{2_ct,4_ct}), nm::ct_v<0> );
SCALAR_SUM_CASE(scalar_st.sum.2_ct_1024_ct.1024_ct.fp32.2x4, (make_shape(2_ct,1024_ct)), make_shape(1024_ct), (tuple{2_ct,4_ct}), nm::ct_v<0> );
SCALAR_SUM_CASE(scalar_st.sum.2_ct_2048_ct.2048_ct.fp32.2x4, (make_shape(2_ct,2048_ct)), make_shape(2048_ct), (tuple{2_ct,4_ct}), nm::ct_v<0> );

SCALAR_SUM_CASE(scalar_st.sum.4_8.8.fp32.2x4,       (make_shape(4,8)),    make_shape(8),    (tuple{2_ct,4_ct}), nm::ct_v<0> );
SCALAR_SUM_CASE(scalar_st.sum.4_16.16.fp32.2x4,     (make_shape(4,16)),   make_shape(16),   (tuple{2_ct,4_ct}), nm::ct_v<0> );
SCALAR_SUM_CASE(scalar_st.sum.4_32.32.fp32.2x4,     (make_shape(4,32)),   make_shape(32),   (tuple{2_ct,4_ct}), nm::ct_v<0> );
SCALAR_SUM_CASE(scalar_st.sum.4_64.64.fp32.2x4,     (make_shape(4,64)),   make_shape(64),   (tuple{2_ct,4_ct}), nm::ct_v<0> );
SCALAR_SUM_CASE(scalar_st.sum.4_128.128.fp32.2x4,   (make_shape(4,128)),  make_shape(128),  (tuple{2_ct,4_ct}), nm::ct_v<0> );
SCALAR_SUM_CASE(scalar_st.sum.4_256.256.fp32.2x4,   (make_shape(4,256)),  make_shape(256),  (tuple{2_ct,4_ct}), nm::ct_v<0> );
SCALAR_SUM_CASE(scalar_st.sum.4_512.512.fp32.2x4,   (make_shape(4,512)),  make_shape(512),  (tuple{2_ct,4_ct}), nm::ct_v<0> );
SCALAR_SUM_CASE(scalar_st.sum.4_1024.1024.fp32.2x4, (make_shape(4,1024)), make_shape(1024), (tuple{2_ct,4_ct}), nm::ct_v<0> );
SCALAR_SUM_CASE(scalar_st.sum.4_2048.2048.fp32.2x4, (make_shape(4,2048)), make_shape(2048), (tuple{2_ct,4_ct}), nm::ct_v<0> );

SCALAR_SUM_CASE(scalar_st.sum.4_8.8.fp32.2x4,       (make_shape(4_ct,8_ct)),    make_shape(8_ct),    (tuple{2_ct,4_ct}), nm::ct_v<0> );
SCALAR_SUM_CASE(scalar_st.sum.4_16.16.fp32.2x4,     (make_shape(4_ct,16_ct)),   make_shape(16_ct),   (tuple{2_ct,4_ct}), nm::ct_v<0> );
SCALAR_SUM_CASE(scalar_st.sum.4_32.32.fp32.2x4,     (make_shape(4_ct,32_ct)),   make_shape(32_ct),   (tuple{2_ct,4_ct}), nm::ct_v<0> );
SCALAR_SUM_CASE(scalar_st.sum.4_64.64.fp32.2x4,     (make_shape(4_ct,64_ct)),   make_shape(64_ct),   (tuple{2_ct,4_ct}), nm::ct_v<0> );
SCALAR_SUM_CASE(scalar_st.sum.4_128.128.fp32.2x4,   (make_shape(4_ct,128_ct)),  make_shape(128_ct),  (tuple{2_ct,4_ct}), nm::ct_v<0> );
SCALAR_SUM_CASE(scalar_st.sum.4_256.256.fp32.2x4,   (make_shape(4_ct,256_ct)),  make_shape(256_ct),  (tuple{2_ct,4_ct}), nm::ct_v<0> );
SCALAR_SUM_CASE(scalar_st.sum.4_512.512.fp32.2x4,   (make_shape(4_ct,512_ct)),  make_shape(512_ct),  (tuple{2_ct,4_ct}), nm::ct_v<0> );
SCALAR_SUM_CASE(scalar_st.sum.4_1024.1024.fp32.2x4, (make_shape(4_ct,1024_ct)), make_shape(1024_ct), (tuple{2_ct,4_ct}), nm::ct_v<0> );
SCALAR_SUM_CASE(scalar_st.sum.4_2048.2048.fp32.2x4, (make_shape(4_ct,2048_ct)), make_shape(2048_ct), (tuple{2_ct,4_ct}), nm::ct_v<0> );