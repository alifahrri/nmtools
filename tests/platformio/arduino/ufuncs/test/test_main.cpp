#include "nmtools/meta.hpp"

#include "nmtools/array/array/ufuncs/add.hpp"
#include "nmtools/array/array/activations/relu.hpp"
#include "nmtools/array/array/mean.hpp"
#include "nmtools/array/array/matmul.hpp"

#include "nmtools/testing/data/array/add.hpp"
#include "nmtools/testing/data/array/relu.hpp"
#include "nmtools/testing/data/array/clip.hpp"
#include "nmtools/testing/data/array/mean.hpp"

#include <Arduino.h>
#include <unity.h>

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
namespace meta = nm::meta;

using nm::utils::isclose, nm::utils::isequal;

#define NMTOOLS_PIO_SUBCASE(case_name, expected, function, ...) \
{ \
    using namespace args; \
    auto res = function(__VA_ARGS__); \
    auto success = isclose(res, expect::expected); \
    TEST_ASSERT_TRUE( success ); \
}

#define NMTOOLS_PIO_CONSTEXPR_SUBCASE(case_name, expected, function, ...) \
{ \
    using namespace args; \
    constexpr auto res = function(__VA_ARGS__); \
    constexpr auto success = isclose(res, expect::expected); \
    static_assert( success ); \
    TEST_ASSERT_TRUE( success ); \
}

#define NM_TEST_SUBCASE(case_name, subcase_name) \
void test_##case_name##_##subcase_name()

#define NMTOOLS_PIO_RUN(test_name, case_name) \
RUN_TEST(test_##test_name##_##case_name);

#ifndef LED_BUILTIN
#define LED_BUILTIN PC13
#endif

/* ========================================================================= */

#if 1
NM_TEST_SUBCASE(add, case1)
{
    NMTOOLS_TESTING_DECLARE_NS( view, add, case1 );
    // NOTE: somehow broken on arduino uno (atmega328p) simavr (not confirmed on HW yet)
    // but ok on arduino mega (atmega2560) simavr, may be related to limited memory or smth
    NMTOOLS_PIO_SUBCASE( case1, result, view::add, a_a, b_a );
    NMTOOLS_PIO_SUBCASE( case1, result, na::add, a_a, b_a );
    NMTOOLS_PIO_SUBCASE( case1, result, view::add, a, b );
    NMTOOLS_PIO_SUBCASE( case1, result, na::add, a, b );
}

NM_TEST_SUBCASE(constexpr_add, case1)
{
    NMTOOLS_TESTING_DECLARE_NS( view, constexpr_add, case1);
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case1, result, view::add, a, b );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case1, result, view::add, a_a, b_a );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case1, result, view::add, a_f, b_f );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case1, result, view::add, a_h, b_h );

    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case1, result, na::add, a, b );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case1, result, na::add, a_a, b_a );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case1, result, na::add, a_f, b_f );
    // NOTE: currently deduced as dynamic array for eval,
    // TODO: fix by deducing this as hybrid ndarray
    // NMTOOLS_PIO_CONSTEXPR_SUBCASE( case1, result, na::add, a_h, b_h );
}

NM_TEST_SUBCASE(constexpr_add, case2)
{
    NMTOOLS_TESTING_DECLARE_NS( view, constexpr_add, case2);
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case2, result, view::add, a, b );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case2, result, view::add, a_a, b );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case2, result, view::add, a_f, b );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case2, result, view::add, a_h, b );

    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case2, result, na::add, a, b );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case2, result, na::add, a_a, b );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case2, result, na::add, a_f, b );
}

NM_TEST_SUBCASE(constexpr_add, case3)
{
    NMTOOLS_TESTING_DECLARE_NS( view, constexpr_add, case3);
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case3, result, view::add, a, b );

    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case3, result, na::add, a, b );
}

NM_TEST_SUBCASE(constexpr_add, case4)
{
    NMTOOLS_TESTING_DECLARE_NS( view, constexpr_add, case4);
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case4, result, view::add, a, b );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case4, result, view::add, a_a, b );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case4, result, view::add, a_f, b );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case4, result, view::add, a_h, b );

    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case4, result, na::add, a, b );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case4, result, na::add, a_a, b );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case4, result, na::add, a_f, b );
}
#endif

NM_TEST_SUBCASE(relu, case1)
{
    NMTOOLS_TESTING_DECLARE_NS( activations, relu, case1 );
    NMTOOLS_PIO_SUBCASE( case1, result, view::relu, a_a );
    NMTOOLS_PIO_SUBCASE( case1, result, na::relu, a_a );

    NMTOOLS_PIO_SUBCASE( case1, result, view::relu, a );
    NMTOOLS_PIO_SUBCASE( case1, result, na::relu, a );
} 

NM_TEST_SUBCASE(reduce_add, case1)
{
    NMTOOLS_TESTING_DECLARE_NS( view, reduce_add, case1);
    NMTOOLS_PIO_SUBCASE( case1, result, view::reduce_add, a_a, axis );
    NMTOOLS_PIO_SUBCASE( case1, result, view::reduce_add, a, axis );
    NMTOOLS_PIO_SUBCASE( case1, result, na::add.reduce, a_a, axis );
    NMTOOLS_PIO_SUBCASE( case1, result, na::add.reduce, a, axis );
}

NM_TEST_SUBCASE(constexpr_reduce_add, case1)
{
    NMTOOLS_TESTING_DECLARE_NS( array, constexpr_reduce_add, case1);
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case1, result, view::reduce_add, a_a, axis );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case1, result, view::reduce_add, a, axis );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case1, result, na::add.reduce, a_a, axis );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case1, result, na::add.reduce, a, axis );
}

NM_TEST_SUBCASE(constexpr_reduce_add, case4)
{
    NMTOOLS_TESTING_DECLARE_NS( array, constexpr_reduce_add, case4);
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case4, result, view::reduce_add, a_a, axis );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case4, result, view::reduce_add, a, axis );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case4, result, na::add.reduce, a_a, axis );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case4, result, na::add.reduce, a, axis );
}

NM_TEST_SUBCASE(constexpr_reduce_add, case9)
{
    NMTOOLS_TESTING_DECLARE_NS( array, constexpr_reduce_add, case9);
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case9, result, view::reduce_add, a_a, axis, dtype, initial, keepdims );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case9, result, view::reduce_add, a, axis, dtype, initial, keepdims );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case9, result, na::add.reduce, a_a, axis, dtype, initial, keepdims );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case9, result, na::add.reduce, a, axis, dtype, initial, keepdims );
}

NM_TEST_SUBCASE(constexpr_reduce_add, case14)
{
    NMTOOLS_TESTING_DECLARE_NS( array, constexpr_reduce_add, case14);
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case14, result, view::reduce_add, a_a, axis, dtype, initial, keepdims );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case14, result, view::reduce_add, a, axis, dtype, initial, keepdims );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case14, result, na::add.reduce, a_a, axis, dtype, initial, keepdims );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case14, result, na::add.reduce, a, axis, dtype, initial, keepdims );
}

NM_TEST_SUBCASE(accumulate_add, case1)
{
    NMTOOLS_TESTING_DECLARE_NS( view, accumulate_add, case1 );
    NMTOOLS_PIO_SUBCASE( case1, result, view::accumulate_add, a_a, axis );
    NMTOOLS_PIO_SUBCASE( case1, result, view::accumulate_add, a, axis );
    NMTOOLS_PIO_SUBCASE( case1, result, na::add.accumulate, a_a, axis );
    NMTOOLS_PIO_SUBCASE( case1, result, na::add.accumulate, a, axis );
}

NM_TEST_SUBCASE(accumulate_add, case2)
{
    NMTOOLS_TESTING_DECLARE_NS( view, accumulate_add, case2 );
    NMTOOLS_PIO_SUBCASE( case2, result, view::accumulate_add, a_a, axis );
    NMTOOLS_PIO_SUBCASE( case2, result, view::accumulate_add, a, axis );
    NMTOOLS_PIO_SUBCASE( case2, result, na::add.accumulate, a_a, axis );
    NMTOOLS_PIO_SUBCASE( case2, result, na::add.accumulate, a, axis );
}

NM_TEST_SUBCASE(accumulate_add, case3)
{
    NMTOOLS_TESTING_DECLARE_NS( view, accumulate_add, case3 );
    NMTOOLS_PIO_SUBCASE( case3, result, view::accumulate_add, a_a, axis );
    NMTOOLS_PIO_SUBCASE( case3, result, view::accumulate_add, a, axis );
    NMTOOLS_PIO_SUBCASE( case3, result, na::add.accumulate, a_a, axis );
    NMTOOLS_PIO_SUBCASE( case3, result, na::add.accumulate, a, axis );
}

NM_TEST_SUBCASE(constexpr_accumulate_add, case1)
{
    NMTOOLS_TESTING_DECLARE_NS( array, constexpr_accumulate_add, case1 );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case1, result, view::accumulate_add, a_a, axis );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case1, result, view::accumulate_add, a, axis );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case1, result, na::add.accumulate, a_a, axis );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case1, result, na::add.accumulate, a, axis );
}

NM_TEST_SUBCASE(constexpr_accumulate_add, case2)
{
    NMTOOLS_TESTING_DECLARE_NS( array, constexpr_accumulate_add, case2 );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case2, result, view::accumulate_add, a_a, axis );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case2, result, view::accumulate_add, a, axis );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case2, result, na::add.accumulate, a_a, axis );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case2, result, na::add.accumulate, a, axis );
}

NM_TEST_SUBCASE(constexpr_accumulate_add, case3)
{
    NMTOOLS_TESTING_DECLARE_NS( array, constexpr_accumulate_add, case3 );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case3, result, view::accumulate_add, a_a, axis );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case3, result, view::accumulate_add, a, axis );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case3, result, na::add.accumulate, a_a, axis );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case3, result, na::add.accumulate, a, axis );
}

NM_TEST_SUBCASE(outer_add, case1)
{
    NMTOOLS_TESTING_DECLARE_NS( view, outer_add, case1 );
    NMTOOLS_PIO_SUBCASE( case1, result, view::outer_add, a_a, b_a );
    NMTOOLS_PIO_SUBCASE( case1, result, view::outer_add, a, b );
    NMTOOLS_PIO_SUBCASE( case1, result, na::add.outer, a_a, b_a );
    NMTOOLS_PIO_SUBCASE( case1, result, na::add.outer, a, b );
}

NM_TEST_SUBCASE(constexpr_outer_add, case1)
{
    NMTOOLS_TESTING_DECLARE_NS( array, constexpr_outer_add, case1 );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case1, result, view::outer_add, a_a, b_a );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case1, result, view::outer_add, a, b );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case1, result, na::add.outer, a_a, b_a );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case1, result, na::add.outer, a, b );
}

NM_TEST_SUBCASE(mean, case1)
{
    NMTOOLS_TESTING_DECLARE_NS( array, mean, case1 );
    NMTOOLS_PIO_SUBCASE( case1, result, view::mean, a_a, axis );
    NMTOOLS_PIO_SUBCASE( case1, result, na::mean, a_a, axis );
    NMTOOLS_PIO_SUBCASE( case1, result, view::mean, a, axis );
    NMTOOLS_PIO_SUBCASE( case1, result, na::mean, a, axis );
}

NM_TEST_SUBCASE(constexpr_mean, case1)
{
    NMTOOLS_TESTING_DECLARE_NS( array, constexpr_mean, case1 );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case1, result, view::mean, a_a, axis );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case1, result, view::mean, a, axis );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case1, result, na::mean, a_a, axis );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case1, result, na::mean, a, axis );
}

/* ========================================================================= */

#ifndef NMTOOLS_TESTING_MINIMIZE_FOOTPRINT

#if 1
NM_TEST_SUBCASE(add, case2)
{
    NMTOOLS_TESTING_DECLARE_NS( view, add, case2 );
    NMTOOLS_PIO_SUBCASE( case2, result, view::add, a_a, b );
}
#endif

NM_TEST_SUBCASE(reduce_add, case4)
{
    NMTOOLS_TESTING_DECLARE_NS( view, reduce_add, case4);
    NMTOOLS_PIO_SUBCASE( case4, result, view::reduce_add, a_a, axis_a );
    NMTOOLS_PIO_SUBCASE( case4, result, view::reduce_add, a, axis );
    // NOTE: need dynamic ndarray, currently disabled for platformio arduino
    // TODO: fix
    // NMTOOLS_PIO_SUBCASE( case4, result, na::add.reduce, a_a, axis_a );
    // NMTOOLS_PIO_SUBCASE( case4, result, na::add.reduce, a, axis );
}

NM_TEST_SUBCASE(reduce_add, case9)
{
    NMTOOLS_TESTING_DECLARE_NS( view, reduce_add, case9 );
    NMTOOLS_PIO_SUBCASE( case9, result, view::reduce_add, a_a, axis, dtype, initial, keepdims );
    NMTOOLS_PIO_SUBCASE( case9, result, view::reduce_add, a, axis, dtype, initial, keepdims );
    // NOTE: need dynamic ndarray, currently disabled for platformio arduino
    // TODO: fix
    // NMTOOLS_PIO_SUBCASE( case9, result, na::add.reduce, a_a, axis, dtype, initial, keepdims );
    // NMTOOLS_PIO_SUBCASE( case9, result, na::add.reduce, a, axis, dtype, initial, keepdims );
}

NM_TEST_SUBCASE(reduce_add, case14)
{
    NMTOOLS_TESTING_DECLARE_NS( view, reduce_add, case14 );
    NMTOOLS_PIO_SUBCASE( case14, result, view::reduce_add, a_a, axis, dtype, initial, keepdims );
    NMTOOLS_PIO_SUBCASE( case14, result, view::reduce_add, a, axis, dtype, initial, keepdims );
    // NOTE: need dynamic ndarray, currently disabled for platformio arduino
    // TODO: fix
    // NMTOOLS_PIO_SUBCASE( case14, result, na::add.reduce, a_a, axis, dtype, initial, keepdims );
    // NMTOOLS_PIO_SUBCASE( case14, result, na::add.reduce, a, axis, dtype, initial, keepdims );
}

NM_TEST_SUBCASE(reduce_add, case15)
{
    NMTOOLS_TESTING_DECLARE_NS( view, reduce_add, case15 );
    NMTOOLS_PIO_SUBCASE( case15, result, view::reduce_add, a_a, axis );
    NMTOOLS_PIO_SUBCASE( case15, result, view::reduce_add, a, axis );
    // NOTE: need dynamic ndarray, currently disabled for platformio arduino
    // TODO: fix
    // NMTOOLS_PIO_SUBCASE( case15, result, na::add.reduce, a_a, axis );
    // NMTOOLS_PIO_SUBCASE( case15, result, na::add.reduce, a, axis );
}

NM_TEST_SUBCASE(reduce_add, case2)
{
    NMTOOLS_TESTING_DECLARE_NS( view, reduce_add, case2);
    NMTOOLS_PIO_SUBCASE( case2, result, view::reduce_add, a_a, axis );
}

NM_TEST_SUBCASE(reduce_add, case3)
{
    NMTOOLS_TESTING_DECLARE_NS( view, reduce_add, case3);
    NMTOOLS_PIO_SUBCASE( case3, result, view::reduce_add, a_a, axis );
}

NM_TEST_SUBCASE(reduce_add, case5)
{
    NMTOOLS_TESTING_DECLARE_NS( view, reduce_add, case5);
    NMTOOLS_PIO_SUBCASE( case5, result, view::reduce_add, a_a, axis_a );
}

NM_TEST_SUBCASE(reduce_add, case6)
{
    NMTOOLS_TESTING_DECLARE_NS( view, reduce_add, case6);
    NMTOOLS_PIO_SUBCASE( case6, result, view::reduce_add, a_a, axis_a );
}

NM_TEST_SUBCASE(reduce_add, case7)
{
    NMTOOLS_TESTING_DECLARE_NS( view, reduce_add, case7);
    NMTOOLS_PIO_SUBCASE( case7, result, view::reduce_add, a_a, axis, dtype );
}

NM_TEST_SUBCASE(reduce_add, case8)
{
    NMTOOLS_TESTING_DECLARE_NS( view, reduce_add, case8);
    NMTOOLS_PIO_SUBCASE( case8, result, view::reduce_add, a_a, axis, dtype, initial );
}

NM_TEST_SUBCASE(reduce_add, case10)
{
    NMTOOLS_TESTING_DECLARE_NS( view, reduce_add, case10);
    NMTOOLS_PIO_SUBCASE( case10, result, view::reduce_add, a_a, axis, dtype, initial, keepdims );
}

NM_TEST_SUBCASE(reduce_add, case11)
{
    NMTOOLS_TESTING_DECLARE_NS( view, reduce_add, case11);
    NMTOOLS_PIO_SUBCASE( case11, result, view::reduce_add, a_a, axis, dtype, initial, keepdims );
}

NM_TEST_SUBCASE(reduce_add, case12)
{
    NMTOOLS_TESTING_DECLARE_NS( view, reduce_add, case12);
    NMTOOLS_PIO_SUBCASE( case12, result, view::reduce_add, a_a, axis_a, dtype, initial, keepdims );
}

NM_TEST_SUBCASE(reduce_add, case13)
{
    NMTOOLS_TESTING_DECLARE_NS( view, reduce_add, case13);
    NMTOOLS_PIO_SUBCASE( case13, result, view::reduce_add, a_a, axis_a, dtype, initial, keepdims );
}

NM_TEST_SUBCASE(reduce_add, case16)
{
    NMTOOLS_TESTING_DECLARE_NS( view, reduce_add, case16);
    NMTOOLS_PIO_SUBCASE( case16, result, view::reduce_add, a_a, axis, nm::None, initial);
}

NM_TEST_SUBCASE(reduce_add, case17)
{
    NMTOOLS_TESTING_DECLARE_NS( view, reduce_add, case17);
    NMTOOLS_PIO_SUBCASE( case17, result, view::reduce_add, a_a, axis, nm::None, initial, keepdims );
}

NM_TEST_SUBCASE(reduce_add, case18)
{
    NMTOOLS_TESTING_DECLARE_NS( view, reduce_add, case18);
    NMTOOLS_PIO_SUBCASE( case18, result, view::reduce_add, a_a, axis, nm::None, initial, keepdims );
}

NM_TEST_SUBCASE(reduce_add, case19)
{
    NMTOOLS_TESTING_DECLARE_NS( view, reduce_add, case19);
    NMTOOLS_PIO_SUBCASE( case19, result, view::reduce_add, a_a, axis, nm::None, initial, keepdims );
}

NM_TEST_SUBCASE(reduce_add, case20)
{
    NMTOOLS_TESTING_DECLARE_NS( view, reduce_add, case20);
    NMTOOLS_PIO_SUBCASE( case20, result, view::reduce_add, a_a, axis, nm::None, initial, keepdims );
}

NM_TEST_SUBCASE(reduce_add, case21)
{
    NMTOOLS_TESTING_DECLARE_NS( view, reduce_add, case21);
    NMTOOLS_PIO_SUBCASE( case21, result, view::reduce_add, a_a, axis, dtype );
}

NM_TEST_SUBCASE(reduce_add, case22)
{
    NMTOOLS_TESTING_DECLARE_NS( view, reduce_add, case22);
    NMTOOLS_PIO_SUBCASE( case22, result, view::reduce_add, a_a, axis, dtype );
}

NM_TEST_SUBCASE(reduce_add, case23)
{
    NMTOOLS_TESTING_DECLARE_NS( view, reduce_add, case23);
    NMTOOLS_PIO_SUBCASE( case23, result, view::reduce_add, a_a, axis, nm::None, nm::None, keepdims );
}

NM_TEST_SUBCASE(reduce_add, case24)
{
    NMTOOLS_TESTING_DECLARE_NS( view, reduce_add, case24);
    NMTOOLS_PIO_SUBCASE( case24, result, view::reduce_add, a_a, axis, nm::None, nm::None, keepdims );
}

NM_TEST_SUBCASE(mean, case2)
{
    NMTOOLS_TESTING_DECLARE_NS( array, mean, case2 );
    NMTOOLS_PIO_SUBCASE( case2, result, view::mean, a_a, axis );
    NMTOOLS_PIO_SUBCASE( case2, result, view::mean, a, axis );
    // NMTOOLS_PIO_SUBCASE( case2, result, na::mean, a_a, axis );
    // NMTOOLS_PIO_SUBCASE( case2, result, na::mean, a, axis );
}

NM_TEST_SUBCASE(mean, case3)
{
    NMTOOLS_TESTING_DECLARE_NS( array, mean, case3 );
    NMTOOLS_PIO_SUBCASE( case3, result, view::mean, a_a, axis );
    NMTOOLS_PIO_SUBCASE( case3, result, view::mean, a, axis );
    // NMTOOLS_PIO_SUBCASE( case3, result, na::mean, a_a, axis );
    // NMTOOLS_PIO_SUBCASE( case3, result, na::mean, a, axis );
}

NM_TEST_SUBCASE(mean, case4)
{
    NMTOOLS_TESTING_DECLARE_NS( array, mean, case4 );
    NMTOOLS_PIO_SUBCASE( case4, result, view::mean, a_a, axis );
    NMTOOLS_PIO_SUBCASE( case4, result, view::mean, a, axis );
    // NMTOOLS_PIO_SUBCASE( case4, result, na::mean, a_a, axis );
    // NMTOOLS_PIO_SUBCASE( case4, result, na::mean, a, axis );
}

NM_TEST_SUBCASE(mean, case5)
{
    NMTOOLS_TESTING_DECLARE_NS( array, mean, case5 );
    NMTOOLS_PIO_SUBCASE( case4, result, view::mean, a_a, axis );
    NMTOOLS_PIO_SUBCASE( case4, result, view::mean, a, axis );
    // NMTOOLS_PIO_SUBCASE( case4, result, na::mean, a_a, axis );
    // NMTOOLS_PIO_SUBCASE( case4, result, na::mean, a, axis );
}

NM_TEST_SUBCASE(mean, case6)
{
    NMTOOLS_TESTING_DECLARE_NS( array, mean, case6 );
    NMTOOLS_PIO_SUBCASE( case6, result, view::mean, a_a, axis, /*dtype=*/nm::None, keepdims );
    NMTOOLS_PIO_SUBCASE( case6, result, view::mean, a, axis, /*dtype=*/nm::None, keepdims );
    // NMTOOLS_PIO_SUBCASE( case6, result, na::mean, a_a, axis, /*dtype=*/nm::None, keepdims );
    // NMTOOLS_PIO_SUBCASE( case6, result, na::mean, a, axis, /*dtype=*/nm::None, keepdims );
}

NM_TEST_SUBCASE(mean, case7)
{
    NMTOOLS_TESTING_DECLARE_NS( array, mean, case7 );
    NMTOOLS_PIO_SUBCASE( case7, result, view::mean, a_a, axis, /*dtype=*/nm::None, keepdims );
    NMTOOLS_PIO_SUBCASE( case7, result, view::mean, a, axis, /*dtype=*/nm::None, keepdims );
    // NMTOOLS_PIO_SUBCASE( case7, result, na::mean, a_a, axis, /*dtype=*/nm::None, keepdims );
    // NMTOOLS_PIO_SUBCASE( case7, result, na::mean, a, axis, /*dtype=*/nm::None, keepdims );
}

NM_TEST_SUBCASE(mean, case8)
{
    NMTOOLS_TESTING_DECLARE_NS( array, mean, case8 );
    NMTOOLS_PIO_SUBCASE( case8, result, view::mean, a_a, axis, /*dtype=*/nm::None, keepdims );
    NMTOOLS_PIO_SUBCASE( case8, result, view::mean, a, axis, /*dtype=*/nm::None, keepdims );
    // NMTOOLS_PIO_SUBCASE( case8, result, na::mean, a_a, axis, /*dtype=*/nm::None, keepdims );
    // NMTOOLS_PIO_SUBCASE( case8, result, na::mean, a, axis, /*dtype=*/nm::None, keepdims );
}

NM_TEST_SUBCASE(mean, case9)
{
    NMTOOLS_TESTING_DECLARE_NS( array, mean, case9 );
    NMTOOLS_PIO_SUBCASE( case9, result, view::mean, a_a, axis, /*dtype=*/nm::None, keepdims );
    NMTOOLS_PIO_SUBCASE( case9, result, view::mean, a, axis, /*dtype=*/nm::None, keepdims );
    // NMTOOLS_PIO_SUBCASE( case9, result, na::mean, a_a, axis, /*dtype=*/nm::None, keepdims );
    // NMTOOLS_PIO_SUBCASE( case9, result, na::mean, a, axis, /*dtype=*/nm::None, keepdims );
}

NM_TEST_SUBCASE(mean, case10)
{
    NMTOOLS_TESTING_DECLARE_NS( array, mean, case10 );
    NMTOOLS_PIO_SUBCASE( case10, result, view::mean, a_a, axis, /*dtype=*/nm::None, keepdims );
    NMTOOLS_PIO_SUBCASE( case10, result, view::mean, a, axis, /*dtype=*/nm::None, keepdims );
    // NMTOOLS_PIO_SUBCASE( case10, result, na::mean, a_a, axis, /*dtype=*/nm::None, keepdims );
    // NMTOOLS_PIO_SUBCASE( case10, result, na::mean, a, axis, /*dtype=*/nm::None, keepdims );
}


NM_TEST_SUBCASE(shape_matmul, case1)
{
    {
        int l_shape[2] = {3,4};
        int r_shape[2] = {4,3};
        int expect[2]  = {3,3};
        auto result = nmtools::index::shape_matmul(l_shape,r_shape);
        TEST_ASSERT_TRUE( isequal(result,expect) );
        static_assert( meta::is_signed_v<int> );
    }
}

#endif // NMTOOLS_TESTING_MINIMIZE_FOOTPRINT
/* ========================================================================= */

void setup()
{
    // initialize LED digital pin as an output.
    pinMode(LED_BUILTIN, OUTPUT);

    delay(1000);

    UNITY_BEGIN();

    #if 1
    NMTOOLS_PIO_RUN(add, case1);
    NMTOOLS_PIO_RUN(constexpr_add, case1);
    NMTOOLS_PIO_RUN(constexpr_add, case2);
    NMTOOLS_PIO_RUN(constexpr_add, case3);
    NMTOOLS_PIO_RUN(constexpr_add, case4);
    #endif

    NMTOOLS_PIO_RUN(relu, case1);

    NMTOOLS_PIO_RUN(reduce_add, case1);
    NMTOOLS_PIO_RUN(constexpr_reduce_add, case1);
    NMTOOLS_PIO_RUN(constexpr_reduce_add, case4);
    NMTOOLS_PIO_RUN(constexpr_reduce_add, case9);
    NMTOOLS_PIO_RUN(constexpr_reduce_add, case14);

    NMTOOLS_PIO_RUN(accumulate_add, case1);
    NMTOOLS_PIO_RUN(accumulate_add, case2);
    NMTOOLS_PIO_RUN(accumulate_add, case3);
    NMTOOLS_PIO_RUN(constexpr_accumulate_add, case1);
    NMTOOLS_PIO_RUN(constexpr_accumulate_add, case2);
    NMTOOLS_PIO_RUN(constexpr_accumulate_add, case3);

    NMTOOLS_PIO_RUN(outer_add, case1);
    NMTOOLS_PIO_RUN(constexpr_outer_add, case1);

    NMTOOLS_PIO_RUN(mean, case1);
    NMTOOLS_PIO_RUN(constexpr_mean, case1);

#ifndef NMTOOLS_TESTING_MINIMIZE_FOOTPRINT

    #if 1
    NMTOOLS_PIO_RUN(add, case2);
    #endif

    NMTOOLS_PIO_RUN(reduce_add, case4);
    NMTOOLS_PIO_RUN(reduce_add, case9);
    NMTOOLS_PIO_RUN(reduce_add, case14);
    NMTOOLS_PIO_RUN(reduce_add, case15);
    NMTOOLS_PIO_RUN(reduce_add, case2);
    NMTOOLS_PIO_RUN(reduce_add, case3);
    NMTOOLS_PIO_RUN(reduce_add, case5);
    NMTOOLS_PIO_RUN(reduce_add, case6);
    NMTOOLS_PIO_RUN(reduce_add, case7);
    NMTOOLS_PIO_RUN(reduce_add, case8);
    NMTOOLS_PIO_RUN(reduce_add, case10);
    NMTOOLS_PIO_RUN(reduce_add, case11);
    NMTOOLS_PIO_RUN(reduce_add, case12);
    NMTOOLS_PIO_RUN(reduce_add, case13);
    NMTOOLS_PIO_RUN(reduce_add, case16);
    NMTOOLS_PIO_RUN(reduce_add, case17);
    NMTOOLS_PIO_RUN(reduce_add, case18);
    NMTOOLS_PIO_RUN(reduce_add, case19);
    NMTOOLS_PIO_RUN(reduce_add, case20);
    NMTOOLS_PIO_RUN(reduce_add, case21);
    NMTOOLS_PIO_RUN(reduce_add, case22);
    NMTOOLS_PIO_RUN(reduce_add, case23);
    NMTOOLS_PIO_RUN(reduce_add, case24);

    NMTOOLS_PIO_RUN(mean, case2);
    NMTOOLS_PIO_RUN(mean, case3);
    NMTOOLS_PIO_RUN(mean, case4);
    NMTOOLS_PIO_RUN(mean, case5);
    NMTOOLS_PIO_RUN(mean, case6);

    NMTOOLS_PIO_RUN(shape_matmul, case1);
#endif // NMTOOLS_TESTING_MINIMIZE_FOOTPRINT

    UNITY_END();
}

void loop()
{
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
}