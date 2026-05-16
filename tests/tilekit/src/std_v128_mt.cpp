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

using context_t = tk::thread_pool<tk::vector::context_t<128>>;

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

#define V128_MT_STD_CASE( case_name, shape, out_shape, tile_shape, axis, num_threads ) \
TEST_CASE(#case_name * doctest::test_suite("tilekit")) \
{ \
    auto gen   = nm::random_engine(); \
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
            ctx.eval(worker_size,std_kernel,out,inp,tk::index(tile_shape),axis); \
        }); \
    auto expected = nm::std(inp,axis); \
    NMTOOLS_ASSERT_CLOSE( out, expected ); \
}

V128_MT_STD_CASE(v128_mt.std.4_128.4.fp32.4x4.2,  (make_shape(4,128)),  make_shape(4), (tuple{4_ct,4_ct}), nm::ct_v<-1>, 2 );
V128_MT_STD_CASE(v128_mt.std.4_256.4.fp32.4x4.2,  (make_shape(4,256)),  make_shape(4), (tuple{4_ct,4_ct}), nm::ct_v<-1>, 2 );
V128_MT_STD_CASE(v128_mt.std.4_512.4.fp32.4x4.2,  (make_shape(4,512)),  make_shape(4), (tuple{4_ct,4_ct}), nm::ct_v<-1>, 2 );
V128_MT_STD_CASE(v128_mt.std.4_1024.4.fp32.4x4.2, (make_shape(4,1024)), make_shape(4), (tuple{4_ct,4_ct}), nm::ct_v<-1>, 2 );
V128_MT_STD_CASE(v128_mt.std.4_2048.4.fp32.4x4.2, (make_shape(4,2048)), make_shape(4), (tuple{4_ct,4_ct}), nm::ct_v<-1>, 2 );

V128_MT_STD_CASE(v128_mt.std.4_ct_128_ct.4_ct.fp32.4x4.2,  (make_shape(4_ct,128_ct)),  make_shape(4_ct), (tuple{4_ct,4_ct}), nm::ct_v<-1>, 2 );
V128_MT_STD_CASE(v128_mt.std.4_ct_256_ct.4_ct.fp32.4x4.2,  (make_shape(4_ct,256_ct)),  make_shape(4_ct), (tuple{4_ct,4_ct}), nm::ct_v<-1>, 2 );
V128_MT_STD_CASE(v128_mt.std.4_ct_512_ct.4_ct.fp32.4x4.2,  (make_shape(4_ct,512_ct)),  make_shape(4_ct), (tuple{4_ct,4_ct}), nm::ct_v<-1>, 2 );
V128_MT_STD_CASE(v128_mt.std.4_ct_1024_ct.4_ct.fp32.4x4.2, (make_shape(4_ct,1024_ct)), make_shape(4_ct), (tuple{4_ct,4_ct}), nm::ct_v<-1>, 2 );
V128_MT_STD_CASE(v128_mt.std.4_ct_2048_ct.4_ct.fp32.4x4.2, (make_shape(4_ct,2048_ct)), make_shape(4_ct), (tuple{4_ct,4_ct}), nm::ct_v<-1>, 2 );

V128_MT_STD_CASE(v128_mt.std.4_128.128.fp32.4x4.2,   (make_shape(4,128)),  make_shape(128),  (tuple{4_ct,4_ct}), nm::ct_v<0>, 2 );
V128_MT_STD_CASE(v128_mt.std.4_256.256.fp32.4x4.2,   (make_shape(4,256)),  make_shape(256),  (tuple{4_ct,4_ct}), nm::ct_v<0>, 2 );
V128_MT_STD_CASE(v128_mt.std.4_512.512.fp32.4x4.2,   (make_shape(4,512)),  make_shape(512),  (tuple{4_ct,4_ct}), nm::ct_v<0>, 2 );
V128_MT_STD_CASE(v128_mt.std.4_1024.1024.fp32.4x4.2, (make_shape(4,1024)), make_shape(1024), (tuple{4_ct,4_ct}), nm::ct_v<0>, 2 );
V128_MT_STD_CASE(v128_mt.std.4_2048.2048.fp32.4x4.2, (make_shape(4,2048)), make_shape(2048), (tuple{4_ct,4_ct}), nm::ct_v<0>, 2 );

V128_MT_STD_CASE(v128_mt.std.4_ct_128_ct.128_ct.fp32.4x4.2,   (make_shape(4_ct,128_ct)),  make_shape(128_ct),  (tuple{4_ct,4_ct}), nm::ct_v<0>, 2 );
V128_MT_STD_CASE(v128_mt.std.4_ct_256_ct.256_ct.fp32.4x4.2,   (make_shape(4_ct,256_ct)),  make_shape(256_ct),  (tuple{4_ct,4_ct}), nm::ct_v<0>, 2 );
V128_MT_STD_CASE(v128_mt.std.4_ct_512_ct.512_ct.fp32.4x4.2,   (make_shape(4_ct,512_ct)),  make_shape(512_ct),  (tuple{4_ct,4_ct}), nm::ct_v<0>, 2 );
V128_MT_STD_CASE(v128_mt.std.4_ct_1024_ct.1024_ct.fp32.4x4.2, (make_shape(4_ct,1024_ct)), make_shape(1024_ct), (tuple{4_ct,4_ct}), nm::ct_v<0>, 2 );
V128_MT_STD_CASE(v128_mt.std.4_ct_2048_ct.2048_ct.fp32.4x4.2, (make_shape(4_ct,2048_ct)), make_shape(2048_ct), (tuple{4_ct,4_ct}), nm::ct_v<0>, 2 );
