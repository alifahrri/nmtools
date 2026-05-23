#include "nmtools/tilekit/vector.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/ndarray.hpp"

#include "kernels/dot.hpp"
#include "nmtools/array/dot.hpp"

#include <nanobench.h>

// due to different ordering of summation, the result may be different
// especially on big array
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

#define V256_DOT_CASE( case_name, shape, out_shape, tile_shape ) \
TEST_CASE(#case_name * doctest::test_suite("tilekit")) \
{ \
    auto gen = nm::random_engine(); \
    auto dtype = nm::float32; \
    auto dim1 = nm::at(shape,nm::ct_v<-1>); \
    auto rhs_shape = [&](){ \
        if constexpr (nm::is_constant_index_v<decltype(dim1)>) { \
            return nmtools_tuple{dim1}; \
        } else { \
            return nmtools_array{dim1}; \
        } \
    }(); \
\
    auto lhs = nm::random(shape,dtype,gen); \
    auto rhs = nm::random(rhs_shape,dtype,gen); \
    auto out = nm::Array::zeros(out_shape,dtype); \
\
    auto ctx = ctx_t(); \
\
    auto min_time = std::chrono::nanoseconds(50'000'000); \
    ankerl::nanobench::Bench() \
        .minEpochTime(min_time) \
        .run(#case_name,[&](){ \
            dot_kernel(ctx,out,lhs,rhs,tk::index(tile_shape)); \
        }); \
\
    auto expected = nm::dot(lhs,rhs); \
    NMTOOLS_ASSERT_CLOSE( out, expected ); \
}

V256_DOT_CASE( v256_st.dot.2_8.2.fp32.2x8,    (make_shape(2,8)),    make_shape(2), (tuple{2_ct,8_ct}) );
V256_DOT_CASE( v256_st.dot.2_16.2.fp32.2x8,   (make_shape(2,16)),   make_shape(2), (tuple{2_ct,8_ct}) );
V256_DOT_CASE( v256_st.dot.2_32.2.fp32.2x8,   (make_shape(2,32)),   make_shape(2), (tuple{2_ct,8_ct}) );
V256_DOT_CASE( v256_st.dot.2_64.2.fp32.2x8,   (make_shape(2,64)),   make_shape(2), (tuple{2_ct,8_ct}) );
V256_DOT_CASE( v256_st.dot.2_128.2.fp32.2x8,  (make_shape(2,128)),  make_shape(2), (tuple{2_ct,8_ct}) );
V256_DOT_CASE( v256_st.dot.2_256.2.fp32.2x8,  (make_shape(2,256)),  make_shape(2), (tuple{2_ct,8_ct}) );
V256_DOT_CASE( v256_st.dot.2_512.2.fp32.2x8,  (make_shape(2,512)),  make_shape(2), (tuple{2_ct,8_ct}) );
V256_DOT_CASE( v256_st.dot.2_1024.2.fp32.2x8, (make_shape(2,1024)), make_shape(2), (tuple{2_ct,8_ct}) );
V256_DOT_CASE( v256_st.dot.2_2048.2.fp32.2x8, (make_shape(2,2048)), make_shape(2), (tuple{2_ct,8_ct}) );

V256_DOT_CASE( v256_st.dot.2_ct_8_ct.2_ct.fp32.2x8,    (make_shape(2_ct,8_ct)),    make_shape(2_ct), (tuple{2_ct,8_ct}) );
V256_DOT_CASE( v256_st.dot.2_ct_16_ct.2_ct.fp32.2x8,   (make_shape(2_ct,16_ct)),   make_shape(2_ct), (tuple{2_ct,8_ct}) );
V256_DOT_CASE( v256_st.dot.2_ct_32_ct.2_ct.fp32.2x8,   (make_shape(2_ct,32_ct)),   make_shape(2_ct), (tuple{2_ct,8_ct}) );
V256_DOT_CASE( v256_st.dot.2_ct_64_ct.2_ct.fp32.2x8,   (make_shape(2_ct,64_ct)),   make_shape(2_ct), (tuple{2_ct,8_ct}) );
V256_DOT_CASE( v256_st.dot.2_ct_128_ct.2_ct.fp32.2x8,  (make_shape(2_ct,128_ct)),  make_shape(2_ct), (tuple{2_ct,8_ct}) );
V256_DOT_CASE( v256_st.dot.2_ct_256_ct.2_ct.fp32.2x8,  (make_shape(2_ct,256_ct)),  make_shape(2_ct), (tuple{2_ct,8_ct}) );
V256_DOT_CASE( v256_st.dot.2_ct_512_ct.2_ct.fp32.2x8,  (make_shape(2_ct,512_ct)),  make_shape(2_ct), (tuple{2_ct,8_ct}) );
V256_DOT_CASE( v256_st.dot.2_ct_1024_ct.2_ct.fp32.2x8, (make_shape(2_ct,1024_ct)), make_shape(2_ct), (tuple{2_ct,8_ct}) );
V256_DOT_CASE( v256_st.dot.2_ct_2048_ct.2_ct.fp32.2x8, (make_shape(2_ct,2048_ct)), make_shape(2_ct), (tuple{2_ct,8_ct}) );

V256_DOT_CASE( v256_st.dot.4_8.4.fp32.2x8,    (make_shape(4,8)),    make_shape(4), (tuple{2_ct,8_ct}) );
V256_DOT_CASE( v256_st.dot.4_16.4.fp32.2x8,   (make_shape(4,16)),   make_shape(4), (tuple{2_ct,8_ct}) );
V256_DOT_CASE( v256_st.dot.4_32.4.fp32.2x8,   (make_shape(4,32)),   make_shape(4), (tuple{2_ct,8_ct}) );
V256_DOT_CASE( v256_st.dot.4_64.4.fp32.2x8,   (make_shape(4,64)),   make_shape(4), (tuple{2_ct,8_ct}) );
V256_DOT_CASE( v256_st.dot.4_128.4.fp32.2x8,  (make_shape(4,128)),  make_shape(4), (tuple{2_ct,8_ct}) );
V256_DOT_CASE( v256_st.dot.4_256.4.fp32.2x8,  (make_shape(4,256)),  make_shape(4), (tuple{2_ct,8_ct}) );
V256_DOT_CASE( v256_st.dot.4_512.4.fp32.2x8,  (make_shape(4,512)),  make_shape(4), (tuple{2_ct,8_ct}) );
V256_DOT_CASE( v256_st.dot.4_1024.4.fp32.2x8, (make_shape(4,1024)), make_shape(4), (tuple{2_ct,8_ct}) );
V256_DOT_CASE( v256_st.dot.4_2048.4.fp32.2x8, (make_shape(4,2048)), make_shape(4), (tuple{2_ct,8_ct}) );

V256_DOT_CASE( v256_st.dot.4_ct_8_ct.4_ct.fp32.2x8,    (make_shape(4_ct,8_ct)),    make_shape(4_ct), (tuple{2_ct,8_ct}) );
V256_DOT_CASE( v256_st.dot.4_ct_16_ct.4_ct.fp32.2x8,   (make_shape(4_ct,16_ct)),   make_shape(4_ct), (tuple{2_ct,8_ct}) );
V256_DOT_CASE( v256_st.dot.4_ct_32_ct.4_ct.fp32.2x8,   (make_shape(4_ct,32_ct)),   make_shape(4_ct), (tuple{2_ct,8_ct}) );
V256_DOT_CASE( v256_st.dot.4_ct_64_ct.4_ct.fp32.2x8,   (make_shape(4_ct,64_ct)),   make_shape(4_ct), (tuple{2_ct,8_ct}) );
V256_DOT_CASE( v256_st.dot.4_ct_128_ct.4_ct.fp32.2x8,  (make_shape(4_ct,128_ct)),  make_shape(4_ct), (tuple{2_ct,8_ct}) );
V256_DOT_CASE( v256_st.dot.4_ct_256_ct.4_ct.fp32.2x8,  (make_shape(4_ct,256_ct)),  make_shape(4_ct), (tuple{2_ct,8_ct}) );
V256_DOT_CASE( v256_st.dot.4_ct_512_ct.4_ct.fp32.2x8,  (make_shape(4_ct,512_ct)),  make_shape(4_ct), (tuple{2_ct,8_ct}) );
V256_DOT_CASE( v256_st.dot.4_ct_1024_ct.4_ct.fp32.2x8, (make_shape(4_ct,1024_ct)), make_shape(4_ct), (tuple{2_ct,8_ct}) );
V256_DOT_CASE( v256_st.dot.4_ct_2048_ct.4_ct.fp32.2x8, (make_shape(4_ct,2048_ct)), make_shape(4_ct), (tuple{2_ct,8_ct}) );
