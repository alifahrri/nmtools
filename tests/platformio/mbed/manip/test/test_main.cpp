// by default mbed declare using namespace std and mbed;
#define MBED_NO_GLOBAL_USING_DIRECTIVE
#include <mbed.h>
#include <unity.h>

#include "nmtools/array/array/transpose.hpp"
#include "nmtools/array/array/zeros.hpp"
#include "nmtools/array/array/where.hpp"
#include "nmtools/array/array/tile.hpp"
#include "nmtools/array/array/take.hpp"
#include "nmtools/array/array/squeeze.hpp"
#include "nmtools/array/array/slice.hpp"
#include "nmtools/array/array/reshape.hpp"
#include "nmtools/array/array/repeat.hpp"
#include "nmtools/array/array/pad.hpp"
#include "nmtools/array/array/ones.hpp"
#include "nmtools/array/array/full.hpp"
#include "nmtools/array/array/flip.hpp"
#include "nmtools/array/array/flatten.hpp"
#include "nmtools/array/array/expand_dims.hpp"
#include "nmtools/array/array/concatenate.hpp"
#include "nmtools/array/array/compress.hpp"
#include "nmtools/array/array/broadcast_to.hpp"
#include "nmtools/array/array/atleast_3d.hpp"
#include "nmtools/array/array/atleast_2d.hpp"
#include "nmtools/array/array/atleast_1d.hpp"
#include "nmtools/array/array/arange.hpp"

#include "nmtools/testing/data/array/arange.hpp"
#include "nmtools/testing/data/array/atleast_1d.hpp"
#include "nmtools/testing/data/array/atleast_2d.hpp"
#include "nmtools/testing/data/array/atleast_3d.hpp"
#include "nmtools/testing/data/array/broadcast_to.hpp"
#include "nmtools/testing/data/array/compress.hpp"
#include "nmtools/testing/data/array/concatenate.hpp"
#include "nmtools/testing/data/array/expand_dims.hpp"
#include "nmtools/testing/data/array/flatten.hpp"
#include "nmtools/testing/data/array/flip.hpp"
#include "nmtools/testing/data/array/full.hpp"
#include "nmtools/testing/data/array/ones.hpp"
#include "nmtools/testing/data/array/pad.hpp"
#include "nmtools/testing/data/array/repeat.hpp"
#include "nmtools/testing/data/array/reshape.hpp"
#include "nmtools/testing/data/array/slice.hpp"
#include "nmtools/testing/data/array/squeeze.hpp"
#include "nmtools/testing/data/array/take.hpp"
#include "nmtools/testing/data/array/tile.hpp"
#include "nmtools/testing/data/array/transpose.hpp"
#include "nmtools/testing/data/array/where.hpp"
#include "nmtools/testing/data/array/zeros.hpp"

#include "nmtools/utils/isequal.hpp"
#include "nmtools/utils/isclose.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

using nm::utils::isclose, nm::utils::isequal;

#define NMTOOLS_PIO_SUBCASE(case_name, expected, function, ...) \
{ \
    using namespace case_name; \
    using namespace case_name::args; \
    auto res = function(__VA_ARGS__); \
    auto success = isclose(res, expect::expected); \
    TEST_ASSERT_TRUE( success ); \
}

void test_transpose()
{
    NMTOOLS_TESTING_DECLARE_NS(transpose);
    NMTOOLS_PIO_SUBCASE( case1, expected, view::transpose, array );
    NMTOOLS_PIO_SUBCASE( case2, expected, view::transpose, array );
    NMTOOLS_PIO_SUBCASE( case3, expected, view::transpose, array, axes );
    NMTOOLS_PIO_SUBCASE( case4, expected, view::transpose, array, axes );
    NMTOOLS_PIO_SUBCASE( case5, expected, view::transpose, array, axes );
    NMTOOLS_PIO_SUBCASE( case6, expected, view::transpose, array, axes );
    NMTOOLS_PIO_SUBCASE( case7, expected, view::transpose, array, axes );
    NMTOOLS_PIO_SUBCASE( case8, expected, view::transpose, array, axes );
    NMTOOLS_PIO_SUBCASE( case9, expected, view::transpose, array, axes );
    NMTOOLS_PIO_SUBCASE( case10, expected, view::transpose, array, axes );
}

void test_zeros()
{
    NMTOOLS_TESTING_DECLARE_NS(array, zeros);
    NMTOOLS_PIO_SUBCASE( case1, result, view::zeros, shape, dtype );

    // eval
    NMTOOLS_PIO_SUBCASE( case1, result, na::zeros, shape, dtype );
}

void test_where()
{
    NMTOOLS_TESTING_DECLARE_NS(view, where);
    NMTOOLS_PIO_SUBCASE( case1, result, view::where, condition, x, y );
    NMTOOLS_PIO_SUBCASE( case2, result, view::where, condition, x, y );
    NMTOOLS_PIO_SUBCASE( case3, result, view::where, condition, x, y );
}

void test_tile()
{
    NMTOOLS_TESTING_DECLARE_NS(view, tile);
    NMTOOLS_PIO_SUBCASE( case1, result, view::tile, array, reps );
    NMTOOLS_PIO_SUBCASE( case2, result, view::tile, array, reps );
    NMTOOLS_PIO_SUBCASE( case3, result, view::tile, array, reps );
    NMTOOLS_PIO_SUBCASE( case4, result, view::tile, array, reps );
    NMTOOLS_PIO_SUBCASE( case5, result, view::tile, array, reps );
}

void test_take()
{
    NMTOOLS_TESTING_DECLARE_NS(view, take);
    NMTOOLS_PIO_SUBCASE( case1, result, view::take, array, indices, axis );
    NMTOOLS_PIO_SUBCASE( case2, result, view::take, array, indices, axis );
    NMTOOLS_PIO_SUBCASE( case3, result, view::take, array, indices, axis );
    NMTOOLS_PIO_SUBCASE( case4, result, view::take, array, indices, axis );
    NMTOOLS_PIO_SUBCASE( case5, result, view::take, array, indices, axis );
    NMTOOLS_PIO_SUBCASE( case6, result, view::take, array, indices, axis );
}

void test_squeeze()
{
    NMTOOLS_TESTING_DECLARE_NS(squeeze);
    NMTOOLS_PIO_SUBCASE( case1, expected, view::squeeze, array );
    NMTOOLS_PIO_SUBCASE( case2, expected, view::squeeze, array );
    NMTOOLS_PIO_SUBCASE( case3, expected, view::squeeze, array );
    NMTOOLS_PIO_SUBCASE( case4, expected, view::squeeze, array );
    NMTOOLS_PIO_SUBCASE( case5, expected, view::squeeze, array );
    NMTOOLS_PIO_SUBCASE( case6, expected, view::squeeze, array );
}

void test_slice()
{
    NMTOOLS_TESTING_DECLARE_NS(array, slice);
    NMTOOLS_PIO_SUBCASE( case1, result, view::slice, array, slice0, slice1, slice2 );
    NMTOOLS_PIO_SUBCASE( case2, result, view::slice, array, slice0, slice1, slice2 );
    NMTOOLS_PIO_SUBCASE( case3, result, view::slice, array, slice0, slice1, slice2 );
    NMTOOLS_PIO_SUBCASE( case4, result, view::slice, array, slice0, slice1, slice2 );
    NMTOOLS_PIO_SUBCASE( case5, result, view::slice, array, slice0, slice1, slice2 );
    NMTOOLS_PIO_SUBCASE( case6, result, view::slice, array, slice0, slice1, slice2 );
    NMTOOLS_PIO_SUBCASE( case7, result, view::slice, array, slice0, slice1, slice2 );
    NMTOOLS_PIO_SUBCASE( case8, result, view::slice, array, slice0, slice1, slice2 );
    NMTOOLS_PIO_SUBCASE( case9, result, view::slice, array, slice0, slice1, slice2 );
    NMTOOLS_PIO_SUBCASE( case10, result, view::slice, array, slice0, slice1, slice2 );
    NMTOOLS_PIO_SUBCASE( case11, result, view::slice, array, slice0, slice1 );
    NMTOOLS_PIO_SUBCASE( case12, result, view::slice, array, slice0, slice1 );
    NMTOOLS_PIO_SUBCASE( case13, result, view::slice, array, slice0, slice1 );
    NMTOOLS_PIO_SUBCASE( case14, result, view::slice, array, slice0, slice1 );
    NMTOOLS_PIO_SUBCASE( case15, result, view::slice, array, slice0, slice1 );
    NMTOOLS_PIO_SUBCASE( case16, result, view::slice, array, slice0, slice1 );
    NMTOOLS_PIO_SUBCASE( case17, result, view::slice, array, slice0, slice1 );
    NMTOOLS_PIO_SUBCASE( case18, result, view::slice, array, slice0, slice1 );
    NMTOOLS_PIO_SUBCASE( case19, result, view::slice, array, slice0, slice1 );
    NMTOOLS_PIO_SUBCASE( case20, result, view::slice, array, slice0, slice1 );
    NMTOOLS_PIO_SUBCASE( case21, result, view::slice, array, slice0, slice1 );
    NMTOOLS_PIO_SUBCASE( case22, result, view::slice, array, slice0, slice1 );
    NMTOOLS_PIO_SUBCASE( case23, result, view::slice, array, slice0, slice1 );
    NMTOOLS_PIO_SUBCASE( case24, result, view::slice, array, slice0, slice1 );
    NMTOOLS_PIO_SUBCASE( case25, result, view::slice, array, slice0, slice1 );
    NMTOOLS_PIO_SUBCASE( case26, result, view::slice, array, slice0, slice1 );
}

void test_reshape()
{
    NMTOOLS_TESTING_DECLARE_NS(reshape);
    NMTOOLS_PIO_SUBCASE( case1, expected, view::reshape, array, newshape );
    NMTOOLS_PIO_SUBCASE( case2, expected, view::reshape, array, newshape );
    NMTOOLS_PIO_SUBCASE( case3, expected, view::reshape, array, newshape );
}

void test_repeat()
{
    NMTOOLS_TESTING_DECLARE_NS(array, repeat);
    NMTOOLS_PIO_SUBCASE( case1, result, view::repeat, array, repeats, axis );
    NMTOOLS_PIO_SUBCASE( case2, result, view::repeat, array, repeats, axis );
    NMTOOLS_PIO_SUBCASE( case3, result, view::repeat, array, repeats, axis );
    NMTOOLS_PIO_SUBCASE( case4, result, view::repeat, array, repeats, axis );
    NMTOOLS_PIO_SUBCASE( case5, result, view::repeat, array, repeats, axis );
    NMTOOLS_PIO_SUBCASE( case6, result, view::repeat, array, repeats, axis );
}

void test_pad()
{
    NMTOOLS_TESTING_DECLARE_NS(array, pad);
    NMTOOLS_PIO_SUBCASE( case1, result, view::pad, array, pad_width );
    NMTOOLS_PIO_SUBCASE( case2, result, view::pad, array, pad_width );
    NMTOOLS_PIO_SUBCASE( case3, result, view::pad, array, pad_width );
    NMTOOLS_PIO_SUBCASE( case4, result, view::pad, array, pad_width );
    NMTOOLS_PIO_SUBCASE( case5, result, view::pad, array, pad_width );
}

void test_ones()
{
    NMTOOLS_TESTING_DECLARE_NS(array, ones);
    NMTOOLS_PIO_SUBCASE( case1, result, view::ones, shape, dtype );
}

void test_full()
{
    NMTOOLS_TESTING_DECLARE_NS(array, full);
    NMTOOLS_PIO_SUBCASE( case1, result, view::full, shape, fill_value );
}

void test_flip()
{
    NMTOOLS_TESTING_DECLARE_NS(flip);
    NMTOOLS_PIO_SUBCASE( case1, result, view::flip, array, axis );
    NMTOOLS_PIO_SUBCASE( case2, result, view::flip, array, axis );
    NMTOOLS_PIO_SUBCASE( case3, result, view::flip, array, axis );
    NMTOOLS_PIO_SUBCASE( case4, result, view::flip, array, axis );
}

void test_flatten()
{
    NMTOOLS_TESTING_DECLARE_NS(flatten);
    NMTOOLS_PIO_SUBCASE( case1, expected, view::flatten, array );
    NMTOOLS_PIO_SUBCASE( case2, expected, view::flatten, array );
    NMTOOLS_PIO_SUBCASE( case3, expected, view::flatten, array );
    NMTOOLS_PIO_SUBCASE( case4, expected, view::flatten, array );
}

void test_expand_dims()
{
    NMTOOLS_TESTING_DECLARE_NS(expand_dims);
    NMTOOLS_PIO_SUBCASE( case1, expected, view::expand_dims, array, axis );
    NMTOOLS_PIO_SUBCASE( case2, expected, view::expand_dims, array, axis );
    NMTOOLS_PIO_SUBCASE( case3, expected, view::expand_dims, array, axis );
    NMTOOLS_PIO_SUBCASE( case4, expected, view::expand_dims, array, axis );
    NMTOOLS_PIO_SUBCASE( case5, expected, view::expand_dims, array, axis );
    NMTOOLS_PIO_SUBCASE( case6, expected, view::expand_dims, array, axis );
    NMTOOLS_PIO_SUBCASE( case7, expected, view::expand_dims, array, axis );
    NMTOOLS_PIO_SUBCASE( case8, expected, view::expand_dims, array, axis );
    NMTOOLS_PIO_SUBCASE( case9, expected, view::expand_dims, array, axis );
    NMTOOLS_PIO_SUBCASE( case10, expected, view::expand_dims, array, axis );
}

void test_concatenate()
{
    NMTOOLS_TESTING_DECLARE_NS(view, concatenate);
    NMTOOLS_PIO_SUBCASE( case1, expected, view::concatenate, lhs, rhs, axis );
    NMTOOLS_PIO_SUBCASE( case2, expected, view::concatenate, lhs, rhs, axis );
    NMTOOLS_PIO_SUBCASE( case3, expected, view::concatenate, lhs, rhs, axis );
    NMTOOLS_PIO_SUBCASE( case4, expected, view::concatenate, lhs, rhs, axis );
}

void test_compress()
{
    NMTOOLS_TESTING_DECLARE_NS(array, compress);
    NMTOOLS_PIO_SUBCASE( case1, result, view::compress, condition, array, axis );
    NMTOOLS_PIO_SUBCASE( case2, result, view::compress, condition, array, axis );
    NMTOOLS_PIO_SUBCASE( case3, result, view::compress, condition, array, axis );
    NMTOOLS_PIO_SUBCASE( case4, result, view::compress, condition, array, axis );
    NMTOOLS_PIO_SUBCASE( case5, result, view::compress, condition, array, axis );
}

void test_broadcast_to()
{
    NMTOOLS_TESTING_DECLARE_NS(broadcast_to);
    NMTOOLS_PIO_SUBCASE( case1, expected, view::broadcast_to, x, shape );
    NMTOOLS_PIO_SUBCASE( case2, expected, view::broadcast_to, x, shape );
    NMTOOLS_PIO_SUBCASE( case3, expected, view::broadcast_to, x, shape );
    NMTOOLS_PIO_SUBCASE( case4, expected, view::broadcast_to, x, shape );
    NMTOOLS_PIO_SUBCASE( case5, expected, view::broadcast_to, x, shape );
    NMTOOLS_PIO_SUBCASE( case6, expected, view::broadcast_to, x, shape );
    NMTOOLS_PIO_SUBCASE( case7, expected, view::broadcast_to, x, shape );
    NMTOOLS_PIO_SUBCASE( case8, expected, view::broadcast_to, x, shape );
    NMTOOLS_PIO_SUBCASE( case9, expected, view::broadcast_to, x, shape );
    NMTOOLS_PIO_SUBCASE( case10, expected, view::broadcast_to, x, shape );
    NMTOOLS_PIO_SUBCASE( case11, expected, view::broadcast_to, x, shape );
}

void test_atleast_3d()
{
    NMTOOLS_TESTING_DECLARE_NS(array, atleast_3d);
    NMTOOLS_PIO_SUBCASE( case1, result, view::atleast_3d, a );
    NMTOOLS_PIO_SUBCASE( case2, result, view::atleast_3d, a );
    NMTOOLS_PIO_SUBCASE( case3, result, view::atleast_3d, a );
    NMTOOLS_PIO_SUBCASE( case4, result, view::atleast_3d, a );
    NMTOOLS_PIO_SUBCASE( case5, result, view::atleast_3d, a );
}

void test_atleast_2d()
{
    NMTOOLS_TESTING_DECLARE_NS(array, atleast_2d);
    NMTOOLS_PIO_SUBCASE( case1, result, view::atleast_2d, a );
    NMTOOLS_PIO_SUBCASE( case2, result, view::atleast_2d, a );
    NMTOOLS_PIO_SUBCASE( case3, result, view::atleast_2d, a );
    NMTOOLS_PIO_SUBCASE( case4, result, view::atleast_2d, a );
}

void test_atleast_1d()
{
    NMTOOLS_TESTING_DECLARE_NS(array, atleast_1d);
    NMTOOLS_PIO_SUBCASE( case1, result, view::atleast_1d, a );
    NMTOOLS_PIO_SUBCASE( case2, result, view::atleast_1d, a );
    NMTOOLS_PIO_SUBCASE( case3, result, view::atleast_1d, a );
    NMTOOLS_PIO_SUBCASE( case4, result, view::atleast_1d, a );
}

void test_arange()
{
    NMTOOLS_TESTING_DECLARE_NS(array, arange);
    NMTOOLS_PIO_SUBCASE( case1, result, view::arange, stop, dtype );
    NMTOOLS_PIO_SUBCASE( case2, result, view::arange, start, stop, dtype );
    NMTOOLS_PIO_SUBCASE( case3, result, view::arange, start, stop, step, dtype );
    NMTOOLS_PIO_SUBCASE( case4, result, view::arange, start, stop, step, dtype );
    NMTOOLS_PIO_SUBCASE( case5, result, view::arange, stop );
    NMTOOLS_PIO_SUBCASE( case6, result, view::arange, start, stop );
    NMTOOLS_PIO_SUBCASE( case7, result, view::arange, start, stop, step );
    NMTOOLS_PIO_SUBCASE( case8, result, view::arange, start, stop );
    NMTOOLS_PIO_SUBCASE( case9, result, view::arange, start, stop, step );
}

#define WAIT_TIME_MS 1000

int main()
{
    thread_sleep_for(WAIT_TIME_MS);

    UNITY_BEGIN();

    RUN_TEST(test_transpose);
    RUN_TEST(test_zeros);
    RUN_TEST(test_where);
    RUN_TEST(test_tile);
    RUN_TEST(test_take);
    RUN_TEST(test_squeeze);
    RUN_TEST(test_slice);
    RUN_TEST(test_reshape);
    RUN_TEST(test_repeat);
    RUN_TEST(test_pad);
    RUN_TEST(test_ones);
    RUN_TEST(test_full);
    RUN_TEST(test_flip);
    RUN_TEST(test_flatten);
    RUN_TEST(test_expand_dims);
    RUN_TEST(test_concatenate);
    RUN_TEST(test_compress);
    RUN_TEST(test_broadcast_to);
    RUN_TEST(test_atleast_3d);
    RUN_TEST(test_atleast_2d);
    RUN_TEST(test_atleast_1d);
    // TODO: fix
    // RUN_TEST(test_arange);

    UNITY_END(); // stop unit testing

    while(true)
    {
        thread_sleep_for(WAIT_TIME_MS);
    }
}