// by default mbed declare using namespace std and mbed;
#define MBED_NO_GLOBAL_USING_DIRECTIVE
#include <mbed.h>
#include <math.h>
#include <unity.h>

// unity provide isnan and isinf as macro
// which breaks isnan and isinf ufuncs
#undef isnan
#undef isinf

#include "nmtools/array/ufuncs/clip.hpp"
#include "nmtools/array/ufuncs/add.hpp"
#include "nmtools/array/ufuncs/sin.hpp"
#include "nmtools/array/ufuncs/arctan2.hpp"
#include "nmtools/array/ufuncs/bitwise_and.hpp"
#include "nmtools/array/ufuncs/divide.hpp"
#include "nmtools/array/ufuncs/greater_equal.hpp"
#include "nmtools/array/ufuncs/hypot.hpp"
#include "nmtools/array/ufuncs/invert.hpp"
#include "nmtools/array/ufuncs/isfinite.hpp"
#include "nmtools/array/ufuncs/isinf.hpp"
#include "nmtools/array/ufuncs/isnan.hpp"
#include "nmtools/array/ufuncs/left_shift.hpp"
#include "nmtools/array/ufuncs/logical_and.hpp"
#include "nmtools/array/ufuncs/logical_not.hpp"
#include "nmtools/array/ufuncs/maximum.hpp"
#include "nmtools/array/ufuncs/multiply.hpp"
#include "nmtools/array/ufuncs/power.hpp"
#include "nmtools/array/ufuncs/reciprocal.hpp"
#include "nmtools/array/ufuncs/rint.hpp"
#include "nmtools/array/ufuncs/signbit.hpp"
#include "nmtools/array/ufuncs/sqrt.hpp"
#include "nmtools/array/ufuncs/subtract.hpp"
#include "nmtools/array/ufuncs/trunc.hpp"
#include "nmtools/array/ufuncs/tanh.hpp"
#include "nmtools/array/ufuncs/tan.hpp"
#include "nmtools/array/ufuncs/square.hpp"
#include "nmtools/array/ufuncs/exp.hpp"
#include "nmtools/array/ufuncs/exp2.hpp"
#include "nmtools/array/ufuncs/expm1.hpp"
#include "nmtools/array/ufuncs/fmax.hpp"
#include "nmtools/array/ufuncs/fmin.hpp"
#include "nmtools/array/ufuncs/fmod.hpp"
#include "nmtools/array/ufuncs/log.hpp"
#include "nmtools/array/ufuncs/log2.hpp"
#include "nmtools/array/ufuncs/log1p.hpp"
#include "nmtools/array/ufuncs/log10.hpp"
#include "nmtools/array/ufuncs/sinh.hpp"
#include "nmtools/array/ufuncs/cos.hpp"
#include "nmtools/array/ufuncs/cosh.hpp"
#include "nmtools/array/ufuncs/cbrt.hpp"
#include "nmtools/array/ufuncs/ceil.hpp"
#include "nmtools/array/ufuncs/equal.hpp"
#include "nmtools/array/ufuncs/greater.hpp"
#include "nmtools/array/ufuncs/less.hpp"
#include "nmtools/array/ufuncs/logical_or.hpp"
#include "nmtools/array/ufuncs/logical_xor.hpp"
#include "nmtools/array/ufuncs/minimum.hpp"
#include "nmtools/array/ufuncs/fabs.hpp"
#include "nmtools/array/ufuncs/floor.hpp"
#include "nmtools/array/ufuncs/not_equal.hpp"
#include "nmtools/array/ufuncs/less_equal.hpp"
#include "nmtools/array/ufuncs/positive.hpp"
#include "nmtools/array/ufuncs/negative.hpp"
#include "nmtools/array/ufuncs/arccos.hpp"
#include "nmtools/array/ufuncs/arccosh.hpp"
#include "nmtools/array/ufuncs/arcsin.hpp"
#include "nmtools/array/ufuncs/arcsinh.hpp"
#include "nmtools/array/ufuncs/arctan.hpp"
#include "nmtools/array/ufuncs/arctan2.hpp"
#include "nmtools/array/ufuncs/arctanh.hpp"
#include "nmtools/array/ufuncs/bitwise_and.hpp"
#include "nmtools/array/ufuncs/bitwise_or.hpp"
#include "nmtools/array/ufuncs/bitwise_xor.hpp"

#include "nmtools/testing/data/array/square.hpp"
#include "nmtools/testing/data/array/tan.hpp"
#include "nmtools/testing/data/array/tanh.hpp"
#include "nmtools/testing/data/array/trunc.hpp"
#include "nmtools/testing/data/array/subtract.hpp"
#include "nmtools/testing/data/array/sqrt.hpp"
#include "nmtools/testing/data/array/signbit.hpp"
#include "nmtools/testing/data/array/rint.hpp"
#include "nmtools/testing/data/array/reciprocal.hpp"
#include "nmtools/testing/data/array/power.hpp"
#include "nmtools/testing/data/array/multiply.hpp"
#include "nmtools/testing/data/array/maximum.hpp"
#include "nmtools/testing/data/array/logical_not.hpp"
#include "nmtools/testing/data/array/logical_and.hpp"
#include "nmtools/testing/data/array/left_shift.hpp"
#include "nmtools/testing/data/array/isnan.hpp"
#include "nmtools/testing/data/array/isinf.hpp"
#include "nmtools/testing/data/array/isfinite.hpp"
#include "nmtools/testing/data/array/invert.hpp"
#include "nmtools/testing/data/array/hypot.hpp"
#include "nmtools/testing/data/array/greater_equal.hpp"
#include "nmtools/testing/data/array/divide.hpp"
#include "nmtools/testing/data/array/bitwise_and.hpp"
#include "nmtools/testing/data/array/arctan2.hpp"
#include "nmtools/testing/data/array/sin.hpp"
#include "nmtools/testing/data/array/add.hpp"
#include "nmtools/testing/data/array/clip.hpp"
#include "nmtools/testing/data/array/exp.hpp"
#include "nmtools/testing/data/array/exp2.hpp"
#include "nmtools/testing/data/array/expm1.hpp"
#include "nmtools/testing/data/array/fmax.hpp"
#include "nmtools/testing/data/array/fmin.hpp"
#include "nmtools/testing/data/array/fmod.hpp"
#include "nmtools/testing/data/array/log.hpp"
#include "nmtools/testing/data/array/log2.hpp"
#include "nmtools/testing/data/array/log1p.hpp"
#include "nmtools/testing/data/array/log10.hpp"
#include "nmtools/testing/data/array/sinh.hpp"
#include "nmtools/testing/data/array/cos.hpp"
#include "nmtools/testing/data/array/cosh.hpp"
#include "nmtools/testing/data/array/cbrt.hpp"
#include "nmtools/testing/data/array/ceil.hpp"
#include "nmtools/testing/data/array/equal.hpp"
#include "nmtools/testing/data/array/greater.hpp"
#include "nmtools/testing/data/array/less.hpp"
#include "nmtools/testing/data/array/logical_or.hpp"
#include "nmtools/testing/data/array/logical_xor.hpp"
#include "nmtools/testing/data/array/minimum.hpp"
#include "nmtools/testing/data/array/fabs.hpp"
#include "nmtools/testing/data/array/floor.hpp"
#include "nmtools/testing/data/array/not_equal.hpp"
#include "nmtools/testing/data/array/less_equal.hpp"
#include "nmtools/testing/data/array/positive.hpp"
#include "nmtools/testing/data/array/negative.hpp"
#include "nmtools/testing/data/array/arccos.hpp"
#include "nmtools/testing/data/array/arccosh.hpp"
#include "nmtools/testing/data/array/arcsin.hpp"
#include "nmtools/testing/data/array/arcsinh.hpp"
#include "nmtools/testing/data/array/arctan.hpp"
#include "nmtools/testing/data/array/arctan2.hpp"
#include "nmtools/testing/data/array/arctanh.hpp"
#include "nmtools/testing/data/array/bitwise_and.hpp"
#include "nmtools/testing/data/array/bitwise_or.hpp"
#include "nmtools/testing/data/array/bitwise_xor.hpp"

#include "nmtools/array/var.hpp"
#include "nmtools/array/mean.hpp"
#include "nmtools/array/stddev.hpp"

#include "nmtools/testing/data/array/var.hpp"
#include "nmtools/testing/data/array/mean.hpp"
#include "nmtools/testing/data/array/stddev.hpp"

// activation functions are also implemented as ufunc
#include "nmtools/array/activations/relu.hpp"
#include "nmtools/array/activations/relu6.hpp"
#include "nmtools/array/activations/prelu.hpp"
#include "nmtools/array/activations/sigmoid.hpp"
#include "nmtools/array/activations/leaky_relu.hpp"
#include "nmtools/array/activations/hardtanh.hpp"
#include "nmtools/array/activations/hardswish.hpp"
#include "nmtools/array/activations/hardshrink.hpp"
#include "nmtools/array/activations/log_sigmoid.hpp"
#include "nmtools/array/activations/tanhshrink.hpp"
#include "nmtools/array/activations/softsign.hpp"
#include "nmtools/array/activations/softshrink.hpp"
#include "nmtools/array/activations/softplus.hpp"
#include "nmtools/array/activations/silu.hpp"
#include "nmtools/array/activations/selu.hpp"
#include "nmtools/array/activations/celu.hpp"
#include "nmtools/array/activations/elu.hpp"
#include "nmtools/array/activations/mish.hpp"

#include "nmtools/testing/data/array/relu.hpp"
#include "nmtools/testing/data/array/relu6.hpp"
#include "nmtools/testing/data/array/prelu.hpp"
#include "nmtools/testing/data/array/sigmoid.hpp"
#include "nmtools/testing/data/array/leaky_relu.hpp"
#include "nmtools/testing/data/array/hardtanh.hpp"
#include "nmtools/testing/data/array/hardswish.hpp"
#include "nmtools/testing/data/array/hardshrink.hpp"
#include "nmtools/testing/data/array/log_sigmoid.hpp"
#include "nmtools/testing/data/array/tanhshrink.hpp"
#include "nmtools/testing/data/array/softsign.hpp"
#include "nmtools/testing/data/array/softshrink.hpp"
#include "nmtools/testing/data/array/softplus.hpp"
#include "nmtools/testing/data/array/silu.hpp"
#include "nmtools/testing/data/array/selu.hpp"
#include "nmtools/testing/data/array/celu.hpp"
#include "nmtools/testing/data/array/elu.hpp"
#include "nmtools/testing/data/array/mish.hpp"

#include "nmtools/utility/isequal.hpp"
#include "nmtools/utility/isclose.hpp"
#include "nmtools/utility/to_string.hpp"

namespace nm = nmtools;
namespace na = nmtools;
namespace view = nm::view;

using nm::utils::isclose, nm::utils::isequal;

#define NMTOOLS_PIO_SUBCASE(case_name, expected, function, ...) \
{ \
    using namespace case_name; \
    using namespace case_name::args; \
    auto res = function(__VA_ARGS__); \
    auto success = isclose(res, expect::expected, 1e-4); \
    TEST_ASSERT_TRUE( success ); \
}

void test_clip()
{
    NMTOOLS_TESTING_USE_CASE(array, clip);
    NMTOOLS_PIO_SUBCASE( case1, result, view::clip, a, amin, amax );
    NMTOOLS_PIO_SUBCASE( case2, result, view::clip, a, amin, amax );
    NMTOOLS_PIO_SUBCASE( case3, result, view::clip, a, amin, amax );
}

void test_add()
{
    NMTOOLS_TESTING_USE_CASE(view, add);
    NMTOOLS_PIO_SUBCASE( case1, result, view::add, a, b );
    NMTOOLS_PIO_SUBCASE( case2, result, view::add, a, b );
    NMTOOLS_PIO_SUBCASE( case3, result, view::add, a, b );
    NMTOOLS_PIO_SUBCASE( case4, result, view::add, a, b );
}

using nmtools::None;

void test_reduce_add()
{
    NMTOOLS_TESTING_USE_CASE(view, reduce_add);
    NMTOOLS_PIO_SUBCASE( case1, result, view::reduce_add, a, axis );
    NMTOOLS_PIO_SUBCASE( case2, result, view::reduce_add, a, axis );
    NMTOOLS_PIO_SUBCASE( case3, result, view::reduce_add, a, axis );
    NMTOOLS_PIO_SUBCASE( case4, result, view::reduce_add, a, axis );
    NMTOOLS_PIO_SUBCASE( case5, result, view::reduce_add, a, axis );
    NMTOOLS_PIO_SUBCASE( case6, result, view::reduce_add, a, axis );
    NMTOOLS_PIO_SUBCASE( case7, result, view::reduce_add, a, axis, dtype );
    NMTOOLS_PIO_SUBCASE( case8, result, view::reduce_add, a, axis, dtype, initial );
    NMTOOLS_PIO_SUBCASE( case9, result, view::reduce_add, a, axis, dtype, initial, keepdims );
    NMTOOLS_PIO_SUBCASE( case10, result, view::reduce_add, a, axis, dtype, initial, keepdims );
    NMTOOLS_PIO_SUBCASE( case11, result, view::reduce_add, a, axis, dtype, initial, keepdims );
    NMTOOLS_PIO_SUBCASE( case12, result, view::reduce_add, a, axis, dtype, initial, keepdims );
    NMTOOLS_PIO_SUBCASE( case13, result, view::reduce_add, a, axis, dtype, initial, keepdims );
    NMTOOLS_PIO_SUBCASE( case14, result, view::reduce_add, a, axis, dtype, initial, keepdims );
    NMTOOLS_PIO_SUBCASE( case15, result, view::reduce_add, a, axis );
    NMTOOLS_PIO_SUBCASE( case16, result, view::reduce_add, a, axis, None, initial );
    NMTOOLS_PIO_SUBCASE( case17, result, view::reduce_add, a, axis, None, initial );
    NMTOOLS_PIO_SUBCASE( case18, result, view::reduce_add, a, axis, None, initial, keepdims );
    NMTOOLS_PIO_SUBCASE( case19, result, view::reduce_add, a, axis, None, initial, keepdims );
    NMTOOLS_PIO_SUBCASE( case20, result, view::reduce_add, a, axis, None, initial, keepdims );
    NMTOOLS_PIO_SUBCASE( case21, result, view::reduce_add, a, axis, dtype );
    NMTOOLS_PIO_SUBCASE( case22, result, view::reduce_add, a, axis, dtype );
    NMTOOLS_PIO_SUBCASE( case23, result, view::reduce_add, a, axis, None, None, keepdims );
    NMTOOLS_PIO_SUBCASE( case24, result, view::reduce_add, a, axis, None, None, keepdims );
}

void test_accumulate_add()
{
    NMTOOLS_TESTING_USE_CASE(view, accumulate_add);
    NMTOOLS_PIO_SUBCASE( case1, result, view::accumulate_add, a, axis );
    NMTOOLS_PIO_SUBCASE( case2, result, view::accumulate_add, a, axis );
    NMTOOLS_PIO_SUBCASE( case3, result, view::accumulate_add, a, axis );
}

void test_outer_add()
{
    NMTOOLS_TESTING_USE_CASE(view, outer_add);
    NMTOOLS_PIO_SUBCASE( case1, result, view::outer_add, a, b );
}

void test_sin()
{
    NMTOOLS_TESTING_USE_CASE(view, sin);
    NMTOOLS_PIO_SUBCASE( case1, result, view::sin, a );
}

void test_relu()
{
    NMTOOLS_TESTING_USE_CASE(activations, relu);
    NMTOOLS_PIO_SUBCASE( case1, result, view::relu, a );
}

void test_relu6()
{
    NMTOOLS_TESTING_USE_CASE(activations, relu6);
    NMTOOLS_PIO_SUBCASE( case1, result, view::relu6, a );
}

void test_prelu()
{
    NMTOOLS_TESTING_USE_CASE(activations, prelu);
    NMTOOLS_PIO_SUBCASE( case1, result, view::prelu, a );
}

void test_leaky_relu()
{
    NMTOOLS_TESTING_USE_CASE(activations, leaky_relu);
    NMTOOLS_PIO_SUBCASE( case1, result, view::leaky_relu, a );
}

void test_sigmoid()
{
    NMTOOLS_TESTING_USE_CASE(activations, sigmoid);
    NMTOOLS_PIO_SUBCASE( case1, result, view::sigmoid, a );
}

void test_hardtanh()
{
    NMTOOLS_TESTING_USE_CASE(activations, hardtanh);
    NMTOOLS_PIO_SUBCASE( case1, result, view::hardtanh, a );
}

void test_hardshrink()
{
    NMTOOLS_TESTING_USE_CASE(activations, hardshrink);
    NMTOOLS_PIO_SUBCASE( case1, result, view::hardshrink, a );
}

void test_hardswish()
{
    NMTOOLS_TESTING_USE_CASE(activations, hardswish);
    NMTOOLS_PIO_SUBCASE( case1, result, view::hardswish, a );
}

void test_divide()
{
    NMTOOLS_TESTING_USE_CASE(view, divide);
    NMTOOLS_PIO_SUBCASE( case1, result, view::divide, a, b );
    NMTOOLS_PIO_SUBCASE( case2, result, view::divide, a, b );
}

void test_greater_equal()
{
    NMTOOLS_TESTING_USE_CASE(view, greater_equal);
    NMTOOLS_PIO_SUBCASE( case1, result, view::greater_equal, a, b );
    NMTOOLS_PIO_SUBCASE( case2, result, view::greater_equal, a, b );
}

void test_hypot()
{
    NMTOOLS_TESTING_USE_CASE(view, hypot);
    NMTOOLS_PIO_SUBCASE( case1, result, view::hypot, a, b );
    NMTOOLS_PIO_SUBCASE( case2, result, view::hypot, a, b );
}

void test_invert()
{
    NMTOOLS_TESTING_USE_CASE(view, invert);
    NMTOOLS_PIO_SUBCASE( case1, result, view::invert, a );
}

void test_isfinite()
{
    NMTOOLS_TESTING_USE_CASE(view, isfinite);
    NMTOOLS_PIO_SUBCASE( case1, result, view::isfinite, a );
}

void test_isinf()
{
    NMTOOLS_TESTING_USE_CASE(view, isinf);
    NMTOOLS_PIO_SUBCASE( case1, result, view::isinf, a );
}

void test_isnan()
{
    NMTOOLS_TESTING_USE_CASE(view, isnan);
    NMTOOLS_PIO_SUBCASE( case1, result, view::isnan, a );
}

void test_left_shift()
{
    NMTOOLS_TESTING_USE_CASE(view, left_shift);
    NMTOOLS_PIO_SUBCASE( case1, result, view::left_shift, a, b );
    NMTOOLS_PIO_SUBCASE( case2, result, view::left_shift, a, b );
}

void test_log_sigmoid()
{
    NMTOOLS_TESTING_USE_CASE(activations, log_sigmoid);
    NMTOOLS_PIO_SUBCASE( case1, result, view::log_sigmoid, a );
}

void test_logical_and()
{
    NMTOOLS_TESTING_USE_CASE(view, logical_and);
    NMTOOLS_PIO_SUBCASE( case1, result, view::logical_and, a, b );
    NMTOOLS_PIO_SUBCASE( case2, result, view::logical_and, a, b );
}

void test_logical_not()
{
    NMTOOLS_TESTING_USE_CASE(view, logical_not);
    NMTOOLS_PIO_SUBCASE( case1, result, view::logical_not, a );
}

void test_maximum()
{
    NMTOOLS_TESTING_USE_CASE(view, maximum);
    NMTOOLS_PIO_SUBCASE( case1, result, view::maximum, a, b );
    NMTOOLS_PIO_SUBCASE( case2, result, view::maximum, a, b );
}

void test_mean()
{
    NMTOOLS_TESTING_USE_CASE(array, mean);
    NMTOOLS_PIO_SUBCASE( case1, result, view::mean, a, axis );
    NMTOOLS_PIO_SUBCASE( case2, result, view::mean, a, axis );
    NMTOOLS_PIO_SUBCASE( case3, result, view::mean, a, axis );
    NMTOOLS_PIO_SUBCASE( case4, result, view::mean, a, axis );
    NMTOOLS_PIO_SUBCASE( case5, result, view::mean, a, axis );
    NMTOOLS_PIO_SUBCASE( case6, result, view::mean, a, axis, None, keepdims );
    NMTOOLS_PIO_SUBCASE( case7, result, view::mean, a, axis, None, keepdims );
    NMTOOLS_PIO_SUBCASE( case8, result, view::mean, a, axis, None, keepdims );
    NMTOOLS_PIO_SUBCASE( case9, result, view::mean, a, axis, None, keepdims );
    NMTOOLS_PIO_SUBCASE( case10, result, view::mean, a, axis, None, keepdims );
    NMTOOLS_PIO_SUBCASE( case11, result, view::mean, a, axis, None, keepdims );
    NMTOOLS_PIO_SUBCASE( case12, result, view::mean, a, axis, None, keepdims );
    NMTOOLS_PIO_SUBCASE( case13, result, view::mean, a, axis, None, keepdims );
    NMTOOLS_PIO_SUBCASE( case14, result, view::mean, a, axis, None, keepdims );
    NMTOOLS_PIO_SUBCASE( case15, result, view::mean, a, axis, None, keepdims );
    NMTOOLS_PIO_SUBCASE( case16, result, view::mean, a, axis, None, keepdims );
    NMTOOLS_PIO_SUBCASE( case17, result, view::mean, a, axis, None, keepdims );
    NMTOOLS_PIO_SUBCASE( case18, result, view::mean, a, axis, None, keepdims );
    NMTOOLS_PIO_SUBCASE( case19, result, view::mean, a, axis, None, keepdims );
    NMTOOLS_PIO_SUBCASE( case20, result, view::mean, a, axis, None, keepdims );
    NMTOOLS_PIO_SUBCASE( case21, result, view::mean, a, axis, None, keepdims );
    NMTOOLS_PIO_SUBCASE( case22, result, view::mean, a, axis, None, keepdims );
    NMTOOLS_PIO_SUBCASE( case23, result, view::mean, a, axis, None, keepdims );
    NMTOOLS_PIO_SUBCASE( case24, result, view::mean, a, axis, None, keepdims );
    NMTOOLS_PIO_SUBCASE( case25, result, view::mean, a, axis, None, keepdims );
    NMTOOLS_PIO_SUBCASE( case26, result, view::mean, a, axis, None, keepdims );
    NMTOOLS_PIO_SUBCASE( case27, result, view::mean, a, axis, None, keepdims );
    NMTOOLS_PIO_SUBCASE( case28, result, view::mean, a, axis, None, keepdims );
    NMTOOLS_PIO_SUBCASE( case29, result, view::mean, a, axis, None, keepdims );
    NMTOOLS_PIO_SUBCASE( case30, result, view::mean, a, axis, None, keepdims );
    NMTOOLS_PIO_SUBCASE( case31, result, view::mean, a, axis, None, keepdims );
    NMTOOLS_PIO_SUBCASE( case32, result, view::mean, a, axis, None, keepdims );
}

void test_multiply()
{
    NMTOOLS_TESTING_USE_CASE(view, multiply);
    NMTOOLS_PIO_SUBCASE( case1, result, view::multiply, a, b );
    NMTOOLS_PIO_SUBCASE( case2, result, view::multiply, a, b );
}

void test_power()
{
    NMTOOLS_TESTING_USE_CASE(view, power);
    NMTOOLS_PIO_SUBCASE( case1, result, view::power, a, b );
    NMTOOLS_PIO_SUBCASE( case2, result, view::power, a, b );
}

void test_reciprocal()
{
    NMTOOLS_TESTING_USE_CASE(view, reciprocal);
    NMTOOLS_PIO_SUBCASE( case1, result, view::reciprocal, a );
}

void test_rint()
{
    NMTOOLS_TESTING_USE_CASE(view, rint);
    NMTOOLS_PIO_SUBCASE( case1, result, view::rint, a );
}

void test_signbit()
{
    NMTOOLS_TESTING_USE_CASE(view, signbit);
    NMTOOLS_PIO_SUBCASE( case1, result, view::signbit, a );
}

void test_sqrt()
{
    NMTOOLS_TESTING_USE_CASE(view, sqrt);
    NMTOOLS_PIO_SUBCASE( case1, result, view::sqrt, a );
}

void test_stddev()
{
    NMTOOLS_TESTING_USE_CASE(array, stddev);
    NMTOOLS_PIO_SUBCASE( case1, result, view::stddev, array, axis, None, ddof, keepdims );
    NMTOOLS_PIO_SUBCASE( case2, result, view::stddev, array, axis, None, ddof, keepdims );
    NMTOOLS_PIO_SUBCASE( case3, result, view::stddev, array, axis, None, ddof, keepdims );
    NMTOOLS_PIO_SUBCASE( case4, result, view::stddev, array, axis, None, ddof, keepdims );
    NMTOOLS_PIO_SUBCASE( case5, result, view::stddev, array, axis, None, ddof, keepdims );
    NMTOOLS_PIO_SUBCASE( case6, result, view::stddev, array, axis, None, ddof, keepdims );
    NMTOOLS_PIO_SUBCASE( case7, result, view::stddev, array, axis, None, ddof, keepdims );
    NMTOOLS_PIO_SUBCASE( case8, result, view::stddev, array, axis, None, ddof, keepdims );
    NMTOOLS_PIO_SUBCASE( case9, result, view::stddev, array, axis, None, ddof, keepdims );
    NMTOOLS_PIO_SUBCASE( case10, result, view::stddev, array, axis, None, ddof, keepdims );
    NMTOOLS_PIO_SUBCASE( case11, result, view::stddev, array, axis, None, ddof, keepdims );
    NMTOOLS_PIO_SUBCASE( case12, result, view::stddev, array, axis, None, ddof, keepdims );
    NMTOOLS_PIO_SUBCASE( case13, result, view::stddev, array, axis, None, ddof, keepdims );
    NMTOOLS_PIO_SUBCASE( case14, result, view::stddev, array, axis, None, ddof, keepdims );
    NMTOOLS_PIO_SUBCASE( case15, result, view::stddev, array, axis, None, ddof, keepdims );
    NMTOOLS_PIO_SUBCASE( case16, result, view::stddev, array, axis, None, ddof, keepdims );
    NMTOOLS_PIO_SUBCASE( case17, result, view::stddev, array, axis, None, ddof, keepdims );
}

void test_subtract()
{
    NMTOOLS_TESTING_USE_CASE( view, subtract );
    NMTOOLS_PIO_SUBCASE( case1, result, view::subtract, a, b );
    NMTOOLS_PIO_SUBCASE( case2, result, view::subtract, a, b );
}

void test_trunc()
{
    NMTOOLS_TESTING_USE_CASE( view, trunc );
    NMTOOLS_PIO_SUBCASE( case1, result, view::trunc, a );
}

void test_var()
{
    NMTOOLS_TESTING_USE_CASE( array, var );
    NMTOOLS_PIO_SUBCASE( case1, result, view::var, array, axis );
    NMTOOLS_PIO_SUBCASE( case2, result, view::var, array, axis );
    NMTOOLS_PIO_SUBCASE( case3, result, view::var, array, axis );
    NMTOOLS_PIO_SUBCASE( case4, result, view::var, array, axis );
    NMTOOLS_PIO_SUBCASE( case5, result, view::var, array, axis );
    NMTOOLS_PIO_SUBCASE( case6, result, view::var, array, axis, None, ddof, keepdims );
    NMTOOLS_PIO_SUBCASE( case7, result, view::var, array, axis, None, ddof, keepdims );
    NMTOOLS_PIO_SUBCASE( case8, result, view::var, array, axis, None, ddof, keepdims );
    NMTOOLS_PIO_SUBCASE( case9, result, view::var, array, axis, None, ddof, keepdims );
    NMTOOLS_PIO_SUBCASE( case10, result, view::var, array, axis, None, ddof, keepdims );
    NMTOOLS_PIO_SUBCASE( case11, result, view::var, array, axis, None, ddof, keepdims );
    NMTOOLS_PIO_SUBCASE( case12, result, view::var, array, axis, None, ddof, keepdims );
    NMTOOLS_PIO_SUBCASE( case13, result, view::var, array, axis, None, ddof, keepdims );
    NMTOOLS_PIO_SUBCASE( case14, result, view::var, array, axis, None, ddof, keepdims );
}

void test_tanhshrink()
{
    NMTOOLS_TESTING_USE_CASE( activations, tanhshrink );
    NMTOOLS_PIO_SUBCASE( case1, result, view::tanhshrink, a );
}

void test_tanh()
{
    NMTOOLS_TESTING_USE_CASE( view, tanh );
    NMTOOLS_PIO_SUBCASE( case1, result, view::tanh, a );
}

void test_tan()
{
    NMTOOLS_TESTING_USE_CASE( view, tan );
    NMTOOLS_PIO_SUBCASE( case1, result, view::tan, a );
}

void test_square()
{
    NMTOOLS_TESTING_USE_CASE( view, square );
    NMTOOLS_PIO_SUBCASE( case1, result, view::square, a );
}

void test_softsign()
{
    NMTOOLS_TESTING_USE_CASE( activations, softsign );
    NMTOOLS_PIO_SUBCASE( case1, result, view::softsign, a );
}

void test_softshrink()
{
    NMTOOLS_TESTING_USE_CASE( activations, softshrink );
    NMTOOLS_PIO_SUBCASE( case1, result, view::softshrink, a );
}

void test_softplus()
{
    NMTOOLS_TESTING_USE_CASE( activations, softplus );
    NMTOOLS_PIO_SUBCASE( case1, result, view::softplus, a );
}

void test_silu()
{
    NMTOOLS_TESTING_USE_CASE( activations, silu );
    NMTOOLS_PIO_SUBCASE( case1, result, view::silu, a );
}

void test_selu()
{
    NMTOOLS_TESTING_USE_CASE( activations, selu );
    NMTOOLS_PIO_SUBCASE( case1, result, view::selu, a );
}

void test_celu()
{
    NMTOOLS_TESTING_USE_CASE( activations, celu );
    NMTOOLS_PIO_SUBCASE( case1, result, view::celu, a );
    NMTOOLS_PIO_SUBCASE( case2, result, view::celu, a, alpha );
}

void test_elu()
{
    NMTOOLS_TESTING_USE_CASE( activations, elu );
    NMTOOLS_PIO_SUBCASE( case1, result, view::elu, a );
    NMTOOLS_PIO_SUBCASE( case2, result, view::elu, a, alpha );
}

void test_exp()
{
    NMTOOLS_TESTING_USE_CASE( view, exp );
    NMTOOLS_PIO_SUBCASE( case1, result, view::exp, a );
}

void test_exp2()
{
    NMTOOLS_TESTING_USE_CASE( view, exp2);
    NMTOOLS_PIO_SUBCASE( case1, result, view::exp2, a );
}

void test_expm1()
{
    NMTOOLS_TESTING_USE_CASE( view, expm1 );
    NMTOOLS_PIO_SUBCASE( case1, result, view::expm1, a );
}

void test_fmax()
{
    NMTOOLS_TESTING_USE_CASE( view, fmax );
    NMTOOLS_PIO_SUBCASE( case1, result, view::fmax, a, b );
    NMTOOLS_PIO_SUBCASE( case2, result, view::fmax, a, b );
}

void test_fmin()
{
    NMTOOLS_TESTING_USE_CASE( view, fmin );
    NMTOOLS_PIO_SUBCASE( case1, result, view::fmin, a, b );
    NMTOOLS_PIO_SUBCASE( case1, result, view::fmin, a, b );
}

void test_fmod()
{
    NMTOOLS_TESTING_USE_CASE( view, fmod );
    NMTOOLS_PIO_SUBCASE( case1, result, view::fmod, a, b );
    NMTOOLS_PIO_SUBCASE( case2, result, view::fmod, a, b );
}

void test_log()
{
    NMTOOLS_TESTING_USE_CASE( view, log );
    NMTOOLS_PIO_SUBCASE( case1, result, view::log, a );
}

void test_log2()
{
    NMTOOLS_TESTING_USE_CASE( view, log2 );
    NMTOOLS_PIO_SUBCASE( case1, result, view::log2, a );
}

void test_log1p()
{
    NMTOOLS_TESTING_USE_CASE( view, log1p );
    NMTOOLS_PIO_SUBCASE( case1, result, view::log1p, a );
}

void test_log10()
{
    NMTOOLS_TESTING_USE_CASE( view, log10 );
    NMTOOLS_PIO_SUBCASE( case1, result, view::log10, a );
}

void test_sinh()
{
    NMTOOLS_TESTING_USE_CASE( view, sinh );
    NMTOOLS_PIO_SUBCASE( case1, result, view::sinh, a );
}

void test_cos()
{
    NMTOOLS_TESTING_USE_CASE( view, cos );
    NMTOOLS_PIO_SUBCASE( case1, result, view::cos, a );
}

void test_cosh()
{
    NMTOOLS_TESTING_USE_CASE( view, cosh );
    NMTOOLS_PIO_SUBCASE( case1, result, view::cosh, a );
}

void test_cbrt()
{
    NMTOOLS_TESTING_USE_CASE( view, cbrt );
    NMTOOLS_PIO_SUBCASE( case1, result, view::cbrt, a );
}

void test_ceil()
{
    NMTOOLS_TESTING_USE_CASE( view, ceil );
    NMTOOLS_PIO_SUBCASE( case1, result, view::ceil, a );
}

void test_equal()
{
    NMTOOLS_TESTING_USE_CASE( view, equal );
    NMTOOLS_PIO_SUBCASE( case1, result, view::equal, a, b );
}

void test_greater()
{
    NMTOOLS_TESTING_USE_CASE( view, greater );
    NMTOOLS_PIO_SUBCASE( case1, result, view::greater, a, b );
}

void test_less()
{
    NMTOOLS_TESTING_USE_CASE( view, less );
    NMTOOLS_PIO_SUBCASE( case1, result, view::less, a, b );
}

void test_logical_or()
{
    NMTOOLS_TESTING_USE_CASE( view, logical_or );
    NMTOOLS_PIO_SUBCASE( case1, result, view::logical_or, a, b );
}

void test_logical_xor()
{
    NMTOOLS_TESTING_USE_CASE( view, logical_xor );
    NMTOOLS_PIO_SUBCASE( case1, result, view::logical_xor, a, b );
}

void test_minimum()
{
    NMTOOLS_TESTING_USE_CASE( view, minimum );
    NMTOOLS_PIO_SUBCASE( case1, result, view::minimum, a, b );
}

void test_fabs()
{
    NMTOOLS_TESTING_USE_CASE( view, fabs );
    NMTOOLS_PIO_SUBCASE( case1, result, view::fabs, a );
}

void test_floor()
{
    NMTOOLS_TESTING_USE_CASE( view, floor );
    NMTOOLS_PIO_SUBCASE( case1, result, view::floor, a )
}

void test_less_equal()
{
    NMTOOLS_TESTING_USE_CASE( view, less_equal );
    NMTOOLS_PIO_SUBCASE( case1, result, view::less_equal, a, b );
    NMTOOLS_PIO_SUBCASE( case2, result, view::less_equal, a, b );
}

void test_not_equal()
{
    NMTOOLS_TESTING_USE_CASE( view, not_equal );
    NMTOOLS_PIO_SUBCASE( case1, result, view::not_equal, a, b );
    NMTOOLS_PIO_SUBCASE( case2, result, view::not_equal, a, b );
}

void test_positive()
{
    NMTOOLS_TESTING_USE_CASE( view, positive );
    NMTOOLS_PIO_SUBCASE( case1, result, view::positive, a );
}

void test_negative()
{
    NMTOOLS_TESTING_USE_CASE( view, negative );
    NMTOOLS_PIO_SUBCASE( case1, result, view::negative, a );
}

void test_arccos()
{
    NMTOOLS_TESTING_USE_CASE( view, arccos );
    NMTOOLS_PIO_SUBCASE( case1, result, view::arccos, a );
}

void test_arccosh()
{
    NMTOOLS_TESTING_USE_CASE( view, arccosh );
    NMTOOLS_PIO_SUBCASE( case1, result, view::arccosh, a );
}

void test_arcsin()
{
    NMTOOLS_TESTING_USE_CASE( view, arcsin );
    NMTOOLS_PIO_SUBCASE( case1, result, view::arcsin, a );
}

void test_arcsinh()
{
    NMTOOLS_TESTING_USE_CASE( view, arcsinh );
    NMTOOLS_PIO_SUBCASE( case1, result, view::arcsinh, a );
}

void test_arctan()
{
    NMTOOLS_TESTING_USE_CASE( view, arctan );
    NMTOOLS_PIO_SUBCASE( case1, result, view::arctan, a );
}

void test_arctan2()
{
    NMTOOLS_TESTING_USE_CASE( view, arctan2 );
    NMTOOLS_PIO_SUBCASE( case1, result, view::arctan2, a, b );
}

void test_arctanh()
{
    NMTOOLS_TESTING_USE_CASE( view, arctanh );
    NMTOOLS_PIO_SUBCASE( case1, result, view::arctanh, a );
}

void test_bitwise_and()
{
    NMTOOLS_TESTING_USE_CASE( view, bitwise_and );
    NMTOOLS_PIO_SUBCASE( case1, result, view::bitwise_and, a, b );
    NMTOOLS_PIO_SUBCASE( case2, result, view::bitwise_and, a, b );
}

void test_bitwise_or()
{
    NMTOOLS_TESTING_USE_CASE( view, bitwise_or );
    NMTOOLS_PIO_SUBCASE( case1, result, view::bitwise_or, a, b );
    NMTOOLS_PIO_SUBCASE( case2, result, view::bitwise_or, a, b );
}

void test_bitwise_xor()
{
    NMTOOLS_TESTING_USE_CASE( view, bitwise_xor );
    NMTOOLS_PIO_SUBCASE( case1, result, view::bitwise_xor, a, b );
    NMTOOLS_PIO_SUBCASE( case2, result, view::bitwise_xor, a, b );
}

void test_mish()
{
    NMTOOLS_TESTING_USE_CASE( activations, mish );
    NMTOOLS_PIO_SUBCASE( case1, result, view::mish, a );
}

#define WAIT_TIME_MS 500

int main()
{
    thread_sleep_for(WAIT_TIME_MS);

    UNITY_BEGIN();

    RUN_TEST(test_add);
    RUN_TEST(test_sin);
    RUN_TEST(test_cos);
    RUN_TEST(test_tan);
    RUN_TEST(test_var);
    RUN_TEST(test_elu);
    RUN_TEST(test_exp);
    RUN_TEST(test_log);
    RUN_TEST(test_cbrt);
    RUN_TEST(test_ceil);
    RUN_TEST(test_exp2);
    RUN_TEST(test_log2);
    RUN_TEST(test_clip);
    RUN_TEST(test_silu);
    RUN_TEST(test_selu);
    RUN_TEST(test_celu);
    RUN_TEST(test_fmax);
    RUN_TEST(test_fmin);
    RUN_TEST(test_fmod);
    RUN_TEST(test_tanh);
    RUN_TEST(test_sinh);
    RUN_TEST(test_cosh);
    RUN_TEST(test_less);
    RUN_TEST(test_fabs);
    RUN_TEST(test_floor);
    RUN_TEST(test_expm1);
    RUN_TEST(test_log1p);
    RUN_TEST(test_log10);
    RUN_TEST(test_equal);
    RUN_TEST(test_relu);
    RUN_TEST(test_relu6);
    RUN_TEST(test_prelu);
    RUN_TEST(test_hypot);
    RUN_TEST(test_sigmoid);
    RUN_TEST(test_greater);
    RUN_TEST(test_arccos);
    RUN_TEST(test_arcsin);
    RUN_TEST(test_arctan);
    RUN_TEST(test_arccosh);
    RUN_TEST(test_arcsinh);
    RUN_TEST(test_arctan2);
    RUN_TEST(test_arctanh);
    RUN_TEST(test_divide);
    RUN_TEST(test_invert);
    RUN_TEST(test_square);
    RUN_TEST(test_mean);
    RUN_TEST(test_mish);
    RUN_TEST(test_rint);
    RUN_TEST(test_isinf);
    RUN_TEST(test_trunc);
    RUN_TEST(test_isnan);
    RUN_TEST(test_power);
    RUN_TEST(test_sqrt);
    RUN_TEST(test_stddev);
    RUN_TEST(test_maximum);
    RUN_TEST(test_minimum);
    RUN_TEST(test_signbit);
    RUN_TEST(test_subtract);
    RUN_TEST(test_multiply);
    RUN_TEST(test_isfinite);
    RUN_TEST(test_softsign);
    RUN_TEST(test_softplus);
    RUN_TEST(test_positive);
    RUN_TEST(test_negative);
    RUN_TEST(test_hardtanh);
    RUN_TEST(test_hardswish);
    RUN_TEST(test_hardshrink);
    RUN_TEST(test_not_equal);
    RUN_TEST(test_outer_add);
    RUN_TEST(test_reduce_add);
    RUN_TEST(test_leaky_relu);
    RUN_TEST(test_less_equal);
    RUN_TEST(test_softshrink);
    RUN_TEST(test_tanhshrink);
    RUN_TEST(test_reciprocal);
    RUN_TEST(test_left_shift);
    RUN_TEST(test_logical_or);
    RUN_TEST(test_bitwise_or);
    RUN_TEST(test_logical_xor);
    RUN_TEST(test_logical_and);
    RUN_TEST(test_bitwise_xor);
    RUN_TEST(test_bitwise_and);
    RUN_TEST(test_logical_not);
    RUN_TEST(test_log_sigmoid);
    RUN_TEST(test_greater_equal);
    RUN_TEST(test_accumulate_add);

    UNITY_END(); // stop unit testing

    while(true)
    {
        thread_sleep_for(WAIT_TIME_MS);
    }
}