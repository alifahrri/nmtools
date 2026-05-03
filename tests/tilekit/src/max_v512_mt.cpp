#include "nmtools/tilekit/vector.hpp"
#include "nmtools/tilekit/thread_pool.hpp"
#include "nmtools/tilekit/tilekit.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/ndarray.hpp"

#include "kernels/max.hpp"

#include <nanobench.h>

// due to different ordering of maxmation, the result may be different
// especially on big array
#undef NMTOOLS_TESTING_PRECISION
#define NMTOOLS_TESTING_PRECISION (1e-2)

namespace nm = nmtools;
using namespace nmtools::literals;
using nmtools_tuple;

using ctx_t = tk::thread_pool<tk::vector::context_t<512>>;

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

#define V512_MT_MAX_CASE(case_name, shape, out_shape, tile_shape, axis, num_threads) \
TEST_CASE(#case_name * doctest::test_suite("tilekit")) \
{ \
    auto gen   = nm::random_engine(); \
    auto dtype = nm::float32; \
\
    auto inp = nm::random(shape,dtype,gen); \
    auto out = nm::Array::zeros(out_shape,dtype); \
\
    auto ctx = ctx_t(num_threads); \
    auto worker_size = num_threads; \
\
    auto min_time = std::chrono::nanoseconds(50'000'000); \
    ankerl::nanobench::Bench() \
        .minEpochTime(min_time) \
        .run(#case_name,[&](){ \
            ctx.eval(worker_size,max_kernel,out,inp,tile_shape,axis); \
        }); \
\
    auto expected = nm::max(inp,axis); \
    NMTOOLS_ASSERT_CLOSE( out, expected ); \
}

// V512_MT_MAX_CASE(v512_mt.max.2_8.2.fp32.2x16,    (make_shape(2,8)),    make_shape(2), (tuple{2_ct,16_ct}), nm::ct_v<-1>, 1 );
V512_MT_MAX_CASE(v512_mt.max.2_16.2.fp32.2x16,   (make_shape(2,16)),   make_shape(2), (tuple{2_ct,16_ct}), nm::ct_v<-1>, 1 );
V512_MT_MAX_CASE(v512_mt.max.2_32.2.fp32.2x16,   (make_shape(2,32)),   make_shape(2), (tuple{2_ct,16_ct}), nm::ct_v<-1>, 1 );
V512_MT_MAX_CASE(v512_mt.max.2_64.2.fp32.2x16,   (make_shape(2,64)),   make_shape(2), (tuple{2_ct,16_ct}), nm::ct_v<-1>, 1 );
V512_MT_MAX_CASE(v512_mt.max.2_128.2.fp32.2x16,  (make_shape(2,128)),  make_shape(2), (tuple{2_ct,16_ct}), nm::ct_v<-1>, 1 );
V512_MT_MAX_CASE(v512_mt.max.2_256.2.fp32.2x16,  (make_shape(2,256)),  make_shape(2), (tuple{2_ct,16_ct}), nm::ct_v<-1>, 1 );
V512_MT_MAX_CASE(v512_mt.max.2_512.2.fp32.2x16,  (make_shape(2,512)),  make_shape(2), (tuple{2_ct,16_ct}), nm::ct_v<-1>, 1 );
V512_MT_MAX_CASE(v512_mt.max.2_1024.2.fp32.2x16, (make_shape(2,1024)), make_shape(2), (tuple{2_ct,16_ct}), nm::ct_v<-1>, 1 );
V512_MT_MAX_CASE(v512_mt.max.2_2048.2.fp32.2x16, (make_shape(2,2048)), make_shape(2), (tuple{2_ct,16_ct}), nm::ct_v<-1>, 1 );

// V512_MT_MAX_CASE(v512_mt.max.2_ct_8_ct.2_ct.fp32.2x16,    (make_shape(2_ct,8_ct)),    make_shape(2_ct), (tuple{2_ct,16_ct}), nm::ct_v<-1>, 1 );
V512_MT_MAX_CASE(v512_mt.max.2_ct_16_ct.2_ct.fp32.2x16,   (make_shape(2_ct,16_ct)),   make_shape(2_ct), (tuple{2_ct,16_ct}), nm::ct_v<-1>, 1 );
V512_MT_MAX_CASE(v512_mt.max.2_ct_32_ct.2_ct.fp32.2x16,   (make_shape(2_ct,32_ct)),   make_shape(2_ct), (tuple{2_ct,16_ct}), nm::ct_v<-1>, 1 );
V512_MT_MAX_CASE(v512_mt.max.2_ct_64_ct.2_ct.fp32.2x16,   (make_shape(2_ct,64_ct)),   make_shape(2_ct), (tuple{2_ct,16_ct}), nm::ct_v<-1>, 1 );
V512_MT_MAX_CASE(v512_mt.max.2_ct_128_ct.2_ct.fp32.2x16,  (make_shape(2_ct,128_ct)),  make_shape(2_ct), (tuple{2_ct,16_ct}), nm::ct_v<-1>, 1 );
V512_MT_MAX_CASE(v512_mt.max.2_ct_256_ct.2_ct.fp32.2x16,  (make_shape(2_ct,256_ct)),  make_shape(2_ct), (tuple{2_ct,16_ct}), nm::ct_v<-1>, 1 );
V512_MT_MAX_CASE(v512_mt.max.2_ct_512_ct.2_ct.fp32.2x16,  (make_shape(2_ct,512_ct)),  make_shape(2_ct), (tuple{2_ct,16_ct}), nm::ct_v<-1>, 1 );
V512_MT_MAX_CASE(v512_mt.max.2_ct_1024_ct.2_ct.fp32.2x16, (make_shape(2_ct,1024_ct)), make_shape(2_ct), (tuple{2_ct,16_ct}), nm::ct_v<-1>, 1 );
V512_MT_MAX_CASE(v512_mt.max.2_ct_2048_ct.2_ct.fp32.2x16, (make_shape(2_ct,2048_ct)), make_shape(2_ct), (tuple{2_ct,16_ct}), nm::ct_v<-1>, 1 );

// V512_MT_MAX_CASE(v512_mt.max.4_8.4.fp32.2x16,    (make_shape(4,8)),    make_shape(4), (tuple{2_ct,16_ct}), nm::ct_v<-1>, 1 );
V512_MT_MAX_CASE(v512_mt.max.4_16.4.fp32.2x16,   (make_shape(4,16)),   make_shape(4), (tuple{2_ct,16_ct}), nm::ct_v<-1>, 1 );
V512_MT_MAX_CASE(v512_mt.max.4_32.4.fp32.2x16,   (make_shape(4,32)),   make_shape(4), (tuple{2_ct,16_ct}), nm::ct_v<-1>, 1 );
V512_MT_MAX_CASE(v512_mt.max.4_64.4.fp32.2x16,   (make_shape(4,64)),   make_shape(4), (tuple{2_ct,16_ct}), nm::ct_v<-1>, 1 );
V512_MT_MAX_CASE(v512_mt.max.4_128.4.fp32.2x16,  (make_shape(4,128)),  make_shape(4), (tuple{2_ct,16_ct}), nm::ct_v<-1>, 1 );
V512_MT_MAX_CASE(v512_mt.max.4_256.4.fp32.2x16,  (make_shape(4,256)),  make_shape(4), (tuple{2_ct,16_ct}), nm::ct_v<-1>, 1 );
V512_MT_MAX_CASE(v512_mt.max.4_512.4.fp32.2x16,  (make_shape(4,512)),  make_shape(4), (tuple{2_ct,16_ct}), nm::ct_v<-1>, 1 );
V512_MT_MAX_CASE(v512_mt.max.4_1024.4.fp32.2x16, (make_shape(4,1024)), make_shape(4), (tuple{2_ct,16_ct}), nm::ct_v<-1>, 1 );
V512_MT_MAX_CASE(v512_mt.max.4_2048.4.fp32.2x16, (make_shape(4,2048)), make_shape(4), (tuple{2_ct,16_ct}), nm::ct_v<-1>, 1 );

// V512_MT_MAX_CASE(v512_mt.max.4_ct_8_ct.4_ct.fp32.2x16,    (make_shape(4_ct,8_ct)),    make_shape(4_ct), (tuple{2_ct,16_ct}), nm::ct_v<-1>, 1 );
V512_MT_MAX_CASE(v512_mt.max.4_ct_16_ct.4_ct.fp32.2x16,   (make_shape(4_ct,16_ct)),   make_shape(4_ct), (tuple{2_ct,16_ct}), nm::ct_v<-1>, 1 );
V512_MT_MAX_CASE(v512_mt.max.4_ct_32_ct.4_ct.fp32.2x16,   (make_shape(4_ct,32_ct)),   make_shape(4_ct), (tuple{2_ct,16_ct}), nm::ct_v<-1>, 1 );
V512_MT_MAX_CASE(v512_mt.max.4_ct_64_ct.4_ct.fp32.2x16,   (make_shape(4_ct,64_ct)),   make_shape(4_ct), (tuple{2_ct,16_ct}), nm::ct_v<-1>, 1 );
V512_MT_MAX_CASE(v512_mt.max.4_ct_128_ct.4_ct.fp32.2x16,  (make_shape(4_ct,128_ct)),  make_shape(4_ct), (tuple{2_ct,16_ct}), nm::ct_v<-1>, 1 );
V512_MT_MAX_CASE(v512_mt.max.4_ct_256_ct.4_ct.fp32.2x16,  (make_shape(4_ct,256_ct)),  make_shape(4_ct), (tuple{2_ct,16_ct}), nm::ct_v<-1>, 1 );
V512_MT_MAX_CASE(v512_mt.max.4_ct_512_ct.4_ct.fp32.2x16,  (make_shape(4_ct,512_ct)),  make_shape(4_ct), (tuple{2_ct,16_ct}), nm::ct_v<-1>, 1 );
V512_MT_MAX_CASE(v512_mt.max.4_ct_1024_ct.4_ct.fp32.2x16, (make_shape(4_ct,1024_ct)), make_shape(4_ct), (tuple{2_ct,16_ct}), nm::ct_v<-1>, 1 );
V512_MT_MAX_CASE(v512_mt.max.4_ct_2048_ct.4_ct.fp32.2x16, (make_shape(4_ct,2048_ct)), make_shape(4_ct), (tuple{2_ct,16_ct}), nm::ct_v<-1>, 1 );

// V512_MT_MAX_CASE(v512_mt.max.2_8.8.fp32.2x16,       (make_shape(2,8)),    make_shape(8),    (tuple{2_ct,16_ct}), nm::ct_v<0>, 1 );
V512_MT_MAX_CASE(v512_mt.max.2_16.16.fp32.2x16,     (make_shape(2,16)),   make_shape(16),   (tuple{2_ct,16_ct}), nm::ct_v<0>, 1 );
V512_MT_MAX_CASE(v512_mt.max.2_32.32.fp32.2x16,     (make_shape(2,32)),   make_shape(32),   (tuple{2_ct,16_ct}), nm::ct_v<0>, 1 );
V512_MT_MAX_CASE(v512_mt.max.2_64.64.fp32.2x16,     (make_shape(2,64)),   make_shape(64),   (tuple{2_ct,16_ct}), nm::ct_v<0>, 1 );
V512_MT_MAX_CASE(v512_mt.max.2_128.128.fp32.2x16,   (make_shape(2,128)),  make_shape(128),  (tuple{2_ct,16_ct}), nm::ct_v<0>, 1 );
V512_MT_MAX_CASE(v512_mt.max.2_256.256.fp32.2x16,   (make_shape(2,256)),  make_shape(256),  (tuple{2_ct,16_ct}), nm::ct_v<0>, 1 );
V512_MT_MAX_CASE(v512_mt.max.2_512.512.fp32.2x16,   (make_shape(2,512)),  make_shape(512),  (tuple{2_ct,16_ct}), nm::ct_v<0>, 1 );
V512_MT_MAX_CASE(v512_mt.max.2_1024.1024.fp32.2x16, (make_shape(2,1024)), make_shape(1024), (tuple{2_ct,16_ct}), nm::ct_v<0>, 1 );
V512_MT_MAX_CASE(v512_mt.max.2_2048.2048.fp32.2x16, (make_shape(2,2048)), make_shape(2048), (tuple{2_ct,16_ct}), nm::ct_v<0>, 1 );

// V512_MT_MAX_CASE(v512_mt.max.2_ct_8_ct.8_ct.fp32.2x16,       (make_shape(2_ct,8_ct)),    make_shape(8_ct),    (tuple{2_ct,16_ct}), nm::ct_v<0>, 1 );
V512_MT_MAX_CASE(v512_mt.max.2_ct_16_ct.16_ct.fp32.2x16,     (make_shape(2_ct,16_ct)),   make_shape(16_ct),   (tuple{2_ct,16_ct}), nm::ct_v<0>, 1 );
V512_MT_MAX_CASE(v512_mt.max.2_ct_32_ct.32_ct.fp32.2x16,     (make_shape(2_ct,32_ct)),   make_shape(32_ct),   (tuple{2_ct,16_ct}), nm::ct_v<0>, 1 );
V512_MT_MAX_CASE(v512_mt.max.2_ct_64_ct.64_ct.fp32.2x16,     (make_shape(2_ct,64_ct)),   make_shape(64_ct),   (tuple{2_ct,16_ct}), nm::ct_v<0>, 1 );
V512_MT_MAX_CASE(v512_mt.max.2_ct_128_ct.128_ct.fp32.2x16,   (make_shape(2_ct,128_ct)),  make_shape(128_ct),  (tuple{2_ct,16_ct}), nm::ct_v<0>, 1 );
V512_MT_MAX_CASE(v512_mt.max.2_ct_256_ct.256_ct.fp32.2x16,   (make_shape(2_ct,256_ct)),  make_shape(256_ct),  (tuple{2_ct,16_ct}), nm::ct_v<0>, 1 );
V512_MT_MAX_CASE(v512_mt.max.2_ct_512_ct.512_ct.fp32.2x16,   (make_shape(2_ct,512_ct)),  make_shape(512_ct),  (tuple{2_ct,16_ct}), nm::ct_v<0>, 1 );
V512_MT_MAX_CASE(v512_mt.max.2_ct_1024_ct.1024_ct.fp32.2x16, (make_shape(2_ct,1024_ct)), make_shape(1024_ct), (tuple{2_ct,16_ct}), nm::ct_v<0>, 1 );
V512_MT_MAX_CASE(v512_mt.max.2_ct_2048_ct.2048_ct.fp32.2x16, (make_shape(2_ct,2048_ct)), make_shape(2048_ct), (tuple{2_ct,16_ct}), nm::ct_v<0>, 1 );

// V512_MT_MAX_CASE(v512_mt.max.4_8.8.fp32.2x16,       (make_shape(4,8)),    make_shape(8),    (tuple{2_ct,16_ct}), nm::ct_v<0>, 1 );
V512_MT_MAX_CASE(v512_mt.max.4_16.16.fp32.2x16,     (make_shape(4,16)),   make_shape(16),   (tuple{2_ct,16_ct}), nm::ct_v<0>, 1 );
V512_MT_MAX_CASE(v512_mt.max.4_32.32.fp32.2x16,     (make_shape(4,32)),   make_shape(32),   (tuple{2_ct,16_ct}), nm::ct_v<0>, 1 );
V512_MT_MAX_CASE(v512_mt.max.4_64.64.fp32.2x16,     (make_shape(4,64)),   make_shape(64),   (tuple{2_ct,16_ct}), nm::ct_v<0>, 1 );
V512_MT_MAX_CASE(v512_mt.max.4_128.128.fp32.2x16,   (make_shape(4,128)),  make_shape(128),  (tuple{2_ct,16_ct}), nm::ct_v<0>, 1 );
V512_MT_MAX_CASE(v512_mt.max.4_256.256.fp32.2x16,   (make_shape(4,256)),  make_shape(256),  (tuple{2_ct,16_ct}), nm::ct_v<0>, 1 );
V512_MT_MAX_CASE(v512_mt.max.4_512.512.fp32.2x16,   (make_shape(4,512)),  make_shape(512),  (tuple{2_ct,16_ct}), nm::ct_v<0>, 1 );
V512_MT_MAX_CASE(v512_mt.max.4_1024.1024.fp32.2x16, (make_shape(4,1024)), make_shape(1024), (tuple{2_ct,16_ct}), nm::ct_v<0>, 1 );
V512_MT_MAX_CASE(v512_mt.max.4_2048.2048.fp32.2x16, (make_shape(4,2048)), make_shape(2048), (tuple{2_ct,16_ct}), nm::ct_v<0>, 1 );

// V512_MT_MAX_CASE(v512_mt.max.4_ct_8_ct.8_ct.fp32.2x16,       (make_shape(4_ct,8_ct)),    make_shape(8_ct),    (tuple{2_ct,16_ct}), nm::ct_v<0>, 1 );
V512_MT_MAX_CASE(v512_mt.max.4_ct_16_ct.16_ct.fp32.2x16,     (make_shape(4_ct,16_ct)),   make_shape(16_ct),   (tuple{2_ct,16_ct}), nm::ct_v<0>, 1 );
V512_MT_MAX_CASE(v512_mt.max.4_ct_32_ct.32_ct.fp32.2x16,     (make_shape(4_ct,32_ct)),   make_shape(32_ct),   (tuple{2_ct,16_ct}), nm::ct_v<0>, 1 );
V512_MT_MAX_CASE(v512_mt.max.4_ct_64_ct.64_ct.fp32.2x16,     (make_shape(4_ct,64_ct)),   make_shape(64_ct),   (tuple{2_ct,16_ct}), nm::ct_v<0>, 1 );
V512_MT_MAX_CASE(v512_mt.max.4_ct_128_ct.128_ct.fp32.2x16,   (make_shape(4_ct,128_ct)),  make_shape(128_ct),  (tuple{2_ct,16_ct}), nm::ct_v<0>, 1 );
V512_MT_MAX_CASE(v512_mt.max.4_ct_256_ct.256_ct.fp32.2x16,   (make_shape(4_ct,256_ct)),  make_shape(256_ct),  (tuple{2_ct,16_ct}), nm::ct_v<0>, 1 );
V512_MT_MAX_CASE(v512_mt.max.4_ct_512_ct.512_ct.fp32.2x16,   (make_shape(4_ct,512_ct)),  make_shape(512_ct),  (tuple{2_ct,16_ct}), nm::ct_v<0>, 1 );
V512_MT_MAX_CASE(v512_mt.max.4_ct_1024_ct.1024_ct.fp32.2x16, (make_shape(4_ct,1024_ct)), make_shape(1024_ct), (tuple{2_ct,16_ct}), nm::ct_v<0>, 1 );
V512_MT_MAX_CASE(v512_mt.max.4_ct_2048_ct.2048_ct.fp32.2x16, (make_shape(4_ct,2048_ct)), make_shape(2048_ct), (tuple{2_ct,16_ct}), nm::ct_v<0>, 1 );

/************************************************************************************************************************************************* */

V512_MT_MAX_CASE(v512_mt.max.1024_2048.-1.1024.fp32.2x16, (make_shape(1024,2048)), make_shape(1024), (tuple{2_ct,16_ct}), nm::ct_v<-1>, 2 );
V512_MT_MAX_CASE(v512_mt.max.2048_2048.-1.2048.fp32.2x16, (make_shape(2048,2048)), make_shape(2048), (tuple{2_ct,16_ct}), nm::ct_v<-1>, 2 );

V512_MT_MAX_CASE(v512_mt.max.1024_2048_ct.-1.1024.fp32.2x16, (make_shape(1024,2048_ct)), make_shape(1024), (tuple{2_ct,16_ct}), nm::ct_v<-1>, 2 );
V512_MT_MAX_CASE(v512_mt.max.2048_2048_ct.-1.2048.fp32.2x16, (make_shape(2048,2048_ct)), make_shape(2048), (tuple{2_ct,16_ct}), nm::ct_v<-1>, 2 );

V512_MT_MAX_CASE(v512_mt.max.1024_ct_2048.-1.1024_ct.fp32.2x16, (make_shape(1024_ct,2048)), make_shape(1024_ct), (tuple{2_ct,16_ct}), nm::ct_v<-1>, 2 );
V512_MT_MAX_CASE(v512_mt.max.2048_ct_2048.-1.2048_ct.fp32.2x16, (make_shape(2048_ct,2048)), make_shape(2048_ct), (tuple{2_ct,16_ct}), nm::ct_v<-1>, 2 );

V512_MT_MAX_CASE(v512_mt.max.1024_ct_2048_ct.-1.1024_ct.fp32.2x16, (make_shape(1024_ct,2048_ct)), make_shape(1024_ct), (tuple{2_ct,16_ct}), nm::ct_v<-1>, 2 );
V512_MT_MAX_CASE(v512_mt.max.2048_ct_2048_ct.-1.2048_ct.fp32.2x16, (make_shape(2048_ct,2048_ct)), make_shape(2048_ct), (tuple{2_ct,16_ct}), nm::ct_v<-1>, 2 );

/************************************************************************************************************************************************* */

V512_MT_MAX_CASE(v512_mt.max.1024_2048.0.2048.fp32.2x16, (make_shape(1024,2048)), make_shape(2048), (tuple{2_ct,16_ct}), nm::ct_v<0>, 2 );
V512_MT_MAX_CASE(v512_mt.max.2048_2048.0.2048.fp32.2x16, (make_shape(2048,2048)), make_shape(2048), (tuple{2_ct,16_ct}), nm::ct_v<0>, 2 );

V512_MT_MAX_CASE(v512_mt.max.1024_2048_ct.0.2048_ct.fp32.2x16, (make_shape(1024,2048_ct)), make_shape(2048_ct), (tuple{2_ct,16_ct}), nm::ct_v<0>, 2 );
V512_MT_MAX_CASE(v512_mt.max.2048_2048_ct.0.2048_ct.fp32.2x16, (make_shape(2048,2048_ct)), make_shape(2048_ct), (tuple{2_ct,16_ct}), nm::ct_v<0>, 2 );

V512_MT_MAX_CASE(v512_mt.max.1024_ct_2048.0.2048.fp32.2x16, (make_shape(1024_ct,2048)), make_shape(2048), (tuple{2_ct,16_ct}), nm::ct_v<0>, 2 );
V512_MT_MAX_CASE(v512_mt.max.2048_ct_2048.0.2048.fp32.2x16, (make_shape(2048_ct,2048)), make_shape(2048), (tuple{2_ct,16_ct}), nm::ct_v<0>, 2 );

V512_MT_MAX_CASE(v512_mt.max.1024_ct_2048_ct.0.2048_ct.fp32.2x16, (make_shape(1024_ct,2048_ct)), make_shape(2048_ct), (tuple{2_ct,16_ct}), nm::ct_v<0>, 2 );
V512_MT_MAX_CASE(v512_mt.max.2048_ct_2048_ct.0.2048_ct.fp32.2x16, (make_shape(2048_ct,2048_ct)), make_shape(2048_ct), (tuple{2_ct,16_ct}), nm::ct_v<0>, 2 );

// faster variant
V512_MT_MAX_CASE(v512_mt.max.1024_ct_2048_ct.0.2048_ct.fp32.1x32, (make_shape(1024_ct,2048_ct)), make_shape(2048_ct), (tuple{1_ct,32_ct}), nm::ct_v<0>, 2 );
V512_MT_MAX_CASE(v512_mt.max.2048_ct_2048_ct.0.2048_ct.fp32.1x32, (make_shape(2048_ct,2048_ct)), make_shape(2048_ct), (tuple{1_ct,32_ct}), nm::ct_v<0>, 2 );

/************************************************************************************************************************************************* */
