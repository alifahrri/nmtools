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

#define SCALAR_SUM_CASE( case_name, shape, out_shape, tile_shape ) \
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
            sum_kernel(ctx,out,inp,tk::index(tile_shape)); \
        }); \
\
    auto expected = nm::sum(inp,nm::ct_v<-1>); \
    NMTOOLS_ASSERT_CLOSE( out, expected ); \
}

SCALAR_SUM_CASE(scalar_st.sum.2_8.fp32.2x4, (make_shape(2,8)), make_shape(2), (tuple{2_ct,4_ct}));
SCALAR_SUM_CASE(scalar_st.sum.2_16.fp32.2x4, (make_shape(2,16)), make_shape(2), (tuple{2_ct,4_ct}));
SCALAR_SUM_CASE(scalar_st.sum.2_32.fp32.2x4, (make_shape(2,32)), make_shape(2), (tuple{2_ct,4_ct}));
SCALAR_SUM_CASE(scalar_st.sum.2_64.fp32.2x4, (make_shape(2,64)), make_shape(2), (tuple{2_ct,4_ct}));
SCALAR_SUM_CASE(scalar_st.sum.2_128.fp32.2x4, (make_shape(2,128)), make_shape(2), (tuple{2_ct,4_ct}));
SCALAR_SUM_CASE(scalar_st.sum.2_256.fp32.2x4, (make_shape(2,256)), make_shape(2), (tuple{2_ct,4_ct}));
SCALAR_SUM_CASE(scalar_st.sum.2_512.fp32.2x4, (make_shape(2,512)), make_shape(2), (tuple{2_ct,4_ct}));
SCALAR_SUM_CASE(scalar_st.sum.2_1024.fp32.2x4, (make_shape(2,1024)), make_shape(2), (tuple{2_ct,4_ct}));
SCALAR_SUM_CASE(scalar_st.sum.2_2048.fp32.2x4, (make_shape(2,2048)), make_shape(2), (tuple{2_ct,4_ct}));

SCALAR_SUM_CASE(scalar_st.sum.4_8.fp32.2x4, (make_shape(4,8)), make_shape(4), (tuple{2_ct,4_ct}));
SCALAR_SUM_CASE(scalar_st.sum.4_16.fp32.2x4, (make_shape(4,16)), make_shape(4), (tuple{2_ct,4_ct}));
SCALAR_SUM_CASE(scalar_st.sum.4_32.fp32.2x4, (make_shape(4,32)), make_shape(4), (tuple{2_ct,4_ct}));
SCALAR_SUM_CASE(scalar_st.sum.4_64.fp32.2x4, (make_shape(4,64)), make_shape(4), (tuple{2_ct,4_ct}));
SCALAR_SUM_CASE(scalar_st.sum.4_128.fp32.2x4, (make_shape(4,128)), make_shape(4), (tuple{2_ct,4_ct}));
SCALAR_SUM_CASE(scalar_st.sum.4_256.fp32.2x4, (make_shape(4,256)), make_shape(4), (tuple{2_ct,4_ct}));
SCALAR_SUM_CASE(scalar_st.sum.4_512.fp32.2x4, (make_shape(4,512)), make_shape(4), (tuple{2_ct,4_ct}));
SCALAR_SUM_CASE(scalar_st.sum.4_1024.fp32.2x4, (make_shape(4,1024)), make_shape(4), (tuple{2_ct,4_ct}));
SCALAR_SUM_CASE(scalar_st.sum.4_2048.fp32.2x4, (make_shape(4,2048)), make_shape(4), (tuple{2_ct,4_ct}));