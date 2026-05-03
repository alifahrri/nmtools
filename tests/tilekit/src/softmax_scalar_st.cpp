#include "nmtools/tilekit/vector.hpp"
#include "nmtools/tilekit/thread_pool.hpp"
#include "nmtools/tilekit/tilekit.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/array/softmax.hpp"
#include "nmtools/ndarray.hpp"

#include "kernels/softmax.hpp"

#include <nanobench.h>

// due to different ordering of softmaxmation, the result may be different
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

namespace view = nmtools::view;
using nm::None, nm::True;

template <typename input_t, typename axis_t>
constexpr auto softmax(const input_t& input, axis_t axis)
{
    auto a_input = view::aliased(input);
    // following pytorch, only allow index axis (index array axis not allowed)
    static_assert( meta::is_index_v<axis_t>
        , "unsupported softmax, expect axis to be index"
    );
    // NOTE: this follow https://cs231n.github.io/linear-classify/#softmax for numerical stability
    auto a = nm::max(a_input,axis,/*dtype=*/None,/*initial=*/None,/*keepdims=*/True);
    auto b = nm::subtract(a_input,a);
    auto c = nm::exp(b);
    auto d = nm::sum(c,axis,/*dtype=*/None,/*initial=*/None,/*keepdims=*/True);
    return nm::divide(c,d);
} // softmax

#define SCALAR_SOFTMAX_CASE( case_name, shape, tile_shape ) \
TEST_CASE(#case_name * doctest::test_suite("tilekit")) \
{ \
    auto gen = nm::random_engine(); \
    auto dtype = nm::float32; \
\
    auto inp = nm::random(shape,dtype,gen); \
    auto out = nm::Array::zeros(shape,dtype); \
\
    auto ctx = scalar_st(); \
\
    auto min_time = std::chrono::nanoseconds(50'000'000); \
    ankerl::nanobench::Bench() \
        .minEpochTime(min_time) \
        .run(#case_name,[&](){ \
            softmax_kernel(ctx,out,inp,tk::index(tile_shape)); \
        }); \
\
    auto expected = ::softmax(inp,nm::ct_v<-1>); \
    NMTOOLS_ASSERT_CLOSE( out, expected ); \
}

SCALAR_SOFTMAX_CASE(scalar_st.softmax.2_8.fp32.2x4,    (make_shape(2,8)),    (tuple{2_ct,4_ct}) );
SCALAR_SOFTMAX_CASE(scalar_st.softmax.2_16.fp32.2x4,   (make_shape(2,16)),   (tuple{2_ct,4_ct}) );
SCALAR_SOFTMAX_CASE(scalar_st.softmax.2_32.fp32.2x4,   (make_shape(2,32)),   (tuple{2_ct,4_ct}) );
SCALAR_SOFTMAX_CASE(scalar_st.softmax.2_64.fp32.2x4,   (make_shape(2,64)),   (tuple{2_ct,4_ct}) );
SCALAR_SOFTMAX_CASE(scalar_st.softmax.2_128.fp32.2x4,  (make_shape(2,128)),  (tuple{2_ct,4_ct}) );
SCALAR_SOFTMAX_CASE(scalar_st.softmax.2_256.fp32.2x4,  (make_shape(2,256)),  (tuple{2_ct,4_ct}) );
SCALAR_SOFTMAX_CASE(scalar_st.softmax.2_512.fp32.2x4,  (make_shape(2,512)),  (tuple{2_ct,4_ct}) );
SCALAR_SOFTMAX_CASE(scalar_st.softmax.2_1024.fp32.2x4, (make_shape(2,1024)), (tuple{2_ct,4_ct}) );
SCALAR_SOFTMAX_CASE(scalar_st.softmax.2_2048.fp32.2x4, (make_shape(2,2048)), (tuple{2_ct,4_ct}) );

SCALAR_SOFTMAX_CASE(scalar_st.softmax.2_ct_8_ct.fp32.2x4,    (make_shape(2_ct,8_ct)),    (tuple{2_ct,4_ct}) );
SCALAR_SOFTMAX_CASE(scalar_st.softmax.2_ct_16_ct.fp32.2x4,   (make_shape(2_ct,16_ct)),   (tuple{2_ct,4_ct}) );
SCALAR_SOFTMAX_CASE(scalar_st.softmax.2_ct_32_ct.fp32.2x4,   (make_shape(2_ct,32_ct)),   (tuple{2_ct,4_ct}) );
SCALAR_SOFTMAX_CASE(scalar_st.softmax.2_ct_64_ct.fp32.2x4,   (make_shape(2_ct,64_ct)),   (tuple{2_ct,4_ct}) );
SCALAR_SOFTMAX_CASE(scalar_st.softmax.2_ct_128_ct.fp32.2x4,  (make_shape(2_ct,128_ct)),  (tuple{2_ct,4_ct}) );
SCALAR_SOFTMAX_CASE(scalar_st.softmax.2_ct_256_ct.fp32.2x4,  (make_shape(2_ct,256_ct)),  (tuple{2_ct,4_ct}) );
SCALAR_SOFTMAX_CASE(scalar_st.softmax.2_ct_512_ct.fp32.2x4,  (make_shape(2_ct,512_ct)),  (tuple{2_ct,4_ct}) );
SCALAR_SOFTMAX_CASE(scalar_st.softmax.2_ct_1024_ct.fp32.2x4, (make_shape(2_ct,1024_ct)), (tuple{2_ct,4_ct}) );
SCALAR_SOFTMAX_CASE(scalar_st.softmax.2_ct_2048_ct.fp32.2x4, (make_shape(2_ct,2048_ct)), (tuple{2_ct,4_ct}) );

SCALAR_SOFTMAX_CASE(scalar_st.softmax.4_8.fp32.2x4,    (make_shape(4,8)),    (tuple{2_ct,4_ct}) );
SCALAR_SOFTMAX_CASE(scalar_st.softmax.4_16.fp32.2x4,   (make_shape(4,16)),   (tuple{2_ct,4_ct}) );
SCALAR_SOFTMAX_CASE(scalar_st.softmax.4_32.fp32.2x4,   (make_shape(4,32)),   (tuple{2_ct,4_ct}) );
SCALAR_SOFTMAX_CASE(scalar_st.softmax.4_64.fp32.2x4,   (make_shape(4,64)),   (tuple{2_ct,4_ct}) );
SCALAR_SOFTMAX_CASE(scalar_st.softmax.4_128.fp32.2x4,  (make_shape(4,128)),  (tuple{2_ct,4_ct}) );
SCALAR_SOFTMAX_CASE(scalar_st.softmax.4_256.fp32.2x4,  (make_shape(4,256)),  (tuple{2_ct,4_ct}) );
SCALAR_SOFTMAX_CASE(scalar_st.softmax.4_512.fp32.2x4,  (make_shape(4,512)),  (tuple{2_ct,4_ct}) );
SCALAR_SOFTMAX_CASE(scalar_st.softmax.4_1024.fp32.2x4, (make_shape(4,1024)), (tuple{2_ct,4_ct}) );
SCALAR_SOFTMAX_CASE(scalar_st.softmax.4_2048.fp32.2x4, (make_shape(4,2048)), (tuple{2_ct,4_ct}) );

SCALAR_SOFTMAX_CASE(scalar_st.softmax.4_ct_8_ct.fp32.2x4,    (make_shape(4_ct,8_ct)),    (tuple{2_ct,4_ct}) );
SCALAR_SOFTMAX_CASE(scalar_st.softmax.4_ct_16_ct.fp32.2x4,   (make_shape(4_ct,16_ct)),   (tuple{2_ct,4_ct}) );
SCALAR_SOFTMAX_CASE(scalar_st.softmax.4_ct_32_ct.fp32.2x4,   (make_shape(4_ct,32_ct)),   (tuple{2_ct,4_ct}) );
SCALAR_SOFTMAX_CASE(scalar_st.softmax.4_ct_64_ct.fp32.2x4,   (make_shape(4_ct,64_ct)),   (tuple{2_ct,4_ct}) );
SCALAR_SOFTMAX_CASE(scalar_st.softmax.4_ct_128_ct.fp32.2x4,  (make_shape(4_ct,128_ct)),  (tuple{2_ct,4_ct}) );
SCALAR_SOFTMAX_CASE(scalar_st.softmax.4_ct_256_ct.fp32.2x4,  (make_shape(4_ct,256_ct)),  (tuple{2_ct,4_ct}) );
SCALAR_SOFTMAX_CASE(scalar_st.softmax.4_ct_512_ct.fp32.2x4,  (make_shape(4_ct,512_ct)),  (tuple{2_ct,4_ct}) );
SCALAR_SOFTMAX_CASE(scalar_st.softmax.4_ct_1024_ct.fp32.2x4, (make_shape(4_ct,1024_ct)), (tuple{2_ct,4_ct}) );
SCALAR_SOFTMAX_CASE(scalar_st.softmax.4_ct_2048_ct.fp32.2x4, (make_shape(4_ct,2048_ct)), (tuple{2_ct,4_ct}) );

SCALAR_SOFTMAX_CASE(scalar_st.softmax.2_8.8.fp32.2x4,       (make_shape(2,8)),    (tuple{2_ct,4_ct}) );
SCALAR_SOFTMAX_CASE(scalar_st.softmax.2_16.16.fp32.2x4,     (make_shape(2,16)),   (tuple{2_ct,4_ct}) );
SCALAR_SOFTMAX_CASE(scalar_st.softmax.2_32.32.fp32.2x4,     (make_shape(2,32)),   (tuple{2_ct,4_ct}) );
SCALAR_SOFTMAX_CASE(scalar_st.softmax.2_64.64.fp32.2x4,     (make_shape(2,64)),   (tuple{2_ct,4_ct}) );
SCALAR_SOFTMAX_CASE(scalar_st.softmax.2_128.128.fp32.2x4,   (make_shape(2,128)),  (tuple{2_ct,4_ct}) );
SCALAR_SOFTMAX_CASE(scalar_st.softmax.2_256.256.fp32.2x4,   (make_shape(2,256)),  (tuple{2_ct,4_ct}) );
SCALAR_SOFTMAX_CASE(scalar_st.softmax.2_512.512.fp32.2x4,   (make_shape(2,512)),  (tuple{2_ct,4_ct}) );
SCALAR_SOFTMAX_CASE(scalar_st.softmax.2_1024.1024.fp32.2x4, (make_shape(2,1024)), (tuple{2_ct,4_ct}) );
SCALAR_SOFTMAX_CASE(scalar_st.softmax.2_2048.2048.fp32.2x4, (make_shape(2,2048)), (tuple{2_ct,4_ct}) );

SCALAR_SOFTMAX_CASE(scalar_st.softmax.2_ct_8_ct.fp32.2x4,       (make_shape(2_ct,8_ct)),    (tuple{2_ct,4_ct}) );
SCALAR_SOFTMAX_CASE(scalar_st.softmax.2_ct_16_ct.fp32.2x4,     (make_shape(2_ct,16_ct)),   (tuple{2_ct,4_ct}) );
SCALAR_SOFTMAX_CASE(scalar_st.softmax.2_ct_32_ct.fp32.2x4,     (make_shape(2_ct,32_ct)),   (tuple{2_ct,4_ct}) );
SCALAR_SOFTMAX_CASE(scalar_st.softmax.2_ct_64_ct.fp32.2x4,     (make_shape(2_ct,64_ct)),   (tuple{2_ct,4_ct}) );
SCALAR_SOFTMAX_CASE(scalar_st.softmax.2_ct_128_ct.fp32.2x4,   (make_shape(2_ct,128_ct)),  (tuple{2_ct,4_ct}) );
SCALAR_SOFTMAX_CASE(scalar_st.softmax.2_ct_256_ct.fp32.2x4,   (make_shape(2_ct,256_ct)),  (tuple{2_ct,4_ct}) );
SCALAR_SOFTMAX_CASE(scalar_st.softmax.2_ct_512_ct.fp32.2x4,   (make_shape(2_ct,512_ct)),  (tuple{2_ct,4_ct}) );
SCALAR_SOFTMAX_CASE(scalar_st.softmax.2_ct_1024_ct.fp32.2x4, (make_shape(2_ct,1024_ct)), (tuple{2_ct,4_ct}) );
SCALAR_SOFTMAX_CASE(scalar_st.softmax.2_ct_2048_ct.fp32.2x4, (make_shape(2_ct,2048_ct)), (tuple{2_ct,4_ct}) );

SCALAR_SOFTMAX_CASE(scalar_st.softmax.4_8.8.fp32.2x4,       (make_shape(4,8)),    (tuple{2_ct,4_ct}) );
SCALAR_SOFTMAX_CASE(scalar_st.softmax.4_16.16.fp32.2x4,     (make_shape(4,16)),   (tuple{2_ct,4_ct}) );
SCALAR_SOFTMAX_CASE(scalar_st.softmax.4_32.32.fp32.2x4,     (make_shape(4,32)),   (tuple{2_ct,4_ct}) );
SCALAR_SOFTMAX_CASE(scalar_st.softmax.4_64.64.fp32.2x4,     (make_shape(4,64)),   (tuple{2_ct,4_ct}) );
SCALAR_SOFTMAX_CASE(scalar_st.softmax.4_128.128.fp32.2x4,   (make_shape(4,128)),  (tuple{2_ct,4_ct}) );
SCALAR_SOFTMAX_CASE(scalar_st.softmax.4_256.256.fp32.2x4,   (make_shape(4,256)),  (tuple{2_ct,4_ct}) );
SCALAR_SOFTMAX_CASE(scalar_st.softmax.4_512.512.fp32.2x4,   (make_shape(4,512)),  (tuple{2_ct,4_ct}) );
SCALAR_SOFTMAX_CASE(scalar_st.softmax.4_1024.1024.fp32.2x4, (make_shape(4,1024)), (tuple{2_ct,4_ct}) );
SCALAR_SOFTMAX_CASE(scalar_st.softmax.4_2048.2048.fp32.2x4, (make_shape(4,2048)), (tuple{2_ct,4_ct}) );

SCALAR_SOFTMAX_CASE(scalar_st.softmax.4_8.8.fp32.2x4,       (make_shape(4_ct,8_ct)),    (tuple{2_ct,4_ct}) );
SCALAR_SOFTMAX_CASE(scalar_st.softmax.4_16.16.fp32.2x4,     (make_shape(4_ct,16_ct)),   (tuple{2_ct,4_ct}) );
SCALAR_SOFTMAX_CASE(scalar_st.softmax.4_32.32.fp32.2x4,     (make_shape(4_ct,32_ct)),   (tuple{2_ct,4_ct}) );
SCALAR_SOFTMAX_CASE(scalar_st.softmax.4_64.64.fp32.2x4,     (make_shape(4_ct,64_ct)),   (tuple{2_ct,4_ct}) );
SCALAR_SOFTMAX_CASE(scalar_st.softmax.4_128.128.fp32.2x4,   (make_shape(4_ct,128_ct)),  (tuple{2_ct,4_ct}) );
SCALAR_SOFTMAX_CASE(scalar_st.softmax.4_256.256.fp32.2x4,   (make_shape(4_ct,256_ct)),  (tuple{2_ct,4_ct}) );
SCALAR_SOFTMAX_CASE(scalar_st.softmax.4_512.512.fp32.2x4,   (make_shape(4_ct,512_ct)),  (tuple{2_ct,4_ct}) );
SCALAR_SOFTMAX_CASE(scalar_st.softmax.4_1024.1024.fp32.2x4, (make_shape(4_ct,1024_ct)), (tuple{2_ct,4_ct}) );
SCALAR_SOFTMAX_CASE(scalar_st.softmax.4_2048.2048.fp32.2x4, (make_shape(4_ct,2048_ct)), (tuple{2_ct,4_ct}) );