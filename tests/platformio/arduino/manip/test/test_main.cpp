#include "nmtools/meta.hpp"

#include "nmtools/array/array/transpose.hpp"
#include "nmtools/array/array/where.hpp"
#include "nmtools/array/array/tile.hpp"
#include "nmtools/array/array/take.hpp"
#include "nmtools/array/array/reshape.hpp"
#include "nmtools/array/array/flatten.hpp"
#include "nmtools/array/array/concatenate.hpp"
#include "nmtools/array/array/broadcast_to.hpp"
#include "nmtools/array/array/split.hpp"

#include "nmtools/testing/data/array/transpose.hpp"
#include "nmtools/testing/data/array/where.hpp"
#include "nmtools/testing/data/array/tile.hpp"
#include "nmtools/testing/data/array/take.hpp"
#include "nmtools/testing/data/array/reshape.hpp"
#include "nmtools/testing/data/array/flatten.hpp"
#include "nmtools/testing/data/array/concatenate.hpp"
#include "nmtools/testing/data/array/broadcast_to.hpp"
#include "nmtools/testing/data/array/split.hpp"

#include "nmtools/utility/isequal.hpp"
#include "nmtools/utility/isclose.hpp"
#include "nmtools/utility/apply_isequal.hpp"

#include <Arduino.h>
#include <unity.h>

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

using nm::utils::isclose, nm::utils::isequal;

#define NMTOOLS_PIO_SUBCASE(case_name, expected, function, ...) \
{ \
    using namespace args; \
    auto res = function(__VA_ARGS__); \
    auto success = isclose(res, expect::expected); \
    TEST_ASSERT_TRUE( success ); \
}

#define NMTOOLS_PIO_SUBCASE_APPLY_ISEQUAL(case_name, expected, function, ...) \
{ \
    using namespace args; \
    auto res = function(__VA_ARGS__); \
    auto success = nm::utils::apply_isequal(res, expect::expected); \
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

NM_TEST_SUBCASE(transpose, case1)
{
    NMTOOLS_TESTING_USE_CASE( transpose, case1 );
    NMTOOLS_PIO_SUBCASE( case1, expected, view::transpose, array_a, axes_a );
    NMTOOLS_PIO_SUBCASE( case1, expected, view::transpose, array, axes_a );
}

NM_TEST_SUBCASE(transpose, case2)
{
    NMTOOLS_TESTING_USE_CASE( transpose, case2 );
    NMTOOLS_PIO_SUBCASE( case2, expected, view::transpose, array_a, axes_a );
    NMTOOLS_PIO_SUBCASE( case2, expected, view::transpose, array, axes_a );
}

NM_TEST_SUBCASE(transpose, case5)
{
    NMTOOLS_TESTING_USE_CASE( transpose, case5 );
    NMTOOLS_PIO_SUBCASE( case5, expected, view::transpose, array_a, axes_a );
    NMTOOLS_PIO_SUBCASE( case5, expected, view::transpose, array, axes );
}

NM_TEST_SUBCASE(transpose, case8)
{
    NMTOOLS_TESTING_USE_CASE( transpose, case8 );
    NMTOOLS_PIO_SUBCASE( case8, expected, view::transpose, array_a, axes_a );
    NMTOOLS_PIO_SUBCASE( case8, expected, view::transpose, array, axes );
}

NM_TEST_SUBCASE(transpose, case10)
{
    NMTOOLS_TESTING_USE_CASE( transpose, case10 );
    NMTOOLS_PIO_SUBCASE( case10, expected, view::transpose, array_a, axes_a );
    NMTOOLS_PIO_SUBCASE( case10, expected, view::transpose, array, axes );
    // TODO: support fixed ndarray
    // NMTOOLS_PIO_SUBCASE( case10, expected, view::transpose, array_f, axes_f );
}

NM_TEST_SUBCASE(constexpr_transpose, case1)
{
    NMTOOLS_TESTING_USE_CASE( constexpr_transpose, case1 );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case1, expected, view::transpose, array, axes_a );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case1, expected, view::transpose, array_a, axes_a );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case1, expected, view::transpose, array_f, axes_a );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case1, expected, view::transpose, array_h, axes_a );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case1, expected, na::transpose, array, axes_a );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case1, expected, na::transpose, array_a, axes_a );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case1, expected, na::transpose, array_f, axes_a );
    // NOTE: currently inferred as dynamic ndarray
    // TODO: infer as hybrid ndarray
    // NMTOOLS_PIO_CONSTEXPR_SUBCASE( case1, expected, na::transpose, array_h, axes_a );
}

NM_TEST_SUBCASE(constexpr_transpose, case2)
{
    NMTOOLS_TESTING_USE_CASE( constexpr_transpose, case2 );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case2, expected, view::transpose, array, axes_a );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case2, expected, view::transpose, array_a, axes_a );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case2, expected, view::transpose, array_f, axes_a );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case2, expected, view::transpose, array_h, axes_a );

    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case2, expected, na::transpose, array, axes_a );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case2, expected, na::transpose, array_a, axes_a );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case2, expected, na::transpose, array_f, axes_a );
    // NMTOOLS_PIO_CONSTEXPR_SUBCASE( case2, expected, na::transpose, array_h, axes_a );
}

NM_TEST_SUBCASE(constexpr_transpose, case5)
{
    NMTOOLS_TESTING_USE_CASE( constexpr_transpose, case5 );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case5, expected, view::transpose, array, axes_a );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case5, expected, view::transpose, array_a, axes_a );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case5, expected, view::transpose, array_f, axes_a );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case5, expected, view::transpose, array_h, axes_a );

    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case5, expected, na::transpose, array, axes_a );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case5, expected, na::transpose, array_a, axes_a );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case5, expected, na::transpose, array_f, axes_a );
    // NMTOOLS_PIO_CONSTEXPR_SUBCASE( case5, expected, na::transpose, array_h, axes_a );
}

NM_TEST_SUBCASE(constexpr_transpose, case8)
{
    NMTOOLS_TESTING_USE_CASE( constexpr_transpose, case8 );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case8, expected, view::transpose, array, axes_a );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case8, expected, view::transpose, array_a, axes_a );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case8, expected, view::transpose, array_f, axes_a );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case8, expected, view::transpose, array_h, axes_a );

    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case8, expected, na::transpose, array, axes_a );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case8, expected, na::transpose, array_a, axes_a );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case8, expected, na::transpose, array_f, axes_a );
    // NMTOOLS_PIO_CONSTEXPR_SUBCASE( case8, expected, na::transpose, array_h, axes_a );
}

NM_TEST_SUBCASE(constexpr_transpose, case10)
{
    NMTOOLS_TESTING_USE_CASE( constexpr_transpose, case10 );
    // NOTE: the following view currently deduced as dynamic ndarray
    // TODO: deduce as hybrid ndarray
    // NMTOOLS_PIO_CONSTEXPR_SUBCASE( case10, expected, view::transpose, array_a, axes_a );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case10, expected, view::transpose, array, axes_ct );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case10, expected, view::transpose, array_a, axes_ct );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case10, expected, view::transpose, array_f, axes_ct );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case10, expected, view::transpose, array_h, axes_ct );

    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case10, expected, na::transpose, array, axes_ct );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case10, expected, na::transpose, array_a, axes_ct );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case10, expected, na::transpose, array_f, axes_ct );
    // NMTOOLS_PIO_CONSTEXPR_SUBCASE( case10, expected, na::transpose, array_h, axes_ct );
}

NM_TEST_SUBCASE(tile, case1)
{
    NMTOOLS_TESTING_USE_CASE( view, tile, case1 );
    NMTOOLS_PIO_SUBCASE( case1, result, view::tile, array, reps );
    NMTOOLS_PIO_SUBCASE( case1, result, view::tile, array_a, reps_a );
    // NMTOOLS_PIO_SUBCASE( case1, result, view::tile, array_f, reps_a );
    // NMTOOLS_PIO_SUBCASE( case1, result, view::tile, array_h, reps_a );

    // NOTE: note supported yet, deduced as dynamic array
    // TODO: infer as hybrid ndarray
    // NMTOOLS_PIO_SUBCASE( case1, result, na::tile, array, reps );
    // NMTOOLS_PIO_SUBCASE( case1, result, na::tile, array_a, reps_a );

    // NOTE: note supported yet, can't handle constant index yet
    // TODO: handle constant index & infer as fixed ndarray
    // NMTOOLS_PIO_SUBCASE( case1, result, na::tile, array, reps_ct );
    // NMTOOLS_PIO_SUBCASE( case1, result, na::tile, array_a, reps_ct );
}

NM_TEST_SUBCASE(tile, case3)
{
    NMTOOLS_TESTING_USE_CASE( view, tile, case3 );
    NMTOOLS_PIO_SUBCASE( case3, result, view::tile, array, reps );
    NMTOOLS_PIO_SUBCASE( case3, result, view::tile, array_a, reps_a );

    // NOTE: note supported yet, deduced as dynamic array
    // TODO: infer as hybrid ndarray
    // NMTOOLS_PIO_SUBCASE( case3, result, view::tile, array_f, reps_a );
    // NMTOOLS_PIO_SUBCASE( case3, result, view::tile, array_h, reps_a );
}

NM_TEST_SUBCASE(tile, case5)
{
    NMTOOLS_TESTING_USE_CASE( view, tile, case5 );
    NMTOOLS_PIO_SUBCASE( case5, result, view::tile, array, reps );
    NMTOOLS_PIO_SUBCASE( case5, result, view::tile, array_a, reps_a );

    // NOTE: note supported yet, deduced as dynamic array
    // TODO: infer as hybrid ndarray
    // NMTOOLS_PIO_SUBCASE( case5, result, view::tile, array_f, reps_a );
    // NMTOOLS_PIO_SUBCASE( case5, result, view::tile, array_h, reps_a );
}

NM_TEST_SUBCASE(constexpr_tile, case1)
{
    NMTOOLS_TESTING_USE_CASE( array, constexpr_tile, case1 );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case1, result, view::tile, array, reps );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case1, result, view::tile, array_a, reps_a );
}

NM_TEST_SUBCASE(constexpr_tile, case3)
{
    NMTOOLS_TESTING_USE_CASE( array, constexpr_tile, case3 );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case3, result, view::tile, array, reps );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case3, result, view::tile, array_a, reps_a );
}

NM_TEST_SUBCASE(constexpr_tile, case5)
{
    NMTOOLS_TESTING_USE_CASE( array, constexpr_tile, case5 );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case5, result, view::tile, array, reps );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case5, result, view::tile, array_a, reps_a );
}

NM_TEST_SUBCASE(take, case1)
{
    NMTOOLS_TESTING_USE_CASE( view, take, case1 );
    NMTOOLS_PIO_SUBCASE( case1, result, view::take, array, indices, axis );
    NMTOOLS_PIO_SUBCASE( case1, result, view::take, array_a, indices_a, axis );
    // NMTOOLS_PIO_SUBCASE( case1, result, view::take, array_f, indices_a, axis );
    // NMTOOLS_PIO_SUBCASE( case1, result, view::take, array_h, indices_a, axis );

    // NOTE: note supported yet, deduced as dynamic array
    // TODO: infer as hybrid ndarray
    // NMTOOLS_PIO_SUBCASE( case1, result, na::take, array, indices, axis );
    // NMTOOLS_PIO_SUBCASE( case1, result, na::take, array_a, indices_a, axis );

    // NOTE: note supported yet, can't handle constant index yet
    // TODO: handle constant index & infer as fixed ndarray
    // NMTOOLS_PIO_SUBCASE( case1, result, na::take, array, indices_ct, axis_ct );
    // NMTOOLS_PIO_SUBCASE( case1, result, na::take, array_a, indices_ct, axis_ct );
}

NM_TEST_SUBCASE(take, case2)
{
    NMTOOLS_TESTING_USE_CASE( view, take, case2 );
    NMTOOLS_PIO_SUBCASE( case2, result, view::take, array_a, indices_a, axis );
    NMTOOLS_PIO_SUBCASE( case2, result, view::take, array, indices, axis );
}

NM_TEST_SUBCASE(take, case5)
{
    NMTOOLS_TESTING_USE_CASE( view, take, case5 );
    NMTOOLS_PIO_SUBCASE( case5, result, view::take, array_a, indices_a, axis );
    NMTOOLS_PIO_SUBCASE( case5, result, view::take, array, indices, axis );
}

NM_TEST_SUBCASE(constexpr_take, case1)
{
    NMTOOLS_TESTING_USE_CASE( array, constexpr_take, case1 );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case1, result, view::take, array, indices, axis );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case1, result, view::take, array_a, indices_a, axis );
}

NM_TEST_SUBCASE(constexpr_take, case2)
{
    NMTOOLS_TESTING_USE_CASE( array, constexpr_take, case2 );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case2, result, view::take, array_a, indices_a, axis );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case2, result, view::take, array, indices, axis );
}

NM_TEST_SUBCASE(constexpr_take, case5)
{
    NMTOOLS_TESTING_USE_CASE( array, constexpr_take, case5 );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case5, result, view::take, array_a, indices_a, axis );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case5, result, view::take, array, indices, axis );
}

NM_TEST_SUBCASE(where, case1)
{
    NMTOOLS_TESTING_USE_CASE( view, where, case1 );
    NMTOOLS_PIO_SUBCASE( case1, result, view::where, condition, x, y );
    NMTOOLS_PIO_SUBCASE( case1, result, view::where, condition_a, x_a, y_a );

    NMTOOLS_PIO_SUBCASE( case1, result, na::where, condition, x, y );
    NMTOOLS_PIO_SUBCASE( case1, result, na::where, condition_a, x_a, y_a );
}

NM_TEST_SUBCASE(where, case2)
{
    NMTOOLS_TESTING_USE_CASE( view, where, case2 );
    NMTOOLS_PIO_SUBCASE( case2, result, view::where, condition_a, x_a, y_a );
    NMTOOLS_PIO_SUBCASE( case2, result, view::where, condition_a, x, y );

    NMTOOLS_PIO_SUBCASE( case2, result, na::where, condition_a, x_a, y_a );
    NMTOOLS_PIO_SUBCASE( case2, result, na::where, condition_a, x, y );
}

NM_TEST_SUBCASE(reshape, case1)
{
    NMTOOLS_TESTING_USE_CASE( reshape, case1 );
    NMTOOLS_PIO_SUBCASE( case1, expected, view::reshape, array_a, newshape_a );
    NMTOOLS_PIO_SUBCASE( case1, expected, view::reshape, array, newshape );

    // NOTE: note supported yet, deduced as dynamic array
    // TODO: infer as hybrid ndarray
    // NMTOOLS_PIO_SUBCASE( case1, expected, na::reshape, array_a, newshape_a );
    // NMTOOLS_PIO_SUBCASE( case1, expected, na::reshape, array, newshape );

    NMTOOLS_PIO_SUBCASE( case1, expected, na::reshape, array, newshape_ct );
    NMTOOLS_PIO_SUBCASE( case1, expected, na::reshape, array_a, newshape_ct );
}

NM_TEST_SUBCASE(constexpr_reshape, case1)
{
    NMTOOLS_TESTING_USE_CASE( constexpr_reshape, case1 );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case1, expected, view::reshape, array_a, newshape_a );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case1, expected, view::reshape, array, newshape );

    // NOTE: note supported yet, deduced as dynamic array
    // TODO: infer as hybrid ndarray
    // NMTOOLS_PIO_CONSTEXPR_SUBCASE( case1, expected, na::reshape, array_a, newshape_a );
    // NMTOOLS_PIO_CONSTEXPR_SUBCASE( case1, expected, na::reshape, array, newshape );

    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case1, expected, na::reshape, array, newshape_ct );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case1, expected, na::reshape, array_a, newshape_ct );
}

NM_TEST_SUBCASE(flatten, case4)
{
    NMTOOLS_TESTING_USE_CASE( flatten, case4 );
    NMTOOLS_PIO_SUBCASE( case4, expected, view::flatten, array_a );
    NMTOOLS_PIO_SUBCASE( case4, expected, view::flatten, array );

    NMTOOLS_PIO_SUBCASE( case4, expected, na::flatten, array_a );
    NMTOOLS_PIO_SUBCASE( case4, expected, na::flatten, array );
}

NM_TEST_SUBCASE(constexpr_flatten, case4)
{
    NMTOOLS_TESTING_USE_CASE( constexpr_flatten, case4 );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case4, expected, view::flatten, array_a );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case4, expected, view::flatten, array );

    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case4, expected, na::flatten, array_a );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case4, expected, na::flatten, array );
}

NM_TEST_SUBCASE(concatenate, case3)
{
    NMTOOLS_TESTING_USE_CASE( view, concatenate, case3 );
    NMTOOLS_PIO_SUBCASE( case3, expected, view::concatenate, lhs_a, rhs_a, axis );
    NMTOOLS_PIO_SUBCASE( case3, expected, view::concatenate, lhs, rhs, axis );

    NMTOOLS_PIO_SUBCASE( case3, expected, na::concatenate, lhs_a, rhs_a, axis );
    NMTOOLS_PIO_SUBCASE( case3, expected, na::concatenate, lhs, rhs, axis );
}

NM_TEST_SUBCASE(concatenate, case4)
{
    NMTOOLS_TESTING_USE_CASE( view, concatenate, case4 );
    NMTOOLS_PIO_SUBCASE( case4, expected, view::concatenate, lhs_a, rhs_a, axis );
    NMTOOLS_PIO_SUBCASE( case4, expected, view::concatenate, lhs, rhs, axis );

    // NOTE: note supported yet, deduced as dynamic array
    // TODO: infer as hybrid ndarray
    // NMTOOLS_PIO_SUBCASE( case4, expected, na::concatenate, lhs_a, rhs_a, axis );
    // NMTOOLS_PIO_SUBCASE( case4, expected, na::concatenate, lhs, rhs, axis );

    NMTOOLS_PIO_SUBCASE( case4, expected, na::concatenate, lhs, rhs, axis_ct );
    NMTOOLS_PIO_SUBCASE( case4, expected, na::concatenate, lhs_a, rhs_a, axis_ct );
}

NM_TEST_SUBCASE(constexpr_concatenate, case3)
{
    NMTOOLS_TESTING_USE_CASE( array, constexpr_concatenate, case3 );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case3, expected, view::concatenate, lhs_a, rhs_a, axis );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case3, expected, view::concatenate, lhs, rhs, axis );

    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case3, expected, na::concatenate, lhs_a, rhs_a, axis );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case3, expected, na::concatenate, lhs, rhs, axis );
}

NM_TEST_SUBCASE(constexpr_concatenate, case4)
{
    NMTOOLS_TESTING_USE_CASE( array, constexpr_concatenate, case4 );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case4, expected, view::concatenate, lhs_a, rhs_a, axis );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case4, expected, view::concatenate, lhs, rhs, axis );

    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case4, expected, na::concatenate, lhs, rhs, axis_ct );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case4, expected, na::concatenate, lhs_a, rhs_a, axis_ct );
}

NM_TEST_SUBCASE(broadcast_to, case1)
{
    NMTOOLS_TESTING_USE_CASE( broadcast_to, case1 );
    NMTOOLS_PIO_SUBCASE( case1, expected, view::broadcast_to, x_a, shape );
    NMTOOLS_PIO_SUBCASE( case1, expected, view::broadcast_to, x, shape );

    // NOTE: note supported yet, deduced as dynamic array
    // TODO: infer as hybrid ndarray
    // NMTOOLS_PIO_SUBCASE( case1, expected, na::broadcast_to, x_a, shape );
    // NMTOOLS_PIO_SUBCASE( case1, expected, na::broadcast_to, x, shape );

    // NOTE: somehow using raw array with fixed index as shape broke runtime
    // (blocks on arduino mega simavr, maybe triggers assertion)
    // TODO: fix
    // NMTOOLS_PIO_SUBCASE( case1, expected, na::broadcast_to, x, shape_ct );
    NMTOOLS_PIO_SUBCASE( case1, expected, na::broadcast_to, x_a, shape_ct );
}

NM_TEST_SUBCASE(broadcast_to, case7)
{
    NMTOOLS_TESTING_USE_CASE( broadcast_to, case7 );
    NMTOOLS_PIO_SUBCASE( case7, expected, view::broadcast_to, x_a, shape );
    NMTOOLS_PIO_SUBCASE( case7, expected, view::broadcast_to, x, shape );

    // NOTE: note supported yet, deduced as dynamic array
    // TODO: infer as hybrid ndarray
    // NMTOOLS_PIO_SUBCASE( case7, expected, na::broadcast_to, x_a, shape );
    // NMTOOLS_PIO_SUBCASE( case7, expected, na::broadcast_to, x, shape );

    // NMTOOLS_PIO_SUBCASE( case7, expected, na::broadcast_to, x, shape_ct );
    NMTOOLS_PIO_SUBCASE( case7, expected, na::broadcast_to, x_a, shape_ct );
}

NM_TEST_SUBCASE(broadcast_to, case10)
{
    NMTOOLS_TESTING_USE_CASE( broadcast_to, case10 );
    NMTOOLS_PIO_SUBCASE( case10, expected, view::broadcast_to, x, shape );
    // NMTOOLS_PIO_SUBCASE( case10, expected, na::broadcast_to, x, shape_ct );
}

NM_TEST_SUBCASE(constexpr_broadcast_to, case1)
{
    NMTOOLS_TESTING_USE_CASE( constexpr_broadcast_to, case1 );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case1, expected, view::broadcast_to, x_a, shape );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case1, expected, view::broadcast_to, x, shape );

    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case1, expected, na::broadcast_to, x_a, shape_ct );
}

NM_TEST_SUBCASE(constexpr_broadcast_to, case7)
{
    NMTOOLS_TESTING_USE_CASE( constexpr_broadcast_to, case7 );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case7, expected, view::broadcast_to, x_a, shape );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case7, expected, view::broadcast_to, x, shape );

    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case7, expected, na::broadcast_to, x_a, shape_ct );
}

NM_TEST_SUBCASE(constexpr_broadcast_to, case10)
{
    NMTOOLS_TESTING_USE_CASE( constexpr_broadcast_to, case10 );
    NMTOOLS_PIO_CONSTEXPR_SUBCASE( case10, expected, view::broadcast_to, x, shape );
}

// list not supported yet on arduino
// NM_TEST_SUBCASE(split, case1)
// {
//     NMTOOLS_TESTING_USE_CASE( array, split, case1 );
//     NMTOOLS_PIO_SUBCASE_APPLY_ISEQUAL( case1, result, view::split, a, indices_or_sections, axis );
// }

NM_TEST_SUBCASE(split, case2)
{
    NMTOOLS_TESTING_USE_CASE( array, split, case2 );
    NMTOOLS_PIO_SUBCASE_APPLY_ISEQUAL( case2, result, view::split, a, indices_or_sections, axis );
    // NMTOOLS_PIO_SUBCASE_APPLY_ISEQUAL( case2, result, view::split, a_f, indices_or_sections, axis );
    NMTOOLS_PIO_SUBCASE_APPLY_ISEQUAL( case2, result, view::split, a_a, indices_or_sections, axis );
}

NM_TEST_SUBCASE(split, case3)
{
    NMTOOLS_TESTING_USE_CASE( array, split, case3 );
    NMTOOLS_PIO_SUBCASE_APPLY_ISEQUAL( case3, result, view::split, a, indices_or_sections, axis );
    // NMTOOLS_PIO_SUBCASE_APPLY_ISEQUAL( case3, result, view::split, a_f, indices_or_sections, axis );
    NMTOOLS_PIO_SUBCASE_APPLY_ISEQUAL( case3, result, view::split, a_a, indices_or_sections, axis );
}

NM_TEST_SUBCASE(split, case4)
{
    NMTOOLS_TESTING_USE_CASE( array, split, case4 );
    NMTOOLS_PIO_SUBCASE_APPLY_ISEQUAL( case4, result, view::split, a, indices_or_sections, axis );
    NMTOOLS_PIO_SUBCASE_APPLY_ISEQUAL( case4, result, view::split, a_a, indices_or_sections, axis );
}

NM_TEST_SUBCASE(split, case5)
{
    NMTOOLS_TESTING_USE_CASE( array, split, case5 );
    NMTOOLS_PIO_SUBCASE_APPLY_ISEQUAL( case5, result, view::split, a, indices_or_sections, axis );
    NMTOOLS_PIO_SUBCASE_APPLY_ISEQUAL( case5, result, view::split, a_a, indices_or_sections, axis );
}

NM_TEST_SUBCASE(split, case6)
{
    NMTOOLS_TESTING_USE_CASE( array, split, case6 );
    NMTOOLS_PIO_SUBCASE_APPLY_ISEQUAL( case6, result, view::split, a, indices_or_sections, axis );
    NMTOOLS_PIO_SUBCASE_APPLY_ISEQUAL( case6, result, view::split, a_a, indices_or_sections, axis );
}

// list not supported on arduino yet
// NM_TEST_SUBCASE(split, case7)
// {
//     NMTOOLS_TESTING_USE_CASE( array, split, case7 );
//     NMTOOLS_PIO_SUBCASE_APPLY_ISEQUAL( case7, result, view::split, a, indices_or_sections, axis );
// }

NM_TEST_SUBCASE(split, case12)
{
    NMTOOLS_TESTING_USE_CASE( array, split, case12 );
    NMTOOLS_PIO_SUBCASE_APPLY_ISEQUAL( case12, result, view::split, a, indices_or_sections, axis );
    NMTOOLS_PIO_SUBCASE_APPLY_ISEQUAL( case12, result, view::split, a_a, indices_or_sections, axis );
}

NM_TEST_SUBCASE(split, case13)
{
    NMTOOLS_TESTING_USE_CASE( array, split, case13 );
    NMTOOLS_PIO_SUBCASE_APPLY_ISEQUAL( case13, result, view::split, a, indices_or_sections, axis );
    NMTOOLS_PIO_SUBCASE_APPLY_ISEQUAL( case13, result, view::split, a_a, indices_or_sections, axis );
}

/* ========================================================================= */

/* ========================================================================= */

// NOTE: optionally disabled to support arduino uno which has only 32KB Flash, 2K RAM
#ifndef NMTOOLS_TESTING_MINIMIZE_FOOTPRINT
NM_TEST_SUBCASE(transpose, case3)
{
    NMTOOLS_TESTING_USE_CASE( transpose, case3 );
    NMTOOLS_PIO_SUBCASE( case3, expected, view::transpose, array_a, axes_a );
}

NM_TEST_SUBCASE(transpose, case4)
{
    NMTOOLS_TESTING_USE_CASE( transpose, case4 );
    NMTOOLS_PIO_SUBCASE( case4, expected, view::transpose, array_a, axes_a );
}

NM_TEST_SUBCASE(transpose, case6)
{
    NMTOOLS_TESTING_USE_CASE( transpose, case6 );
    NMTOOLS_PIO_SUBCASE( case6, expected, view::transpose, array_a, axes_a );
}

NM_TEST_SUBCASE(transpose, case7)
{
    NMTOOLS_TESTING_USE_CASE( transpose, case7 );
    NMTOOLS_PIO_SUBCASE( case7, expected, view::transpose, array_a, axes_a );
}

NM_TEST_SUBCASE(transpose, case9)
{
    NMTOOLS_TESTING_USE_CASE( transpose, case9 );
    NMTOOLS_PIO_SUBCASE( case9, expected, view::transpose, array_a, axes_a );
}

NM_TEST_SUBCASE(tile, case2)
{
    NMTOOLS_TESTING_USE_CASE( view, tile, case2 );
    NMTOOLS_PIO_SUBCASE( case2, result, view::tile, array_a, reps_a );
}

NM_TEST_SUBCASE(tile, case4)
{
    NMTOOLS_TESTING_USE_CASE( view, tile, case4 );
    NMTOOLS_PIO_SUBCASE( case4, result, view::tile, array_a, reps_a );
}

NM_TEST_SUBCASE(take, case3)
{
    NMTOOLS_TESTING_USE_CASE( view, take, case3 );
    NMTOOLS_PIO_SUBCASE( case3, result, view::take, array_a, indices_a, axis );
}

NM_TEST_SUBCASE(take, case4)
{
    NMTOOLS_TESTING_USE_CASE( view, take, case4 );
    NMTOOLS_PIO_SUBCASE( case4, result, view::take, array_a, indices_a, axis );
}

NM_TEST_SUBCASE(take, case6)
{
    NMTOOLS_TESTING_USE_CASE( view, take, case6 );
    NMTOOLS_PIO_SUBCASE( case6, result, view::take, array_a, indices_a, axis );
}

NM_TEST_SUBCASE(where, case3)
{
    NMTOOLS_TESTING_USE_CASE( view, where, case3 );
    NMTOOLS_PIO_SUBCASE( case3, result, view::where, condition_a, x_a, y_a );
}

NM_TEST_SUBCASE(reshape, case2)
{
    NMTOOLS_TESTING_USE_CASE( reshape, case2 );
    NMTOOLS_PIO_SUBCASE( case2, expected, view::reshape, array_a, newshape_a );
}

NM_TEST_SUBCASE(reshape, case3)
{
    NMTOOLS_TESTING_USE_CASE( reshape, case3 );
    NMTOOLS_PIO_SUBCASE( case3, expected, view::reshape, array_a, newshape_a );
}

NM_TEST_SUBCASE(flatten, case1)
{
    NMTOOLS_TESTING_USE_CASE( flatten, case1 );
    NMTOOLS_PIO_SUBCASE( case1, expected, view::flatten, array_a );
}

NM_TEST_SUBCASE(flatten, case2)
{
    NMTOOLS_TESTING_USE_CASE( flatten, case2 );
    NMTOOLS_PIO_SUBCASE( case2, expected, view::flatten, array_a );
}

NM_TEST_SUBCASE(flatten, case3)
{
    NMTOOLS_TESTING_USE_CASE( flatten, case3 );
    NMTOOLS_PIO_SUBCASE( case3, expected, view::flatten, array_a );
}

NM_TEST_SUBCASE(concatenate, case1)
{
    NMTOOLS_TESTING_USE_CASE( view, concatenate, case1 );
    NMTOOLS_PIO_SUBCASE( case1, expected, view::concatenate, lhs_a, rhs_a, axis );
}

NM_TEST_SUBCASE(concatenate, case2)
{
    NMTOOLS_TESTING_USE_CASE( view, concatenate, case2 );
    NMTOOLS_PIO_SUBCASE( case2, expected, view::concatenate, lhs_a, rhs_a, axis );
}

NM_TEST_SUBCASE(broadcast_to, case2)
{
    NMTOOLS_TESTING_USE_CASE( broadcast_to, case2 );
    NMTOOLS_PIO_SUBCASE( case2, expected, view::broadcast_to, x_a, shape );
}

NM_TEST_SUBCASE(broadcast_to, case3)
{
    NMTOOLS_TESTING_USE_CASE( broadcast_to, case3 );
    NMTOOLS_PIO_SUBCASE( case3, expected, view::broadcast_to, x_a, shape );
}

NM_TEST_SUBCASE(broadcast_to, case4)
{
    NMTOOLS_TESTING_USE_CASE( broadcast_to, case4 );
    NMTOOLS_PIO_SUBCASE( case4, expected, view::broadcast_to, x_a, shape );
}

NM_TEST_SUBCASE(broadcast_to, case5)
{
    NMTOOLS_TESTING_USE_CASE( broadcast_to, case5 );
    NMTOOLS_PIO_SUBCASE( case5, expected, view::broadcast_to, x_a, shape );
}

NM_TEST_SUBCASE(broadcast_to, case6)
{
    NMTOOLS_TESTING_USE_CASE( broadcast_to, case6 );
    NMTOOLS_PIO_SUBCASE( case6, expected, view::broadcast_to, x_a, shape );
}

NM_TEST_SUBCASE(broadcast_to, case8)
{
    NMTOOLS_TESTING_USE_CASE( broadcast_to, case8 );
    NMTOOLS_PIO_SUBCASE( case8, expected, view::broadcast_to, x_a, shape );
}

NM_TEST_SUBCASE(broadcast_to, case9)
{
    NMTOOLS_TESTING_USE_CASE( broadcast_to, case9 );
    NMTOOLS_PIO_SUBCASE( case9, expected, view::broadcast_to, x_a, shape );
}

NM_TEST_SUBCASE(broadcast_to, case11)
{
    NMTOOLS_TESTING_USE_CASE( broadcast_to, case11 );
    NMTOOLS_PIO_SUBCASE( case11, expected, view::broadcast_to, x, shape );
}
#endif // NMTOOLS_TESTING_MINIMIZE_FOOTPRINT

/* ========================================================================= */

void setup()
{
    // initialize LED digital pin as an output.
    pinMode(LED_BUILTIN, OUTPUT);

    delay(1000);

    UNITY_BEGIN();
    NMTOOLS_PIO_RUN(transpose, case1)
    NMTOOLS_PIO_RUN(transpose, case2)
    NMTOOLS_PIO_RUN(transpose, case5)
    NMTOOLS_PIO_RUN(transpose, case8)
    NMTOOLS_PIO_RUN(transpose, case10)

    NMTOOLS_PIO_RUN(constexpr_transpose, case1)
    NMTOOLS_PIO_RUN(constexpr_transpose, case2)
    NMTOOLS_PIO_RUN(constexpr_transpose, case5)
    NMTOOLS_PIO_RUN(constexpr_transpose, case8)
    NMTOOLS_PIO_RUN(constexpr_transpose, case10)

    NMTOOLS_PIO_RUN(tile, case1)
    NMTOOLS_PIO_RUN(tile, case3)
    NMTOOLS_PIO_RUN(tile, case5)

    NMTOOLS_PIO_RUN(constexpr_tile, case1)
    NMTOOLS_PIO_RUN(constexpr_tile, case3)
    NMTOOLS_PIO_RUN(constexpr_tile, case5)

    NMTOOLS_PIO_RUN(take, case1)
    NMTOOLS_PIO_RUN(take, case2)
    NMTOOLS_PIO_RUN(take, case5)

    NMTOOLS_PIO_RUN(constexpr_take, case1)
    NMTOOLS_PIO_RUN(constexpr_take, case2)
    NMTOOLS_PIO_RUN(constexpr_take, case5)

    NMTOOLS_PIO_RUN(where, case1)
    NMTOOLS_PIO_RUN(where, case2)

    NMTOOLS_PIO_RUN(reshape, case1)
    NMTOOLS_PIO_RUN(constexpr_reshape, case1)

    NMTOOLS_PIO_RUN(flatten, case4)
    NMTOOLS_PIO_RUN(constexpr_flatten, case4)

    NMTOOLS_PIO_RUN(concatenate, case3)
    NMTOOLS_PIO_RUN(concatenate, case4)
    NMTOOLS_PIO_RUN(constexpr_concatenate, case3)
    NMTOOLS_PIO_RUN(constexpr_concatenate, case4)

    NMTOOLS_PIO_RUN(broadcast_to, case1)
    NMTOOLS_PIO_RUN(broadcast_to, case7)
    NMTOOLS_PIO_RUN(broadcast_to, case10)

    NMTOOLS_PIO_RUN(constexpr_broadcast_to, case1)
    NMTOOLS_PIO_RUN(constexpr_broadcast_to, case7)
    NMTOOLS_PIO_RUN(constexpr_broadcast_to, case10)

    NMTOOLS_PIO_RUN(split, case2)
    NMTOOLS_PIO_RUN(split, case3)
    NMTOOLS_PIO_RUN(split, case4)
    NMTOOLS_PIO_RUN(split, case5)
    NMTOOLS_PIO_RUN(split, case6)
    NMTOOLS_PIO_RUN(split, case12)
    NMTOOLS_PIO_RUN(split, case13)

#ifndef NMTOOLS_TESTING_MINIMIZE_FOOTPRINT
    NMTOOLS_PIO_RUN(transpose, case3)
    NMTOOLS_PIO_RUN(transpose, case4)
    NMTOOLS_PIO_RUN(transpose, case6)
    NMTOOLS_PIO_RUN(transpose, case7)
    NMTOOLS_PIO_RUN(transpose, case9)

    NMTOOLS_PIO_RUN(tile, case2)
    NMTOOLS_PIO_RUN(tile, case4)

    NMTOOLS_PIO_RUN(take, case3)
    NMTOOLS_PIO_RUN(take, case4)
    NMTOOLS_PIO_RUN(take, case6)

    NMTOOLS_PIO_RUN(where, case3)

    NMTOOLS_PIO_RUN(reshape, case2)
    NMTOOLS_PIO_RUN(reshape, case3)

    NMTOOLS_PIO_RUN(flatten, case1)
    NMTOOLS_PIO_RUN(flatten, case2)
    NMTOOLS_PIO_RUN(flatten, case3)

    NMTOOLS_PIO_RUN(concatenate, case1)
    NMTOOLS_PIO_RUN(concatenate, case2)

    NMTOOLS_PIO_RUN(broadcast_to, case11)
#endif
    UNITY_END();
}

void loop()
{
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
}