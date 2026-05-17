#include "nmtools/tilekit/vector.hpp"
#include "nmtools/tilekit/tilekit.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/ndarray.hpp"
#include "nmtools/array/layer_norm.hpp"

#include "kernels/layer_norm.hpp"

#include <nanobench.h>

#undef NMTOOLS_TESTING_PRECISION
#define NMTOOLS_TESTING_PRECISION (1e-2)

namespace nm = nmtools;
namespace view = nmtools::view;
using namespace nmtools::literals;
using nmtools_tuple;

using context_t = tk::scalar_t;

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

template <typename input_t, typename weight_t, typename bias_t, typename axis_t, typename epsilon_t>
constexpr auto layer_norm(const input_t& input, const weight_t& weight, const bias_t& bias, const axis_t& axis, epsilon_t epsilon)
{
    using nmtools::None, nmtools::True;
    auto aliased  = view::aliased(input,weight,bias,epsilon);
    auto a_input  = nmtools::get<0>(aliased);
    auto a_weight = nmtools::get<1>(aliased);
    auto a_bias   = nmtools::get<2>(aliased);
    auto a_epsilon = nmtools::get<3>(aliased);

    auto dtype = None;
    auto ddof  = 0;
    auto keepdims = True;

    auto mean  = nmtools::mean(a_input,axis,dtype,keepdims);
    auto shift = view::subtract(a_input,mean);

    auto var  = nmtools::var(a_input,axis,dtype,ddof,keepdims);
    auto std  = view::sqrt(view::add(var,a_epsilon));
    auto norm = view::divide(shift,std);
    return nmtools::add(view::multiply(norm,a_weight),a_bias);
}

#define SCALAR_LAYER_NORM_CASE( case_name, shape, weight_shape, bias_shape, tile_shape, weight_tile, bias_tile, axis ) \
TEST_CASE(#case_name * doctest::test_suite("tilekit")) \
{ \
    auto gen   = nm::random_engine(); \
    auto dtype = nm::float32; \
    auto out_shape = shape; \
\
    auto weight = nm::random(weight_shape,dtype,gen); \
    auto bias   = nm::random(bias_shape,dtype,gen); \
    auto inp = nm::random(shape,dtype,gen); \
    auto out = nm::Array::zeros(out_shape,dtype); \
\
    auto ctx = context_t(); \
\
    auto min_time = std::chrono::nanoseconds(50'000'000); \
    ankerl::nanobench::Bench() \
        .minEpochTime(min_time) \
        .run(#case_name,[&](){ \
            layer_norm_kernel(ctx,out,inp,weight,bias,tk::index(tile_shape),tk::index(weight_tile),tk::index(bias_tile),axis); \
        }); \
    auto expected = ::layer_norm(inp,weight,bias,axis,1e-5); \
    NMTOOLS_ASSERT_CLOSE( out, expected ); \
}

SCALAR_LAYER_NORM_CASE(scalar_st.layer_norm.2_8.fp32.2x4,    (make_shape(2,8)),    make_shape(8), make_shape(8), (tuple{2_ct,4_ct}), (tuple{4_ct}), (tuple{4_ct}), nm::ct_v<-1> );
SCALAR_LAYER_NORM_CASE(scalar_st.layer_norm.2_16.fp32.2x4,   (make_shape(2,16)),   make_shape(16), make_shape(16), (tuple{2_ct,4_ct}), (tuple{4_ct}), (tuple{4_ct}), nm::ct_v<-1> );
SCALAR_LAYER_NORM_CASE(scalar_st.layer_norm.2_32.fp32.2x4,   (make_shape(2,32)),   make_shape(32), make_shape(32), (tuple{2_ct,4_ct}), (tuple{4_ct}), (tuple{4_ct}), nm::ct_v<-1> );
SCALAR_LAYER_NORM_CASE(scalar_st.layer_norm.2_64.fp32.2x4,   (make_shape(2,64)),   make_shape(64), make_shape(64), (tuple{2_ct,4_ct}), (tuple{4_ct}), (tuple{4_ct}), nm::ct_v<-1> );
SCALAR_LAYER_NORM_CASE(scalar_st.layer_norm.2_128.fp32.2x4,  (make_shape(2,128)),  make_shape(128), make_shape(128), (tuple{2_ct,4_ct}), (tuple{4_ct}), (tuple{4_ct}), nm::ct_v<-1> );
SCALAR_LAYER_NORM_CASE(scalar_st.layer_norm.2_256.fp32.2x4,  (make_shape(2,256)),  make_shape(256), make_shape(256), (tuple{2_ct,4_ct}), (tuple{4_ct}), (tuple{4_ct}), nm::ct_v<-1> );
SCALAR_LAYER_NORM_CASE(scalar_st.layer_norm.2_512.fp32.2x4,  (make_shape(2,512)),  make_shape(512), make_shape(512), (tuple{2_ct,4_ct}), (tuple{4_ct}), (tuple{4_ct}), nm::ct_v<-1> );
SCALAR_LAYER_NORM_CASE(scalar_st.layer_norm.2_1024.fp32.2x4, (make_shape(2,1024)), make_shape(1024), make_shape(1024), (tuple{2_ct,4_ct}), (tuple{4_ct}), (tuple{4_ct}), nm::ct_v<-1> );
SCALAR_LAYER_NORM_CASE(scalar_st.layer_norm.2_2048.fp32.2x4, (make_shape(2,2048)), make_shape(2048), make_shape(2048), (tuple{2_ct,4_ct}), (tuple{4_ct}), (tuple{4_ct}), nm::ct_v<-1> );

SCALAR_LAYER_NORM_CASE(scalar_st.layer_norm.2_ct_8_ct.fp32.2x4,    (make_shape(2_ct,8_ct)),    make_shape(8_ct), make_shape(8_ct), (tuple{2_ct,4_ct}), (tuple{4_ct}), (tuple{4_ct}), nm::ct_v<-1> );
SCALAR_LAYER_NORM_CASE(scalar_st.layer_norm.2_ct_16_ct.fp32.2x4,   (make_shape(2_ct,16_ct)),   make_shape(16_ct), make_shape(16_ct), (tuple{2_ct,4_ct}), (tuple{4_ct}), (tuple{4_ct}), nm::ct_v<-1> );
SCALAR_LAYER_NORM_CASE(scalar_st.layer_norm.2_ct_32_ct.fp32.2x4,   (make_shape(2_ct,32_ct)),   make_shape(32_ct), make_shape(32_ct), (tuple{2_ct,4_ct}), (tuple{4_ct}), (tuple{4_ct}), nm::ct_v<-1> );
SCALAR_LAYER_NORM_CASE(scalar_st.layer_norm.2_ct_64_ct.fp32.2x4,   (make_shape(2_ct,64_ct)),   make_shape(64_ct), make_shape(64_ct), (tuple{2_ct,4_ct}), (tuple{4_ct}), (tuple{4_ct}), nm::ct_v<-1> );
SCALAR_LAYER_NORM_CASE(scalar_st.layer_norm.2_ct_128_ct.fp32.2x4,  (make_shape(2_ct,128_ct)),  make_shape(128_ct), make_shape(128_ct), (tuple{2_ct,4_ct}), (tuple{4_ct}), (tuple{4_ct}), nm::ct_v<-1> );
SCALAR_LAYER_NORM_CASE(scalar_st.layer_norm.2_ct_256_ct.fp32.2x4,  (make_shape(2_ct,256_ct)),  make_shape(256_ct), make_shape(256_ct), (tuple{2_ct,4_ct}), (tuple{4_ct}), (tuple{4_ct}), nm::ct_v<-1> );
SCALAR_LAYER_NORM_CASE(scalar_st.layer_norm.2_ct_512_ct.fp32.2x4,  (make_shape(2_ct,512_ct)),  make_shape(512_ct), make_shape(512_ct), (tuple{2_ct,4_ct}), (tuple{4_ct}), (tuple{4_ct}), nm::ct_v<-1> );
SCALAR_LAYER_NORM_CASE(scalar_st.layer_norm.2_ct_1024_ct.fp32.2x4, (make_shape(2_ct,1024_ct)), make_shape(1024_ct), make_shape(1024_ct), (tuple{2_ct,4_ct}), (tuple{4_ct}), (tuple{4_ct}), nm::ct_v<-1> );
SCALAR_LAYER_NORM_CASE(scalar_st.layer_norm.2_ct_2048_ct.fp32.2x4, (make_shape(2_ct,2048_ct)), make_shape(2048_ct), make_shape(2048_ct), (tuple{2_ct,4_ct}), (tuple{4_ct}), (tuple{4_ct}), nm::ct_v<-1> );

SCALAR_LAYER_NORM_CASE(scalar_st.layer_norm.4_8.fp32.2x4,    (make_shape(4,8)),    make_shape(8), make_shape(8), (tuple{2_ct,4_ct}), (tuple{4_ct}), (tuple{4_ct}), nm::ct_v<-1> );
SCALAR_LAYER_NORM_CASE(scalar_st.layer_norm.4_16.fp32.2x4,   (make_shape(4,16)),   make_shape(16), make_shape(16), (tuple{2_ct,4_ct}), (tuple{4_ct}), (tuple{4_ct}), nm::ct_v<-1> );
SCALAR_LAYER_NORM_CASE(scalar_st.layer_norm.4_32.fp32.2x4,   (make_shape(4,32)),   make_shape(32), make_shape(32), (tuple{2_ct,4_ct}), (tuple{4_ct}), (tuple{4_ct}), nm::ct_v<-1> );
SCALAR_LAYER_NORM_CASE(scalar_st.layer_norm.4_64.fp32.2x4,   (make_shape(4,64)),   make_shape(64), make_shape(64), (tuple{2_ct,4_ct}), (tuple{4_ct}), (tuple{4_ct}), nm::ct_v<-1> );
SCALAR_LAYER_NORM_CASE(scalar_st.layer_norm.4_128.fp32.2x4,  (make_shape(4,128)),  make_shape(128), make_shape(128), (tuple{2_ct,4_ct}), (tuple{4_ct}), (tuple{4_ct}), nm::ct_v<-1> );
SCALAR_LAYER_NORM_CASE(scalar_st.layer_norm.4_256.fp32.2x4,  (make_shape(4,256)),  make_shape(256), make_shape(256), (tuple{2_ct,4_ct}), (tuple{4_ct}), (tuple{4_ct}), nm::ct_v<-1> );
SCALAR_LAYER_NORM_CASE(scalar_st.layer_norm.4_512.fp32.2x4,  (make_shape(4,512)),  make_shape(512), make_shape(512), (tuple{2_ct,4_ct}), (tuple{4_ct}), (tuple{4_ct}), nm::ct_v<-1> );
SCALAR_LAYER_NORM_CASE(scalar_st.layer_norm.4_1024.fp32.2x4, (make_shape(4,1024)), make_shape(1024), make_shape(1024), (tuple{2_ct,4_ct}), (tuple{4_ct}), (tuple{4_ct}), nm::ct_v<-1> );
SCALAR_LAYER_NORM_CASE(scalar_st.layer_norm.4_2048.fp32.2x4, (make_shape(4,2048)), make_shape(2048), make_shape(2048), (tuple{2_ct,4_ct}), (tuple{4_ct}), (tuple{4_ct}), nm::ct_v<-1> );

SCALAR_LAYER_NORM_CASE(scalar_st.layer_norm.4_ct_8_ct.fp32.2x4,    (make_shape(4_ct,8_ct)),    make_shape(8_ct), make_shape(8_ct), (tuple{2_ct,4_ct}), (tuple{4_ct}), (tuple{4_ct}), nm::ct_v<-1> );
SCALAR_LAYER_NORM_CASE(scalar_st.layer_norm.4_ct_16_ct.fp32.2x4,   (make_shape(4_ct,16_ct)),   make_shape(16_ct), make_shape(16_ct), (tuple{2_ct,4_ct}), (tuple{4_ct}), (tuple{4_ct}), nm::ct_v<-1> );
SCALAR_LAYER_NORM_CASE(scalar_st.layer_norm.4_ct_32_ct.fp32.2x4,   (make_shape(4_ct,32_ct)),   make_shape(32_ct), make_shape(32_ct), (tuple{2_ct,4_ct}), (tuple{4_ct}), (tuple{4_ct}), nm::ct_v<-1> );
SCALAR_LAYER_NORM_CASE(scalar_st.layer_norm.4_ct_64_ct.fp32.2x4,   (make_shape(4_ct,64_ct)),   make_shape(64_ct), make_shape(64_ct), (tuple{2_ct,4_ct}), (tuple{4_ct}), (tuple{4_ct}), nm::ct_v<-1> );
SCALAR_LAYER_NORM_CASE(scalar_st.layer_norm.4_ct_128_ct.fp32.2x4,  (make_shape(4_ct,128_ct)),  make_shape(128_ct), make_shape(128_ct), (tuple{2_ct,4_ct}), (tuple{4_ct}), (tuple{4_ct}), nm::ct_v<-1> );
SCALAR_LAYER_NORM_CASE(scalar_st.layer_norm.4_ct_256_ct.fp32.2x4,  (make_shape(4_ct,256_ct)),  make_shape(256_ct), make_shape(256_ct), (tuple{2_ct,4_ct}), (tuple{4_ct}), (tuple{4_ct}), nm::ct_v<-1> );
SCALAR_LAYER_NORM_CASE(scalar_st.layer_norm.4_ct_512_ct.fp32.2x4,  (make_shape(4_ct,512_ct)),  make_shape(512_ct), make_shape(512_ct), (tuple{2_ct,4_ct}), (tuple{4_ct}), (tuple{4_ct}), nm::ct_v<-1> );
SCALAR_LAYER_NORM_CASE(scalar_st.layer_norm.4_ct_1024_ct.fp32.2x4, (make_shape(4_ct,1024_ct)), make_shape(1024_ct), make_shape(1024_ct), (tuple{2_ct,4_ct}), (tuple{4_ct}), (tuple{4_ct}), nm::ct_v<-1> );
SCALAR_LAYER_NORM_CASE(scalar_st.layer_norm.4_ct_2048_ct.fp32.2x4, (make_shape(4_ct,2048_ct)), make_shape(2048_ct), make_shape(2048_ct), (tuple{2_ct,4_ct}), (tuple{4_ct}), (tuple{4_ct}), nm::ct_v<-1> );