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

using context_t = tk::thread_pool<tk::scalar_t>;

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

#define SCALAR_SUM_CASE( case_name, shape, out_shape, tile_shape, axis, num_threads ) \
TEST_CASE(#case_name * doctest::test_suite("tilekit")) \
{ \
    auto gen = nm::random_engine(); \
    auto dtype = nm::float32; \
\
    auto inp = nm::random(shape,dtype,gen); \
    auto out = nm::Array::zeros(out_shape,dtype); \
\
    auto ctx = context_t(num_threads); \
    auto worker_size = num_threads; \
\
    auto min_time = std::chrono::nanoseconds(50'000'000); \
    ankerl::nanobench::Bench() \
        .minEpochTime(min_time) \
        .run(#case_name,[&](){ \
            ctx.eval(worker_size,sum_kernel,out,inp,tk::index(tile_shape),axis); \
        }); \
\
    auto expected = nm::sum(inp,axis); \
    NMTOOLS_ASSERT_CLOSE( out, expected ); \
}

SCALAR_SUM_CASE(scalar_mt.sum.2_128.2.fp32.2x4,  (make_shape(2,128)),  make_shape(2), (tuple{2_ct,4_ct}), nm::ct_v<-1>, 2 );
SCALAR_SUM_CASE(scalar_mt.sum.2_256.2.fp32.2x4,  (make_shape(2,256)),  make_shape(2), (tuple{2_ct,4_ct}), nm::ct_v<-1>, 2 );
SCALAR_SUM_CASE(scalar_mt.sum.2_512.2.fp32.2x4,  (make_shape(2,512)),  make_shape(2), (tuple{2_ct,4_ct}), nm::ct_v<-1>, 2 );
SCALAR_SUM_CASE(scalar_mt.sum.2_1024.2.fp32.2x4, (make_shape(2,1024)), make_shape(2), (tuple{2_ct,4_ct}), nm::ct_v<-1>, 2 );
SCALAR_SUM_CASE(scalar_mt.sum.2_2048.2.fp32.2x4, (make_shape(2,2048)), make_shape(2), (tuple{2_ct,4_ct}), nm::ct_v<-1>, 2 );
SCALAR_SUM_CASE(scalar_mt.sum.2_4096.2.fp32.2x4, (make_shape(2,4096)), make_shape(2), (tuple{2_ct,4_ct}), nm::ct_v<-1>, 2 );
SCALAR_SUM_CASE(scalar_mt.sum.2_8192.2.fp32.2x4, (make_shape(2,8192)), make_shape(2), (tuple{2_ct,4_ct}), nm::ct_v<-1>, 2 );

SCALAR_SUM_CASE(scalar_mt.sum.2_ct_128_ct.2_ct.fp32.2x4,  (make_shape(2_ct,128_ct)),  make_shape(2_ct), (tuple{2_ct,4_ct}), nm::ct_v<-1>, 2 );
SCALAR_SUM_CASE(scalar_mt.sum.2_ct_256_ct.2_ct.fp32.2x4,  (make_shape(2_ct,256_ct)),  make_shape(2_ct), (tuple{2_ct,4_ct}), nm::ct_v<-1>, 2 );
SCALAR_SUM_CASE(scalar_mt.sum.2_ct_512_ct.2_ct.fp32.2x4,  (make_shape(2_ct,512_ct)),  make_shape(2_ct), (tuple{2_ct,4_ct}), nm::ct_v<-1>, 2 );
SCALAR_SUM_CASE(scalar_mt.sum.2_ct_1024_ct.2_ct.fp32.2x4, (make_shape(2_ct,1024_ct)), make_shape(2_ct), (tuple{2_ct,4_ct}), nm::ct_v<-1>, 2 );
SCALAR_SUM_CASE(scalar_mt.sum.2_ct_2048_ct.2_ct.fp32.2x4, (make_shape(2_ct,2048_ct)), make_shape(2_ct), (tuple{2_ct,4_ct}), nm::ct_v<-1>, 2 );
SCALAR_SUM_CASE(scalar_mt.sum.2_ct_4096_ct.2_ct.fp32.2x4, (make_shape(2_ct,4096_ct)), make_shape(2_ct), (tuple{2_ct,4_ct}), nm::ct_v<-1>, 2 );
SCALAR_SUM_CASE(scalar_mt.sum.2_ct_8192_ct.2_ct.fp32.2x4, (make_shape(2_ct,8192_ct)), make_shape(2_ct), (tuple{2_ct,4_ct}), nm::ct_v<-1>, 2 );

SCALAR_SUM_CASE(scalar_mt.sum.4_128.4.fp32.2x4,  (make_shape(4,128)),  make_shape(4), (tuple{2_ct,4_ct}), nm::ct_v<-1>, 2 );
SCALAR_SUM_CASE(scalar_mt.sum.4_256.4.fp32.2x4,  (make_shape(4,256)),  make_shape(4), (tuple{2_ct,4_ct}), nm::ct_v<-1>, 2 );
SCALAR_SUM_CASE(scalar_mt.sum.4_512.4.fp32.2x4,  (make_shape(4,512)),  make_shape(4), (tuple{2_ct,4_ct}), nm::ct_v<-1>, 2 );
SCALAR_SUM_CASE(scalar_mt.sum.4_1024.4.fp32.2x4, (make_shape(4,1024)), make_shape(4), (tuple{2_ct,4_ct}), nm::ct_v<-1>, 2 );
SCALAR_SUM_CASE(scalar_mt.sum.4_2048.4.fp32.2x4, (make_shape(4,2048)), make_shape(4), (tuple{2_ct,4_ct}), nm::ct_v<-1>, 2 );
SCALAR_SUM_CASE(scalar_mt.sum.4_4096.4.fp32.2x4, (make_shape(4,4096)), make_shape(4), (tuple{2_ct,4_ct}), nm::ct_v<-1>, 2 );
SCALAR_SUM_CASE(scalar_mt.sum.4_8192.4.fp32.2x4, (make_shape(4,8192)), make_shape(4), (tuple{2_ct,4_ct}), nm::ct_v<-1>, 2 );

SCALAR_SUM_CASE(scalar_mt.sum.4_ct_128_ct.4_ct.fp32.2x4,  (make_shape(4_ct,128_ct)),  make_shape(4_ct), (tuple{2_ct,4_ct}), nm::ct_v<-1>, 2 );
SCALAR_SUM_CASE(scalar_mt.sum.4_ct_256_ct.4_ct.fp32.2x4,  (make_shape(4_ct,256_ct)),  make_shape(4_ct), (tuple{2_ct,4_ct}), nm::ct_v<-1>, 2 );
SCALAR_SUM_CASE(scalar_mt.sum.4_ct_512_ct.4_ct.fp32.2x4,  (make_shape(4_ct,512_ct)),  make_shape(4_ct), (tuple{2_ct,4_ct}), nm::ct_v<-1>, 2 );
SCALAR_SUM_CASE(scalar_mt.sum.4_ct_1024_ct.4_ct.fp32.2x4, (make_shape(4_ct,1024_ct)), make_shape(4_ct), (tuple{2_ct,4_ct}), nm::ct_v<-1>, 2 );
SCALAR_SUM_CASE(scalar_mt.sum.4_ct_2048_ct.4_ct.fp32.2x4, (make_shape(4_ct,2048_ct)), make_shape(4_ct), (tuple{2_ct,4_ct}), nm::ct_v<-1>, 2 );
SCALAR_SUM_CASE(scalar_mt.sum.4_ct_4096_ct.4_ct.fp32.2x4, (make_shape(4_ct,4096_ct)), make_shape(4_ct), (tuple{2_ct,4_ct}), nm::ct_v<-1>, 2 );
SCALAR_SUM_CASE(scalar_mt.sum.4_ct_8192_ct.4_ct.fp32.2x4, (make_shape(4_ct,8192_ct)), make_shape(4_ct), (tuple{2_ct,4_ct}), nm::ct_v<-1>, 2 );

SCALAR_SUM_CASE(scalar_mt.sum.2_128.128.fp32.2x4,   (make_shape(2,128)),  make_shape(128),  (tuple{2_ct,4_ct}), nm::ct_v<0>, 2 );
SCALAR_SUM_CASE(scalar_mt.sum.2_256.256.fp32.2x4,   (make_shape(2,256)),  make_shape(256),  (tuple{2_ct,4_ct}), nm::ct_v<0>, 2 );
SCALAR_SUM_CASE(scalar_mt.sum.2_512.512.fp32.2x4,   (make_shape(2,512)),  make_shape(512),  (tuple{2_ct,4_ct}), nm::ct_v<0>, 2 );
SCALAR_SUM_CASE(scalar_mt.sum.2_1024.1024.fp32.2x4, (make_shape(2,1024)), make_shape(1024), (tuple{2_ct,4_ct}), nm::ct_v<0>, 2 );
SCALAR_SUM_CASE(scalar_mt.sum.2_2048.2048.fp32.2x4, (make_shape(2,2048)), make_shape(2048), (tuple{2_ct,4_ct}), nm::ct_v<0>, 2 );
SCALAR_SUM_CASE(scalar_mt.sum.2_4096.4096.fp32.2x4, (make_shape(2,4096)), make_shape(4096), (tuple{2_ct,4_ct}), nm::ct_v<0>, 2 );
SCALAR_SUM_CASE(scalar_mt.sum.2_8192.8192.fp32.2x4, (make_shape(2,8192)), make_shape(8192), (tuple{2_ct,4_ct}), nm::ct_v<0>, 2 );

SCALAR_SUM_CASE(scalar_mt.sum.2_ct_128_ct.128_ct.fp32.2x4,   (make_shape(2_ct,128_ct)),  make_shape(128_ct),  (tuple{2_ct,4_ct}), nm::ct_v<0>, 2 );
SCALAR_SUM_CASE(scalar_mt.sum.2_ct_256_ct.256_ct.fp32.2x4,   (make_shape(2_ct,256_ct)),  make_shape(256_ct),  (tuple{2_ct,4_ct}), nm::ct_v<0>, 2 );
SCALAR_SUM_CASE(scalar_mt.sum.2_ct_512_ct.512_ct.fp32.2x4,   (make_shape(2_ct,512_ct)),  make_shape(512_ct),  (tuple{2_ct,4_ct}), nm::ct_v<0>, 2 );
SCALAR_SUM_CASE(scalar_mt.sum.2_ct_1024_ct.1024_ct.fp32.2x4, (make_shape(2_ct,1024_ct)), make_shape(1024_ct), (tuple{2_ct,4_ct}), nm::ct_v<0>, 2 );
SCALAR_SUM_CASE(scalar_mt.sum.2_ct_2048_ct.2048_ct.fp32.2x4, (make_shape(2_ct,2048_ct)), make_shape(2048_ct), (tuple{2_ct,4_ct}), nm::ct_v<0>, 2 );
SCALAR_SUM_CASE(scalar_mt.sum.2_ct_4096_ct.4096.fp32.2x4, (make_shape(2_ct,4096_ct)), make_shape(4096_ct), (tuple{2_ct,4_ct}), nm::ct_v<0>, 2 );
SCALAR_SUM_CASE(scalar_mt.sum.2_ct_8192_ct.8192.fp32.2x4, (make_shape(2_ct,8192_ct)), make_shape(8192_ct), (tuple{2_ct,4_ct}), nm::ct_v<0>, 2 );

SCALAR_SUM_CASE(scalar_mt.sum.4_128.128.fp32.2x4,   (make_shape(4,128)),  make_shape(128),  (tuple{2_ct,4_ct}), nm::ct_v<0>, 2 );
SCALAR_SUM_CASE(scalar_mt.sum.4_256.256.fp32.2x4,   (make_shape(4,256)),  make_shape(256),  (tuple{2_ct,4_ct}), nm::ct_v<0>, 2 );
SCALAR_SUM_CASE(scalar_mt.sum.4_512.512.fp32.2x4,   (make_shape(4,512)),  make_shape(512),  (tuple{2_ct,4_ct}), nm::ct_v<0>, 2 );
SCALAR_SUM_CASE(scalar_mt.sum.4_1024.1024.fp32.2x4, (make_shape(4,1024)), make_shape(1024), (tuple{2_ct,4_ct}), nm::ct_v<0>, 2 );
SCALAR_SUM_CASE(scalar_mt.sum.4_2048.2048.fp32.2x4, (make_shape(4,2048)), make_shape(2048), (tuple{2_ct,4_ct}), nm::ct_v<0>, 2 );
SCALAR_SUM_CASE(scalar_mt.sum.4_4096.4096.fp32.2x4, (make_shape(4,4096)), make_shape(4096), (tuple{2_ct,4_ct}), nm::ct_v<0>, 2 );
SCALAR_SUM_CASE(scalar_mt.sum.4_8192.8192.fp32.2x4, (make_shape(4,8192)), make_shape(8192), (tuple{2_ct,4_ct}), nm::ct_v<0>, 2 );

SCALAR_SUM_CASE(scalar_mt.sum.4_ct_128_ct.128_ct.fp32.2x4,   (make_shape(4_ct,128_ct)),  make_shape(128_ct),  (tuple{2_ct,4_ct}), nm::ct_v<0>, 2 );
SCALAR_SUM_CASE(scalar_mt.sum.4_ct_256_ct.256_ct.fp32.2x4,   (make_shape(4_ct,256_ct)),  make_shape(256_ct),  (tuple{2_ct,4_ct}), nm::ct_v<0>, 2 );
SCALAR_SUM_CASE(scalar_mt.sum.4_ct_512_ct.512_ct.fp32.2x4,   (make_shape(4_ct,512_ct)),  make_shape(512_ct),  (tuple{2_ct,4_ct}), nm::ct_v<0>, 2 );
SCALAR_SUM_CASE(scalar_mt.sum.4_ct_1024_ct.1024_ct.fp32.2x4, (make_shape(4_ct,1024_ct)), make_shape(1024_ct), (tuple{2_ct,4_ct}), nm::ct_v<0>, 2 );
SCALAR_SUM_CASE(scalar_mt.sum.4_ct_2048_ct.2048_ct.fp32.2x4, (make_shape(4_ct,2048_ct)), make_shape(2048_ct), (tuple{2_ct,4_ct}), nm::ct_v<0>, 2 );
SCALAR_SUM_CASE(scalar_mt.sum.4_ct_4096_ct.4096_ct.fp32.2x4, (make_shape(4_ct,4096_ct)), make_shape(4096_ct), (tuple{2_ct,4_ct}), nm::ct_v<0>, 2 );
SCALAR_SUM_CASE(scalar_mt.sum.4_ct_8192_ct.8192_ct.fp32.2x4, (make_shape(4_ct,8192_ct)), make_shape(8192_ct), (tuple{2_ct,4_ct}), nm::ct_v<0>, 2 );