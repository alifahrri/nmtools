#include "nmtools/array/array/transpose.hpp"
#include "nmtools/constants.hpp"
#include "nmtools/testing/data/array/transpose.hpp"
#include "nmtools/testing/doctest.hpp"

#include <array>
#include <vector>

namespace nm = nmtools;
namespace na = nm::array;

#define TRANSPOSE_SUBCASE(case_name, array, axes) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS( transpose, case_name ); \
    auto array = na::transpose(args::array, args::axes); \
    NMTOOLS_ASSERT_CLOSE( array, expect::expected ); \
}

TEST_CASE("transpose(array)" * doctest::test_suite("array::transpose"))
{
    TRANSPOSE_SUBCASE( case1, array_a, axes_a );
    TRANSPOSE_SUBCASE( case2, array_a, axes_a );
    TRANSPOSE_SUBCASE( case3, array_a, axes_a );
    TRANSPOSE_SUBCASE( case4, array_a, axes_a );
    TRANSPOSE_SUBCASE( case5, array_a, axes_a );
    TRANSPOSE_SUBCASE( case6, array_a, axes_a );
    TRANSPOSE_SUBCASE( case7, array_a, axes_a );
    TRANSPOSE_SUBCASE( case8, array_a, axes_a );
    TRANSPOSE_SUBCASE( case9, array_a, axes_a );
    TRANSPOSE_SUBCASE( case10, array_a, axes_a );

    // TODO: fix
    // TRANSPOSE_SUBCASE( case1, array_a, axes_v );
    // TRANSPOSE_SUBCASE( case2, array_a, axes_v );
    // TRANSPOSE_SUBCASE( case3, array_a, axes_v );
    // TRANSPOSE_SUBCASE( case4, array_a, axes_v );
    // TRANSPOSE_SUBCASE( case5, array_a, axes_v );
    // TRANSPOSE_SUBCASE( case6, array_a, axes_v );
    // TRANSPOSE_SUBCASE( case7, array_a, axes_v );
    // TRANSPOSE_SUBCASE( case8, array_a, axes_v );
    // TRANSPOSE_SUBCASE( case9, array_a, axes_v );
    // TRANSPOSE_SUBCASE( case10, array_a, axes_v );

    TRANSPOSE_SUBCASE( case1, array_a, axes_ct );
    TRANSPOSE_SUBCASE( case2, array_a, axes_ct );
    TRANSPOSE_SUBCASE( case3, array_a, axes_ct );
    TRANSPOSE_SUBCASE( case4, array_a, axes_ct );
    TRANSPOSE_SUBCASE( case5, array_a, axes_ct );
    TRANSPOSE_SUBCASE( case6, array_a, axes_ct );
    TRANSPOSE_SUBCASE( case7, array_a, axes_ct );
    TRANSPOSE_SUBCASE( case8, array_a, axes_ct );
    TRANSPOSE_SUBCASE( case9, array_a, axes_ct );
    TRANSPOSE_SUBCASE( case10, array_a, axes_ct );
}

TEST_CASE("transpose(fixed_ndarray)" * doctest::test_suite("array::transpose"))
{
    TRANSPOSE_SUBCASE( case1, array_f, axes_a );
    TRANSPOSE_SUBCASE( case2, array_f, axes_a );
    TRANSPOSE_SUBCASE( case3, array_f, axes_a );
    TRANSPOSE_SUBCASE( case4, array_f, axes_a );
    TRANSPOSE_SUBCASE( case5, array_f, axes_a );
    TRANSPOSE_SUBCASE( case6, array_f, axes_a );
    TRANSPOSE_SUBCASE( case7, array_f, axes_a );
    TRANSPOSE_SUBCASE( case8, array_f, axes_a );
    TRANSPOSE_SUBCASE( case9, array_f, axes_a );
    TRANSPOSE_SUBCASE( case10, array_f, axes_a );

    // TODO: fix
    // TRANSPOSE_SUBCASE( case1, array_f, axes_v );
    // TRANSPOSE_SUBCASE( case2, array_f, axes_v );
    // TRANSPOSE_SUBCASE( case3, array_f, axes_v );
    // TRANSPOSE_SUBCASE( case4, array_f, axes_v );
    // TRANSPOSE_SUBCASE( case5, array_f, axes_v );
    // TRANSPOSE_SUBCASE( case6, array_f, axes_v );
    // TRANSPOSE_SUBCASE( case7, array_f, axes_v );
    // TRANSPOSE_SUBCASE( case8, array_f, axes_v );
    // TRANSPOSE_SUBCASE( case9, array_f, axes_v );
    // TRANSPOSE_SUBCASE( case10, array_f, axes_v );

    TRANSPOSE_SUBCASE( case1, array_f, axes_ct );
    TRANSPOSE_SUBCASE( case2, array_f, axes_ct );
    TRANSPOSE_SUBCASE( case3, array_f, axes_ct );
    TRANSPOSE_SUBCASE( case4, array_f, axes_ct );
    TRANSPOSE_SUBCASE( case5, array_f, axes_ct );
    TRANSPOSE_SUBCASE( case6, array_f, axes_ct );
    TRANSPOSE_SUBCASE( case7, array_f, axes_ct );
    TRANSPOSE_SUBCASE( case8, array_f, axes_ct );
    TRANSPOSE_SUBCASE( case9, array_f, axes_ct );
    TRANSPOSE_SUBCASE( case10, array_f, axes_ct );
}

TEST_CASE("transpose(hybrid_ndarray)" * doctest::test_suite("array::transpose"))
{
    TRANSPOSE_SUBCASE( case1, array_h, axes_a );
    TRANSPOSE_SUBCASE( case2, array_h, axes_a );
    TRANSPOSE_SUBCASE( case3, array_h, axes_a );
    TRANSPOSE_SUBCASE( case4, array_h, axes_a );
    TRANSPOSE_SUBCASE( case5, array_h, axes_a );
    TRANSPOSE_SUBCASE( case6, array_h, axes_a );
    TRANSPOSE_SUBCASE( case7, array_h, axes_a );
    TRANSPOSE_SUBCASE( case8, array_h, axes_a );
    TRANSPOSE_SUBCASE( case9, array_h, axes_a );
    TRANSPOSE_SUBCASE( case10, array_h, axes_a );

    // TODO: fix
    // TRANSPOSE_SUBCASE( case1, array_h, axes_v );
    // TRANSPOSE_SUBCASE( case2, array_h, axes_v );
    // TRANSPOSE_SUBCASE( case3, array_h, axes_v );
    // TRANSPOSE_SUBCASE( case4, array_h, axes_v );
    // TRANSPOSE_SUBCASE( case5, array_h, axes_v );
    // TRANSPOSE_SUBCASE( case6, array_h, axes_v );
    // TRANSPOSE_SUBCASE( case7, array_h, axes_v );
    // TRANSPOSE_SUBCASE( case8, array_h, axes_v );
    // TRANSPOSE_SUBCASE( case9, array_h, axes_v );
    // TRANSPOSE_SUBCASE( case10, array_h, axes_v );

    // TODO: fix
    // TRANSPOSE_SUBCASE( case1, array_h, axes_ct );
    // TRANSPOSE_SUBCASE( case2, array_h, axes_ct );
    // TRANSPOSE_SUBCASE( case3, array_h, axes_ct );
    // TRANSPOSE_SUBCASE( case4, array_h, axes_ct );
    // TRANSPOSE_SUBCASE( case5, array_h, axes_ct );
    // TRANSPOSE_SUBCASE( case6, array_h, axes_ct );
    // TRANSPOSE_SUBCASE( case7, array_h, axes_ct );
    // TRANSPOSE_SUBCASE( case8, array_h, axes_ct );
    // TRANSPOSE_SUBCASE( case9, array_h, axes_ct );
    // TRANSPOSE_SUBCASE( case10, array_h, axes_ct );
}

TEST_CASE("transpose(dynamic_ndarray)" * doctest::test_suite("array::transpose"))
{
    TRANSPOSE_SUBCASE( case1, array_d, axes_a );
    TRANSPOSE_SUBCASE( case2, array_d, axes_a );
    TRANSPOSE_SUBCASE( case3, array_d, axes_a );
    TRANSPOSE_SUBCASE( case4, array_d, axes_a );
    TRANSPOSE_SUBCASE( case5, array_d, axes_a );
    TRANSPOSE_SUBCASE( case6, array_d, axes_a );
    TRANSPOSE_SUBCASE( case7, array_d, axes_a );
    TRANSPOSE_SUBCASE( case8, array_d, axes_a );
    TRANSPOSE_SUBCASE( case9, array_d, axes_a );
    TRANSPOSE_SUBCASE( case10, array_d, axes_a );

    TRANSPOSE_SUBCASE( case1, array_d, axes_v );
    TRANSPOSE_SUBCASE( case2, array_d, axes_v );
    TRANSPOSE_SUBCASE( case3, array_d, axes_v );
    TRANSPOSE_SUBCASE( case4, array_d, axes_v );
    TRANSPOSE_SUBCASE( case5, array_d, axes_v );
    TRANSPOSE_SUBCASE( case6, array_d, axes_v );
    TRANSPOSE_SUBCASE( case7, array_d, axes_v );
    TRANSPOSE_SUBCASE( case8, array_d, axes_v );
    TRANSPOSE_SUBCASE( case9, array_d, axes_v );
    TRANSPOSE_SUBCASE( case10, array_d, axes_v );

    // TODO: fix
    // TRANSPOSE_SUBCASE( case1, array_d, axes_ct );
    // TRANSPOSE_SUBCASE( case2, array_d, axes_ct );
    // TRANSPOSE_SUBCASE( case3, array_d, axes_ct );
    // TRANSPOSE_SUBCASE( case4, array_d, axes_ct );
    // TRANSPOSE_SUBCASE( case5, array_d, axes_ct );
    // TRANSPOSE_SUBCASE( case6, array_d, axes_ct );
    // TRANSPOSE_SUBCASE( case7, array_d, axes_ct );
    // TRANSPOSE_SUBCASE( case8, array_d, axes_ct );
    // TRANSPOSE_SUBCASE( case9, array_d, axes_ct );
    // TRANSPOSE_SUBCASE( case10, array_d, axes_ct );
}